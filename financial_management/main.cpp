#include <iostream>
#include <fstream>
#include "record.h"
#include "income_record.h"
#include "spend_record.h"
#include "recordmanager.h"
#include "menu.h"

using namespace std;

int main() {
    record_manager manager;
    manager.showallrecords();

    int choice;
    
    do {
        showmenu();
        choice = getInput<int>(0, 12);
        menu(choice, manager);
        
        if (choice != 0) {
            cout << "\n--- Press Enter to continue ---";
            while (cin.get() != '\n') {
          
            }
        }

    } while (choice != 0);

    manager.savetofile();
    return 0;
}
