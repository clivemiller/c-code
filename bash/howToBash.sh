# Declaration of types of variables
# String
myString="Hello, World!"
echo "$myString"
# Integer
myInteger=42
echo "$myInteger"
# Float (using bc for calculations)
myFloat=3.14
# Array
myArray=("apple" "banana" "cherry")
# Associative Array (declare -A for associative arrays)
declare -A myAssocArray
myAssocArray=([name]="John" [age]=30 [city]="New York")

echo "Array element: ${myArray[1]}"
echo "Associative array element: ${myAssocArray[name]}"

# Boolean (using 0 and 1)
myBoolean=1  # 1 for true, 0 for false
# Null (unset variable)
myNullVar=
unset myNullVar

# use unset to remove a variable or list
unset myString
echo "After unset, myString is: '${myString:-undefined}'"

# Constant (using readonly)
readonly MY_CONSTANT="I am constant"
# Exported Variable (available to child processes)
export MY_EXPORTED_VAR="I am exported"
# Local Variable (within a function)
myFunction() {
    local myLocalVar="I am local"
    echo "$myLocalVar"
}
myFunction

# Special Variable (like $?, $#, $0, etc.)
echo "Script name: $0"
echo "Number of arguments: $#"
echo "Last command exit status: $?"
# Environment Variable (inherited from the environment)
echo "Home directory: $HOME"
# Command Substitution (using the output of a command)
currentDate=$(date)
echo "Current date: $currentDate"
# Arithmetic Expansion (performing arithmetic operations)
sum=$((myInteger + 10))
echo "Sum: $sum"

#  reading in user input
echo "Please enter your name:"
read userName1
echo "Hello, $userName1!"

# or -p to prompt on the same line
read -p "Enter your name: " userName2
echo "Hello, $userName2!"


# -s to hide input (for passwords)
read -sp "Enter your password: " userPassword
echo -e "\nPassword received."  # -e to enable interpretation of backslash escapes

# if statement; -gt for greater than, -lt for less than, -eq for equal to, -ne for not equal to
read -p "Enter a number: " userNumber
if [ "$userNumber" -gt 10 ]; then
    echo "The number is greater than 10."
else if [ "$userNumber" -eq 10 ]; then
    echo "The number is exactly 10."
else
    echo "The number is less than 10."
fi