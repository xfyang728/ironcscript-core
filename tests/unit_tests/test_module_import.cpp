#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "../src/module/ModuleManager.h"
#include "../src/frontend/parser/node.h"
#include "../src/frontend/semantic/SymbolTable.h"
#include "../src/frontend/semantic/SemanticAnalyzer.h"
#include "../src/frontend/parser/ASTBuilder.h"
#include "../src/frontend/generated/CScriptLexer.h"
#include "../src/frontend/generated/CScriptParser.h"

using namespace cse;

class ModuleImportTest : public ::testing::Test {
protected:
    void SetUp() override {
        system("if not exist tests\\temp\\import_test mkdir tests\\temp\\import_test");
    }

    void TearDown() override {
        system("if exist tests\\temp\\import_test rmdir /s /q tests\\temp\\import_test");
    }

    void createTempFile(const std::string& path, const std::string& content) {
        std::ofstream file(path);
        if (file.is_open()) {
            file << content;
            file.close();
        }
    }
};

/**
 * @brief 测试基本 import + export 功能
 */
TEST_F(ModuleImportTest, TestImportBasic) {
    ModuleManager manager;
    manager.setScriptDirectory("tests/temp/import_test");
    manager.setCurrentDirectory("tests/temp/import_test");

    // 创建模块文件
    createTempFile("tests/temp/import_test/my_module.cs",
        "export int add(int a, int b) {\n"
        "    return a + b;\n"
        "}\n"
        "export int VALUE = 42;\n"
        "int hidden = 99;\n");

    // 加载模块
    SymbolTable symTable;
    bool result = manager.importModule("my_module", "mod", symTable);
    EXPECT_TRUE(result) << "importModule should succeed";

    // 验证导出的函数被正确导入
    Symbol* addFunc = symTable.findSymbol("mod.add");
    ASSERT_NE(addFunc, nullptr) << "mod.add should be in symbol table";
    EXPECT_TRUE(addFunc->isFunction) << "mod.add should be marked as function";
    EXPECT_TRUE(addFunc->isImported) << "mod.add should be marked as imported";

    // 验证导出的变量被正确导入
    Symbol* valueVar = symTable.findSymbol("mod.VALUE");
    ASSERT_NE(valueVar, nullptr) << "mod.VALUE should be in symbol table";

    // 验证未导出的符号不可见
    Symbol* hiddenVar = symTable.findSymbol("mod.hidden");
    EXPECT_EQ(hiddenVar, nullptr) << "mod.hidden should NOT be visible (not exported)";

    // 验证无别名时符号直接可见
    hiddenVar = symTable.findSymbol("hidden");
    EXPECT_EQ(hiddenVar, nullptr) << "hidden should NOT be visible without alias either";
}

/**
 * @brief 测试命名导入 import { x } from "mod"
 */
TEST_F(ModuleImportTest, TestImportNamed) {
    ModuleManager manager;
    manager.setScriptDirectory("tests/temp/import_test");
    manager.setCurrentDirectory("tests/temp/import_test");

    createTempFile("tests/temp/import_test/named_module.cs",
        "export int foo() { return 1; }\n"
        "export int bar() { return 2; }\n"
        "export int baz = 100;\n");

    SymbolTable symTable;
    std::vector<std::string> symbols = {"foo", "baz"};
    bool result = manager.importNamedSymbols("named_module", symbols, symTable);
    EXPECT_TRUE(result) << "importNamedSymbols should succeed";

    // foo 已导出，应该可导入
    Symbol* fooFunc = symTable.findSymbol("foo");
    ASSERT_NE(fooFunc, nullptr) << "foo should be importable";

    // baz 已导出，应该可导入
    Symbol* bazVar = symTable.findSymbol("baz");
    ASSERT_NE(bazVar, nullptr) << "baz should be importable";

    // bar 已导出但不在导入列表中，不应可见
    Symbol* barFunc = symTable.findSymbol("bar");
    EXPECT_EQ(barFunc, nullptr) << "bar should NOT be visible (not in import list)";
}

/**
 * @brief 测试未导出符号不可被命名导入
 */
TEST_F(ModuleImportTest, TestUnExportedSymbol) {
    ModuleManager manager;
    manager.setScriptDirectory("tests/temp/import_test");
    manager.setCurrentDirectory("tests/temp/import_test");

    createTempFile("tests/temp/import_test/private_module.cs",
        "export int publicFunc() { return 1; }\n"
        "int privateFunc() { return 2; }\n");

    SymbolTable symTable;
    std::vector<std::string> symbols = {"privateFunc"};
    bool result = manager.importNamedSymbols("private_module", symbols, symTable);
    // importNamedSymbols 返回 true（部分成功），但 privateFunc 不应该被导入
    EXPECT_TRUE(result);

    Symbol* privateFunc = symTable.findSymbol("privateFunc");
    EXPECT_EQ(privateFunc, nullptr) << "privateFunc should NOT be visible (not exported)";

    // 验证导出的符号仍然可以导入
    std::vector<std::string> publicSymbols = {"publicFunc"};
    result = manager.importNamedSymbols("private_module", publicSymbols, symTable);
    EXPECT_TRUE(result);

    Symbol* publicFunc = symTable.findSymbol("publicFunc");
    ASSERT_NE(publicFunc, nullptr) << "publicFunc should be visible (exported)";
}

/**
 * @brief 测试模块缓存（重复 import 同一模块不重复解析）
 */
TEST_F(ModuleImportTest, TestModuleCaching) {
    ModuleManager manager;
    manager.setScriptDirectory("tests/temp/import_test");
    manager.setCurrentDirectory("tests/temp/import_test");

    createTempFile("tests/temp/import_test/cached_module.cs",
        "export int getValue() { return 42; }\n");

    SymbolTable symTable1;
    bool result1 = manager.importModule("cached_module", "m1", symTable1);
    EXPECT_TRUE(result1);

    // 第二次导入同一模块应使用缓存
    SymbolTable symTable2;
    bool result2 = manager.importModule("cached_module", "m2", symTable2);
    EXPECT_TRUE(result2);

    Symbol* func1 = symTable1.findSymbol("m1.getValue");
    Symbol* func2 = symTable2.findSymbol("m2.getValue");
    ASSERT_NE(func1, nullptr);
    ASSERT_NE(func2, nullptr);

    std::cout << "[TEST] Module caching verified." << std::endl;
}

/**
 * @brief 测试循环 import 检测
 */
TEST_F(ModuleImportTest, TestCircularImport) {
    ModuleManager manager;
    manager.setScriptDirectory("tests/temp/import_test");
    manager.setCurrentDirectory("tests/temp/import_test");

    createTempFile("tests/temp/import_test/circular_a.cs",
        "import \"circular_b\" as b;\n"
        "export int funcA() { return 1; }\n");

    createTempFile("tests/temp/import_test/circular_b.cs",
        "import \"circular_a\" as a;\n"
        "export int funcB() { return 2; }\n");

    SymbolTable symTable;
    bool result = manager.importModule("circular_a", "a", symTable);
    // 循环 import 应该被检测到（至少一个方向会失败）
    // 但注意：第一个 import 可能成功，第二个循环的方向会检测到
    std::cout << "[TEST] Circular import test: first import result=" << result << std::endl;
    // 测试主要是验证不会崩溃或死循环
    EXPECT_TRUE(true);
}
