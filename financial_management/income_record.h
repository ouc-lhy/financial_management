#include"record.h"
#include <string>
#pragma once
enum income_category{
	salary=0,business,investment,interest,allowance,otherincome
};
string itypeToString(income_category itype);
ostream& operator<<(ostream& out, income_category itype);
istream& operator>>(istream& in, income_category& it);

class income_record:public record{
	private:
		income_category itype;
	public:
		income_record();
		income_record(date dt, double money, income_category itype,string sb);
		~income_record();
		income_category gettype();
		void settype(income_category type);
		friend ostream& operator<<(ostream& out, income_record rd);
		friend istream& operator>>(istream& in, income_record& rd);
		void showrecord() override;
		void save(ofstream& out);
		virtual bool isIncome() const; 
		virtual bool isSpend() const;

};
