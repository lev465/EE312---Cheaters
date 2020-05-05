//
// Created by Luis Vazquez Delgado on 5/2/20.
//

#ifndef CHEATERS_HASHTABLE_H
#define CHEATERS_HASHTABLE_H
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class hashTable {

private:
    static const long HASHSIZE = 602513;

    typedef struct hashNode{
        int data;
        hashNode* next;
    } hashNode;

    hashNode* hashArray[HASHSIZE];

public:

    hashTable();
    bool emptyKey(unsigned long index);
    hashNode* getIndexNode (unsigned long index);
    void hashEntry(int fileIndex, unsigned long hashIndex);
    void hashDelete(unsigned long hashIndex);
    int getHashElement(hashNode* element);


    ~hashTable();

};


#endif //CHEATERS_HASHTABLE_H
