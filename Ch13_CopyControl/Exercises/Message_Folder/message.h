// message.h -- Chapter 13 copy-control example
#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>
#include <string>
#include <set>

class Folder;

class Message
{
    friend class Folder;
public:
    // folders is implicitly initialized to the empty set
    explicit Message(const std::string& str = "")
        : contents(str)
        { }
    // copy control to manage pointers to this Message
    Message(const Message&);             // copy ctor
    Message& operator=(const Message&);  // copy assignment
    ~Message();                          // destructor

    // add/remove this Message from the specified Folder's set of messages
    void save(Folder&);
    void remove(Folder&);

    std::set<Folder*>::iterator addFolder(Folder* f)
        { return folders.insert(f).first; }
    std::size_t removeFolder(Folder* f)
        { return folders.erase(f); }

    friend void swap(Message& lhs, Message& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Message& m);

private:
    std::string contents;       // actual message text
    std::set<Folder*> folders;  // Folders that have this Message

// utility functions used by copy constructor, assignment, and destructor
    // add this Message to the Folders that point to the parameter
    void add_to_Folders(const Message&);
    // remove this Message from every Foldder in folders
    void remove_from_Folders();
};


#endif /*MESSAGE_H_*/
