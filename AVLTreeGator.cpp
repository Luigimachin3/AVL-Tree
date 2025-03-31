//Project 1 --Luis Martinez

#include "AVLTreeGator.h"
#include "iomanip"

AVLTreeGator::studentNode::studentNode(string name, int id) {
    this->gatorName = name;
    this->gatorId = id;
    this->height = 1;
    left = nullptr;
    right = nullptr;
}

unsigned int AVLTreeGator::height(studentNode *node) {
    if (node != nullptr) {
        return node->height;
    } else {
        return 0;
    }
}

AVLTreeGator::studentNode *AVLTreeGator::balanceTree(studentNode *root) {
    int leftHeight = (int) height(root->left);
    int rightHeight = (int) height(root->right);

    // Check right-heavy skew
    if (leftHeight - rightHeight < -1) {
        int rightLeftHeight = (int) height(root->right->left);
        int rightRightHeight = (int) height(root->right->right);

        if (rightLeftHeight - rightRightHeight > 0) {
            root = rotateRightLeft(root);
            root->height++;
            root->left->height -= 2;
            root->right->height--;
        } else if (root->right->right) {
            root = rotateLeft(root);
            root->left->height -= 2;
        }
    }
        // Check left-heavy skew
    else if (leftHeight - rightHeight > 1) {
        int leftLeftHeight = (int) height(root->left->left);
        int leftRightHeight = (int) height(root->left->right);

        if (leftLeftHeight - leftRightHeight < 0) {
            root = rotateLeftRight(root);
            root->height++;
            root->right->height -= 2;
            root->left->height--;
        } else if (root->left->left) {
            root = rotateRight(root);
            root->right->height -= 2;
        }
    }
    return root;
}

AVLTreeGator::studentNode *AVLTreeGator::insertNameId(studentNode *root, string studentName, unsigned int studentId) {
    if (root == nullptr) {
        cout << "successful" << endl;
        return new studentNode(studentName, studentId);
    }

    if (studentId < root->gatorId) {
        root->left = insertNameId(root->left, studentName, studentId);
    } else if (studentId != root->gatorId) {
        root->right = insertNameId(root->right, studentName, studentId);
    } else {
        cout << "unsuccessful" << endl;
        return root;
    }
    root->height = 1 + max(height(root->left), height(root->right));
    return balanceTree(root);
}

AVLTreeGator::studentNode *AVLTreeGator::removeAccount(studentNode *root, unsigned int studentId) {
    // Base case
    if (!root) {
        cout << "unsuccessful" << endl;
        return root;
    }
    // If the node is not a leaf
    if (studentId < root->gatorId) {
        root->left = removeAccount(root->left, studentId);
        root->height = 1 + max(height(root->left), height(root->right));
        return balanceTree(root);
    } else if (studentId > root->gatorId) {
        root->right = removeAccount(root->right, studentId);
        root->height = 1 + max(height(root->left), height(root->right));
        return balanceTree(root);
    }
    // If the node is a leaf
    if (root->left == nullptr) {
        studentNode *tempNode = root->right;
        delete root;
        cout << "successful" << endl;
        if (tempNode != nullptr)
            return balanceTree(tempNode);
        return tempNode;
    } else if (root->right == nullptr) {
        studentNode *tempNode = root->left;
        delete root;
        cout << "successful" << endl;
        return balanceTree(tempNode);
    }
        // If the node has two children
    else {
        // Find the inorder successor
        studentNode *successorParent = root;
        studentNode *successorTemp = root->right;
        // Find the leftmost child of the right subtree
        while (successorTemp->left != nullptr) {
            successorParent = successorTemp;
            successorTemp = successorTemp->left;
        }
        // Copy the inorder successor's data to this node
        if (successorParent != root) {
            successorParent->left = successorTemp->right;
        } else {
            successorParent->right = successorTemp->right;
        }
        root->gatorId = successorTemp->gatorId;
        root->gatorName = successorTemp->gatorName;

        delete successorTemp;
        cout << "successful" << endl;
        return balanceTree(root);
    }
}

void AVLTreeGator::removeNode(studentNode *root) {
    if (!root) {
        return;
    }
    removeNode(root->left);
    removeNode(root->right);
    delete root;
}

AVLTreeGator::studentNode *AVLTreeGator::searchGatorId(studentNode *root, unsigned int targetId) {
    if (!root || root->gatorId == targetId) {
        return root;
    }
    if (targetId < root->gatorId) {
        return searchGatorId(root->left, targetId);
    }
    return searchGatorId(root->right, targetId);
}

AVLTreeGator::studentNode *AVLTreeGator::searchNameId(studentNode *root, string targetName, bool &isFound) {
    if (!root) {
        return nullptr;
    }
    if (root->gatorName == targetName) {
        cout << setw(8) << setfill('0') << root->gatorId << endl;
        isFound = true;
    }
    searchNameId(root->left, targetName, isFound);
    searchNameId(root->right, targetName, isFound);

    return root;
}

AVLTreeGator::studentNode *AVLTreeGator::rotateLeft(studentNode *node) {
    studentNode *rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;

    if (node == root) {
        root = rightChild;
    }
    return rightChild;
}

AVLTreeGator::studentNode *AVLTreeGator::rotateRight(studentNode *node) {
    studentNode *leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;

    if (node == root) {
        root = leftChild;
    }
    return leftChild;
}

AVLTreeGator::studentNode *AVLTreeGator::rotateLeftRight(studentNode *node) {
    studentNode *grandchild = node->left->right;
    studentNode *greatGrandchild = node->left->right->left;

    node->left->right = greatGrandchild;
    grandchild->left = node->left;
    node->left = grandchild;

    return rotateRight(node);
}

AVLTreeGator::studentNode *AVLTreeGator::rotateRightLeft(studentNode *node) {
    studentNode *grandchild = node->right->left;
    studentNode *greatGrandchild = node->right->left->right;

    node->right->left = greatGrandchild;
    grandchild->right = node->right;
    node->right = grandchild;

    return rotateLeft(node);
}

void AVLTreeGator::printInorder(studentNode *node, vector<studentNode *> &inorder) {
    if (!node) {
        return;
    }
    printInorder(node->left, inorder);
    inorder.push_back(node);
    printInorder(node->right, inorder);
}

void AVLTreeGator::printPreorder(studentNode *node, vector<studentNode *> &preorder) {
    if (!node) {
        return;
    }
    preorder.push_back(node);
    printPreorder(node->left, preorder);
    printPreorder(node->right, preorder);
}

void AVLTreeGator::printPostorder(studentNode *node, vector<studentNode *> &postorder) {
    if (!node) {
        return;
    }
    printPostorder(node->left, postorder);
    printPostorder(node->right, postorder);
    postorder.push_back(node);
}


AVLTreeGator::AVLTreeGator() {
    root = nullptr;
}

AVLTreeGator::~AVLTreeGator() {
    removeNode(this->root);
}


void AVLTreeGator::insert(string gatorName, unsigned int gatorId) {
    if (!root) {
        root = new studentNode(gatorName, gatorId);
        cout << "successful" << endl;
    } else
        this->insertNameId(this->root, gatorName, gatorId);
}

void AVLTreeGator::searchId(unsigned int gatorId) {
    studentNode *result = searchGatorId(this->root, gatorId);
    if (result) {
        cout << result->gatorName << endl;
    }
    else{
        cout << "unsuccessful" << endl;
    }
}


void AVLTreeGator::searchName(string gatorName) {
    bool exists = false;
    searchNameId(this->root, gatorName, exists);
    if (!exists){
        cout << "unsuccessful" << endl;
    }
}

void AVLTreeGator::printInorder() {
    vector<studentNode *> nodeList;
    printInorder(this->root, nodeList);

    for (int i = 0; i < nodeList.size(); i++) {
        cout << nodeList[i]->gatorName;
        if (i != nodeList.size() - 1){
            cout << ", ";
        }
    }
    cout << endl;
}

void AVLTreeGator::printPreorder() {
    vector<studentNode *> nodeList;
    printPreorder(this->root, nodeList);

    for (int i = 0; i < nodeList.size(); i++) {
        cout << nodeList[i]->gatorName;
        if (i != nodeList.size() - 1)
            cout << ", ";
    }
    cout << endl;
}

void AVLTreeGator::printPostorder() {
    vector<studentNode *> nodeList;
    printPostorder(this->root, nodeList);

    for (int i = 0; i < nodeList.size(); i++) {
        cout << nodeList[i]->gatorName;
        if (i != nodeList.size() - 1)
            cout << ", ";
    }
    cout << endl;
}


void AVLTreeGator::printLevelCount() {
    cout << height(this->root) << endl;
}

void AVLTreeGator::removeInorder(unsigned int position) {
    stack<studentNode *> nodeStack;
    studentNode *currNode = this->root;
    unsigned int tracker = 0;

    while (currNode || !nodeStack.empty()) {
        if (currNode) {
            nodeStack.push(currNode);
            currNode = currNode->left;
        } else {
            currNode = nodeStack.top();
            nodeStack.pop();
            if (tracker++ == position) {
                break;
            }
            currNode = currNode->right;
        }
    }
    if (currNode) {
        removeAccount(this->root, currNode->gatorId);
    } else {
        cout << "unsuccessful" << endl;
    }
}

void AVLTreeGator::remove(unsigned int gatorId) {
    this->root = removeAccount(this->root, gatorId);
}
