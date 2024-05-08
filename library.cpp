/*
Syed Sufiyan Ahmed

CS 251 Project 1: Library Management System


*/

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function prototypes for all the glorious function decomposition
void printMenu();
void addItem(vector<string> &, vector<string> &, vector<int> &);
void displayEntry(vector<string> &, vector<string> &, vector<int> &);
void fileReading(ifstream &, vector<string> &, vector<string> &, vector<int> &);
void outputData(vector<string> &, vector<string> &, vector<int> &);
void checkoutBook(vector<string> &, vector<string> &, vector<int> &);
void searchLibrary(vector<string> &, vector<string> &, vector<int> &);
void removeEntry(vector<string> &, vector<string> &, vector<int> &);

int main()
{
    string command;
    vector<string> bookTitle;
    vector<string> isbnNum;
    vector<int> bookStatus;

    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do
    {
        // Output the menu and acquire a user selection
        printMenu();
        cout << endl
             << "Enter a command (case does not matter): ";

        // We use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline
        getline(cin, command);
        cout << endl;
        // function call for Add
        if (command == "A" || command == "a")
        {
            addItem(bookTitle, isbnNum, bookStatus);
            cout << endl;
        }
        // function call for Display
        else if (command == "D" || command == "d")
        {
            displayEntry(bookTitle, isbnNum, bookStatus);
            cout << endl;
        }
        // function call for Clear
        else if (command == "C" || command == "c")
        {
            bookTitle.clear();
            isbnNum.clear();
            cout << "Your library is now empty.\n";
            cout << endl;
        }
        // function call for Load
        else if (command == "L" || command == "l")
        {
            bookTitle.clear();
            isbnNum.clear();
            string fileName;
            ifstream infile;
            while (true)
            {
                cout << "What database to read from? ";
                getline(cin, fileName);
                cout << endl;
                infile.open(fileName);

                if (!infile.is_open())
                {
                    cout << "Could not find the database file.\n";
                    continue;
                }
                else
                {
                    break;
                }
            }

            fileReading(infile, bookTitle, isbnNum, bookStatus);
            cout << endl;
            infile.close();
        }
        // function call for Output
        else if (command == "o" || command == "O")
        {
            outputData(bookTitle, isbnNum, bookStatus);
            cout << endl;
        }
        // function call for checkout
        else if (command == "P" || command == "p")
        {
            checkoutBook(bookTitle, isbnNum, bookStatus);
            cout << endl;
        }
        // function call for search
        else if (command == "S" || command == "s")
        {
            searchLibrary(bookTitle, isbnNum, bookStatus);
            cout << endl;
        }
        // function call for Remove
        else if (command == "R" || command == "r")
        {
            removeEntry(bookTitle, isbnNum, bookStatus);
            cout << endl;
        }

    } while (!(command == "x" || command == "X"));

    return 0;
}

// Function definitions for all the glorious function decomposition
// Tip: alphabetical order makes it easy to find things if you have
//      a lot of function decomposition.

/// @brief print out the main menu of the management system
void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;
    cout << "S - Search For A Library Entry" << endl;
    cout << "X - Exit Program" << endl;
}
/*Add entries to the library. The function takes three parameters passed by reference and the book name and isbn is asked. It first checks if the book name has
entered correctly without commas. This function also updates the ISBN number for the same book name entered via user and stores it to the vector. During seach operation whem the
user enters the name of the book onyl the latest isbn number displays to the user*/
void addItem(vector<string> &bookName, vector<string> &bookNum,
             vector<int> &bookStat)
{
    string name;
    string number;
    bool found = false;
    size_t index;

    cout << "What is the book title? ";
    getline(cin, name);
    cout << endl;

    index = name.find(',');

    if (index != string::npos)
    {
        found = true;
    }

    if (found)
    {
        cout << "The book title cannot contain commas.\n";
        return;
    }
    cout << "What is the 13-digit ISBN (with hyphens)? ";
    getline(cin, number);
    cout << endl;

    if (number.empty())
    {
        number = "000-0-00-000000-0";
    }
    int defaultNum = 0;
    bookStat.push_back(defaultNum);
    // for-loop to check if the user entered the same book again; if so the new isbn is only updated to the old book. In this case it is used because if the user searches the book
    // only the latest will be shown to the user and the rest will not pop-up
    bool foundName = false;
    for (int j = 0; j < bookName.size(); j++)
    {
        if (bookName.at(j).find(name) != string::npos)
        {
            bookNum.at(j) = number;
            foundName = true;
        }
    }
    if (!foundName)
    {
        bookName.push_back(name);
        bookNum.push_back(number);
    }

    cout << "The Following Entry Was Added\n";
    cout << "-----------------------------\n";
    cout << name << " --- " << number << " --- "
         << "In Library\n";
    return;
}
// This function here displays the loaded files or added entries to the output when called and again here three parameters were given, before outputing the for loop in the belwo code
// checks for the spaces and terminates them and thus the entry is now displayed to the otuput.
void displayEntry(vector<string> &books, vector<string> &bookISBN,
                  vector<int> &statusBook)
{

    cout << "Your Current Library\n";
    cout << "--------------------\n";

    if (books.empty() || bookISBN.empty())
    {
        cout << "The library has no books.\n";
    }
    for (size_t l = 0; l < bookISBN.size(); l++)
    {
        size_t start = bookISBN[l].size() - 1;
        while (start >= 0 && bookISBN[l][start] == ' ')
        {
            start--;
        }
    }
    // displaying books stored in books vector and the isbn numebers stored in the isbn vector and few if-else statements to check the status of the each book based on the number assigned to them
    for (size_t i = 0; i < books.size(); i++)
    {
        cout << books.at(i) << " --- " << bookISBN.at(i) << " "
             << "--- ";
        if (statusBook.at(i) == 0)
        {
            cout << "In Library\n";
        }
        else if (statusBook.at(i) == 1)
        {
            cout << "Checked Out\n";
        }
        else if (statusBook.at(i) == 2)
        {
            cout << "On Loan\n";
        }
        else if (statusBook.at(i) == 3)
        {
            cout << "Unknown State\n";
        }
        else
        {

            cout << "Invalid State\n";
        }
    }

    return;
}

/// the main part of the program. Here I have used few string functions like find and substr to parse the string and store the acquired data in three differnet vectors
/// Firstly I have read the line using getline and also delimeter passed into it and then I used find function throughout the entire line to find the first comma and then
// I have used the if statements; if comma has first commz has found then the prorgam checks for the second comma if it is found it parses the string and if not then that means
// that there are only two data present. The outer if statement if no comma has found then in the else statement the program only takes the first data that is book name and stores it in vector
void fileReading(ifstream &file, vector<string> &bookName,
                 vector<string> &numISBN, vector<int> &bookStat)
{
    string readData;
    size_t found;
    while (getline(file, readData, '\n'))
    {
        found = readData.find(',');
        if (found != string::npos)
        {
            size_t pos1 = readData.find(',', found + 1);
            if (pos1 != string::npos)
            {
                bookName.push_back(readData.substr(0, found));
                size_t i;
                int nospace = 0;
                size_t iterateSpace = found;
                for (i = iterateSpace + 1; i < pos1; i++)
                {
                    if (isspace(readData[i]) && i == iterateSpace + 1)
                    {
                        continue;
                    }
                    else if (isdigit(readData[i]))
                    {
                        nospace = i;
                        break;
                    }
                }
                numISBN.push_back(readData.substr(nospace, pos1 - nospace));
                int intConvert = stoi(readData.substr(pos1 + 1));
                bookStat.push_back(intConvert);
            }
            else
            {
                bookName.push_back(readData.substr(0, found));
                size_t x;
                size_t start = 0;
                int z = found;
                for (x = z + 1; x < readData.size(); x++)
                {
                    if (isspace(readData[x]))
                    {
                        continue;
                    }
                    else if (isdigit(readData[x]))
                    {
                        start = x;
                        break;
                    }
                }
                numISBN.push_back(readData.substr(x));
                int intbookStatus = 0;
                bookStat.push_back(intbookStatus);
            }
        }
        else
        {
            bookName.push_back(readData);
            string defaultNum = "000-0-00-000000-0";
            numISBN.push_back(defaultNum);
            int intDefault = 0;
            bookStat.push_back(intDefault);
        }
    }
    cout << "Read in " << bookStat.size() << " lines from the file.\n";

    return;
}
/// the data that are stored in three different vectors are now used to transfer the contents and write in a file. This is done the user is given a file name to enter the data
// When the user enters the filename, it is then opened and then the program writes in the file
void outputData(vector<string> &bookTitle, vector<string> &isbnNum,
                vector<int> &bookStatus)
{
    cout << "Enter a file name: \n";
    string fileName;
    getline(cin, fileName);

    ofstream fileptr;
    fileptr.open(fileName);
    if (!fileptr.is_open())
    {
        cout << "Could not open database file for writing.\n";
    }
    else
    {
        size_t l;
        for (l = 0; l < bookStatus.size(); l++)
        {
            fileptr << bookTitle.at(l) << ", " << isbnNum.at(l) << ", "
                    << bookStatus.at(l) << endl;
        }
    }
    fileptr.close();
    return;
}
// the checkoutbook displays the stats to the output, when the file is read and stroed in vectors; the stat vector where all the information regarding the status fo the book is stored it then prints the
//  total number of books of one kind and other vice-versa and then prints the all books type
void checkoutBook(vector<string> &bookName, vector<string> &bookNum,
                  vector<int> &stat)
{

    cout << "Your Current Library's Stats\n";
    cout << "----------------------------\n";
    int checkLib = 0;
    int checkedOut = 0;
    int onLoan = 0;
    int unknownState = 0;
    int allOther = 0;

    for (int i = 0; i < stat.size(); i++)
    {
        if (stat.at(i) == 0)
        {
            checkLib++;
        }
        else if (stat.at(i) == 1)
        {
            checkedOut++;
        }
        else if (stat.at(i) == 2)
        {
            onLoan++;
        }
        else if (stat.at(i) == 3)
        {
            unknownState++;
        }
    }
    int rem = checkLib + checkedOut + onLoan + unknownState;
    allOther = stat.size() - rem;
    int total = allOther + rem;
    cout << "Total Books: " << total << endl;
    cout << "  In Library: " << checkLib << endl;
    cout << "  Checked Out: " << checkedOut << endl;
    cout << "  On Loan: " << onLoan << endl;
    cout << "  Unknown: " << unknownState << endl;
    cout << "  Other: " << allOther << endl;

    return;
}
/// The search library function searches the matched book or isbn numbers from the entries stored in vectors. Only the latest entries will be displayed according to the book name
void searchLibrary(vector<string> &name, vector<string> &isbn,
                   vector<int> &stat)
{

    cout << "Would you like to search by (1) name or (2) ISBN.\n";
    cout << "Enter the numeric choice: ";
    int num;
    cin >> num;
    cout << endl;
    cin.ignore();

    string book = "";
    string numISBN = "";

    if (num == 1)
    {
        cout << "Enter the book name: ";
        getline(cin, book);
        cout << endl;
    }
    else if (num == 2)
    {
        cout << "Enter the book 13-digit ISBN (with dashes): ";
        getline(cin, numISBN);
        cout << endl;
    }
    else
    {
        cout << "Invalid search by choice option.\n";
    }
    for (size_t l = 0; l < isbn.size(); l++)
    {
        size_t start = isbn[l].size() - 1;
        while (start >= 0 && isbn[l][start] == ' ')
        {
            start--;
        }
    }

    if (num == 1)
    {
        cout << "The Following Are Your Search Results\n";
        cout << "-------------------------------------\n";
        bool isFound = false;
        for (int i = 0; i < name.size(); i++)
        {
            if (name.at(i).compare(book) == 0)
            {
                cout << name.at(i) << " --- " << isbn.at(i) << " --- "
                     << "In Library\n";
                isFound = true;
            }
        }
        if (!isFound)
        {
            cout << "No matching entry found in the library.\n";
        }
    }
    else if (num == 2)
    {
        cout << "The Following Are Your Search Results\n";
        cout << "-------------------------------------\n";
        bool isFound = false;
        for (int j = 0; j < isbn.size(); j++)
        {
            if (isbn[j].compare(numISBN) == 0)
            {
                cout << name.at(j) << " --- " << isbn.at(j) << " --- "
                     << "In Library\n";
                isFound = true;
            }
        }
        if (!isFound)
        {
            cout << "No matching entry found in the library.\n";
        }
    }
    return;
}
void removeEntry(vector<string> &name, vector<string> &bookNum,
                 vector<int> &status)
{

    cout << "Would you like remove by (1) name or (2) ISBN.\n";
    cout << "Enter the numeric choice: ";
    int choice;
    cin >> choice;
    cin.ignore();
    cout << endl;

    if (choice == 1)
    {
        string bookName;
        cout << "Enter the book name: ";
        getline(cin, bookName);
        cout << endl;

        cout << "The Following Entry Was Removed From The Library\n";
        cout << "------------------------------------------------\n";
        bool matchFound = false;
        for (int i = 0; i < name.size(); i++)
        {
            if (name.at(i) == bookName)
            {
                cout << name.at(i) << " --- " << bookNum.at(i) << " --- "
                     << "In Library\n";
                name.erase(name.begin() + i);
                bookNum.erase(bookNum.begin() + i);
                matchFound = true;
            }
        }
        if (!matchFound)
        {
            cout << " No matching entry found in the library.\n";
        }
    }
    else if (choice == 2)
    {
        string numISBN = "";
        cout << "Enter the book 13-digit ISBN (with dashes): \n";
        getline(cin, numISBN);
        cout << endl;
        bool matchFound = false;
        cout << "The Following Entry Was Removed From The Library\n";
        cout << "------------------------------------------------\n";
        for (int j = 0; j < bookNum.size(); j++)
        {
            if (bookNum[j] == numISBN)
            {
                cout << name.at(j) << " --- " << bookNum.at(j) << " --- "
                     << "In Library\n";
                name.erase(name.begin() + j);
                bookNum.erase(bookNum.begin() + j);
                matchFound = true;
            }
        }
        if (!matchFound)
        {
            cout << " No matching entry found in the library.\n";
        }
    }
    else
    {
        cout << "Invalid remove by choice option.\n";
    }
    return;
}