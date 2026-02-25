@echo off
set /p NUM="Enter number: "

echo Compiling %FILENAME%...

g++ multiplyByXGenerator.cpp -o multiplyByXGenerator.out ; ./multiplyByXGenerator.out %NUM% > multiplyBy%NUM%_generated.s;
python multiplyByXTester_generator.py %NUM% > multiplyByXTester.cpp;
g++ multiplyByXTester.cpp multiplyBy%NUM%_generated.s -o multiplyByXTester.out ; ./multiplyByXTester.out;

echo Execution Successful!
pause