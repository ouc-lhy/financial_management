#pragma once
#include"income_record.h"
ostream& operator<<(ostream& out, income_category itype) {
	out << int(itype);
	return out;
}

istream& operator>>(istream& in, income_category& it) {
	int value;
	in >> value;
	it = income_category(value);
	return in;
}

string itypeToString(income_category itype)
{
	switch (itype) {
	case salary:          return "salary";
	case business:        return "business";
	case investment:      return "investment";
	case interest:        return "interest";
	case allowance:       return "allowance";
	case otherincome:		return "others";
	default:              return "unknown";

	}
}

income_record::income_record() {
	itype = salary;
}
income_record::income_record(date dt, double money, income_category itype, string sb) :record(dt, money, sb), itype(itype) {
}

income_record::~income_record() {}

income_category income_record::gettype() {
	return itype;
}
void income_record::settype(income_category type)
{
	itype = type;
}
ostream& operator<<(ostream& out, income_record rd) {
	out << 1 << " " << std::fixed << std::setprecision(2)<< rd.money<< " " << rd.dt << " " << rd.itype << " " << rd.who << endl;
	return out;
}

istream& operator>>(istream& in, income_record& rd)
{
	in >> rd.money >> rd.dt >> rd.itype;
	in >> ws;
	getline(in, rd.who);
	return in;
}

void income_record::showrecord() {
	cout << setw(8) << "income"
		<< setw(12) << fixed << setprecision(2) << getmoney() << "гд"
		<< setw(9) << getdate()
		<< setw(14) << itypeToString(gettype())
		<< setw(9) << "From:"
		<< getwho()
		<< endl;
}

void income_record::save(ofstream& out)
{
	out << 1 << " " << fixed << setprecision(2) << money << " " << dt << " " << itype << " " << who << endl;

}

bool income_record::isIncome() const
{
	return true;
}

bool income_record::isSpend() const
{
	return false;
}


