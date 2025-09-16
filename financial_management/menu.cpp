#include "menu.h"
#include <iostream>
#include <limits>
using namespace std;

date inputdate() {
    int y, m, d;
    while (true) {
        cout << "year: ";
        y = getInput<int>(1000, 9999);
        cout << "Month: ";
        m = getInput<int>(1, 12);
        cout << "Day: ";
        d = getInput<int>(1, 31);
        
        date dt(y, m, d);
        if (dt.isvalid()) {
            return dt;
        }
        cout << "invalid date, please enter again" << endl;
    }
}

void inputdaterange(date& start, date& end) {
    int y, m, d;
    int y0, m0, d0;

    while(true) {
        cout << "Start date - Year (-1 for no start limit): ";
        y = getInput<int>(-1, 9999);
        if (y == -1) {
            start = date(-1, 1, 1);
            break;
        } else {
            cout << "Month: ";
            m = getInput<int>(1, 12);
            cout << "Day: ";
            d = getInput<int>(1, 31);
            start = date(y, m, d);
            if (start.getyear() != -1 && !start.isvalid()) {
                cout << "Invalid start date." << endl;
            } else {
                break;
            }
        }
    }

    while(true) {
        cout << "End date - Year (-1 for no end limit): ";
        y0 = getInput<int>(-1, 9999);
        if (y0 == -1) {
            end = date(-1, 12, 31);
            break;
        } else {
            cout << "Month: ";
            m0 = getInput<int>(1, 12);
            cout << "Day: ";
            d0 = getInput<int>(1, 31);
            end = date(y0, m0, d0);
            if (end.getyear() != -1 && !end.isvalid()) {
                cout << "Invalid end date." << endl;
            } else if (start.getyear() != -1 && y0 != -1 && end < start) {
                cout << "Invalid. end date can not be earlier than start date" << endl;
            } else {
                break;
            }
        }
    }
}

string inputwho() {
    string who;
    while (true) {
        getline(cin, who);
        if (who.find_first_not_of(" \t\n\r") != string::npos) {
            return who; 
        }
        cout << "Name cannot be empty! Please enter again: ";
    }
}

void showmenu() {
    cout << "\n================================================" << endl;
    cout << "          Personal Finance Management System" << endl;
    cout << "================================================" << endl;
    cout << "1 - Add Income Record" << endl;
    cout << "2 - Add Spending Record" << endl;
    cout << "3 - View Income Records within Date Range" << endl;
    cout << "4 - View Spending Records within Date Range" << endl;
    cout << "5 - Check Real-time Balance" << endl;
    cout << "6 - Search Records by Date" << endl;
    cout << "7 - Modify Records by Date" << endl;
    cout << "8 - Delete Records by Date" << endl;
    cout << "9 - Statistics by Category within Date Range" << endl;
    cout << "10 - Showallrecords" << endl;
    cout << "11 - Set sort type" << endl;
    cout << "12 - Set expect target" << endl;
    cout << "0 - Exit System" << endl;
    cout << "================================================" << endl;
    cout << "Please select operation (0-12): ";
}

void menu(int choice, record_manager& manager) {
    switch (choice) {
        case 1: {
            cout << "please enter money: ";
            double money = getInput<double>(0.01,99999999.99);
            date dt = inputdate();
            
            cout << "please enter type:\nsalary=0,business=1,investment=2,interest=3,allowance=4,otherincome=5" << endl;
            int it_val = getInput<int>(0, 5);
            income_category it = static_cast<income_category>(it_val);

            cout << "please enter fromwho: ";
            string who;
            who=inputwho();

            income_record* ird = new income_record(dt, money, it, who);
            manager.addrecord(ird);
            manager.balancewarning();
            manager.savetofile();
            break;
        }

        case 2: {
            cout << "please enter money: ";
            double money = getInput<double>(0.01,99999999.99);
            date dt = inputdate();
            
            cout << "please enter type:\nhousing=0,food=1,transport=2,insurance=3,healthcare=4,clothes=5,education=6,entertain=7,pet=8,travel=9,otherspend=10" << endl;
            int st_val = getInput<int>(0, 10);
            spend_category st = static_cast<spend_category>(st_val);

            cout << "please enter towho: ";
            string who;
            who = inputwho();
            
            spend_record* srd = new spend_record(dt, money, who, st);
            manager.addrecord(srd);
            manager.balancewarning();
            manager.savetofile(); 
            break;
        }

        case 3: {
            date dt1, dt2;
            inputdaterange(dt1, dt2);
            manager.viewincomerecords(dt1, dt2);
            break;
        }

        case 4: {
            date dt1, dt2;
            inputdaterange(dt1, dt2);
            manager.viewspendrecords(dt1, dt2);
            break;
        }

        case 5: {
            manager.checkbalance();
            break;
        }

        case 6: {
            date dt = inputdate();
            manager.searchbydate(dt.getyear(), dt.getmonth(), dt.getday());
            break;
        }
   
        case 7: {
            cout << "Modify Record by Date" << endl;
            date targetDate = inputdate();
            manager.modifybydate(targetDate.getyear(), targetDate.getmonth(), targetDate.getday());
            break;
        }

        case 8: {
            date dt = inputdate();
            manager.deletebydate(dt.getyear(), dt.getmonth(), dt.getday());
            manager.balancewarning();
            break;
        }

        case 9: {
            date dt1, dt2;
            inputdaterange(dt1, dt2);
            manager.statisticsbyCategory(dt1, dt2);
            break;
        }

        case 10: {
            manager.showallrecords();
            break;
        }

        case 11: {
            cout << "\ncurrent sort type:" << manager.sortTypeToString()<<endl<<endl;
            cout << "please enter new sort type: \n" << "money_ascend = 1, money_descend = 2, type_ascend = 3, date_ascend = 4, date_descend = 5" << endl;
            int sorttype = getInput<int>(1, 5);
            manager.set_sorttype(sorttype);
            break;
        }
        case 12: {
            cout << "please enter the expect target you want to set" << endl;
            cout << "expect target:";
            double newtarget;
            newtarget=getInput<double>(0.01);
            manager.settarget(newtarget);
            manager.balancewarning();
            break;
        }
        case 0: {
            cout << "\nThank you for using Personal Finance Management System. Goodbye!" << endl;
            break;
        }

        default: {
            cout << "\nInvalid input, please select again (0-12)!" << endl;
            break;
        }
    }
}
