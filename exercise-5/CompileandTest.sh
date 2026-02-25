read -p "Enter number: " NUM

echo "Compiling for number: $NUM..."

g++ multiplyByXGenerator.cpp -o multiplyByXGenerator.out && ./multiplyByXGenerator.out "$NUM" > "multiplyBy${NUM}_generated.s"

python3 multiplyByXTester_generator.py "$NUM" > multiplyByXTester.cpp

g++ multiplyByXTester.cpp "multiplyBy${NUM}_generated.s" -o multiplyByXTester.out && ./multiplyByXTester.out

echo "Execution Successful!"

read -n 1 -s -r -p "Press any key to continue..."
echo ""