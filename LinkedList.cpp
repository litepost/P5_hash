/**
 * Author: Jeff Leupold
 * Project 5: Hashing the Hobbit
 * Date: 2020-11-17
 */

#include "LinkedList.h"
using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
}

LinkedList::~LinkedList() {
    clear();
}

LinkedList::LinkedList(const LinkedList &other) {
    head = copy(other.head);
}

LinkedList &LinkedList::operator=(const LinkedList &rhs) {
    if (&rhs != this) {
        clear();
        head = copy(rhs.head);
    }
    return *this;
}

LinkedList::ListElem *LinkedList::copy(LinkedList::ListElem *headToCopy) {
    ListElem anchor("", 0, nullptr), *source, *tail;
    tail = &anchor;
    for (source = headToCopy; source != nullptr; source = source->next) {
        tail->next = new ListElem(source->key, source->wordCount, nullptr);
        tail = tail->next;
    }
    return anchor.next;
}

void LinkedList::clear() {
    while (head != nullptr) {
        ListElem *toDelete = head;
        head = head->next;
        delete toDelete;
    }
    //is head null?
    //point toDelete to head
    //assign head to the next pointer
    //delete the node
}

void LinkedList::add(string key) {


    if (search(key) == -1)
        //takes old and makes it next, and then creates a new head
        head = new ListElem(key, 1, head);
    else
        for (ListElem *cur = head; cur != nullptr ; cur = cur->next) {
            if (cur->key == key)
                cur->wordCount++;
        }
}

int LinkedList::search(string key) const {


    for (ListElem *cur = head; cur != nullptr ; cur = cur->next) {
        if (cur->key == key) {
            //cur->key crashes if there's no key, but we know there's a key because of the for loop conditions
            return cur->wordCount;
        }
    }
    return -1;
}

void LinkedList::remove(string key) {
    //if empty list
    if (head == nullptr)
        return;
    //special case if found at head of list
    //(*head).key == key
    if (head->key == key) {
        ListElem *toDelete = head;
        head = head->next;
        return;
    }
    //normal case is to find later down the list
    ListElem *prior = head;
    for (ListElem *cur = head->next; cur != nullptr; cur = cur->next) {
        if (cur->key == key) {
            prior->next = cur->next;
            delete cur;
            return;
        }
        prior = prior->next;
    }
}

bool LinkedList::isEmpty() const {
    if (head == nullptr)
        return true;
    else
        return false;
}

int LinkedList::size() const {
    int elemCount = 0;

    for (ListElem *cur = head; cur != nullptr ; cur = cur->next)
        elemCount++;

    return elemCount;
}

int LinkedList::totalWordCount() const {
    int totalCount = 0;

    for (ListElem *cur = head; cur != nullptr ; cur = cur->next)
        totalCount += cur->wordCount;

    return totalCount;
}
