/**
 * Author: Jeff Leupold
 * Project 5: Hashing the Hobbit
 * Date: 2020-11-17
 */
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "English.h"
using namespace std;

void removeCommonWords(WordCounter &wordCounter) {
    vector<string> common = English::commonWords();

    for (int i = 0; i < common.size(); ++i) {
        wordCounter.removeWord(common[i]);
    }
}

void importTextFile(string fileName, WordCounter &wordCounter) {
    string line = "";
    string word = "";
    string prevWord = "";
    bool newLine = true;

    ifstream textFile;
    textFile.open(fileName);

    if (textFile) {
        // getline() removes \n
        while (getline(textFile, line)) {
            istringstream ss(line);
            //signal that I am starting a new line
            newLine = true;
            while (ss >> word) {
                //if start of new line, the last word on the previous line isn't something weird, and it ends with -
                if (newLine && prevWord.length() > 1 && prevWord.substr(prevWord.length()-1) == "-") {
                    //remove last word from previous line because
                    // it needs to be combined with first word on current line - ex. base- ball --> baseball
                    wordCounter.removeWord(prevWord);
                    word = prevWord.substr(0, prevWord.length()-1) + word;
                }
                word = English::cleanWord(word);
                wordCounter.addWord(word);
                newLine = false;
            }
            //save last word of each line because it might be split at a syllable
            prevWord = word;
        }
    }
    textFile.close();
    //remove common words all at once rather than testing each word
    removeCommonWords(wordCounter);
}

/**
 * prints word count for word(s) specified by user
 * @param input - given by user
 * @param wordCounter
 */
void wordAnalyzer(string input, WordCounter &wordCounter) {
    istringstream ss(input);
    string word = "";
    int count = 0;

    while (ss >> word) {
        count = wordCounter.getWordCount(word);
        if (count == -1)
            count = 0;
        cout << word << ": " << count << endl;
    }
    cout << endl;
}

/**
 * Prints number of unique words, the total number of words, and the load factor
 * @param wordCounter
 */
void printStatistics(WordCounter &wordCounter) {
    cout << "word count statistics:" << endl;
    cout << "\tunique: " << wordCounter.getUniqueWordCount() << endl;
    cout << "\ttotal: " << wordCounter.getTotalWordCount() << endl;
    cout << "\tload: " << wordCounter.getLoadLoadFactor() << endl << endl;
}

int main() {
    string filename = "";
    string wordToAdd = "";
    string wordsToAnalyze = "";
    int cap = 0;

    cout << "What is the file name?";
    //cin >> filename;
    filename = "C:\\Users\\amisa\\Documents\\JeffLeupold\\SeattleU\\DataStructures2\\P5_hash\\QuickBrownFox_hyphen.txt";
//    filename = "C:\\Users\\jlleupol\\Documents\\JeffLeupold\\SeattleU\\DataStructures\\P5.Hashing-Hobbit\\files\\alice.txt";
//    filename = "C:\\Users\\jlleupol\\Documents\\JeffLeupold\\SeattleU\\DataStructures\\P5.Hashing-Hobbit\\files\\hobbit.txt";

    cout << "what is the capacity?";
    cin >> cap;
//    cap = 11;
//    cap = 599;
//    cap = 833;
//    cout << "Capacity: " << cap << endl;

    WordCounter wc(cap);
    importTextFile(filename, wc);

    printStatistics(wc);

    cout << "Enter words (separated by space): ";
    getline(cin, wordsToAnalyze);
    wordAnalyzer(wordsToAnalyze, wc);

    cout << "Made a copy" << endl;
    //English e2(english);
    WordCounter wc2(wc);

    cout << "Add a word to *new* WordCounter object:";
    cin >> wordToAdd;

    if (English::isCommonWord(wordToAdd))
        cout << "You tried to add a common word" << endl;
    else
        wc2.addWord(wordToAdd);

    cout << "Original WordCounter object" << endl;
    printStatistics(wc);
    wordAnalyzer(wordToAdd, wc);
    cout << "Copy of object" << endl;
    printStatistics(wc2);
    wordAnalyzer(wordToAdd, wc2);

    cout << "Turn new object into old object and watch your word disappear" << endl;
    wc2 = wc;
    cout << "Original WordCounter object" << endl;
    printStatistics(wc);
    wordAnalyzer(wordToAdd, wc);
    cout << "New WordCounter object" << endl;
    printStatistics(wc2);
    wordAnalyzer(wordToAdd, wc2);


    return EXIT_SUCCESS;
}
