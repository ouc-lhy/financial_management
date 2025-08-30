#include "recordmanager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include "income_record.h"
#include "spend_record.h"
#pragma once
using namespace std;

template<class T>
T getInput(T minVal = -numeric_limits<T>::max(), T maxVal = numeric_limits<T>::max());

date inputdate();

void record_manager::addrecord(record* rd)
{
	records.push_back(rd);
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
		cerr << "Warning: Failed to read target. Using default: " << target << endl;
	}
	in.ignore(); 
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
			addrecord(rd);
		}
	}

	in.close();
	cout << "totally load " << records.size() << " records" << endl;
}

void record_manager::savetofile()
{
	ofstream out(filename);
	out << target << endl;
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
	vector<record*> recordsToModify;

	// ����ƥ��ļ�¼
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

	// ��ʾ�ҵ��ļ�¼
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

	// ѡ��Ҫ�޸ĵļ�¼
	cout << "Select record number to modify (0 to cancel): ";
	int choice = getInput<int>(0, recordsToModify.size());

	if (choice == 0) {
		cout << "Modification cancelled." << endl;
		return;
	}

	record* selectedRecord = recordsToModify[choice - 1];

	// �޸ļ�¼��Ϣ
	cout << "\n=== Modify Record ===" << endl;

	// �޸Ľ��
	cout << "Current money: " << selectedRecord->getmoney() << endl;
	cout << "Enter new money (0 to keep current): ";
	int newMoney = getInput<int>(0); 
	if (newMoney > 0) {
		selectedRecord->setmoney(newMoney);
	}

	// �޸�����
	cout << "Current date: " << selectedRecord->getdate() << endl;
	cout << "Modify date? (1=Yes, 0=No): ";
	int modifyDate = getInput<int>(0, 1);
	if (modifyDate == 1) {
		cout << "Enter new date:" << endl;
		date newDate = inputdate();
		selectedRecord->setdate(newDate);
		cout << "Date updated successfully." << endl;
	}

	// �޸ĶԷ���Ϣ
	cout << "Current To/From: " << selectedRecord->getwho() << endl;
	cout << "Enter new To/From (press Enter to keep current): ";
	string newWho;
	getline(cin, newWho);
	if (!newWho.empty()) {
		selectedRecord->setwho(newWho);
	}

	// �޸����ͣ������֧���ľ������ͣ�
	if (selectedRecord->isIncome()) {
		income_record* incomeRec = dynamic_cast<income_record*>(selectedRecord);
		cout << "Current income type: " << itypeToString(incomeRec->gettype()) << endl;
		cout << "Enter new income type (0-5, -1 to keep current):\n"
			<< "salary=0,business=1,investment=2,interest=3,allowance=4,otherincome=5" << endl;
		int newType = getInput<int>(-1, 5);
		if (newType != -1) {
			incomeRec->settype(static_cast<income_category>(newType));
		}
	}
	else {
		spend_record* spendRec = dynamic_cast<spend_record*>(selectedRecord);
		cout << "Current spend type: " << otypeToString(spendRec->gettype()) << endl;
		cout << "Enter new spend type (0-10, -1 to keep current):\n"
			<< "housing=0,food=1,transport=2,insurance=3,healthcare=4,clothes=5,"
			<< "education=6,entertain=7,pet=8,travel=9,otherspend=10" << endl;
		int newType = getInput<int>(-1, 10);
		if (newType != -1) {
			spendRec->settype(static_cast<spend_category>(newType));
		}
	}

	cout << "Record modified successfully!" << endl;
	savetofile(); // �����޸ĵ��ļ�
}

void record_manager::deletebydate(int y, int m, int d)
{
	vector<record*> recordsToDelete;
	vector<int> indices; // ����ԭʼ����

	// ����ƥ��ļ�¼����¼ԭʼ����
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

	// ��ʾ�ҵ��ļ�¼
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

	// ѡ��ɾ����ʽ
	cout << "\nEnter record number to delete (1-" << recordsToDelete.size() << ")" << endl;
	cout << "Or enter -1 to delete ALL records for this date" << endl;
	cout << "Or enter 0 to cancel: ";

	int choice = getInput<int>(-1, recordsToDelete.size());

	if (choice == 0) {
		cout << "Deletion cancelled." << endl;
		return;
	}

	if (choice == -1) {
		// ɾ�������ڵ����м�¼���Ӻ���ǰɾ�����������仯��
		for (int i = indices.size() - 1; i >= 0; i--) {
			delete records[indices[i]];
			records.erase(records.begin() + indices[i]);
		}
		cout << "All " << recordsToDelete.size() << " records deleted successfully!" << endl;
	}
	else {
		// ɾ��������¼
		int selectedIndex = indices[choice - 1];
		delete records[selectedIndex];
		records.erase(records.begin() + selectedIndex);
		cout << "Record deleted successfully!" << endl;
	}

	savetofile(); // ���浽�ļ�
}


void record_manager::checkbalance()
{
	int totalincome = 0;
	int totalspend = 0;
	for (int i = 0; i < getsize(); i++) {
		if (records[i]->isIncome())
			totalincome += records[i]->getmoney();
		else
			totalspend += records[i]->getmoney();
	}
	int netincome = totalincome - totalspend;
	cout << "total income:" << totalincome << endl;
	cout << "total spend:" << totalspend << endl;
	cout << "net balance:" << (netincome >= 0 ? "+" : "") << netincome << endl;
	cout <<"target:" << target << endl;
	balancewarning();
}

void record_manager::statisticsbyCategory(date dt1, date dt2)
{
	int incomeAmount[6] = { 0 };
	int incomeCount[6] = { 0 };

	int spendAmount[11] = { 0 };
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

	std::cout << "\n--- Income Statistics ---\n";
	bool hasIncome = false;
	for (int i = 0; i < 6; i++) {
		if (incomeAmount[i] > 0) {
			std::cout << std::setw(15) << std::left << itypeToString((income_category)i)
				<< ": " << incomeAmount[i] << "�� (" << incomeCount[i] << " times)\n";
			hasIncome = true;
		}
	}
	if (!hasIncome) {
		std::cout << "No income records.\n";
	}
	std::cout << "\n--- Spend Statistics ---\n";
	bool hasSpend = false;
	for (int i = 0; i < 11; i++) {
		if (spendAmount[i] > 0) {
			std::cout << std::setw(15) << std::left << otypeToString((spend_category)i)
				<< ": " << spendAmount[i] << "�� (" << spendCount[i] << " times)\n";
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
	int totalincome = 0;
	int totalspend = 0;
	for (int i = 0; i < getsize(); i++) {
		if (records[i]->isIncome())
			totalincome += records[i]->getmoney();
		else
			totalspend += records[i]->getmoney();
	}
	int netincome = totalincome - totalspend;
	if(netincome<0)
		cout << "Warning: You are overspending! (Net: " << netincome << "��)" << endl;
	if (netincome >= target) {
		cout << "Congratulations! You've reached your financial goal: " << target << "��!" << endl;
	}
	else {
		cout << "Goal: " << target << "��, Need: " << (target - netincome) << "�� more." << endl;
	}
}

int record_manager::gettarget()
{
	return target;
}

void record_manager::settarget(int et)
{
	target = et;
}


int record_manager::get_sorttype() const { return sorttype; }

void record_manager::set_sorttype(int st) { sorttype = st; }

record_manager::record_manager() :sorttype(0),target(10000)
{
	loadfromfile();
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

record_manager::~record_manager() {
	savetofile();
	for (int i = 0; i < getsize(); i++) {
		delete records[i];
	}
	records.clear();
}

