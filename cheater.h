//cheater.h
//
//This is the class defined for cheaters. It contains the file index of file 1, file 2, and their similarity according to
//hash collisions

//Written by: Luis Vazquez
//Lev465
//05/07/2020

#ifndef CHEATERS_CHEATER_H
#define CHEATERS_CHEATER_H


class cheater {

private:
    int index1;
    int index2;
    int similar;

public:
    //
    cheater(int in1, int in2, int sim);

    //FUNCTION: getIn1
    //returns index1 of current class
    int getIn1();

    //FUNCTION: getIn2
    //returns index2 of current class
    int getIn2();

    //FUNCTION: getSim
    //returns similarity of current class
    int getSim();
};


#endif //CHEATERS_CHEATER_H
