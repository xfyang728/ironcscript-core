@echo off
"D:\MyCode\CScriptEngine\build\CScriptEngine.exe" "D:\MyCode\CScriptEngine\tests\scripts\test_scanf.c" < "D:\MyCode\CScriptEngine\tests\inputs\test_scanf_default.txt" > "D:\MyCode\CScriptEngine\tests\output\test_output_1.txt" 2>&1
echo Exit code: %errorlevel% >> "D:\MyCode\CScriptEngine\tests\output\test_output_1.txt"
