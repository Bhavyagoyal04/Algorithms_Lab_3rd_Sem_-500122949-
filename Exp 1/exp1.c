#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the structure of a tree node
struct Node {
    int data;                  // Store node data
    struct Node* left;         // Pointer to left child
    struct Node* right;        // Pointer to right child
};

// Function to create a new node with a specified value
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));  // Allocate memory for new node
    newNode->data = val;       // Assign the given value to node data
    newNode->left = newNode->right = NULL; // Initialize children as NULL
    return newNode;
}

// Function to insert a node iteratively
struct Node* insertIterative(struct Node* root, int val) {
    struct Node* newNode = createNode(val);  // Create new node with given value
    if (!root) return newNode;               // If tree is empty, return new node as root

    struct Node* parent = NULL;   // Initialize parent as NULL
    struct Node* current = root;  // Start from the root of the tree

    while (current) {             // Traverse the tree to find insertion point
        parent = current;
        if (val < current->data)
            current = current->left;  // Move to left subtree
        else
            current = current->right; // Move to right subtree
    }

    if (val < parent->data)       // Insert new node as left or right child
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;                  // Return the root of the modified tree
}

// Function to insert a node recursively
struct Node* insertRecursive(struct Node* root, int val) {
    if (!root) return createNode(val);  // Base case: if tree is empty, create new node
    if (val < root->data)
        root->left = insertRecursive(root->left, val);  // Insert into left subtree
    else
        root->right = insertRecursive(root->right, val); // Insert into right subtree
    return root;                      // Return root of the modified tree
}

// Function for in-order traversal of the tree (left, root, right)
void inOrderTraversal(struct Node* root) {
    if (!root) return;               // Base case: if node is NULL, do nothing
    inOrderTraversal(root->left);    // Traverse left subtree
    printf("%d ", root->data);       // Print the node's data
    inOrderTraversal(root->right);   // Traverse right subtree
}

// Function to compare performance of iterative and recursive insertions
void compareInsertPerformance(int arr[], int size) {
    struct Node* rootIterative = NULL; // Initialize root for iterative insertion
    struct Node* rootRecursive = NULL; // Initialize root for recursive insertion

    // Measure time for iterative insertion
    clock_t startIter = clock();
    for (int i = 0; i < size; i++) {
        rootIterative = insertIterative(rootIterative, arr[i]);
    }
    clock_t endIter = clock();
    double durationIter = (double)(endIter - startIter) * 1000000 / CLOCKS_PER_SEC;

    // Measure time for recursive insertion
    clock_t startRec = clock();
    for (int i = 0; i < size; i++) {
        rootRecursive = insertRecursive(rootRecursive, arr[i]);
    }
    clock_t endRec = clock();
    double durationRec = (double)(endRec - startRec) * 1000000 / CLOCKS_PER_SEC;

    // Print in-order traversal and time taken for iterative insertion
    printf("In-order traversal for iterative insertion: ");
    inOrderTraversal(rootIterative);
    printf("\nTime taken for iterative insertion: %.2f microseconds\n", durationIter);

    // Print in-order traversal and time taken for recursive insertion
    printf("In-order traversal for recursive insertion: ");
    inOrderTraversal(rootRecursive);
    printf("\nTime taken for recursive insertion: %.2f microseconds\n", durationRec);
}

// Main function
int main() {
    int arr[] = {10, 5, 15, 2, 7, 12, 20};  // Array of values to insert into BST
    int size = sizeof(arr) / sizeof(arr[0]); // Calculate number of elements

    compareInsertPerformance(arr, size);     // Compare iterative and recursive insertions

    return 0;
}