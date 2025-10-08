import random # Imports the random module

def selecting_random_word(filename):
    """
    This reads the given file and return a random word from it.
    The file that is being used should contain words that are separated by spaces and newline
    """
    with open(filename, 'r') as file:
        words = file.read().split() # This splits the content of the file into a list of words
    return random.choice(words).lower() # This returns a random word from the list in lowercases

def displaying_progress(word, guessed_letters): # This returns a string that shows the correctly guessed letters and the underscores for the rest
    return ''.join([letter if letter in guessed_letters else '_' for letter in word])

def word_guessing_game(filename):
    word = selecting_random_word(filename) # Selecting a random word from the file
    guessed_letters = set() # Tracks the letters that has been guessed
    max_wrong_guesses = len(word) # This is the maximum allowed wrong guesses
    wrong_guesses = 0 # Counter for wrong guesses

    print(f"Welcome to my word guessing game!\nThe word has {len(word)} letters.")

    while wrong_guesses < max_wrong_guesses:
        print(f"Current progress: {displaying_progress(word, guessed_letters)}")
        guess = input("Guess a letter (A-Z): ").lower() # This prompts the user for a letter

        if len(guess) != 1 or not guess.isalpha():
            print("Invalid input. Please enter a single letter.")
            continue # Skipping to the next loop if the input is invalid

        if guess in guessed_letters:
            print("You already guessed that letter. Try again.")
            continue # Skipping if the letter was already guessed

        guessed_letters.add(guess) # This adds the guessed letter to the set

        if guess not in word:
            wrong_guesses += 1 # Incrementing wrong guesses counter if the guess is incorrect
            print(f"Wrong guess! You have {max_wrong_guesses - wrong_guesses} guesses left.")
        else:
            print("Good guess!") # Feedback for correct guess

        if all(letter in guessed_letters for letter in word):
            print(f"Congratulations! You guessed the word: {word}")
            break

    else:
        print(f"Game over! The word was: {word}")

if __name__ == "__main__":
    word_guessing_game('WordGuessingGameWords.txt') # if the script ran correctly, game starts
