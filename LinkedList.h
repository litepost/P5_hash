/**
 * Author: Jeff Leupold
 * Project 5: Hashing the Hobbit
 * Date: 2020-11-17
 */

#include <iostream>
#include <string>

#pragma once

//dictionary of int: string functionality in a linked list implementation
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList &other);
    LinkedList &operator=(const LinkedList &rhs);

    void add(std::string key); //lightning fast
    void remove(std::string key); //not fast - linear search
    int search(std::string key) const; //not fast - linear search
    bool isEmpty() const;
    int size() const;
    int totalWordCount() const;

private:
    struct ListElem {
        std::string key;
        int wordCount;
        ListElem *next;

        //convenience constructor
        ListElem(std::string k, int c, ListElem *n) {
            key = k;
            wordCount = c;
            next = n;
        }
    };
    ListElem *head;

    void clear();
    static ListElem *copy(ListElem *headToCopy);

};
