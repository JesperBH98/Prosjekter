# The menu class handles the displying options and gets the user input
class Menu:
    def __init__(self):
        # List of the menu options
        self.options = [
            "Open a new account",
            "Deposit money into your account",
            "Withdraw money from your account",
            "Add interests to your account",
            "Get the current balance of your account",
            "Quit"
        ]

    def add_option(self, option_text):
        # Adding a new option to the menu
        self.options.append(option_text)

    def get_input(self):
        # Displaying the menu and gets a valid user choice
        print("\n----- Bank Account Menu -----")
        for idx, option in enumerate(self.options, 1):
            print(f"{idx} {option}")
        print("----------------------------------")
        while True:
            try:
                choice = int(input("Enter your choice (1-{}): ".format(len(self.options))))
                if 1 <= choice <= len(self.options):
                    return choice # Returning the valid choice
                else:
                    print("Invalid choice. Please try again.")
            except ValueError:
                print("Please enter a valid number.")
                
# BankAccount class that handles the account operations
class BankAccount:
    def __init__(self, balance=0.0):
        # This initializes account with a option starting balancing given by the user
        self.balance = balance

    def deposit(self, amount):
        # Adding money to the user account, the amount has to be positive
        if amount > 0:
            self.balance += amount
            print(f"Deposited: ${amount:.2f}")
        else:
            print("Deposit amount must be positive.")

    def withdraw(self, amount):
        # Withdrawing money if the amount is positive and the account has sufficient balance
        if amount <= 0:
            print("Withdrawal amount must be positive.")
        elif amount > self.balance:
            print("Insufficient funds.")
        else:
            self.balance -= amount
            print(f"Withdrew: ${amount:.2f}")

    def add_interest(self, rate=0.02):
        #Adding interest rate to the balance of the account, the default interest rate is 2%
        interest = self.balance * rate
        self.balance += interest
        print(f"Interest added: ${interest:.2f}")

    def get_balance(self):
        # Returns the current balance of the account
        return self.balance

# This is the main program loop and is for interacting with the user
def main():
    menu = Menu() # Creating a menu instance for the user
    account = None # No accounts exists when starting the script, the account needs to  be added

    while True:
        choice = menu.get_input() # Showing the menu and gets the users choice

        if choice == 1:
            # Opening an account
            if account is None:
                try:
                    initial = float(input("Enter the deposit amount: "))
                    account = BankAccount(initial)
                    print("Your account was created successfully!")
                except ValueError:
                    print("Invalid amount.")
            else:
                print("Account already exists.")

        elif choice == 2:
            # Depositing money
            if account:
                try:
                    amount = float(input("Enter deposit amount: "))
                    account.deposit(amount)
                except ValueError:
                    print("Invalid amount.")
            else:
                print("You need to open an account first.")

        # Withdrawing money
        elif choice == 3:
            if account:
                try:
                    amount = float(input("Enter withdrawal amount: "))
                    account.withdraw(amount)
                except ValueError:
                    print("Invalid amount.")
            else:
                print("Please open an account first.")

        # Adding interest
        elif choice == 4:
            if account:
                try:
                    rate = input("Enter interest rate as a decimal (press Enter for 0.02): ")
                    if rate.strip() == "":
                        account.add_interest()
                    else:
                        account.add_interest(float(rate))
                except ValueError:
                    print("Invalid rate.")
            else:
                print("You need to open an account first.")

        # Getting the current balance
        elif choice == 5:
            if account:
                print(f"Current balance: ${account.get_balance():.2f}")
            else:
                print("You need to open an account first.")

        # This quits the program
        elif choice == 6:
            print("Thank you for using my bank account management system. Goodbye!")
            break

if __name__ == "__main__":
    main() # This will start the program if the script is ran correctly
