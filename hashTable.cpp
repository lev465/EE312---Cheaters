//
// Created by Luis Vazquez Delgado on 5/2/20.
//

#include "hashTable.h"

using namespace std;

hashTable::hashTable()
{
    for (int i = 0; i<HASHSIZE; i++)
        hashArray[i]=NULL;
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

hashTable::~hashTable()
{
    cout << "this is the destructor" << endl;
}

