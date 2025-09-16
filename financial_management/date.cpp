#pragma once
#include "date.h"
#include <ctime>
using namespace std;
date::date() :year(2000), month(1), day(1) {
}

date::date(int y , int m, int d) :year(y), month(m), day(d){
}

date::~date() {
}
int date::getyear() {
	return year;
}
int date::getmonth() {
	return month;
}
int date::getday() {
	return day;
}
void date::setyear(int y) {
	year = y;
}
void date::setmonth(int m) {
	month = m;
}
void date::setday(int d) {
	day = d;
}

ostream& operator<<(ostream& out, date dt) {
	out << dt.getyear() << "/" << ((dt.getmonth()) < 10 ? "0" : "") << dt.getmonth() << "/" << ((dt.getday()) < 10 ? "0" : "") << dt.getday() ;
	return out;
}


istream& operator>>(istream& in, date& dt)
{
	char slash;
	in >> dt.year >> slash >> dt.month >> slash >> dt.day;
	return in;
}

bool operator>(const date& d1, const date& d2) {
	if (d1.year != d2.year) {
		return d1.year > d2.year;
	}
	else if (d1.month != d2.month) {
		return d1.month > d2.month;
	}
	else{
		return d1.day > d2.day;
	}
}

bool operator==(const date& d1, const date& d2) {
	if (d1.year != d2.year) {
		return false;
	}
	else if (d1.month != d2.month) {
		return false;
	}
	else if (d1.day != d2.day) {
		return false;
	}
	else return true;
}

bool operator<(const date& d1, const date& d2) {
	return d2 > d1;
}

bool operator<=(const date& d1, const date& d2) {
	return !(d1 > d2);
}

bool operator>=(const date& d1, const date& d2) {
	return d1 > d2 || d1 == d2;
}

bool operator!=(const date& d1, const date& d2) {
	return !(d1 == d2);
}
bool date::isvalid() const {
	if (year < 1000) {
		return false;
	}
	if (month < 1 || month > 12) {
		return false;
	}

	int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		daysInMonth[2] = 29;
	}

	if (day < 1 || day > daysInMonth[month]) {
		return false;
	}

	time_t now = time(0);
	struct tm current_time_struct = {};
	errno_t err = localtime_s(&current_time_struct, &now);
	if (err != 0) {
		cerr << "fail to get current date"<<endl;
		return false;
	}
	date current_date(current_time_struct.tm_year + 1900,
		current_time_struct.tm_mon + 1,
		current_time_struct.tm_mday);

	if (*this > current_date) {
		return false;
	}
	
	return true;

}