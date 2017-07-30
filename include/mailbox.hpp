#pragma once
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <iostream>

template <typename MessageType>
class mailbox;


enum class mailbox_read_strategy 
{
    DELETE_IF_ALL, // require all listeners to ready before deletion
    DELETE_IF_ANY  // delete if any have read
};


template <typename message_type>
class mailbox_reader_interface
{
    public: virtual void notify(mailbox<message_type>& mailbox) = 0;
};


template <typename message_type>
class mailbox : public mailbox_reader_interface <message_type>
{
    using listener_type = mailbox_reader_interface <message_type>;
    using message_item  = typename std::list <message_type>::const_iterator;
    
    private: std::vector<listener_type*> listeners_;
    private: std::map <listener_type*, message_item> messages_ptr_;
    private: std::list <message_type> messages_;
    private: mailbox_read_strategy read_strategy_;

    public: explicit mailbox();

    public: explicit mailbox(mailbox_read_strategy read_strategy);

    public: ~mailbox();

    public: bool subscribe(listener_type* listener);

    public: bool unsubscribe(listener_type* listener);

    public: void write(const message_type message);

    public: message_type read(listener_type* listener);

    public: const message_type peek(listener_type* listener);

    public: bool has_unread_messages(listener_type* listener);

    public: void delete_old_messages();

    public: virtual void notify(mailbox <message_type>& mailbox) override;
};






template <typename message_type>
mailbox<message_type>::mailbox()
:   read_strategy_(mailbox_read_strategy::DELETE_IF_ALL)
{
}





template <typename message_type>
mailbox<message_type>::mailbox(mailbox_read_strategy read_strategy)
:   read_strategy_(read_strategy)
{
}


    
    
    
template <typename message_type>
mailbox<message_type>::~mailbox() {}




template <typename message_type>
bool mailbox<message_type>::subscribe(listener_type* listener)
{
    bool inserted = false; // error by default
    try // bad_alloc is thrown if unable to add to vector
    {
        listeners_.push_back(listener);
        messages_ptr_[listener] = messages_.end();
        inserted = true;
    }
    catch(...)
    {
    }

    return inserted;
}





template <typename message_type>
bool mailbox<message_type>::unsubscribe(listener_type* listener)
{
    auto begin = listeners_.begin();
    auto end   = listeners_.end();
    auto pos   = std::find(begin, end, listener);

    // Remove both items if we can find a valid listener
    if (pos != end)
    {
        listeners_.erase(pos);
        messages_ptr_.erase(listener);
    }

    return (pos != end);
}





template <typename message_type>
void mailbox<message_type>::write(const message_type message)
{
    auto end = messages_.end();
    auto pos = messages_.insert(end, message);

    for (auto listener : listeners_)
    {
        if (listener != nullptr)
        {
            // if the reader previously read all messages or was recently
            // created it will have a nullptr.
            //
            // therefore we set it to the newly created message.
            if (messages_ptr_[listener] == messages_.end())
                messages_ptr_[listener] = pos;

            listener->notify(*this);
        }
    }
}





template <typename message_type>
message_type mailbox<message_type>::read(listener_type* listener)
{
    message_type message;
    // a nullptr means no unread messages exist.
    if (has_unread_messages(listener))
    {
        message = *messages_ptr_[listener];
        messages_ptr_[listener]++;
        delete_old_messages();
    }

    return message;
}





template <typename message_type>
const message_type mailbox<message_type>::peek(listener_type* listener)
{
    message_type message;

    // a nullptr means no unread messages exist.
    if (has_unread_messages(listener))
    {
        message = *messages_ptr_[listener];
    }

    return message;
}





template <typename message_type>
bool mailbox<message_type>::has_unread_messages(listener_type* listener)
{
    // a nullptr means no unread messages exist.
    return (messages_ptr_[listener] != messages_.end());
}





template <typename message_type>
void mailbox<message_type>::delete_old_messages()
{
    message_item begin = messages_.begin();
    message_item end   = messages_.end();
    message_item read  = messages_.end();

    bool any_read = false;
    bool all_read = false;

    for (auto it = begin; it != end; it++)
    {
        all_read = true;
        any_read = false;

        for (auto listener : listeners_)
        {
            if (messages_ptr_[listener] == it)
            {   // contradiction: a listener has read this message.
                any_read = true;
            }
            else
            {   // contradiction: a reader has NOT read the message.
                all_read = false;
            }
        }

        if (any_read && read_strategy_ == mailbox_read_strategy::DELETE_IF_ANY)
        {
            read = it;
            for (auto listener : listeners_)
            {
                if (messages_ptr_[listener] == it)
                    messages_ptr_[listener]++;
            }
        }

        else
        if (all_read && read_strategy_ == mailbox_read_strategy::DELETE_IF_ALL)
        {
            read = it;
        }
    }

    messages_.erase(begin, read);
}




template <typename message_type>
void mailbox<message_type>::notify(mailbox<message_type>& mailbox)
{
    while(mailbox.has_unread_messages(this))
    {
        const message_type message = mailbox.read(this);
        write(message);
    }
}