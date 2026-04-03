#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "../src/module/ModuleManager.h"
#include "../src/frontend/parser/node.h"

using namespace cse;

class ModuleManagerIncludeTest : public ::testing::Test {
protected:
    void SetUp() override {
        ModuleManager::globalIncludeDepth = 0;
        ModuleManager::globalFailedIncludes = 0;
    }

    void TearDown() override {
    }

    static void SetUpTestSuite() {
        system("if not exist tests\\temp\\include_test mkdir tests\\temp\\include_test");
    }

    static void TearDownTestSuite() {
        system("if exist tests\\temp\\include_test rmdir /s /q tests\\temp\\include_test");
    }

    void createTempFile(const std::string& path, const std::string& content) {
        std::ofstream file(path);
        if (file.is_open()) {
            file << content;
            file.close();
        }
    }
};

TEST_F(ModuleManagerIncludeTest, TestCircularIncludeDetection) {
    ModuleManager manager;

    createTempFile("tests/temp/include_test/a.cs",
        "#include \"b.cs\";\n"
        "int a = 1;\n");

    createTempFile("tests/temp/include_test/b.cs",
        "#include \"a.cs\";\n"
        "int b = 2;\n");

    manager.setScriptDirectory("tests/temp/include_test");

    NBlock block;
    bool result = manager.includeFile("a.cs", block);

    EXPECT_FALSE(result) << "Circular include should be detected";
}

TEST_F(ModuleManagerIncludeTest, TestDepthLimit) {
    ModuleManager manager;
    manager.setMaxIncludeDepth(3);

    std::string content = "int x = 1;\n";
    for (int i = 0; i < 5; ++i) {
        std::string path = "tests/temp/include_test/depth_" + std::to_string(i) + ".cs";
        std::string nextPath = "tests/temp/include_test/depth_" + std::to_string(i + 1) + ".cs";
        if (i < 4) {
            content = "#include \"depth_" + std::to_string(i + 1) + ".cs\";\nint x" + std::to_string(i) + " = " + std::to_string(i) + ";\n";
        } else {
            content = "int x4 = 4;\n";
        }
        createTempFile(path, content);
    }

    manager.setScriptDirectory("tests/temp/include_test");

    NBlock block;
    bool result = manager.includeFile("depth_0.cs", block);

    EXPECT_FALSE(result) << "Include depth limit should be enforced";
}

TEST_F(ModuleManagerIncludeTest, TestIsCurrentlyLoading) {
    ModuleManager manager;

    createTempFile("tests/temp/include_test/loading.cs",
        "int x = 1;\n");

    manager.setScriptDirectory("tests/temp/include_test");

    EXPECT_FALSE(manager.isCurrentlyLoading("tests/temp/include_test/loading.cs"));
}

TEST_F(ModuleManagerIncludeTest, TestResolveIncludePath) {
    ModuleManager manager;

    createTempFile("tests/temp/include_test/utils.cs",
        "int utils = 1;\n");

    manager.setScriptDirectory("tests/temp/include_test");

    std::string resolved = manager.resolveIncludePath("utils.cs");
    EXPECT_FALSE(resolved.empty());
    EXPECT_NE(resolved.find("utils.cs"), std::string::npos);
}

TEST_F(ModuleManagerIncludeTest, TestSetIncludeSearchPaths) {
    ModuleManager manager;

    std::vector<std::string> paths = {"tests/temp/path1", "tests/temp/path2"};
    manager.setIncludeSearchPaths(paths);

    manager.setScriptDirectory("tests/temp");
}

TEST_F(ModuleManagerIncludeTest, TestIncludeBasic) {
    ModuleManager manager;

    createTempFile("tests/temp/include_test/helper.cs",
        "int helper_value = 42;\n");

    manager.setScriptDirectory("tests/temp/include_test");

    NBlock block;
    bool result = manager.includeFile("helper.cs", block);

    EXPECT_TRUE(result) << "Basic include should succeed";
}

TEST_F(ModuleManagerIncludeTest, TestIncludeFileNotFound) {
    ModuleManager manager;
    manager.setScriptDirectory("tests/temp/include_test");

    NBlock block;
    bool result = manager.includeFile("nonexistent.cs", block);

    EXPECT_FALSE(result) << "Include non-existent file should fail";
}

TEST_F(ModuleManagerIncludeTest, TestIncludeWithDifferentExtensions) {
    ModuleManager manager;

    createTempFile("tests/temp/include_test/ext_test.cs",
        "int ext_value = 100;\n");

    manager.setScriptDirectory("tests/temp/include_test");

    NBlock block;
    bool result = manager.includeFile("ext_test", block);

    EXPECT_TRUE(result) << "Include with extension fallback should succeed";
}