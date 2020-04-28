#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int openFile(string filename){
    ifstream inFile;
    inFile.open(filename);

    string s;
    inFile >> s;
    
    while (inFile) {
        inFile >> s;
    }

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

int main(int argc, char* argv[])
{
    string dir = argv[1];//string("sm_doc_set");
    vector<string> files = vector<string>();
    
    getdir(dir,files);

    files.erase(files.begin(), files.begin()+2);

    for (unsigned int i = 0;i < files.size();i++) {
	string filename =string(argv[1]) +"/"+ files[i];
        cout << i << files[i] << endl;
	openFile(filename);
    }
    return 0;
}
