#include "doubly-linked-list.h"
#include <iostream>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    Node* ptr;
    while (head_ != nullptr){
        ptr = head_->next;
        delete head_;
        head_ = ptr;
    }
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return(CAPACITY);
}

bool DoublyLinkedList::empty() const
{
    if (size_ == 0)
        return true;
    else
        return false;
}

bool DoublyLinkedList::full() const
{
    if (size_ == CAPACITY)
        return true;
    else
        return false;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if (index == 0)
        return head_->value;

    Node *ptr = head_;
    int count = 0;
    while (ptr != nullptr){
        if (count == index)
            return ptr -> value;
        count ++;
        ptr = ptr -> next;
    }
    return tail_ -> value;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    Node *ptr = head_;

    int count = 0;
    while (ptr -> next != nullptr){
        if (ptr->value == value)
            return count;
        ptr = ptr -> next;
        count ++;
    }
    return size_;
}

void DoublyLinkedList::print() const
{
    cout<<"Your list: ";
    Node* ptr = head_;
    while (ptr != nullptr) {
        int i = ptr->value;
        cout << i<<' ';
        ptr = ptr->next;
    }
    cout<<'\n';
    cout<<'\n';

}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    if (index >= size_)
        return NULL;
    else{
        Node *ptr = head_;
        while (index != 0){
            ptr = ptr->next;
            if (ptr == head_)
                return NULL;
            index--;
        }
        return ptr;
    }
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    //If insert front
    if (index == 0) {
        return(insert_front(value));
    }

    //If insert back
    else if (index == size_){
        return(insert_back(value));
    }

    else if (size_ < CAPACITY && index <= size_){
        Node* node = new Node(value);
        Node* ptr = head_;
        int count = 0;
        while (ptr != nullptr && count < index){
            if (count == index-1){
                node->next = ptr->next;
                ptr->next = node;
                node->prev=ptr;
                size_++;
                return true;
            }
            ptr = ptr->next;
            count++;
        }
    }
    return false;
}

bool DoublyLinkedList::insert_front(DataType value)
{
    if (size_ < CAPACITY) {
        Node *node = new Node(value);
        node->prev = nullptr;

        if (size_ == 0){
            head_ = node;
            tail_ = node;
            node->next = nullptr;
        }
        else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        size_++;
        return true;
    }
    return false;
}

bool DoublyLinkedList::insert_back(DataType value)
{
    if (size_ < CAPACITY){
        Node* node = new Node(value);
        node->next = nullptr;
        if (size_ == 0){
            node->prev = nullptr;
            head_ = node;
            tail_ = node;
        }
        else{
            Node* ptr = head_;
            while (ptr -> next != nullptr){
                ptr = ptr->next;
            }
            ptr->next = node;
            node->prev = ptr;
            tail_ = node;
        }
        size_ ++;
        return true;
    }
    return false;
}

bool DoublyLinkedList::remove(unsigned int index)
{
    if (index == 0)
        return(remove_front());
    else if (index == size_-1)
        return(remove_back());
    else if (size_ > 0 && index < size_+1){
        Node* ptr = head_;
        int count = 0;
        while (ptr!= nullptr && count < index){
            if (count == index){
                Node* ptr1;
                ptr1 = ptr->prev;
                ptr1->next = ptr->next;
                ptr1 = ptr->next;
                ptr1->prev = ptr->prev;
                delete ptr;
                size_--;
                return true;
            }

            count++;
            ptr = ptr->next;
        }
    }
    return false;
}

bool DoublyLinkedList::remove_front()
{
    if (size_ != 0){
        Node* ptr = head_;
        size_--;
        if (size_ == 0) {
            head_ = nullptr;
            tail_ = nullptr;
        }
        else {
            head_ = ptr->next;
            head_->prev = nullptr;
        }
        delete ptr;
        return true;
    }
    else
        return false;
}

bool DoublyLinkedList::remove_back()
{
    if (head_ != nullptr){
        if (head_->next == nullptr){
            head_ = nullptr;
        }
        else{
            Node* ptr = head_;
            while (ptr->next->next != nullptr)
                ptr = ptr->next;
            Node* last = ptr->next;
            ptr->next = nullptr;
            tail_ = ptr;
            delete last;
        }
        size_--;
        if (size_ == 0) {
            head_ = nullptr;
            tail_ = nullptr;
        }
        return true;
    }
    return false;
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    Node* ptr = head_;
    int count = 0;
    while (ptr!= nullptr){
        if (count == index) {
            ptr->value = value;
            return true;
        }
        ptr = ptr -> next;
        count++;
    }
    return false;
}

