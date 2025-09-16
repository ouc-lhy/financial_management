#pragma once
#include "spend_record.h"
#include <iostream>
#include <string>
using namespace std;
ostream& operator<<(ostream& out, spend_category otype)
{
	out << int(otype);
	return out;
}
istream& operator>>(istream& in, spend_category& st) {
	int value;
	in >> value;
	st = spend_category(value);
	return in;
}

string otypeToString(spend_category otype) {
	switch (otype) {
	case housing:           return "housing";
	case food:              return "food";
	case transport:         return "transport";
	case insurance:         return "insurance";
	case healthcare:        return "healthcare";
	case clothes:			return "clothes";
	case education:         return "education";
	case entertain:         return "entertain";
	case pet:				return "pet";
	case travel:            return "travel";
	case otherspend:        return "otherspend";
	default:                return "unknown";

	}
}

spend_record::spend_record() {
	otype = food;
}

spend_record::spend_record(date dt, double money, string sb, spend_category otype) :record(dt, money, sb), otype(otype) {
}

spend_record::~spend_record() {}

spend_category spend_record::gettype() {
	return otype;
}
void spend_record::settype(spend_category type)
{
	otype = type;
}

ostream& operator<<(ostream& out, spend_record rd) {
	out << 0 << " " << fixed << setprecision(2) << rd.money << " " << rd.dt << " " << rd.otype<< " " << rd.who << endl;
	return out;
}

istream& operator>>(istream& in, spend_record& rd)
{
	in >> rd.money >> rd.dt >> rd.otype;
	in >> ws;
	getline(in, rd.who);
	return in;
}

void spend_record::showrecord() {
	cout << setw(8) << "spend"
		<< setw(12) << fixed <<setprecision(2) << getmoney() << "гд"
		<< setw(9) << getdate()
		<< setw(14) << otypeToString(gettype())
		<< setw(9) << "To:"
		<< getwho()
		<< endl;
}

void spend_record::save(ofstream& out)
{
	out << 0 << " " << fixed << setprecision(2) << money << " " << dt << " " << otype << " " << who << endl;
}

bool spend_record::isIncome() const { return false; }
bool spend_record::isSpend() const { return true; }

