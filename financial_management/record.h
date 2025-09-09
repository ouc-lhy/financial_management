#include"date.h"
#include<iostream>
#include <fstream>
#include<iomanip>
#pragma once
const string filename = "records.txt";
using namespace std;

class record{
	protected:
		date dt;
		double money;
		string who;
	public:
		record();
		record(date dt,double m,string sb);
		virtual ~record();
		date getdate();
		void setdate(date dt1);
		double getmoney();
		void setmoney(double m);
		string getwho();
		void setwho(string sb);

		virtual  void showrecord()=0;
		virtual void save(ofstream& out)= 0;
		virtual bool isIncome() const = 0;
		virtual bool isSpend() const = 0;

};

