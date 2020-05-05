//
// Created by Luis Vazquez Delgado on 5/5/20.
//

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

bool cheater::operator <(cheater const &rhs)
{
    return this->similar < rhs.similar;
}

bool cheater::operator >(cheater const &rhs)
{
    return this->similar > rhs.similar;
}

bool cheater::operator ==(cheater const &rhs)
{
    return this->similar == rhs.similar;
}