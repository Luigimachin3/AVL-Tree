//Project 1 --Luis Martinez

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;


class AVLTreeGator {
private:
    //Struct for the node of the tree which will hold the student's gatorName and gatorId
    struct studentNode {
        string gatorName;
        unsigned int gatorId;
        unsigned int height;
        studentNode *left;
        studentNode *right;

        //Constructor with parameters
        studentNode(string name, int id);
    };

    // Root of the tree
    studentNode *root;
    // Height
    unsigned int height(studentNode *node);
    // Function to balance the tree
    studentNode *balanceTree(studentNode *root);

    // Insert function to insert a new node
    studentNode *insertNameId(studentNode *root, string studentName, unsigned int studentId);

    //Remove account and remove node for destructor
    studentNode *removeAccount(studentNode *root, unsigned int studentId);
    void removeNode(studentNode *root);

    //Search functions to find a node by gatorId or gatorName
    studentNode *searchGatorId(studentNode *root, unsigned int targetId);
    studentNode *searchNameId(studentNode *root, string targetName, bool &isFound);

    //Rotation Tools
    studentNode *rotateLeft(studentNode *node);
    studentNode *rotateRight(studentNode *node);
    studentNode *rotateLeftRight(studentNode *node);
    studentNode *rotateRightLeft(studentNode *node);

    //Print Functions to print the tree in order, pre-order, and post order
    void printInorder(studentNode *node, vector<studentNode *> &inorder);
    void printPreorder(studentNode *node, vector<studentNode *> &preorder);
    void printPostorder(studentNode *node, vector<studentNode *> &postorder);

public:
    // Constructor and Destructor of AVLTreeGator
    AVLTreeGator();
    ~AVLTreeGator();

    //Insert public function that uses the private insert function
    void insert(string gatorName, unsigned int gatorId);

    // Search public functions that uses the private search functions
    void searchId(unsigned int gatorId);
    void searchName(string gatorName);

    //Print Functions that uses the private print functions
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();

    // Remove public function that uses the private remove function
    void removeInorder(unsigned int position);
    void remove(unsigned int gatorId);
};
