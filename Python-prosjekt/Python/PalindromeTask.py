def is_palindrome(s):
    # Remove spaces and punctuation, and convert to lowercase
    cleaned = ''.join(char.lower() for char in s if char.isalnum())
    # An empty string or a string with only non-alphanumeric characters is not a palindrome
    if not cleaned:
        return False
    # This checks if the cleaned string is reading the same forwards and backwards
    return cleaned == cleaned[::-1]

def main():
    # Prompting the user for input
    user_input = input("Enter a string to check if it is a palindrome: ")
    # Checks if the input is a palindrome and prints the result
    if is_palindrome(user_input):
        print(f'"{user_input}" is a palindrome!')
    else:
        print(f'"{user_input}" is NOT a palindrome.')

if __name__ == "__main__":
    main() # This runs the main function if this script is ran correctly
