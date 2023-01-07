// Contact Class Interface
#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>
#include <string>

class Contact {
    friend std::ostream& operator<< (std::ostream&, const Contact&);
    friend std::istream& operator>> (std::istream&, Contact&);
public:
    Contact (int = 0, const std::string& = "", const std::string& = "",
        const std::string& = "");
    ~Contact();
    
    void setID (int);
    int getID () const;

    void setFName (const std::string&);
    const char* getFName () const;

    void setLName (const std::string&);
    const char* getLName () const;

    void setPhnNum (const std::string&);
    const char* getPhnNum () const;

private:
    int id;
    char fName[15];
    char lName[25];
    char phnNum[18];
};

#endif
