#include <iostream>
#include <fstream>
#include <string>
#include "Contact.h"
#include "PhoneBook.h"

using namespace std;

PhoneBook phonebook;

// showMenu Function Prototype
void showMenu ();

int main() {
    cout << "Welcome To Phonebook Software Written By Reza Sajjadian\n\n";

    // Check If The User's First Time Entering
    ifstream input{"register.txt"};
    int firstTime{0};
    if (!input) firstTime = 1;
    input.close();

    // If It's The First Time For The User
    if (firstTime) {
        cout << "You Have To Sign Up Due To Being First Time Visiting.\n";
        
        // Get Username
        cout << "Enter Username: ";
        string userName;
        cin >> userName;

        // Get Password
        cout << "Enter Password: ";
        string passwd;
        cin >> passwd;

        // Write Username and Password into register.txt
        ofstream output{"register.txt"};
        output << userName << " " << passwd;

        // Create Phonebook
        cout << "\nWe're Creating A Phonebook For You.\n";
        cout << "Name Your Phonebook: ";
        string ttl;
        cin.ignore();
        getline(cin, ttl);
        phonebook.setTitle(ttl);
        output << " " << ttl;
        cout << "You're Successfully Signed Up :)\n\n";
        output.close();
        
        // Create Random-Access File
        ofstream output2{ttl + ".dat", ios::out | ios::binary};
        Contact contact;
        for (int i{0}; i < 200; ++i) {
            output2.write(reinterpret_cast<const char*>(&contact), sizeof(Contact));
        }
        output2.close();
    }

    // If It's NOT The First Time For The User
    else {
        // Get Info For Login
        ifstream input{"register.txt"};
        string userName;
        input >> userName;
        string passwd;
        input >> passwd;
        string ttl;
        input >> ttl;
        phonebook.setTitle(ttl);

        // Login Fields
        cout << "Enter Username: " << userName << endl;
        cout << "Enter Password: " << passwd << endl;
        cout << "You're Successfully Logged In :)\n\n";
        input.close();
    }


    // Create A Menu Of Choices
    enum class ChoiceType{ADD = 1, REMOVE, EDIT, LIST, FIND, EXIT};

    // Get The Choice From User
    showMenu();
    int choiceInt;
    do {
        cout << "==> ";
        cin >> choiceInt;
    } while (static_cast<ChoiceType>(choiceInt) < ChoiceType::ADD ||
            static_cast<ChoiceType>(choiceInt) > ChoiceType::EXIT);

    // As Long As The Choice Isn't EXIT, Continue
    while(static_cast<ChoiceType>(choiceInt) != ChoiceType::EXIT) {
        // Regarding To The Choice, Handle.
        switch (static_cast<ChoiceType>(choiceInt)) {
            case ChoiceType::ADD:
                cout << endl;
                cout << "/ADD/\n";
                phonebook.add();
                cout << endl;
                break;

            case ChoiceType::REMOVE:
                cout << endl;
                cout << "/REMOVE/\n";
                phonebook.remove();
                cout << endl;
                break;

            case ChoiceType::EDIT:
                cout << endl;
                cout << "/EDIT/\n";
                phonebook.edit();
                cout << endl;
                break;

            case ChoiceType::LIST:
                cout << endl;
                cout << "/LIST/\n";
                phonebook.list();
                cout << endl;
                break;

            case ChoiceType::FIND:
                cout << endl;
                cout << "/FIND/\n";
                phonebook.find();
                cout << endl;
                break;

            case ChoiceType::EXIT:
                break;
        }


        // Get The Choice From User
        showMenu();
        do {
            cout << "==> ";
            cin >> choiceInt;
        } while (static_cast<ChoiceType>(choiceInt) < ChoiceType::ADD ||
                static_cast<ChoiceType>(choiceInt) > ChoiceType::EXIT);
    }

    cout << "End Of Program.\n";
    return 0;
}


void showMenu () {
    cout << "What Type Of Operation Would You Like To Do?\n";
    cout << "1. Add Contact\t\t";
    cout << "2. Remove Contact\n";
    cout << "3. Edit Contact\t\t";
    cout << "4. List Phonebook\n";
    cout << "5. Find Contact\t\t";
    cout << "6. Exit\n";
}
