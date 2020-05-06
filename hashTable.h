//hashTable.h
//
//This is the class defined for a hash table. The hash table is an array that contains the file index of the origin for
//each entry. Collisions are handled by creating new entries in the linked list
//Written by: Luis Vazquez
//Lev465
//05/07/2020

#ifndef CHEATERS_HASHTABLE_H
#define CHEATERS_HASHTABLE_H
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class hashTable {

private:
    typedef struct hashNode{
        int data;
        hashNode* next;
    } hashNode;

    unsigned long hashSize;
    hashNode** hashArray;

public:

    //hashTable constructor
    //initiates the hashTable as null pointers of hashNodes given the size
    hashTable(unsigned long);

    //FUNCTION: emptyKey
    //checks whether any entries in the hash table have been made at the given index
    //INPUTS: index of the hash table to check
    //OUTPUTS: true if nothing has been placed in the index, false otherwise
    bool emptyKey(unsigned long index);

    //FUNCTION: getIndexNode
    //returns the first node in the hash table for the given index
    //INPUTS: index of hash table for check
    //OUTPUTS: index of the first element in linked list of hash table index
    hashNode* getIndexNode (unsigned long index);

    //FUNCTION: hashEntry
    //adds a new entry into the hash table. Deals with collisions by creating another entry in the linked list at the index
    //INPUTS: index of file entry originated from, and index for hash table entry
    //OUTPUTS: none
    void hashEntry(int fileIndex, unsigned long hashIndex);

    //FUNCTION: hashDelete
    //deletes the topmost element in the linked list at a hash table element
    //INPUTS: index to delete entry for
    //OUTPUTS: none.
    void hashDelete(unsigned long hashIndex);

    //FUNCTION: getHashElement
    //returns the index for the file where the entry originated from
    //INPUTS: pointer to hashNode to get data from
    //OUTPUTS: index of file entry originated from
    int getHashElement(hashNode* element);

    //FUNCTION: hashfn
    //hash function for strings
    //assumes string has already been processed to contain only alphanumeric characters
    //uses hash(s) = sum [s[i] * 11^i] % (hash table size)
    //INPUTS: string to be processed
    //OUTPUTS: index for hash table entry
    unsigned long hashf(string &s);

    //destructor
    //deletes allocated space for the hash table
    ~hashTable();

};


#endif //CHEATERS_HASHTABLE_H
