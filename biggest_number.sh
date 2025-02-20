echo "Enter the first number: "
read first_num

echo "Enter the second number: "
read second_num

if [ $first_num -gt $second_num ]; then
	echo "First number $first_num is greater."
else
	echo "Second number $second_num is greater."
fi
