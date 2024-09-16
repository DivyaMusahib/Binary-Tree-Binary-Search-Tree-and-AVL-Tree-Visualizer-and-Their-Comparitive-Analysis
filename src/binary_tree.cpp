#include <iostream>
#include <queue>
#include <cmath>
#include <graphics.h>  // Graphics library

using namespace std;

// Tree node structure
struct t_node {
    int data;
    t_node* left;
    t_node* right;
    int size;  // To store the size of the subtree

    t_node(int x) : data(x), left(nullptr), right(nullptr), size(1) {}
};

// Update the size of the subtree rooted at node
int updateSize(t_node* node) {
    if (!node) return 0;
    node->size = 1 + updateSize(node->left) + updateSize(node->right);
    return node->size;
}

// Tree traversal functions
void Inorder(t_node* root) {
    if (!root) return;
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
}

void Preorder(t_node* root) {
    if (!root) return;
    cout << root->data << " ";
    Preorder(root->left);
    Preorder(root->right);
}

void Postorder(t_node* root) {
    if (!root) return;
    Postorder(root->left);
    Postorder(root->right);
    cout << root->data << " ";
}

void LevelOrder(t_node* root) {
    if (!root) return;
    queue<t_node*> q;
    q.push(root);
    while (!q.empty()) {
        t_node* current = q.front();
        cout << current->data << " ";
        q.pop();
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

// Function to search a node in the binary tree
bool searchNode(t_node* root, int key) {
    if (!root) return false;
    if (root->data == key) return true;
    return searchNode(root->left, key) || searchNode(root->right, key);
}

// Function to find the height of the binary tree
int findHeight(t_node* root) {
    if (!root) return 0;
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

// Function to count the total nodes in the binary tree
int countNodes(t_node* root) {
    if (!root) return 0;
    return updateSize(root);  // Ensure size is updated
}

// Function to find the number of elements less than the given key
int order_of_key(t_node* root, int key) {
    if (!root) return 0;

    int leftSize = (root->left ? root->left->size : 0);

    if (key <= root->data) {
        return order_of_key(root->left, key);
    } else {
        return leftSize + 1 + order_of_key(root->right, key);
    }
}

// Function to count leaf nodes in the binary tree
int countLeafNodes(t_node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Function to check if the tree is balanced
bool isBalanced(t_node* root) {
    if (!root) return true;
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    if (abs(leftHeight - rightHeight) > 1) return false;
    return isBalanced(root->left) && isBalanced(root->right);
}

// Function to find the diameter of the binary tree
int findDiameter(t_node* root, int& diameter) {
    if (!root) return 0;
    int leftHeight = findDiameter(root->left, diameter);
    int rightHeight = findDiameter(root->right, diameter);
    diameter = max(diameter, leftHeight + rightHeight + 1);
    return max(leftHeight, rightHeight) + 1;
}

void printTree(int x, int y, t_node* root, int level) {
    if (!root) return;

    char str[10];
    itoa(root->data, str, 10);

    // Set the color for the node based on its level in the tree
    int nodeColor = (level % 3 == 0) ? LIGHTBLUE : (level % 3 == 1) ? LIGHTGREEN : LIGHTCYAN;
    int textColor = BLACK; // White for root node

    setcolor(nodeColor);
    setfillstyle(SOLID_FILL, nodeColor);
    circle(x, y, 15);  // Draw the circle representing the node
    floodfill(x, y, nodeColor);  // Fill the node with the color

    // Draw the text inside the node
    setcolor(textColor);  // Text color contrast, white for the root node
    outtextxy(x - 5, y - 5, str);  // Display node data inside the circle

    // Drawing connecting lines with different color
    setcolor(RED);  // Line color
    circle(x, y, 15);

    int treeHeight = findHeight(root);
    int offset = 300 / pow(2, level + 1);
    int yOffset = 100;

    // Connect and draw left and right child nodes
    if (root->left) {
        setcolor(YELLOW);  // Set color for the left child line
        line(x, y + 20, x - offset, y + yOffset);
        printTree(x - offset, y + yOffset, root->left, level + 1);
    }
    if (root->right) {
        setcolor(WHITE);  // Set color for the right child line
        line(x, y + 20, x + offset, y + yOffset);
        printTree(x + offset, y + yOffset, root->right, level + 1);
    }
}

void visualizeAndUpdateTree(t_node* root) {
    cleardevice();  // Clear the current visualization
    
    // Set background color
    setbkcolor(LIGHTGRAY);  
    cleardevice();  // Reapply the background color after clearing the screen

    // Set text style for the heading
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);

    // Display heading text with a vibrant color
    setcolor(MAGENTA);
    outtextxy(250, 20, "Binary Tree Visualizer");

    // Visualize the tree
    printTree(300, 100, root, 0);
    delay(200);  // Reduced delay for faster visualization
}


int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    initwindow(800, 600, "Binary Tree Visualization");

    // Set the background color once at the start
    setbkcolor(LIGHTGRAY);  
    cleardevice();  // Apply the background color

    cout << "Enter root node data: ";
    int x;
    cin >> x;
    t_node* root = new t_node(x);

    queue<t_node*> q;
    q.push(root);

    visualizeAndUpdateTree(root);

    cout << "Enter 'n' at any point to stop adding nodes.\n";

    while (!q.empty()) {
        t_node* temp = q.front();
        q.pop();

        string input;

        cout << "Enter left child of " << temp->data << " (or 'n' to stop): ";
        cin >> input;
        if (input == "n" || input == "N") {
            break;
        }
        int lc = stoi(input);
        if (lc != -1) {
            temp->left = new t_node(lc);
            q.push(temp->left);
            updateSize(root);
            visualizeAndUpdateTree(root);
        }

        cout << "Enter right child of " << temp->data << " (or 'n' to stop): ";
        cin >> input;
        if (input == "n" || input == "N") {
            break;
        }
        int rc = stoi(input);
        if (rc != -1) {
            temp->right = new t_node(rc);
            q.push(temp->right);
            updateSize(root);
            visualizeAndUpdateTree(root);
        }
    }

    int c = 1;
    while (c) {
        cout << "1. In-order Traversal\n2. Pre-order Traversal\n3. Post-order Traversal\n4. Level-order Traversal\n5. Search for a value\n6. Height of the tree\n7. Count total nodes\n8. Count leaf nodes\n9. Check if the tree is balanced\n10. Find the diameter of the tree\n11. Visualize Tree\n12. Find order of key\n13. Exit\nEnter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "In-order Traversal: ";
                Inorder(root);
                break;
            case 2:
                cout << "Pre-order Traversal: ";
                Preorder(root);
                break;
            case 3:
                cout << "Post-order Traversal: ";
                Postorder(root);
                break;
            case 4:
                cout << "Level-order Traversal: ";
                LevelOrder(root);
                break;
            case 5: {
                cout << "Enter the node to search: ";
                int key;
                cin >> key;
                if (searchNode(root, key))
                    cout << "Node " << key << " found in the tree.\n";
                else
                    cout << "Node " << key << " not found in the tree.\n";
                break;
            }
            case 6:
                cout << "Height of the tree: " << findHeight(root) << endl;
                break;
            case 7:
                cout << "Total nodes in the tree: " << countNodes(root) << endl;
                break;
            case 8:
                cout << "Total leaf nodes in the tree: " << countLeafNodes(root) << endl;
                break;
            case 9:
                if (isBalanced(root))
                    cout << "The tree is balanced.\n";
                else
                    cout << "The tree is not balanced.\n";
                break;
            case 10: {
                int diameter = 0;
                findDiameter(root, diameter);
                cout << "Diameter of the tree: " << diameter << endl;
                break;
            }
            case 11:
                cleardevice();
                printTree(300, 100, root, 0);
                getch();
                cleardevice();
                break;
            case 12: {
                cout << "Enter the key to find order: ";
                int key;
                cin >> key;
                int order = order_of_key(root, key);
                cout << "Number of elements less than " << key << " is: " << order << endl;
                break;
            }
            case 13:
                c = 0;
                break;
            default:
                cout << "Invalid choice! Try again!\n";
        }
        cout << "\n\n";
    }

    getch();
    closegraph();
    return 0;
}