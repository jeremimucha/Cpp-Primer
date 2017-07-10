#include "message.h"
#include "folder.h"


// add this Message to Folders that point to m
void Message::add_to_Folders(const Message& m)
{
    for(Folder* f : m.folders)  // for each Folder that holds m
        f->addMsg(this);        // add a pointer to this Message to that Folder
}

// remove this message from t he corresponding Folders
void Message::remove_from_Folders()
{
    for(Folder* f : folders)    // for each pointer in folders
        f->remMsg(this);        // remove this Message from that Folder
}


// copy ctor
Message::Message(const Message& m)
    : contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);  // add this Message to the Folders that point to m
}


// dtor
Message::~Message()
{
    remove_from_Folders();
}


// copy assignment
Message& Message::operator=(const Message& rhs)
{
    // handle self-assignment by removing pointers before inserting them
    remove_from_Folders();      // update existing Folders
    contents = rhs.contents;    // copy message ontents from rhs
    folders = rhs.folders;      // copy Folder pointers from rhs
    add_to_Folders(rhs);        // add this Message to those Folders
    return *this;
}


void Message::save(Folder& f)
{
    folders.insert(&f);     // add the given Folder to our list of Folders
    f.addMsg(this);         //add this Message to f's set of Messages
}

void Message::remove(Folder& f)
{
    folders.erase(&f);      // take the given Folder our of our set of Folders
    f.remMsg(this);         // remove this Message from f's set to Messages
}

void swap(Message& lhs, Message& rhs)
{
    using std::swap;    // not strictly needed in this case, but good habit
    // remove pointers to each Message from their (original) respective Folders
    for(Folder* f : lhs.folders)
        f->remMsg(&lhs);
    for(Folder* f : rhs.folders)
        f->remMsg(&rhs);
    // swap the contents and Folder pointer sets
    swap(lhs.folders, rhs.folders);     // uses swap(set&, set&)
    swap(lhs.contents, rhs.contents);   // swap(string& string&)
    // add pointers to each Message to their (new) respective Folders
    for(Folder* f : lhs.folders)
        f->addMsg(&lhs);
    for(Folder* f : rhs.folders)
        f->addMsg(&rhs);
}


std::ostream& operator<<(std::ostream& os, const Message& m)
{
    os << m.contents << ":   ";
    for(Folder* f : m.folders)
        os << reinterpret_cast<void*>(f) << ", ";
    return os;
}

// void swap(Message& lhs, Message& rhs)
