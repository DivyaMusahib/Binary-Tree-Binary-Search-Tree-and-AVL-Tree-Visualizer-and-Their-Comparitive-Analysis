# Binary Tree, Binary Search Tree and AVL Tree Visualization <br> And their Comparitive Analysis

This project demonstrates the implementation and visualization of Binary Trees, Binary Search Trees (BSTs), and AVL Trees using C++. It uses the Turbo C graphics library to visually represent the tree structures.

## Overview
This project consists of three main parts:
1. Binary Tree Operations
2. Binary Search Tree Operations
3. AVL Tree Operations

Each part demonstrates the implementation and visualization of the respective tree structures.

## Features
### Binary Tree Operations:
- Insertion
- In-order, Pre-order, Post-order, Level-order Traversal
- Node Search
- Height Calculation
- Node and Leaf Counting
- Balance Check
- Diameter Calculation

### Binary Search Tree Operations:
- BST Property-Based Insertion
- All Binary Tree Operations with Enhanced Search Efficiency

### AVL Tree Operations:
- AVL Tree Property-Based Insertion
- All Binary Tree Operations with Enhanced Search Efficiency and Balancing

### Tree Visualization:
Dynamic visualization after each operation.

## Comparative Analysis
### Insertion
- **Binary Tree:** Nodes are inserted in level order.
- **BST:** Nodes are inserted based on value, maintaining the BST property.
- **AVL Tree:** Nodes are inserted based on value, maintaining the AVL Tree property (balance factor between -1 and 1).

### Search Efficiency
- **Binary Tree:** Linear search, potentially inefficient.
- **BST:** Faster search due to the binary search property.
- **AVL Tree:** Fast search due to the balanced binary search tree property.

### Balancing
- **Binary Tree:** No inherent balancing mechanism.
- **BST:** Can be unbalanced, but can be balanced with additional techniques.
- **AVL Tree:** Self-balancing mechanism to maintain balance factor between -1 and 1.

## Getting Started
1. Clone the repository.
2. Open the project in your preferred C++ IDE.
3. Compile and run the project.

## Requirements
- Turbo C++ with graphics library installed.

## How to Use
- Run the program.
- Input nodes to create the tree.
- Perform operations like traversal, search, height calculation, balancing, etc.
- Visualize the tree structure after each operation.

## Comparative Analysis: Normal Binary Tree vs Binary Search Tree (BST) vs AVL Tree

### Basic Structure Comparison

- **Binary Tree:** 
  A binary tree is a general-purpose data structure where each node has at most two children. There is no specific order for the nodes, meaning the left and right children can have any value in relation to the parent node.

- **Binary Search Tree (BST):** 
  A BST is a specialized type of binary tree where for every node, the left child contains only nodes with values less than the parent node, and the right child contains only nodes with values greater than the parent node. This ordering allows for more efficient searching, insertion, and deletion operations compared to a normal binary tree.

- **AVL Tree:** 
  An AVL tree is a self-balancing binary search tree where the balance factor (difference between heights of left and right subtrees) is maintained between -1 and 1. This self-balancing property ensures optimal search, insertion, and deletion operations.

### Time Complexity Analysis

| Operation            | Binary Tree         | Binary Search Tree (BST) | AVL Tree         |
|----------------------|---------------------|--------------------------|------------------|
| **Search**           | O(n)                | O(h) where h is the height of the tree. Average case: O(log n), Worst case: O(n) for an unbalanced tree | O(log n) |
| **Insertion**        | O(n)                | O(h), with similar average and worst-case considerations as search | O(log n) |
| **Deletion**         | O(n)                | O(h), considering the height of the tree | O(log n) |
| **Traversal (In-order, Pre-order, Post-order)** | O(n) | O(n) | O(n) |
| **Height Calculation** | O(n) | O(n) | O(log n) |
| **Balance Check**    | O(n)                | O(n) | O(log n) |
| **Diameter Calculation** | O(n^2) (naive) / O(n) (optimized) | O(n^2) (naive) / O(n) (optimized) | O(n) |

### Key Observations

- **Search Efficiency:** 
  A BST generally provides better search performance, especially when balanced, due to its ordered structure. An AVL tree further improves search performance by maintaining a balance factor between -1 and 1. A normal binary tree might require a complete traversal to find a node, resulting in O(n) time complexity.

- **Insertion and Deletion:** 
  BSTs benefit from their ordered structure, allowing more efficient insertions and deletions. AVL trees build upon this efficiency by automatically rebalancing the tree after insertions and deletions, maintaining optimal time complexities. However, these efficiencies can degrade to O(n) if the BST or AVL tree becomes unbalanced, resembling a linked list in the worst case.

- **Traversal:** 
  Both types of trees exhibit similar time complexity for tree traversals (O(n)) since every node must be visited.

- **Height and Balance:** 
  A balanced AVL tree can maintain optimal time complexities for height calculation, balance check, and diameter calculation. In contrast, a normal binary tree does not inherently support balancing, which could lead to suboptimal performance.

### Visualization Considerations

- **Node Overlap:** 
  In visualization, BSTs tend to have a more predictable structure, making it easier to avoid node overlap. AVL trees maintain a balanced structure, making visualization more straightforward. A normal binary tree, with its more arbitrary structure, might require additional considerations for layout and dynamic resizing.

- **Dynamic Resizing:** 
  Since BSTs and AVL trees tend to have a more uniform shape when balanced, they may require less dynamic resizing compared to a normal binary tree, which can grow in a more irregular manner.

### Conclusion

This project demonstrates and compares the performance and structure of a normal binary tree, a binary search tree (BST), and an AVL tree through various operations and visualizations. Understanding the differences in their time complexities and practical applications can help in selecting the appropriate data structure for specific use cases. The visualizations included in this project provide clear examples of how these trees operate and the impact of their structure on performance.

## Conclusion
This project offers an intuitive way to learn and understand the differences and similarities between Binary Trees, BSTs, and AVL Trees, providing both a functional and visual comparison.