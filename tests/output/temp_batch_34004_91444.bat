@echo off
"D:\MyCode\IronCScript\ironcscript-core\build\IronCScriptCLI.exe" "D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib/stdio/test_scanf_basic.c" < "D:\MyCode\IronCScript\ironcscript-core\tests\inputs\test_scanf_basic_default.txt" > "D:\MyCode\IronCScript\ironcscript-core\tests\output\test_output_1.txt" 2>&1
echo Exit code: %errorlevel% >> "D:\MyCode\IronCScript\ironcscript-core\tests\output\test_output_1.txt"
