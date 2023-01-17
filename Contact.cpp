// Contact Class Implementation
#include <iostream>
#include <string>
#include <iomanip>
#include "Contact.h"

using namespace std;

void drawLine (char, int);

// Format Strings
void formStr (string&);


ostream& operator<< (ostream& output, const Contact& contact) {
    output << "#" << left << setw(5) << contact.getID() << setw(22) <<
        contact.getFName() << setw(30) << contact.getLName() <<
        setw(18) << contact.getPhnNum() << endl;
        drawLine('-', 84);
        cout << endl;
    return output;
}


istream& operator>> (istream& input, Contact& contact) {
    cin.ignore();
    cout << "Enter First Name: ";
    string fName;
    getline(input, fName);
    formStr(fName);
    contact.setFName(fName);

    cout << "Enter Last Name: ";
    string lName;
    getline(input, lName);
    formStr(lName);
    contact.setLName(lName);

    cout << "Enter Phone Number: ";
    string phnNum;
    getline(input, phnNum);
    contact.setPhnNum(phnNum);

    return input;
}


Contact::Contact (int contactID, const string& firstName, const string& lastName, const string& phoneNumber) {
    setID(contactID);
    setFName(firstName);
    setLName(lastName);
    setPhnNum(phoneNumber);
}

Contact::~Contact () {}


void Contact::setID (int id) {
    if (id >= 0 && id <= 200) this->id = id;
    else cout << "not a valid id\n";
}

int Contact::getID () const {return id;}


void Contact::setFName (const string& fName) {
    size_t length{fName.size()};
    length = (length < 15 ? length : 14);
    fName.copy(this->fName, length);
    this->fName[length] = '\0';
}

const char* Contact::getFName () const {return fName;}


void Contact::setLName (const string& lName) {
    size_t length{lName.size()};
    length = (length < 25 ? length : 24);
    lName.copy(this->lName, length);
    this->lName[length] = '\0';
}

const char* Contact::getLName () const {return lName;}


void Contact::setPhnNum (const string& phnNum) {
    size_t length{phnNum.size()};
    length = (length < 18 ? length : 17);
    phnNum.copy(this->phnNum, length);
    this->phnNum[length] = '\0';
}

const char* Contact::getPhnNum () const {return phnNum;}


// Format Strings
void formStr (string& str) {
    if (islower(str[0])) str[0] = toupper(str[0]);
    for (size_t i{1}; i < str.size(); ++i) {
        if (isupper(str[i])) str[i] = tolower(str[i]);
    }
}
