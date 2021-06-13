/**
 * Author: Jeff Leupold
 * Project 5: Hashing the Hobbit
 * Date: 2020-11-17
 */

#pragma once
#include <string>
#include "LinkedList.h"


class WordCounter {
public:
    WordCounter();
    explicit WordCounter(int capacity);

    ~WordCounter();
    WordCounter(const WordCounter &other);
    WordCounter &operator=(const WordCounter &rhs);

    void addWord(std::string newWord);
    void removeWord(std::string word);

    /**
     * number of occurrences of a word in a text file
     * @param word given by the user
     * @return number of occurrences
     */
    int getWordCount(std::string word) const; //word count for a particular word
    /**
     * Given that each element in the array is a linked list, the load factor is often > 1.
     * The equation is the average length of the linked lists in the hash table
     * @return numbre of elements / capacity
     */
    double getLoadLoadFactor() const;

    /**
     * Counts the number of unique words from a text file, after removing common words
     * @return number of keys in hash table
     */
    int getUniqueWordCount() const; //number of keys

    /**
     * loops through each linked list and sums the "payload" for each node
     * @return the number of words in a text file
     */
    int getTotalWordCount() const; //sum of key counts

    /**
     * true if every linked list is null
     * @return true/false
     */
    bool empty() const;

private:
    static const int DEFAULT_CAPACITY = 101;  // Usually you want a prime number here
    int capacity;
    LinkedList *table;

    /**
     * Function to assign a bucket to a word
     * @param key the word to hash
     * @param tableSize - required to allow a static function - just pass capacity to function
     * @return
     */
    static int hash(std::string key, int tableSize);
    int next(int bucket) const;
};



