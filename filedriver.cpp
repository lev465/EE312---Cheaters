#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include<locale> //check alnum
using namespace std;

//function - remove nonalphanumeric characters
string alphanumeric(string *s){
    string::size_type i = 0;

    while(i < s->length()){
        if( s->at(i) >= 'A' && s->at(i) <= 'Z') {
            s->replace(i, 1, 1, s->at(i) + 0x20);   //s[i] = (s->at(i)+0x20);
            i++;
        }
        else if ((s->at(i) >= 'a' && s->at(i) <= 'z') || (s->at(i) >= '0' && s->at(i) <= '9'))  {
//            s[i] = s[i];
            i++;
        }
        else {
            s->erase(s->begin() + i);
        }
    }
    return *s;
}

int openFile(string filename){
    vector<string> queue;
    ifstream inFile;
    inFile.open(filename);
    const int NUMWORDS = 6;

    string s;
    inFile >> s;
    s = alphanumeric(&s);
    queue.emplace_back(s);
    string temp = s;

    while (inFile) {

        for (int i = 1; i < NUMWORDS; i++) {
            inFile >> s;
            s = alphanumeric(&s);
            queue.emplace_back(s);
            temp+= s;
        }

        cout << "6 word queue - " << temp << endl;

        while(inFile >> s) {
            queue.erase(queue.begin());
            //inFile >> s;
            s = alphanumeric(&s);
            queue.emplace_back(s);
            temp = "";

            for(unsigned long j = 0; j != queue.size(); j++)
                temp = temp + queue.at(j);

            cout << "6 word queue - " << temp << " - queue size - "<< queue.size() << endl;
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
    //string dir = "/Users/LuisVazquez/Downloads/Cheaters/cmake-build-debug/sm_doc_set";
    string dir = argv[1];   //string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir, files);

    files.erase(files.begin(), files.begin() + 2);

    for (unsigned int i = 0; i < files.size(); i++) {
        string filename = dir + "/" + files[i];//           string(argv[1]) + "/" + files[i];
        cout << i << files[i] << endl;
        openFile(filename);
    }
}
