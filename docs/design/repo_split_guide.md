# Git Subtree 分离脚本

## 方案说明
使用 git subtree split 将现有仓库的某些目录分离成独立的仓库，保留完整的提交历史。

## 执行步骤

### 1. 创建开源仓库 (ironcscript-core)

```bash
# 创建新仓库
mkdir ironcscript-core
cd ironcscript-core
git init

# 从当前仓库分离开源模块（使用 subtree split）
# 在原仓库执行：
git subtree split --prefix=src/frontend --prefix=src/ir --prefix=src/bytecode --prefix=src/backend --prefix=src/common --prefix=src/exception -b split/opensource

# 推送到新仓库
git push git@github.com:yourname/ironcscript-core.git split/opensource:main
```

### 2. 创建闭源仓库 (ironcscript-commercial)

```bash
# 创建新仓库
mkdir ironcscript-commercial
cd ironcscript-commercial
git init

# 分离闭源模块
git subtree split --prefix=src/industrial --prefix=src/platform --prefix=src/debugger --prefix=src/gc --prefix=src/sandbox -b split/commercial

# 推送（私有仓库）
git push git@private:yourname/ironcscript-commercial.git split/commercial:main
```

### 3. 克隆开源仓库

```bash
git clone git@github.com:yourname/ironcscript-core.git
```

## 目录结构结果

```
原仓库 (CScriptEngine)
├── src/                    # 空目录（删除）
├── ironcscript-core/       # GitHub 公开仓库
│   ├── src/
│   │   ├── frontend/
│   │   ├── ir/
│   │   ├── bytecode/
│   │   ├── backend/
│   │   ├── common/
│   │   └── exception/
│   ├── include/
│   ├── examples/
│   └── docs/
│
├── ironcscript-commercial/ # 本地私有仓库
│   ├── industrial/
│   ├── platforms/
│   ├── debugger/
│   ├── gc/
│   ├── sandbox/
│   └── lib/
│
└── ironcscript-sdk/        # 打包分发目录
    ├── core/
    └── commercial/
```

## 验证开源部分可编译

```bash
cd ironcscript-core
mkdir build
cd build
cmake ..
cmake --build . --config Release
ctest -C Release
```

## 注意事项

1. **保留原仓库**：在完成分离前，不要删除或修改原仓库
2. **先测试**：在大规模操作前，先在小目录上测试
3. **推送前检查**：确认远程仓库地址正确
4. **分支保护**：在 GitHub 设置 main 分支保护规则
