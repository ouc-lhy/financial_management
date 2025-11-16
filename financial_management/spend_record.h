#include "record.h"
#pragma once
enum spend_category {
    housing=0,food,transport,insurance,healthcare,clothes,education,entertain,pet,travel,otherspend
};

string otypeToString(spend_category otype);
ostream& operator<<(ostream& out, spend_category otype);
istream& operator>>(istream& in, spend_category& st);

class spend_record :public record {
private:
    spend_category otype;
public:
    spend_record();
    spend_record(date dt, double money,string sb, spend_category otype);
    ~spend_record();
    spend_category gettype();
    void settype(spend_category type);
    friend ostream& operator<<(ostream& out, spend_record rd);
    friend istream& operator>>(istream& in, spend_record& rd);
    void showrecord();
    void save(ofstream& out);
    bool isIncome() const;
    bool isSpend() const;

};