#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//#include "hashTable.h"

using namespace std;

typedef struct hashNode{
    int data;
    hashNode* next;
} hashNode;

//function - removes non-alphanumeric characters from a string (i.e. punctuation, special characters)
string alphanumeric(string *s){
    string::size_type i = 0;

    while(i < s->length()){
        if( s->at(i) >= 'A' && s->at(i) <= 'Z') {
            s->replace(i, 1, 1, s->at(i) + 0x20);   //s[i] = (s->at(i)+0x20);
            i++;
        }
        else if ((s->at(i) >= 'a' && s->at(i) <= 'z') || (s->at(i) >= '0' && s->at(i) <= '9'))  {
            i++;
        }
        else {
            s->erase(s->begin() + i);
        }
    }
    return *s;
}

//hash function for strings
//assumes string has already been processed to contain only alphanumeric characters
// uses hash(s) = sum [s[i] * p^i % m]
// s is the string, and i runs from 0 to length of string - 1
unsigned long hashfn(string &s){
    int p = 67;
    int m = 1e9 + 9;
    unsigned long ex = 1;
    unsigned long res = 0;
    for(string::size_type i=0; i < s.length(); i++){
           res = (res + (s[i]-0x30)*ex) % m;
           ex = ex * p;
    }

    return res;
}

void HashEntry ( hashNode* hashTable[], int data, unsigned long index){
    
}

//opens a file and outputs a produces word concatenations of given number of words
int openFile(string filename, unsigned int NUMWORDS, hashNode* hashTable[], int index){
    vector<string> queue;
    ifstream inFile;
    inFile.open(filename);

    string s;
    inFile >> s;
    s = alphanumeric(&s);
    if(s!= "")
        queue.emplace_back(s);
    string temp = s;

   while (inFile) {

        for (int i = 1; i < NUMWORDS; i++) {
            inFile >> s;
            s = alphanumeric(&s);
            if(s!="") {
                queue.emplace_back(s);
                temp += s;
            } else i--;
        }

        cout << "6 word queue - " << temp << endl;
        cout << "Hash function return - " << hashfn(temp) << endl;


        while(inFile >> s) {
            s = alphanumeric(&s);
            if (s != "") {
                queue.erase(queue.begin());
                queue.emplace_back(s);
                temp = "";

                for (unsigned long j = 0; j != queue.size(); j++)
                    temp = temp + queue.at(j);

                cout << "6 word queue - " << temp << " - queue size - " << queue.size() << endl;
                cout << "Hash function return - " << hashfn(temp) << endl;
            }
        }
   }

    inFile.close();
    return 0;

}


/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main(int argc, char* argv[]) {
    string dir = "/Users/LuisVazquez/Downloads/Cheaters/cmake-build-debug/big_doc_set"; //argv[1];   //string("sm_doc_set");
    const unsigned int NUMWORDS = 6;
    //const unsigned int NUMWORDS = atoi(argv[2]);

    const unsigned long HASHSIZE = 1e9 + 9;

    vector<string> files = vector<string>();
    hashNode * hashTable[HASHSIZE];

    getdir(dir, files);

    files.erase(files.begin(), files.begin() + 2);

    for (unsigned int i = 0; i < files.size(); i++) {
        string filename = dir + "/" + files[i];//           string(argv[1]) + "/" + files[i];
        cout << i << files[i] << endl;
        openFile(filename, NUMWORDS, hashTable, i);
    }
}