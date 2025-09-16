#include "recordmanager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include "income_record.h"
#include "spend_record.h"
using namespace std;

template<class T>
T getInput(T minVal = -numeric_limits<T>::max(), T maxVal = numeric_limits<T>::max());

date inputdate();

string inputwho();

string record_manager::sortTypeToString() const {
	switch (sorttype) {
	case 1: return "Money Ascending";
	case 2: return "Money Descending";
	case 3: return "Type Order";
	case 4: return "Date Ascending";
	case 5: return "Date Descending";
	default: return "Default: Date Ascending";
	}
}

void record_manager::addrecord(record* rd)
{
	records.push_back(rd);
	sort_records();
	cout << "Record added successfully!" << endl;
}

void record_manager::showallrecords()
{
	if (getsize() == 0) {
		cout << "no records" << endl;
		return;
	}
	cout << setw(12) << "type"
		<< setw(13) << "money"
		<< setw(16) << "date"
		<< setw(14) << "category"
		<< setw(9) << "    To/From:"
		<< endl;
	sort_records();
	for (int i = 0; i < getsize(); i++) {
		cout << setw(4) << i + 1;
		records[i]->showrecord();
	}
}

void record_manager::loadfromfile() {
	ofstream create(filename, ios::app);
	create.close();
	ifstream in(filename);
	if (!in) {
		cerr << "can not open file" << endl;
		return;
	}
	if (!(in >> target)) {
		target = 10000;
		in.clear();
		in.ignore();
		cerr << "Warning: Failed to read target. Using default: " << target << endl;
	}

	if (!(in >> sorttype)) {
		sorttype = 4; 
		in.clear();
		in.ignore();
		cerr << "Warning: Failed to read sorttype. Using default: " << sorttype << endl;
	}

	int type;
	while (in >> type) {
		record* rd = nullptr;

		if (type == 0) {
			spend_record* s = new spend_record();
			in >> *s;
			rd = s;
		}
		else if (type == 1) {
			income_record* i = new income_record();
			in >> *i;
			rd = i;
		}

		if (rd) {
			records.push_back(rd);
		}
	}
	in.close();
	cout << "totally load " << records.size() << " records" << endl;
	cout << "target:" << fixed << setprecision(2)<<target << endl;
	cout << "sort type:" << sortTypeToString() << endl;
}

void record_manager::savetofile()
{
	sort_records();
	ofstream out(filename);
	out << fixed << setprecision(2)<<target << endl;
	out << sorttype << endl;
	for (int i = 0; i < getsize(); i++) {
		records[i]->save(out);
	}
	out.close();
}

void record_manager::viewincomerecords(date dt1, date dt2)
{
	cout << setw(12) << "type"
		<< setw(13) << "money"
		<< setw(16) << "date"
		<< setw(14) << "category"
		<< setw(9) << "    To/From:"
		<< endl;
		
	sort_records();
	int count = 1;
	if (dt1.getyear() != -1 && dt2.getyear() != -1) {
		for (int i = 0; i < getsize(); i++) {
			if (records[i]->getdate() >= dt1 && records[i]->getdate() <= dt2 && records[i]->isIncome()) {
				cout << setw(4) << count++;
				records[i]->showrecord();
			}
		}
	}
	else if (dt1.getyear() == -1 && dt2.getyear() == -1) {
		for (int i = 0; i < getsize(); i++) {
			if (records[i]->isIncome()) {
				cout << setw(4) << count++;
				records[i]->showrecord();
			}
		}
	}
	else if (dt1.getyear() == -1) {
		for (int i = 0; i < getsize(); i++) {
			if (records[i]->getdate() <= dt2 && records[i]->isIncome()) {
				cout << setw(4) << count++;
				records[i]->showrecord();
			}
		}
	}
	else {
		for (int i = 0; i < getsize(); i++) {
			if (records[i]->getdate() >= dt1 && records[i]->isIncome()) {
				cout << setw(4) << count++;
				records[i]->showrecord();
			}
		}
	}
	if (count == 1) {
		cout << "No income_ records found in the specified date range." << endl;
	}
}

void record_manager::viewspendrecords(date dt1, date dt2)
{
	cout << setw(12) << "type"
		<< setw(13) << "money"
		<< setw(16) << "date"
		<< setw(14) << "category"
		<< setw(9) << "    To/From:"
		<< endl;
	sort_records();
	int count = 1;
	if (dt1.getyear() != -1 && dt2.getyear() != -1) {
		for (int i = 0; i < getsize(); i++) {
			if (records[i]->getdate() >= dt1 && records[i]->getdate() <= dt2 && records[i]->isSpend()) {
				cout << setw(4) << count++;
				records[i]->showrecord();
			}
		}
	}
	else if (dt1.getyear() == -1 && dt2.getyear() == -1) {
		for (int i = 0; i < getsize(); i++) {
			if (records[i]->isSpend()) {
				cout << setw(4) << count++;
				records[i]->showrecord();
			}
		}
	}
	else if (dt1.getyear() == -1) {
		for (int i = 0; i < getsize(); i++) {
			if (records[i]->getdate() <= dt2 && records[i]->isSpend()) {
				cout << setw(4) << count++;
				records[i]->showrecord();
			}
		}
	}
	else {
		for (int i = 0; i < getsize(); i++) {
			if (records[i]->getdate() >= dt1 && records[i]->isSpend()) {
				cout << setw(4) << count++;
				records[i]->showrecord();
			}
		}
	}
	if (count == 1) {
		cout << "No spend_ records found in the specified date range." << endl;
	}
}

void record_manager::searchbydate(int y, int m, int d)
{
	cout << setw(12) << "type"
		<< setw(13) << "money"
		<< setw(16) << "date"
		<< setw(14) << "category"
		<< setw(9) << "    To/From:"
		<< endl;
	int count = 1;
	sort_records();
	for (int i = 0; i < getsize(); i++) {
		if (records[i]->getdate().getyear() == y && records[i]->getdate().getmonth() == m && records[i]->getdate().getday() == d) {
			cout << setw(4) << count++;
			records[i]->showrecord();
		}
	}
	if (count == 1) {
		cout << "No records found in the specified date." << endl;
	}
}

void record_manager::modifybydate(int y, int m, int d)
{
	sort_records();
	vector<record*> recordsToModify;

	for (int i = 0; i < getsize(); i++) {
		if (records[i]->getdate().getyear() == y &&
			records[i]->getdate().getmonth() == m &&
			records[i]->getdate().getday() == d) {
			recordsToModify.push_back(records[i]);
		}
	}

	if (recordsToModify.empty()) {
		cout << "No records found for date " << y << "/" << m << "/" << d << endl;
		return;
	}

	cout << "Found " << recordsToModify.size() << " records for date " << y << "/" << m << "/" << d << ":" << endl;
	cout << setw(12) << "type"
		<< setw(13) << "money"
		<< setw(16) << "date"
		<< setw(14) << "category"
		<< setw(9) << "    To/From:"
		<< endl;

	for (int i = 0; i < recordsToModify.size(); i++) {
		cout << setw(4) << i + 1;
		recordsToModify[i]->showrecord();
	}

	cout << "Select record number to modify (0 to cancel): ";
	int choice = getInput<int>(0, recordsToModify.size());

	if (choice == 0) {
		cout << "Modification cancelled." << endl;
		return;
	}

	record* selectedRecord = recordsToModify[choice - 1];

	cout << "\n=== Modify Record ===" << endl;

	cout << "Current money: " << selectedRecord->getmoney() << endl;
	cout << "Modify money? (1=Yes, 0=No): ";
	int modifyMoney = getInput<int>(0, 1);
	if (modifyMoney == 1) {
		cout << "Enter new money: ";
		double newMoney = getInput<double>(0.01, 99999999.99);
		selectedRecord->setmoney(newMoney);
		cout << "Money updated successfully." << endl;
	}


	cout << "Current date: " << selectedRecord->getdate() << endl;
	cout << "Modify date? (1=Yes, 0=No): ";
	int modifyDate = getInput<int>(0, 1);
	if (modifyDate == 1) {
		cout << "Enter new date:" << endl;
		date newDate = inputdate();
		selectedRecord->setdate(newDate);
		cout << "Date updated successfully." << endl;
	}

	cout << "Current To/From: " << selectedRecord->getwho() << endl;
	cout << "Modify To/From? (1=Yes, 0=No): ";
	int modifyWho = getInput<int>(0, 1);
	if (modifyWho == 1) {
		cout << "Enter new To/From: ";
		string newWho = inputwho();
		selectedRecord->setwho(newWho);
		cout << "To/From updated successfully." << endl;
	}

	if (selectedRecord->isIncome()) {
		income_record* incomeRec = dynamic_cast<income_record*>(selectedRecord);
		cout << "Current income type: " << itypeToString(incomeRec->gettype()) << endl;
		cout << "Modify income type? (1=Yes, 0=No): ";
		int modifyType = getInput<int>(0, 1);
		if (modifyType == 1) {
			cout << "Enter new income type (0-5):\n"
				<< "salary=0, business=1, investment=2, interest=3, allowance=4, otherincome=5: ";
			int newType = getInput<int>(0, 5);
			incomeRec->settype(static_cast<income_category>(newType));
			cout << "Income type updated successfully." << endl;
		}
	}
	else {
		spend_record* spendRec = dynamic_cast<spend_record*>(selectedRecord);
		cout << "Current spend type: " << otypeToString(spendRec->gettype()) << endl;
		cout << "Modify spend type? (1=Yes, 0=No): ";
		int modifyType = getInput<int>(0, 1);
		if (modifyType == 1) {
			cout << "Enter new spend type (0-10):\n"
				<< "housing=0, food=1, transport=2, insurance=3, healthcare=4,\n"
				<< "clothes=5, education=6, entertain=7, pet=8, travel=9, otherspend=10:\n";
			int newType = getInput<int>(0, 10);
			spendRec->settype(static_cast<spend_category>(newType));
			cout << "Spend type updated successfully." << endl;
		}
	}

	cout << "Record modified successfully!" << endl;

	if(modifyMoney == 1)balancewarning();

	sort_records();
	savetofile(); 
}

void record_manager::deletebydate(int y, int m, int d)
{
	sort_records();
	vector<record*> recordsToDelete;
	vector<int> indices;

	for (int i = 0; i < getsize(); i++) {
		if (records[i]->getdate().getyear() == y &&
			records[i]->getdate().getmonth() == m &&
			records[i]->getdate().getday() == d) {
			recordsToDelete.push_back(records[i]);
			indices.push_back(i);
		}
	}

	if (recordsToDelete.empty()) {
		cout << "No records found for date " << y << "/" << m << "/" << d << endl;
		return;
	}

	cout << "Found " << recordsToDelete.size() << " records for date " << y << "/" << m << "/" << d << ":" << endl;
	cout << setw(12) << "type"
		<< setw(13) << "money"
		<< setw(16) << "date"
		<< setw(14) << "category"
		<< setw(9) << "    To/From:"
		<< endl;

	for (int i = 0; i < recordsToDelete.size(); i++) {
		cout << setw(4) << i + 1;
		recordsToDelete[i]->showrecord();
	}

	cout << "\nEnter record number to delete (1-" << recordsToDelete.size() << ")" << endl;
	cout << "Or enter -1 to delete ALL records for this date" << endl;
	cout << "Or enter 0 to cancel: ";

	int choice = getInput<int>(-1, recordsToDelete.size());

	if (choice == 0) {
		cout << "Deletion cancelled." << endl;
		return;
	}

	if (choice == -1) {
		cout << "\n You are about to delete ALL " << recordsToDelete.size()
			<< " records on " << y << "/" << m << "/" << d << "." << endl;
		cout << "This action cannot be undone. Confirm? (1=Yes, 0=No): ";
		int confirm = getInput<int>(0, 1);
		if (confirm != 1) {
			cout << "Deletion cancelled." << endl;
			return;
		}

		for (int i = indices.size() - 1; i >= 0; i--) {
			delete records[indices[i]];
			records.erase(records.begin() + indices[i]);
		}
		cout << "All " << recordsToDelete.size() << " records deleted successfully!" << endl;
	}
	else {
		record* selected = recordsToDelete[choice - 1];
		cout << "\n You are about to delete the following record:" << endl;
		cout << setw(4) << 1;
		selected->showrecord();
		cout << "This action cannot be undone. Confirm? (1=Yes, 0=No): ";
		int confirm = getInput<int>(0, 1);
		if (confirm != 1) {
			cout << "Deletion cancelled." << endl;
			return;
		}

		int selectedIndex = indices[choice - 1];
		delete records[selectedIndex];
		records.erase(records.begin() + selectedIndex);
		cout << "Record deleted successfully!" << endl;
	}

	sort_records();
	savetofile(); 
}

void record_manager::checkbalance()
{
	double totalincome = 0;
	double totalspend = 0;
	for (int i = 0; i < getsize(); i++) {
		if (records[i]->isIncome())
			totalincome += records[i]->getmoney();
		else
			totalspend += records[i]->getmoney();
	}
	double netincome = totalincome - totalspend;
	cout << "total income:" << totalincome << endl;
	cout << "total spend:" << totalspend << endl;
	cout << "net balance:" << (netincome >= 0 ? "+" : "") << netincome << endl;
	cout <<"target:" << target << endl;
	balancewarning();
}

void record_manager::statisticsbyCategory(date dt1, date dt2)
{
	double incomeAmount[6] = { 0 };
	int incomeCount[6] = { 0 };

	double spendAmount[11] = { 0 };
	int spendCount[11] = { 0 };

	for (int i = 0; i < getsize(); i++) {
		record* rd = records[i];
		date dt = rd->getdate();

		bool inRange = true;
		if (dt1.getyear() != -1 && dt < dt1) {
			inRange = false;
		}
		if (dt2.getyear() != -1 && dt > dt2) {
			inRange = false;
		}
		if (!inRange) continue;

		if (rd->isIncome()) {
			income_record* ir = (income_record*)rd;
			income_category it = ir->gettype();
			if (it >= 0 && it <= 5) {
				incomeAmount[it] += rd->getmoney();
				incomeCount[it]++;
			}
		}
		else if (rd->isSpend()) {
			spend_record* sr = (spend_record*)rd;
			spend_category st = sr->gettype();
			if (st >= 0 && st <= 10) {
				spendAmount[st] += rd->getmoney();
				spendCount[st]++;
			}
		}
	}

	double totalIncome = 0, totalSpend = 0;
	for (int i = 0; i < 6; i++) totalIncome += incomeAmount[i];
	for (int i = 0; i < 11; i++) totalSpend += spendAmount[i];

	std::cout << "\n--- Income Statistics ---\n";
	if (totalIncome > 0) {
		std::cout << std::setw(16) << "Category"
			<< std::setw(16) << "Amount(гд)"
			<< std::setw(8) << "Times"
			<< std::setw(14) << "Percent(%)"
			<< std::setw(14) << "Avg(гд)"
			<< std::endl;
		std::cout << std::string(68, '-') << std::endl; 
	}

	bool hasIncome = false;
	for (int i = 0; i < 6; i++) {
		if (incomeAmount[i] > 0) {
			double percentage = (totalIncome > 0) ? (incomeAmount[i] / totalIncome * 100.0f) : 0.0f;
			double avgPerTransaction = (incomeCount[i] > 0) ? (incomeAmount[i] / incomeCount[i]) : 0.0f;
			std::cout << std::setw(16) << itypeToString((income_category)i)
				<< std::fixed << std::setprecision(2)
				<< std::setw(16) << incomeAmount[i]
				<< std::setw(8) << incomeCount[i]
				<< std::setprecision(3)
				<< std::setw(14) << percentage
				<< std::setprecision(2)
				<< std::setw(14) << avgPerTransaction
				<< std::endl;
			hasIncome = true;
		}
	}
	if (!hasIncome) {
		std::cout << "No income records.\n";
	}

	std::cout << "\n--- Spend Statistics ---\n";
	if (totalSpend > 0) {
		std::cout << std::setw(16) << "Category"
			<< std::setw(16) << "Amount(гд)"
			<< std::setw(8) << "Times"
			<< std::setw(14) << "Percent(%)"
			<< std::setw(14) << "Avg(гд)"
			<< std::endl;
		std::cout << std::string(68, '-') << std::endl;
	}

	bool hasSpend = false;
	for (int i = 0; i < 11; i++) {
		if (spendAmount[i] > 0) {
			double percentage = (totalSpend > 0) ? (spendAmount[i] / totalSpend * 100.0f) : 0.0f;
			double avgPerTransaction = (spendCount[i] > 0) ? (spendAmount[i] / spendCount[i]) : 0.0f;
			std::cout << std::setw(16) << otypeToString((spend_category)i)
				<< std::fixed << std::setprecision(2)
				<< std::setw(16) << spendAmount[i]
				<< std::setw(8) << spendCount[i]
				<< std::setprecision(3)
				<< std::setw(14) << percentage
				<< std::setprecision(2)
				<< std::setw(14) << avgPerTransaction
				<< std::endl;
			hasSpend = true;
		}
	}
	if (!hasSpend) {
		std::cout << "No spend records.\n";
	}
}

int record_manager::getsize()
{
	return records.size();
}

void record_manager::balancewarning()
{
	double totalincome = 0;
	double totalspend = 0;
	for (int i = 0; i < getsize(); i++) {
		if (records[i]->isIncome())
			totalincome += records[i]->getmoney();
		else
			totalspend += records[i]->getmoney();
	}
	double netincome = totalincome - totalspend;
	if(netincome<0)
		cout << "\nWarning: You are overspending! (Net: " << netincome << "гд)" << endl;
	else if (netincome >= target) {
		cout << "\nCongratulations! You've reached your financial goal: " << target << "гд!" << endl;
	}
	else {
		cout << "\nGoal: " << target << "гд, Need: " << (target - netincome) << "гд more." << endl;
	}
}

double record_manager::gettarget()
{
	return target;
}

void record_manager::settarget(double et)
{
	target = et;
	savetofile();
}


int record_manager::get_sorttype() const { return sorttype; }

void record_manager::set_sorttype(int st) {
	sorttype = st;
	savetofile();
}

bool compare_by_date_asc(record* a, record* b) {
	return a->getdate() < b->getdate();
}

bool compare_by_date_desc(record* a, record* b) {
	return a->getdate() > b->getdate();
}

bool compare_by_money_asc(record* a, record* b) {
	return a->getmoney() < b->getmoney();
}

bool compare_by_money_desc(record* a, record* b) {
	return a->getmoney() > b->getmoney();
}

bool compare_by_type(record* a, record* b) {
	if (a->isIncome() && !b->isIncome()) return true;
	if (!a->isIncome() && b->isIncome()) return false;

	if (a->isIncome() && b->isIncome()) {
		return ((income_record*)a)->gettype() < ((income_record*)b)->gettype();
	}

	if (!a->isIncome() && !b->isIncome()) {
		return ((spend_record*)a)->gettype() < ((spend_record*)b)->gettype();
	}

	return false;
}

void record_manager::sort_records() {
	switch (sorttype) {
	case 1: sort(records.begin(), records.end(), compare_by_money_asc); break;
	case 2: sort(records.begin(), records.end(), compare_by_money_desc); break;
	case 3: sort(records.begin(), records.end(), compare_by_type); break;
	case 4: sort(records.begin(), records.end(), compare_by_date_asc); break;
	case 5: sort(records.begin(), records.end(), compare_by_date_desc); break;
	default: sort(records.begin(), records.end(), compare_by_date_asc);
	}
}

record_manager::record_manager() :sorttype(4), target(10000)
{
	loadfromfile();
}


record_manager::~record_manager() {
	for (int i = 0; i < getsize(); i++) {
		delete records[i];
	}
	records.clear();
}

