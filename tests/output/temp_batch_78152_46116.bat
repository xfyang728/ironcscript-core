@echo off
"D:\MyCode\IronCScript\ironcscript-core\build\IronCScriptCLI.exe" "D:\MyCode\IronCScript\ironcscript-core\tests\scripts\09_stdlib/stdio/test_scanf_single.c" < "D:\MyCode\IronCScript\ironcscript-core\tests\inputs\test_int_100_200_300.txt" > "D:\MyCode\IronCScript\ironcscript-core\tests\output\test_output_78.txt" 2>&1
echo Exit code: %errorlevel% >> "D:\MyCode\IronCScript\ironcscript-core\tests\output\test_output_78.txt"
