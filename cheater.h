//
// Created by Luis Vazquez Delgado on 5/5/20.
//

#ifndef CHEATERS_CHEATER_H
#define CHEATERS_CHEATER_H


class cheater {

private:
    int index1;
    int index2;
    int similar;

public:
    cheater(int in1, int in2, int sim);

    int getIn1();
    int getIn2();
    int getSim();

    bool operator <(cheater const &rhs);
    bool operator >(cheater const &rhs);
    bool operator ==(cheater const &rhs);

};


#endif //CHEATERS_CHEATER_H
