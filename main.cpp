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

int main() {
    //Create Tree
    AVLTreeGator avlTree;

    //Collect command count
    unsigned int numOfCommands;
    cout << "Enter the number of commands to execute: ";
    cin >> numOfCommands;

    while (numOfCommands--) {

        string cmd;
        cout << "Enter insert, remove, or search"
        cin >> cmd;

        //Insert Command to store "gatorName" and "gatorId"
        if (cmd == "insert") {
            string gatorName, gatorId;
            cout << "Enter gator name using quotes: "
            cin.ignore();
            getline(cin, gatorName, '\"');
            getline(cin, gatorName, '\"');
            cout << "Enter gator ID: ";
            cin >> gatorId;

            if (!isAlphaOrSpace(gatorName) || !checkId(gatorId) || cin.get() != '\n') {
                cout << "unsuccessful" << endl;
            } else {
                avlTree.insert(gatorName, stol(gatorId));
            }
        }

            //Remove Command to removeAccount node
        else if (cmd == "remove") {
            string gatorId;
            cout << "Enter gator ID: ";
            cin >> gatorId;
            // Handle invalid gatorId removeAccount
            if (!checkId(gatorId) || cin.get() != '\n') {
                cout << "unsuccessful" << endl;
            } else {
                avlTree.remove(stol(gatorId));
            }

        }

            // Search Command to find "gatorName" or "gatorId"
        else if (cmd == "search") {
            string input;
            cout << "Find gator name or gator Id" ;
            cin >> input;

            // Handle Name searchGatorId
            if (input[0] == '\"') {
                if (input[input.length() - 1] == '\"') {
                    input = input.substr(1, input.length() - 2);
                } else {
                    string remainderOfName;
                    cin.ignore();
                    getline(cin, remainderOfName, '\"');
                    input += remainderOfName;
                }
                if (cin.peek() != '\n' && cin.peek() != EOF) {
                    cout << "unsuccessful" << endl;
                } else {
                    avlTree.searchName(input);
                }
            }
                // Handle ID searchGatorId
            else if (checkId(input)) {
                avlTree.searchId(stol(input));
            }
                // Handle invalid searchGatorId
            else {
                cout << "unsuccessful" << endl;
            }
        }

            //Print Command to print tree Inorder
        else if (cmd == "printInorder") {
            if (cin.peek() != '\n' && cin.peek() != EOF) {
                cout << "unsuccessful" << endl;
            } else {
                cin.ignore();
                avlTree.printInorder();
            }
        }

            //Print Command to print tree Preorder
        else if (cmd == "printPreorder") {
            if (cin.peek() != '\n' && cin.peek() != EOF) {
                cout << "unsuccessful" << endl;
            } else {
                cin.ignore();
                avlTree.printPreorder();
            }

            //Print Command to print tree Postorder
        } else if (cmd == "printPostorder") {
            if (cin.peek() != '\n' && cin.peek() != EOF) {
                cout << "unsuccessful" << endl;
            } else {
                cin.ignore();
                avlTree.printPostorder();
            }

            //Print Command to print tree LevelCount
        } else if (cmd == "printLevelCount") {
            if (cin.peek() != '\n' && cin.peek() != EOF) {
                cout << "unsuccessful" << endl;
            } else {
                cin.ignore();
                avlTree.printLevelCount();
            }

            //Remove Command to removeAccount node
        } else if (cmd == "removeInorder") {
            unsigned int count;
            cin >> count;

            if (cin.peek() != '\n' && cin.peek() != EOF) {
                cout << "unsuccessful" << endl;
            } else {
                cin.ignore();
                avlTree.removeInorder(count);
            }
        } else {
            cout << "unsuccessful" << endl;
        }
    }
    return 0;
}