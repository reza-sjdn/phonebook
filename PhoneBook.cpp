// PhoneBook Class Implementaion
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "PhoneBook.h"
#include "Contact.h"


// Defining Macros For Write Into And Read From Records
#define writeIntoRec(contact) (output.write(reinterpret_cast<const char*>(&contact), sizeof(Contact)));

#define readFromRec(contact) (input.read(reinterpret_cast<char*>(&contact), sizeof(Contact)));

using namespace std;

// GLOBAL fUNCTIONS PROTOTYPE
// Show A Message Before Operation Finishs
char endMessage (const string&);

// A Small Function For Drawing Lines With Specified Characters
void drawLine (char, int);

// Search For ID Function Prototype
int searchByID (const string&);

// Search For First Name Function Prototype
int searchByFName (const string&);

// Search For Last Name Function Prototype
int searchByLName (const string&);

// Search For Phone Number Function Prototype
int searchByPhnNum (const string&);




// Constructor
PhoneBook::PhoneBook (const string& ttl) {setTitle(ttl);}

// Destructor
PhoneBook::~PhoneBook () {}


// Add Contact To PhoneBook
void PhoneBook::add () {
    // Find The First Empty Record
    int key{firstEmptyRec()};

    // Read The Contact From User
    cout << "Recieving Contact ...\n";
    Contact contact;
    cin >> contact;
    contact.setID(key);

    char ans{endMessage("Add")};
    if (ans == 'y') {
        // Open Random-Access File For Write
        ofstream output{file, ios::in | ios::out | ios::binary};
        if (!output) {
            cerr << "File Couldn't Be Opened." << endl;
            exit(EXIT_FAILURE);
        }

        // Find The Record In File And Write Into It
        output.seekp((key - 1) * sizeof(Contact));
        writeIntoRec(contact);
        output.close();
    } 

    else cout << "Operation Cancelled!\n";
}



// Remove One Contact By ID
void PhoneBook::remove () {
    // Get An ID From User And Search For It
    int id{searchByID(file)};

    char ans{endMessage("Remove")};
    if (ans == 'y') {
        // Create A Blank Contact To Be Written In The Specified Record
        // This Is Like Removing A Full Record
        Contact blankContact;

        // Open Random-Access File For Write
        ofstream output{file, ios::in | ios::out | ios::binary};
        if (!output) {
            cerr << "File Couldn't Be Opened." << endl;
            exit(EXIT_FAILURE);
        }

        // Find The Record In File And Write Into It
        output.seekp((id - 1) * sizeof(Contact));
        writeIntoRec(blankContact);

        output.close();
    }

    else cout << "Operation Cancelled!\n";
}



// Edit An Existing Contact
void PhoneBook::edit () {
    // Get An ID From User And Search For It
    int id{searchByID(file)};

    // This Contact Will Be Substitude
    cout << "Recieving New Contact ...\n";
    Contact contact;
    cin >> contact;
    contact.setID(id);

    char ans{endMessage("Edit")};
    if (ans == 'y') {
        // Open Random-Access File For Write
        ofstream output{file, ios::in | ios::out | ios::binary};
        if (!output) {
            cerr << "File Couldn't Be Opened." << endl;
            exit(EXIT_FAILURE);
        }

        // Find The Record In File And Write Into It
        output.seekp((id - 1) * sizeof(Contact));
        writeIntoRec(contact);

        output.close();
    }
    
    else cout << "Operation Cancelled!\n";
}



void PhoneBook::list () {
    // Header For Displaying File Name
    double shift{floor((84 - getTitle().size()) / 2)};
    drawLine('=', shift - 6); cout << ">>>>> ";
    cout << getTitle();
    cout <<" <<<<<"; drawLine('=', shift - 6);
    cout << endl;

    // Main Header
    cout << endl << left << setw(6) << "ID" << setw(22) << "First Name" 
        << setw(30) << "Family Name" << setw(18) << "Phone Number" << endl;
    drawLine('=', 84);
    cout << endl;

    // Open Random-Access File For Read 
    ifstream input{file, ios::in | ios::binary};
    if (!input) {
        cerr << "File Couldn't Be Opened." << endl;
        exit(EXIT_FAILURE);
    }

    // Read From File And Display It
    int numOfContacts{0};
    Contact contact;
    readFromRec(contact);
    while(input) {
        if (contact.getID() != 0) {
            cout << contact;
            ++numOfContacts;
        }
        readFromRec(contact);
    }

    cout << numOfContacts << " Contacts." << endl;

    input.close();
}



// This Function Searches For A Pattern And Returns
// The Number Of Found Result
int PhoneBook::find () {
    // Create A Menu Of Choices
    enum class patternType{ID = 1, FNAME , LNAME, PHONENUMBER};
    cout << "What Type Of Search Would You Like To Do?\n";
    cout << "1. Search By ID\n";
    cout << "2. Search By First Name\n";
    cout << "3. Search By Last Name\n";
    cout << "4. Search By Phone Number\n";

    // Get The Choice From User
    int choice;
    do {
        cout << "==> ";
        cin >> choice;
    } while (static_cast<patternType>(choice) < patternType::ID || 
            static_cast<patternType>(choice) > patternType::PHONENUMBER);


    // Regarding To The Choice, Handle.
    int results;
    switch (static_cast<patternType>(choice)) {
        case patternType::ID:
            results = 1;
            return results;

        case patternType::FNAME:
            results = searchByFName(file);
            return results;

        case patternType::LNAME:
            results = searchByLName(file);
            return results;

        case patternType::PHONENUMBER:
            results = searchByPhnNum(file);
            return results;

        default:
            cout << "Not A Valid Choice!";
    }

    return -1;
}



void PhoneBook::setTitle (const string& title) {
    this->title = title;
    file = title + ".dat";
}

string PhoneBook::getTitle () const {return title;}



// First Empty Record Browser
int PhoneBook::firstEmptyRec () {
    // Open Random-Access File For Read 
    ifstream input{file, ios::in | ios::binary};
    if (!input) {
        cerr << "File Couldn't Be Opened." << endl;
        exit(EXIT_FAILURE);
    }

    // Find The First Empty Record
    Contact contact;
    for (int rec{1}; rec <= 200; ++rec) {
        readFromRec(contact);
        if (contact.getID() == 0) {
            input.close();
            return rec;
        }
    }

    // If PhoneBook Capacity Is Full 
    input.close();
    return -1;
}


// Show A Message Before Operation Finishs
char endMessage (const string& op) {
    cout << "\nAre You Sure To " << op << " This Contact(y/n)? ";
    char ans;
    cin >> ans;
    return ans;
}

// A Small Function For Drawing Lines With Specified Characters
void drawLine(char ch, int size) {
    for (int i{0}; i < size; ++i) cout << ch;
}



// Search By ID [GLOB]
int searchByID (const string& file) {
    // Open File For Read
    ifstream input{file, ios::in | ios::binary};
    if (!input) {
        cerr << "File Couldn't Be Opened." << endl;
        exit(EXIT_FAILURE);
    }

    // Get ID From User
    cout << "Enter ID Without #: ";
    int id; 
    cin >> id;

    // Search For ID
    Contact contact;
    input.seekg((id - 1) * sizeof(Contact));
    readFromRec(contact);
    drawLine('-', 84);
    cout << endl;
    cout << contact;

    input.close();
    return id;
}



// Search By First Name [GLOB]
int searchByFName (const string& file) {
    // Open File For Read
    ifstream input{file, ios::in | ios::binary};
    if (!input) {
        cerr << "File Couldn't Be Opened." << endl;
        exit(EXIT_FAILURE);
    }

    // Get First Name From User
    cout << "Enter First Name: ";
    char fName[15];
    cin.ignore();
    cin.get(fName, 15);

    // Search For First Name
    Contact contact;
    int results{0};
    readFromRec(contact);
    while (input) {
        // It's Not Needed The Whole String, But Part Of It Is Enough
        // To Search All The Occurences
        if (strstr(contact.getFName(), fName) != nullptr) {
            cout << contact;
            ++results;
        }
        readFromRec(contact); 
    }

    input.close();
    return results;
}



// Search By Last Name [GLOB]
int searchByLName (const string& file) {
    // Open File For Read
    ifstream input{file, ios::in | ios::binary};
    if (!input) {
        cerr << "File Couldn't Be Opened." << endl;
        exit(EXIT_FAILURE);
    }

    // Get Last Name From User
    cout << "Enter Last Name: ";
    char lName[25];
    cin.ignore();
    cin.get(lName, 25);

    // Search For Last Name
    Contact contact;
    int results{0};
    readFromRec(contact);
    while (input) {
        // It's Not Needed The Whole String, But Part Of It Is Enough
        // To Search All The Occurences
        if (strstr(contact.getLName(), lName) != nullptr) {
            cout << contact;
            ++results;
        }
        readFromRec(contact); 
    }

    input.close();
    return results;
}



// Search By Phone Number [GLOB]
int searchByPhnNum (const string& file) {
    // Open File For Read
    ifstream input{file, ios::in | ios::binary};
    if (!input) {
        cerr << "File Couldn't Be Opened." << endl;
        exit(EXIT_FAILURE);
    }

    // Get Phone Number From User
    cout << "Enter Phone Number: ";
    char phnNum[18]; 
    cin.ignore();
    cin.get(phnNum, 18);

    // Search For Phone Number
    Contact contact;
    int results{0};
    readFromRec(contact);
    while (input) {
        // It's Not Needed The Whole String, But Part Of It Is Enough
        // To Search All The Occurences
        if (strstr(contact.getPhnNum(), phnNum) != nullptr) {
            cout << contact;
            ++results;
        }
        readFromRec(contact); 
    }

    input.close();
    return results;
}
