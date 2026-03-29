@echo off
"D:\MyCode\CScriptEngine\build\CScriptEngine.exe" "D:\MyCode\CScriptEngine\tests\scripts\test_scanf_single.c" < "D:\MyCode\CScriptEngine\tests\inputs\test_int_100_200_300.txt" > "D:\MyCode\CScriptEngine\tests\output\test_output_77.txt" 2>&1
echo Exit code: %errorlevel% >> "D:\MyCode\CScriptEngine\tests\output\test_output_77.txt"
