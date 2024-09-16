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

// BST insertion function
t_node* insertBST(t_node* root, int key) {
    if (!root) return new t_node(key);

    if (key < root->data) {
        root->left = insertBST(root->left, key);
    } else {
        root->right = insertBST(root->right, key);
    }

    updateSize(root);
    return root;
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

// Function to search a node in the BST
bool searchNode(t_node* root, int key) {
    if (!root) return false;
    if (root->data == key) return true;
    if (key < root->data) return searchNode(root->left, key);
    return searchNode(root->right, key);
}

// Function to find the height of the BST
int findHeight(t_node* root) {
    if (!root) return 0;
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

// Function to count the total nodes in the BST
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

// Function to count leaf nodes in the BST
int countLeafNodes(t_node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Function to check if the BST is balanced
bool isBalanced(t_node* root) {
    if (!root) return true;
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    if (abs(leftHeight - rightHeight) > 1) return false;
    return isBalanced(root->left) && isBalanced(root->right);
}

// Function to find the diameter of the BST
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

    int radius = 20;  // Increased radius for larger nodes

    setcolor(COLOR(144, 238, 144));  // Light Green for node
    setfillstyle(SOLID_FILL, COLOR(144, 238, 144));
    circle(x, y, radius);
    floodfill(x, y, COLOR(144, 238, 144));

    setcolor(WHITE);  // White for text
    outtextxy(x - 8, y - 8, str);  // Adjusted text position for larger node

    setcolor(RED);  // Red for node border
    circle(x, y, radius);

    int treeHeight = findHeight(root);
    int offset = 300 / pow(2, level + 1);
    int yOffset = 100;

    if (root->left) {
        setcolor(COLOR(255, 255, 0));  // Yellow for lines
        line(x, y + radius + 5, x - offset, y + yOffset);
        printTree(x - offset, y + yOffset, root->left, level + 1);
    }
    if (root->right) {
        setcolor(COLOR(255, 255, 0));  // Yellow for lines
        line(x, y + radius + 5, x + offset, y + yOffset);
        printTree(x + offset, y + yOffset, root->right, level + 1);
    }
}




void visualizeAndUpdateTree(t_node* root) {
    cleardevice();  // Clear the current visualization

    // Set background color
    setbkcolor(COLOR(0, 0, 102));  // Dark Blue background
    cleardevice();

    // Set text style for the heading
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    setcolor(COLOR(255, 165, 0));  // Orange for heading

    // Display heading text at the top center
    outtextxy(250, 20, "Binary Search Tree Visualizer");

    printTree(400, 100, root, 0);  // Re-draw the tree from the root
    delay(500);  // Small delay for visualization effect
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    initwindow(800, 600, "Binary Search Tree Visualization");
    cleardevice();

    cout << "Enter root node data: ";
    int x;
    cin >> x;
    t_node* root = new t_node(x);

    visualizeAndUpdateTree(root);

    cout << "Enter 'n' at any point to stop adding nodes.\n";

    while (true) {
        string input;
        cout << "Enter node value (or 'n' to stop): ";
        cin >> input;
        if (input == "n" || input == "N") {
            break;
        }
        int val = stoi(input);
        root = insertBST(root, val);
        visualizeAndUpdateTree(root);
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
                visualizeAndUpdateTree(root);
                break;
            case 12: {
                cout << "Enter key: ";
                int key;
                cin >> key;
                cout << "Order of key " << key << " is: " << order_of_key(root, key) << endl;
                break;
            }
            case 13:
                c = 0;
                break;
            default:
                cout << "Invalid choice, try again!\n";
        }
        cout << endl;
    }

    closegraph();
    return 0;
}
