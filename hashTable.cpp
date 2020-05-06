//hashTable.cpp
//
//This is the class defined for a hash table. The hash table is an array that contains the file index of the origin for
//each entry. Collisions are handled by creating new entries in the linked list
//Written by: Luis Vazquez
//Lev465
//05/07/2020
#include "hashTable.h"

using namespace std;

hashTable::hashTable(unsigned long size)
{
    hashArray= new hashNode*[size];
    hashSize = size;
}

bool hashTable::emptyKey(unsigned long index)
{
    if(hashArray[index] == NULL)
        return true;
    else
        return false;
}

hashTable::hashNode* hashTable::getIndexNode (unsigned long index)
{
    return hashArray[index];
}

void hashTable::hashEntry(int fileIndex, unsigned long hashIndex)
{
    hashNode* temp = new hashNode;
    temp->data = fileIndex;
    temp->next = hashArray[hashIndex];
    hashArray[hashIndex] = temp;
}

void hashTable::hashDelete(unsigned long hashIndex)
{
    if(!emptyKey(hashIndex)){
        hashNode* temp = hashArray[hashIndex]->next;
        delete hashArray[hashIndex];
        hashArray[hashIndex] = temp;
    }
}

int hashTable::getHashElement(hashNode *element)
{
        return element->data;
}

unsigned long hashTable::hashf(string &s)
{
    unsigned int p = 11;
    unsigned long p_i = 1;
    unsigned long result = 0;

    for(string::size_type i=0; i < s.length(); i++){
        result = (result + (s[i]-0x30)*p_i);
        p_i = p_i * p;
    }

    return result%hashSize;
}

hashTable::~hashTable()
{
    delete[] hashArray;
}

