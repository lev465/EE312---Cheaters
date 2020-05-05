#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "hashTable.h"
#include "cheater.h"

using namespace std;


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
    unsigned int p = 19;
    unsigned int m = 602513;
    unsigned long ex = 1;
    unsigned long res = 0;
    for(string::size_type i=0; i < s.length(); i+=2){
           res = (res + (s[i]-0x30)*ex);
           ex = ex * p;
    }

    return res%m;
}

//opens a file and outputs a produces word concatenations of given number of words
int openFile(string filename, unsigned int NUMWORDS, hashTable& T, int fileIndex){
    vector<string> queue;
    ifstream inFile;
    inFile.open(filename);

    string s;
    inFile >> s;
    s = alphanumeric(&s);
    while(s == "") {
        inFile >> s;
        s = alphanumeric(&s);
    }
    queue.emplace_back(s);
    string temp = s;

   while (inFile) {
       int i=1;
       while( i!=NUMWORDS){
            inFile >> s;
            s = alphanumeric(&s);
            if(s!="") {
                queue.emplace_back(s);
                temp += s;
                i++;
            }
        }

        cout << "6 word queue - " << temp << endl;
        cout << "Hash function return - " << hashfn(temp) << endl;
        T.hashEntry(fileIndex, hashfn(temp));


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
                T.hashEntry(fileIndex, hashfn(temp));
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


void findCheaters(vector<cheater>& cheaterList, vector<vector<int>>& simMatrix, int threshold){
    for(int i = 0; i < simMatrix.size(); i++) {
        for(int j = 0; j < i; j++) {
            if(simMatrix[i][j] >= threshold){
                cheaterList.emplace_back(cheater(i,j,simMatrix[i][j]));
            }
            cout << simMatrix[i][j] << " ";
        }
        cout << "\n" << endl;
    }
}

bool comparator(cheater& lhs, cheater& rhs) {
    return lhs.getSim() > rhs.getSim();
}

int main(int argc, char* argv[]) {
    string dir = "/Users/LuisVazquez/Downloads/Cheaters/cmake-build-debug/big_doc_set"; //argv[1];   //string("sm_doc_set");
    const unsigned int NUMWORDS = 6;
    const int THRESHOLD = 200;

    //const unsigned int NUMWORDS = atoi(argv[2]);
    //const int THRESHOLD = atoi(argv[3]);

    const size_t HASHSIZE = 602513;

    vector<string> files = vector<string>();
    hashTable T = hashTable();

    getdir(dir, files);

    files.erase(files.begin(), files.begin() + 2);

    for (unsigned int i = 0; i < files.size(); i++) {
        string filename;
        if(dir[dir.length()-1]!= '/') {
            filename = dir + "/" + files[i];//           string(argv[1]) + "/" + files[i];
        } else filename = dir + files[i];
        cout << i << files[i] << endl;
        openFile(filename, NUMWORDS,T , i);
    }

    vector<vector<int>> simMatrix(files.size(), vector<int> (files.size()));

    for(int i = 0; i<HASHSIZE; i++){

        while(!T.emptyKey(i)){
            auto temp_ptr = T.getIndexNode(i);
            int j = T.getHashElement(temp_ptr);


            while(temp_ptr->next!=NULL){
                temp_ptr = temp_ptr->next;
                int k = T.getHashElement(temp_ptr);
                if(k!=j) {
                    simMatrix[j][k] = simMatrix[j][k] + 1;
                }
            }
            T.hashDelete(i);
        }
    }

    vector<cheater> C;
    findCheaters(C, simMatrix, THRESHOLD);
    sort(C.begin(), C.end(), &comparator);

    for(int i=0; i<C.size(); i++)
        cout <<  C[i].getSim() <<": " << files[C[i].getIn1()] << " - " << files[C[i].getIn2()] <<  endl;



}
