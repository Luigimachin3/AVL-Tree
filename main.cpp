//Project 1 --Luis Martinez

#include "AVLTreeGator.h"

// Helper Functions
bool isAlphaOrSpace(string &name) {
    int length = name.length();
    for (int i = 0; i < length; i++) {
        char currentChar = name[i];
        if ((currentChar < 'a' || currentChar > 'z') &&
            (currentChar < 'A' || currentChar > 'Z') &&
            currentChar != ' ') {
            return false;
        }
    }
    return true;
}

bool checkId(string inputId) {
    if (inputId.length() != 8) {
        return false;
    }

    for (int i = 0; i < 8; i++) {
        if (inputId[i] < '0' || inputId[i] > '9') {
            return false;
        }
    }
    return true;
}

void mainMenu() {
    cout << "\n====== LIST OF COMMANDS ======\n";
    cout << "1. Insert (\"Name\" + ID)\n";
    cout << "2. Remove by ID\n";
    cout << "3. Search by ID\n";
    cout << "4. Search by Name\n";
    cout << "5. Print Inorder\n";
    cout << "6. Print Preorder\n";
    cout << "7. Print Postorder\n";
    cout << "8. Print Level Count\n";
    cout << "9. Remove by Inorder Position\n";
    cout << "0. Exit\n";
    cout << "=============================\n" << endl;
}

int main() {
    AVLTreeGator avlTree;
    string input;

    cout << "Welcome to the AVL Gator Tree!" << endl;
    mainMenu();

    while (true) {
        cout << "\nEnter command (1-9, 0 to exit, or type 'm' to see the menu): ";
        getline(cin, input);

        if (input == "0") {
            cout << "Goodbye" << endl;
            break;
        }

        if (input == "m" || input == "M") {
            mainMenu();
            continue;
        }

        int choice;
        try {
            choice = stoi(input);
        } catch (...) {
            cout << "Invalid option. Type 'm' to see the menu again." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                cout << "Enter name in quotes and 8-digit-ID (e.g., \"Bob\" 12345678): ";
                string gatorName, gatorId;
                getline(cin, gatorName, '"');
                getline(cin, gatorName, '"');
                cin >> gatorId;
                cin.ignore();
                if (!isAlphaOrSpace(gatorName) || !checkId(gatorId)) {
                    cout << "unsuccessful" << endl;
                } else {
                    avlTree.insert(gatorName, stol(gatorId));
                }
                break;
            }
            case 2: {
                cout << "Enter 8-digit ID to remove: ";
                string id;
                cin >> id;
                cin.ignore();
                if (!checkId(id)) cout << "unsuccessful" << endl;
                else avlTree.remove(stol(id));
                break;
            }
            case 3: {
                cout << "Enter 8-digit ID to search: ";
                string id;
                cin >> id;
                cin.ignore();
                if (!checkId(id)) cout << "unsuccessful" << endl;
                else avlTree.searchId(stol(id));
                break;
            }
            case 4: {
                cout << "Enter name in quotes to search: ";
                string name;
                getline(cin, name, '"');
                getline(cin, name, '"');
                if (!isAlphaOrSpace(name)) cout << "unsuccessful" << endl;
                else avlTree.searchName(name);
                cin.ignore();
                break;
            }
            case 5:
                avlTree.printInorder();
                break;
            case 6:
                avlTree.printPreorder();
                break;
            case 7:
                avlTree.printPostorder();
                break;
            case 8:
                avlTree.printLevelCount();
                break;
            case 9: {
                cout << "Enter position to remove: ";
                int pos;
                cin >> pos;
                cin.ignore();
                avlTree.removeInorder(pos);
                break;
            }
            default:
                cout << "Invalid option. Type 'm' to see the menu again." << endl;
        }
    }
    return 0;
}