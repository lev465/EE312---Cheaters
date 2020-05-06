//cheater.cpp
//
//This is the class defined for cheaters. It contains the file index of file 1, file 2, and their similarity according to
//hash collisions
//Written by: Luis Vazquez
//Lev465
//05/07/2020


#include "cheater.h"

cheater::cheater(int in1, int in2, int sim)
{
    index1=in1;
    index2=in2;
    similar=sim;
}

int cheater::getIn1()
{
    return index1;
}

int cheater::getIn2()
{
    return index2;
}

int cheater::getSim()
{
    return similar;
}