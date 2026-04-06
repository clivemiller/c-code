def get_arg_count(s):
    """Count the number of words in the string"""
    arg_count = 0
    in_word = False
    
    for char in s:
        if char in ' \t\n':
            in_word = False
        else:
            if not in_word:
                arg_count += 1
                in_word = True
    
    return arg_count


def get_each_arg_size(s):
    """Get the size of each argument/word in the string"""
    arg_sizes = []
    size_counter = 0
    in_word = False
    
    for char in s:
        if char in ' \t\n':
            if in_word:
                arg_sizes.append(size_counter)
                size_counter = 0
                in_word = False
        else:
            size_counter += 1
            in_word = True
    
    # Store the size of the last word if we ended in one
    if in_word:
        arg_sizes.append(size_counter)
    
    return arg_sizes


def makearg(s):
    """
    Parse a string into tokens (words) similar to shell parsing.
    Returns: (argc, args) where argc is the count and args is a list of strings
    """
    arg_count = get_arg_count(s)
    arg_sizes = get_each_arg_size(s)
    
    # In Python, we'll use a list to hold our args
    args = []
    
    # Build each argument
    current_word = []
    in_word = False
    
    for char in s:
        if char in ' \t\n':
            if in_word:
                # End of word - add it to args
                args.append(''.join(current_word))
                current_word = []
                in_word = False
        else:
            # Add character to current word
            current_word.append(char)
            in_word = True
    
    # Add the last word if we ended in one
    if in_word:
        args.append(''.join(current_word))
    
    # Python doesn't need NULL terminator, but we return the count for consistency
    return arg_count, args


def print_args(args, argc):
    """Debug function to print the final args array"""
    print("\n=== Debug: Final Args Array ===")
    print(f"argc = {argc}")
    for i, arg in enumerate(args):
        print(f'args[{i}] = "{arg}"')
    print(f"args[{len(args)}] = None (equivalent to NULL)")
    print("===============================\n")


def main():
    s = "ls -l file"
    argc, args = makearg(s)
    
    # Debug print the final array
    print_args(args, argc)


if __name__ == "__main__":
    main()