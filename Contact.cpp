// Contact Class Implementation
#include <iostream>
#include <string>
#include <iomanip>
#include "Contact.h"

using namespace std;

void drawLine (char, int);

ostream& operator<< (ostream& output, const Contact& contact) {
    output << "#" << left << setw(5) << contact.getID() << setw(22) <<
        contact.getFName() << setw(30) << contact.getLName() <<
        setw(18) << contact.getPhnNum() << endl;
        drawLine('-', 84);
        cout << endl;
    return output;
}


istream& operator>> (istream& input, Contact& contact) {
    cout << "Enter First Name: ";
    string fName;
    input >> fName;
    contact.setFName(fName);

    cout << "Enter Last Name: ";
    string lName;
    input >> lName;
    contact.setLName(lName);

    cout << "Enter Phone Number: ";
    string phnNum;
    input >> phnNum;
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
    length = (length < 15 ? length : 14);
    lName.copy(this->lName, length);
    this->lName[length] = '\0';
}

const char* Contact::getLName () const {return lName;}


void Contact::setPhnNum (const string& phnNum) {
    size_t length{phnNum.size()};
    length = (length < 15 ? length : 14);
    phnNum.copy(this->phnNum, length);
    this->phnNum[length] = '\0';
}

const char* Contact::getPhnNum () const {return phnNum;}

