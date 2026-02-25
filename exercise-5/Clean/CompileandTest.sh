read -p "Enter number: " NUM

g++ multiplyByXGenerator.cpp -o multiplyByXGenerator.out
echo "Compiled CPP Generator > \"multiplyByXGenerator.out\""

./multiplyByXGenerator.out "$NUM" > "multiplyByX_generated.s"
echo "Generated assembly file > \"multiplyByX_generated.s\""

python3 multiplyByXTester_generator.py "$NUM" > multiplyByXTester.cpp
echo "Generated CPP Tester > \"multiplyByXTester.cpp\""

g++ multiplyByXTester.cpp "multiplyByX_generated.s" -o multiplyByXTester.out
echo "Compiling CPP Tester > \"multiplyByXTester.out\""

./multiplyByXTester.out
echo "Running Tester > \"multiplyByXTester.out\""

echo "Execution Successful!"

read -n 1 -s -r -p "Press any key to continue..."
echo ""