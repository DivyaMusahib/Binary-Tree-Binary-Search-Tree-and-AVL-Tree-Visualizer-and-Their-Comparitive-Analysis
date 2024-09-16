#include <iostream>
#include <queue>
#include <cmath>
#include <graphics.h>

using namespace std;

// AVL Tree node structure
struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    int size;

    AVLNode(int x) : data(x), left(nullptr), right(nullptr), height(1), size(1) {}
};

// Function to get the height of a node
int getHeight(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Function to get the size of a node's subtree
int getSize(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->size;
}

// Function to update the height and size of a node
void updateHeightAndSize(AVLNode* node) {
    if (node == nullptr) return;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    node->size = 1 + getSize(node->left) + getSize(node->right);
}

// Function to get the balance factor of a node
int getBalanceFactor(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotation
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeightAndSize(y);
    updateHeightAndSize(x);

    return x;
}

// Left rotation
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeightAndSize(x);
    updateHeightAndSize(y);

    return y;
}

// Insert a node into the AVL tree
AVLNode* insert(AVLNode* node, int key) {
    if (node == nullptr) return new AVLNode(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node; // Duplicate keys not allowed

    updateHeightAndSize(node);

    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to print the AVL tree
void printTree(int x, int y, AVLNode* root, int level) {
    if (!root) return;

    char str[20];
    sprintf(str, "%d (BF:%d)", root->data, getBalanceFactor(root));

    int radius = 20;  // Node radius

    setcolor(COLOR(144, 238, 144));  // Light Green for node
    setfillstyle(SOLID_FILL, COLOR(144, 238, 144));
    circle(x, y, radius);
    floodfill(x, y, COLOR(144, 238, 144));

    setcolor(WHITE);  // White for text
    outtextxy(x - 15, y - 8, str);  // Adjusted text position

    setcolor(RED);  // Red for node border
    circle(x, y, radius);

    int treeHeight = getHeight(root);
    int offset = 300 / pow(2, level + 1);
    int yOffset = 50;

    if (root->left) {
        setcolor(COLOR(255, 255, 0));  // Yellow for lines
        line(x, y + radius + 5, x - offset - (level * 20), y + yOffset);
        printTree(x - offset - (level * 20), y + yOffset, root->left, level + 1);
    }
    if (root->right) {
        setcolor(COLOR(255, 255, 0));  // Yellow for lines
        line(x, y + radius + 5, x + offset + (level * 20), y + yOffset);
        printTree(x + offset + (level * 20), y + yOffset, root->right, level + 1);
    }
}


void drawNode(int x, int y, int data) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, CYAN);
    fillellipse(x, y, 20, 20);
    
    setbkcolor(CYAN);
    setcolor(WHITE);
    char num[5];
    sprintf(num, "%d", data);
    outtextxy(x - 10, y - 5, num);
}

// Modified function to visualize and update the AVL tree with increased gap between root's immediate children
void visualizeAndUpdateTree(AVLNode* root, int x = 400, int y = 100, int level = 0) {
    if (root == NULL) return;

    int baseHorizontalSpacing = 50;
    int horizontalSpacing = (level == 0) ? 150 : baseHorizontalSpacing; // Increased spacing for root's immediate children
    int verticalSpacing = 50;

    // Recursively draw the left and right subtrees
    if (root->left != NULL) {
        int childX = (level == 0) ? x - horizontalSpacing : x - baseHorizontalSpacing * (level + 1);
        line(x, y, childX, y + verticalSpacing);
        visualizeAndUpdateTree(root->left, childX, y + verticalSpacing, level + 1);
    }

    if (root->right != NULL) {
        int childX = (level == 0) ? x + horizontalSpacing : x + baseHorizontalSpacing * (level + 1);
        line(x, y, childX, y + verticalSpacing);
        visualizeAndUpdateTree(root->right, childX, y + verticalSpacing, level + 1);
    }

    // Draw the current node
    drawNode(x, y, root->data);
}

// Inorder traversal
void inorder(AVLNode* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Search for a node
bool searchNode(AVLNode* root, int key) {
    if (root == nullptr) return false;
    if (root->data == key) return true;
    if (key < root->data) return searchNode(root->left, key);
    return searchNode(root->right, key);
 }

// Find height of the tree
int findHeight(AVLNode* root) {
    if (root == nullptr) return 0;
    return max(findHeight(root->left), findHeight(root->right)) + 1;
}

// Count total nodes
int countNodes(AVLNode* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Count leaf nodes
int countLeafNodes(AVLNode* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Find diameter of the tree
int findDiameter(AVLNode* root, int &diameter) {
    if (root == nullptr) return 0;
    int leftHeight = findDiameter(root->left, diameter);
    int rightHeight = findDiameter(root->right, diameter);
    diameter = max(diameter, leftHeight + rightHeight + 1);
    return max(leftHeight, rightHeight) + 1;
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    initwindow(800, 600, "AVL Tree Visualization");
    setbkcolor(LIGHTGRAY);
    cleardevice();

    // Title of the visualization
    setcolor(RED); // Title font color
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(250, 20, "AVL Tree Visualizer");

    AVLNode* root = nullptr;

    cout << "Enter 'n' at any point to stop adding nodes.\n";

    while (true) {
        string input;
        cout << "Enter node value (or 'n' to stop): ";
        cin >> input;
        if (input == "n" || input == "N") {
            break;
        }
        int val = stoi(input);
        root = insert(root, val);
        visualizeAndUpdateTree(root);
    }

    int choice;
    do {
        cout << "\n1. Insert a node\n2. Inorder Traversal\n3. Search for a value\n"
             << "4. Height of the tree\n5. Count total nodes\n6. Count leaf nodes\n"
             << "7. Find the diameter of the tree\n8. Visualize Tree\n9. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "Enter the value to insert: ";
                cin >> val;
                root = insert(root, val);
                visualizeAndUpdateTree(root);
                break;
            }
            case 2:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 3: {
                int key;
                cout << "Enter the value to search: ";
                cin >> key;
                if (searchNode(root, key))
                    cout << "Value " << key << " found in the tree.\n";
                else
                    cout << "Value " << key << " not found in the tree.\n";
                break;
            }
            case 4:
                cout << "Height of the tree: " << findHeight(root) << endl;
                break;
            case 5:
                cout << "Total nodes in the tree: " << countNodes(root) << endl;
                break;
            case 6:
                cout << "Total leaf nodes in the tree: " << countLeafNodes(root) << endl;
                break;
            case 7: {
                int diameter = 0;
                findDiameter(root, diameter);
                cout << "Diameter of the tree: " << diameter << endl;
                break;
            }
            case 8:
                visualizeAndUpdateTree(root);
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 9);

    closegraph();
    return 0;
}