#pragma once
#include "recordmanager.h"
#include "date.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// 日期相关函数
date inputdate();

void inputdaterange(date& start, date& end);

// 菜单显示函数
void showmenu();

// 菜单处理函数
void menu(int choice, record_manager& manager);

// 工具函数

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