#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

Node* insertRecursive(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }
    
    if (key < root->data) {
        root->left = insertRecursive(root->left, key);
    }
    else if (key > root->data) {
        root->right = insertRecursive(root->right, key);
    }
    
    return root;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
    }
}

Node* insertIterative(Node* root, int key) {
    Node* newNode = new Node(key);
    
    if (root == nullptr) {
        return newNode;
    }

    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr) {
        parent = current;
        if (key < current->data) {
            current = current->left;
        }
        else if (key > current->data) {
            current = current->right;
        } else {
            return root;
        }
    }

    if (key < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    return root;
}

int main() {
    Node* root = nullptr;
    
    root = insertRecursive(root, 50);
    insertRecursive(root, 30);
    insertRecursive(root, 20);
    insertRecursive(root, 40);
    insertRecursive(root, 70);
    insertRecursive(root, 60);
    insertRecursive(root, 80);

    std::cout << "Inorder traversal after recursive insertion: ";
    inorder(root);
    std::cout << std::endl;

    Node* root2 = nullptr;
    root2 = insertIterative(root2, 50);
    insertIterative(root2, 30);
    insertIterative(root2, 20);
    insertIterative(root2, 40);
    insertIterative(root2, 70);
    insertIterative(root2, 60);
    insertIterative(root2, 80);

    std::cout << "Inorder traversal after iterative insertion: ";
    inorder(root2);
    std::cout << std::endl;

    return 0;
}