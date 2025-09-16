#pragma once
#include "recordmanager.h"
#include "date.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

date inputdate();

void inputdaterange(date& start, date& end);

void showmenu();

void menu(int choice, record_manager& manager);

template<class T>
T getInput(T minVal = -numeric_limits<T>::max(), T maxVal = numeric_limits<T>::max()) {
    T value;
    int state = 0;
    while (!state) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input, please re-enter" << endl;
        }
        else if (value < minVal || value > maxVal) {
            cout << "Input out of range, please re-enter" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else {
            state = 1;
            cin.ignore(1000, '\n');

        }
    }
    return value;

}