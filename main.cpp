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
//PROTOTYPES

//FUNCTION: fixDir
//checks for correct formatting of directory in linux command line entry
//INPUTS: string of directory to be fixed (assumes non-empty string)
//OUTPUTS: correctly formatted directory string
string fixDir(string &s);

//FUNCTION: alphanumeric
//removes non-alphanumeric characters from a string (i.e. punctuation, special characters)
//INPUTS:
//returns string containing only lower case and numeric characters
string alphanumeric(string &s);

//FUNCTION: openFile
//opens a file using a queue for strings to process into alphanumeric strings, concatenate in groups, and send to a hash table
//INPUTS: name of file to open, amount of words to concatenate before sending to hash function
//        hash table to store keys, and the file index to relate to the key.
//OUTPUTS: 0 for success. Hash table for the file is filled.
int openFile(string filename, unsigned int NUMWORDS, hashTable& T, int fileIndex);

//FUNCTION: getdir
//opens a directory and fills a vector with file names in the directory
//INPUTS: directory name and string vector to place file names in
//OUTPUTS: returns 0 for success and fills a vector with name of files in directory
int getdir (string dir, vector<string> &files);

//FUNCTION: findCheaters
//creates list of cheaters that have similarities in a comparison matrix above the given threshold
//INPUTS: vector of cheaters to fill, comparison matrix between files filled out, and threshold to surpass to add cheaters
//OUTPUTS: filled list of cheaters above the threshold
void findCheaters(vector<cheater>& cheaterList, vector<vector<int>>& simMatrix, int threshold);

//FUNCTION: cheaterSort
//helper function for the std::sort function that returns sorts in descending order based on similarity between files
//INPUTS: cheaters to compare
//OUTPUTS: true if lhs > rhs, false otherwise
bool cheaterSort(cheater& lhs, cheater& rhs);

//MAIN PROGRAM
int main(int argc, char* argv[]) {
//    string dir = "/Users/LuisVazquez/Downloads/Cheaters/cmake-build-debug/big_doc_set"; //argv[1];   //string("sm_doc_set");
//    const unsigned int NUMWORDS = 6;
//    const int THRESHOLD = 200;

    string dir = argv[1];
    const unsigned int NUMWORDS = atoi(argv[2]);
    const int THRESHOLD = atoi(argv[3]);

    const size_t HASHSIZE = 800089;

    vector<string> files = vector<string>();
    hashTable T = hashTable(HASHSIZE);

    getdir(dir, files);

    files.erase(files.begin(), files.begin() + 2);  //delete first two entries (not files)

    dir = fixDir(dir);

    for (unsigned int i = 0; i < files.size(); i++) {
        string filename= dir + files[i];
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
    sort(C.begin(), C.end(), &cheaterSort);

    for(int i=0; i<C.size(); i++)
        cout <<  C[i].getSim() <<": " << files[C[i].getIn1()] << " - " << files[C[i].getIn2()] <<  endl;

    return 0;
}

string fixDir(string &s)
{
    if(s[s.length()-1]!= '/') {
        return  s + "/";
    } else return s;
}


string alphanumeric(string &s)
{
    string::size_type i = 0;

    while(i < s.length()){

        if( s.at(i) >= 'A' && s.at(i) <= 'Z') {                                                   //upper case alpha -> lower case
            s.replace(i, 1, 1, s.at(i) + 0x20);   //s[i] = (s->at(i)+0x20);
            i++;
        }
        else if ((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= '0' && s.at(i) <= '9'))   //lower case alpha or number
            i++;
        else                                                                                    //nonalphanumeric
            s.erase(s.begin() + i);
    }

    return s;
}


int openFile(string filename, unsigned int NUMWORDS, hashTable& T, int fileIndex)
{
    vector<string> queue;
    ifstream inFile;
    inFile.open(filename);

    string s;
    inFile >> s;
    s = alphanumeric(s);

    while(s == "") {
        inFile >> s;
        s = alphanumeric(s);
    }

    queue.emplace_back(s);
    string temp = s;

    while (inFile) {
        int i=1;
        while( i!=NUMWORDS){
            inFile >> s;
            s = alphanumeric(s);
            if(s!="") {
                queue.emplace_back(s);
                temp += s;
                i++;
            }
        }

        T.hashEntry(fileIndex, T.hashf(temp));

        while(inFile >> s) {
            s = alphanumeric(s);
            if (s != "") {
                queue.erase(queue.begin());
                queue.emplace_back(s);
                temp = "";

                for (unsigned long j = 0; j != queue.size(); j++)
                    temp = temp + queue.at(j);

                T.hashEntry(fileIndex, T.hashf(temp));
            }
        }
    }

    inFile.close();
    return 0;

}


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


void findCheaters(vector<cheater>& cheaterList, vector<vector<int>>& simMatrix, int threshold)
{
    for(int i = 0; i < simMatrix.size(); i++) {
        for(int j = 0; j < i; j++) {
            if(simMatrix[i][j] >= threshold){
                cheaterList.emplace_back(cheater(i,j,simMatrix[i][j]));
            }
        }
    }
}

bool cheaterSort(cheater& lhs, cheater& rhs)
{
    return lhs.getSim() > rhs.getSim();
}
