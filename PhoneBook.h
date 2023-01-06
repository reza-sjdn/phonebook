// PhoneBook Class Interface
#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <string>
#include "Contact.h"

class PhoneBook {
public:
    explicit PhoneBook (const std::string& = "contacts");
    ~PhoneBook ();

    void add ();
    void remove (); 
    void edit ();
    void list ();
    int find ();

    void setTitle (const std::string&);
    std::string getTitle () const;

private:
    std::string title;

    // Name Of The Associated File
    std::string file;

    // Utility Function For Finding The First Empty Record
    int firstEmptyRec ();
};

#endif
