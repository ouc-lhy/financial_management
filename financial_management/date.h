#pragma once
#include<iostream>
using namespace std;
class date{
	private:
		int year;
		int month;
		int day;
	public:
		date();
		date(int y, int m, int d);
		~date();
		int getyear();
		int getmonth();
		int getday();
		void setyear(int y);
		void setmonth(int m);
		void setday(int d);
		friend ostream& operator<<(ostream& out,date dt);
		friend istream& operator>>(istream& in, date& dt);

		friend bool operator>(const date& d1, const date& d2);
		friend bool operator<(const date& d1, const date& d2);
		friend bool operator==(const date& d1, const date& d2);
		friend bool operator!=(const date& d1, const date& d2);
		friend bool operator>=(const date& d1, const date& d2);
		friend bool operator<=(const date& d1, const date& d2);
		
		bool isvalid() const;

};

