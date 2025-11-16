#include<iostream>
#include<fstream>
#include"income_record.h"
#include"spend_record.h"
#include <vector>
#include <algorithm>
#include <string>
#pragma once

class record_manager {
private:
    vector<record*> records;
    int sorttype;
    double target;

public:
    
    void addrecord(record* rd);
    void showallrecords();
    void loadfromfile();
    void savetofile();
    void viewincomerecords(date dt1,date dt2);
    void viewspendrecords(date dt1, date dt2);
    void searchbydate(int y,int m,int d);
    void modifybydate(int y, int m, int d);
    void deletebydate(int y, int m, int d);
    void checkbalance();
    void statisticsbyCategory(date dt1, date dt2);
    int getsize();
    void balancewarning();
    double gettarget();
    void settarget(double et);
    int get_sorttype() const;
    void set_sorttype(int st);
    string sortTypeToString() const;
    void sort_records();
    record_manager();
    ~record_manager();
    
};

