/**
 * Author: Jeff Leupold
 * Project 5: Hashing the Hobbit
 * Date: 2020-11-17
 */

#include <hash_fun.h>
#include "WordCounter.h"
using namespace std;

WordCounter::WordCounter() {
    capacity = DEFAULT_CAPACITY;
    table = new LinkedList[capacity];
}

WordCounter::WordCounter(int userCapacity) {
    capacity = userCapacity;
    table = new LinkedList[capacity];
}

WordCounter::~WordCounter() {
//    for (int i = 0; i < capacity; ++i) {
//        delete [] table[i];
//    }
    delete [] table;
}

WordCounter::WordCounter(const WordCounter &other) {
    capacity = other.capacity;
    table = new LinkedList[other.capacity];

    for (int i = 0; i < capacity; ++i) {
        table[i] = other.table[i];
    }
}

WordCounter &WordCounter::operator=(const WordCounter &rhs) {
    capacity = rhs.capacity;

    for (int i = 0; i < capacity; ++i) {
        this->table[i] = rhs.table[i];
    }
    return *this;
}

void WordCounter::addWord(std::string newWord) {
    int index = hash(newWord, capacity);
    //add function looks existence. If exists, then iterates wordCount
    table[index].add(newWord);
}

void WordCounter::removeWord(std::string word) {
    int index = hash(word, capacity);
    table[index].remove(word);
}

int WordCounter::getWordCount(std::string word) const {
    //number of occurrences of word
    int index = hash(word, capacity);
    return table[index].search(word);
}

double WordCounter::getLoadLoadFactor() const {
    int bucketCount = 0;

    for (int i = 0; i < capacity; ++i) {
        bucketCount += table[i].size();
//        if (!table[i].isEmpty())
//            bucketCount++;
    }
    return bucketCount / (double)capacity;
}

int WordCounter::getUniqueWordCount() const {
    int wordCount = 0;

    for (int i = 0; i < capacity; ++i) {
        wordCount += table[i].size();
    }

    return wordCount;
}

int WordCounter::getTotalWordCount() const {
    int totalWordCount = 0;

    for (int i = 0; i < capacity; ++i)
        totalWordCount += table[i].totalWordCount();

    return totalWordCount;
}

bool WordCounter::empty() const {
    for (int i = 0; i < capacity; ++i) {
        if (!table[i].isEmpty())
            return false;
    }
    return true;
}

int WordCounter::hash(std::string key, int tableSize) {
    std::hash<string> h;
    return h(key) % tableSize;
}
