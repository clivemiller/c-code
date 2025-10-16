# echo "Enter file name: "
# read fileName

# mkdir preserve
# if mv $fileName ./preserve; then
#     rm -rf ./purge
# fi

# echo "Done!"

# for _ in {1..4}; do
# echo "hello"
# done

myString="Hello, World!"

grep -o '[^a-zA-Z0-9]' <<< $( cat ./fileTest.sh )