// folder.h -- Chapter 13 copy-control
// Folder class - companion to the Message class
// ex 13.36
#ifndef FOLDER_H_
#define FOLDER_H_

#include <iostream>
#include <set>

class Message;

class Folder
{
public:
    Folder()
        : messages()
        { }
    Folder(const Folder& f);
    Folder(Folder&& f);
    ~Folder();
    Folder& operator=(const Folder& f);
    Folder& operator=(Folder&& f);

    std::set<Message*>::iterator addMsg(Message* m)
        { return messages.insert(m).first; }
    std::size_t remMsg(Message* m)
        { return messages.erase(m); }

    friend void swap(Folder& lhs, Folder& rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Folder& f);
private:
    std::set<Message*> messages;

// utility functions used by copy ctor, assignment and dtor
    void remove_from_Messages();
    void add_to_Messages(const Folder&);
    // move Message Pointers from f to this Folder
    void move_Messages(Folder* f);
};


inline Folder::Folder(const Folder& f)
    : messages(f.messages)
{
    add_to_Messages(f);
}

inline Folder::Folder(Folder&& f)
{
    move_Messages(&f);
}

inline Folder::~Folder()
{
    remove_from_Messages();
}

inline Folder& Folder::operator=(const Folder& rhs)
{
    // handle self-assignment by removing pointers before inserting them
    remove_from_Messages();
    messages = rhs.messages;
    add_to_Messages(rhs);
    return *this;
}

inline Folder& Folder::operator=(Folder&& f)
{
    if(this == &f)
        return *this;
    remove_from_Messages();
    move_Messages(&f);
    return *this;
}


#endif /*FOLDER_H_*/
