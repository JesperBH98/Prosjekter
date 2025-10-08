# Book class, book title, author, and the number of pages in book
class Book:
    def __init__(self, title, author, num_pages):
        self.title = title
        self.author = author
        self.num_pages = num_pages

    # Returning a readable string representation of the chosen book
    def __repr__(self):
        return f'"{self.title}" by {self.author} ({self.num_pages} pages)'

# This library class manages a collection of books and then tracks the checked out books
class Library:
    def __init__(self):
        self.books = []
        self.checked_out_books = []

    # Adding a book object to the library
    def add_book(self, book):
        self.books.append(book)
        print(f'Added: {book}')

    # Removing a book in the library by its title, removes book if found
    def remove_book(self, title):
        for i, book in enumerate(self.books):
            if book.title == title:
                removed = self.books.pop(i)
                print(f'Removed: {removed}')
                return
        # Prints error message if book isen't found
        print(f'Book titled "{title}" not found in the library.')

    # Borrowing book from the library with the title, if found move the book from available books to the checked out books
    def check_out(self, title):
        for i, book in enumerate(self.books):
            if book.title == title:
                checked_out = self.books.pop(i)
                self.checked_out_books.append(checked_out)
                print(f'Checked out: {checked_out}')
                return checked_out
        # Prints error message if book isen't found
        print(f'Book titled "{title}" not available for checkout.')
        return None

    # Returning a chosen book to the library with the title, if checked out move it to the available books
    def check_in(self, title):
        for i, book in enumerate(self.checked_out_books):
            if book.title == title:
                checked_in = self.checked_out_books.pop(i)
                self.books.append(checked_in)
                print(f'Checked in: {checked_in}')
                return
        print(f'Book titled "{title}" was not checked out.')

    # Printing all the books that are available in the library
    def list_books_in_library(self):
        if not self.books:
            print("No books in the library.")
        else:
            print("Books currently in the library:")
            for book in self.books:
                print(f' - {book}')

# This is the required test script
if __name__ == "__main__":
    # Create Library instance
    library = Library()

    # Creating book instances
    book1 = Book("A Doll's House", "Henrik Ibsen", 96)
    book2 = Book("Hunger", "Knut Hamsun", 240)
    book3 = Book("The Kon-Tiki Expedition", "Thor Heyerdahl", 304)
    book4 = Book("Hedda Gabler", "Henrik Ibsen", 128)

    # Adding books to the library
    library.add_book(book1)
    library.add_book(book2)
    library.add_book(book3)
    library.add_book(book4)

    # Attempt to check out a book
    checked_out = library.check_out("Hunger")

    # Attempting to return a book
    if checked_out:
        library.check_in("Hunger")  # Pass the title, not the book object

    # Removes a book from the library
    library.remove_book("A Doll's House")

    # Print the list of books to verify results from the test script
    library.list_books_in_library()
