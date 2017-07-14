#include "folder.h"
#include "message.h"


void Folder::remove_from_Messages()
{
    for(Message* m : messages)
        m->folders.erase(this);
}

void Folder::add_to_Messages(const Folder& f)
{
    for(Message* m : f.messages)    // for each message to f reffers to
        m->folders.insert(this);    // add a pointer to this folder
}

void Folder::move_Messages(Folder* f)
{
    messages = std::move(f->messages);
    for(Message* m : f->messages){
        m->folders.erase(f);
        m->folders.insert(this);
    }
    f->messages.clear();
}

void swap(Folder& lhs, Folder& rhs) noexcept
{
    using std::swap;
    for(Message* m : lhs.messages)
        m->removeFolder(&lhs);
    for(Message* m : rhs.messages)
        m->removeFolder(&rhs);
    // swap the Message pointer sets
    swap(lhs.messages, rhs.messages);
    for(Message* m : lhs.messages)
        m->addFolder(&lhs);
    for(Message* m : rhs.messages)
        m->addFolder(&rhs);
}

std::ostream& operator<<(std::ostream& os, const Folder& f)
{
    os << "Messages in folder " << reinterpret_cast<const void*>(&f) << ":\n";
    for(Message* m : f.messages){
        os << reinterpret_cast<void*>(m) << ":   " << *m;
    }
    return os;
}