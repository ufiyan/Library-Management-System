# Library-Management-System
This repository contains the implementation of a Library Management System developed as part of a project for CS 251. The system helps curate and manage a collection of books by implementing essential library functionalities using a simplified dataset. This project focuses on efficient data management through vectors and strings, providing streamlined interactions through a text-based user interface.

Features
The system provides the following functionalities:

Add Item to Library: Allows users to add a book to the library by providing the title and ISBN number.
Clear the Library: Resets the system by removing all entries.
Display Library Entries: Outputs all the current entries with their titles, ISBNs, and status.
List Invalid Entries: Identifies and lists entries with errors in their ISBN or status.
Load Library from File: Imports book data from a provided CSV file.
Output Library to File: Exports all library entries to a CSV file.
Print Checkout Stats: Prints an overview of book statuses such as checked out, on loan, and in the library.
Search Library: Searches by title or ISBN for a specific book.
Remove an Entry: Removes the last matching book by title or ISBN.
Exit Program: Safely exits the application.
Data Structure
Books in the library have three attributes:

Title: Book's name (without commas).
ISBN Number: Unique identifier following the 13-digit ISBN format.
Checkout Status: Integer indicating the availability of the book.
Technologies and Restrictions
Languages & Libraries: Developed in C++ using standard file and string handling libraries.
Program Constraints: No external libraries or global variables are used. Code adheres to specific constraints for structured, efficient execution.
Execution Instructions
Clone the repository and ensure all required files are available.
Follow the prompts to interact with the system and explore its capabilities.
For detailed execution examples, refer to the Example Execution section in the project documentation.
