#include <iostream>
using namespace std;

struct Node {
  char data;
  struct Node* left;
  struct Node* right;

  Node(char data) {
    this->data = data;
    left = right = NULL;
  }
};

// Preorder traversal
void preorderTraversal(struct Node* node) {
  if (node == NULL)
    return;
  cout << node->data << "->";
  preorderTraversal(node->left);
  preorderTraversal(node->right);
}

// Postorder traversal
void postorderTraversal(struct Node* node) {
  if (node == NULL)
    return;
  postorderTraversal(node->left);
  postorderTraversal(node->right);
  cout << node->data << "->";
}

// Inorder traversal
void inorderTraversal(struct Node* node) {
  if (node == NULL)
    return;
  inorderTraversal(node->left);
  cout << node->data << "->";
  inorderTraversal(node->right);
}

// Function to insert nodes based on user input
Node* insertNode() {
  char value;
  cout << "Enter value ('0' for no node): ";
  cin >> value;

  if (value == '0') {
    return NULL;
  }

  Node* newNode = new Node(value);
  
  cout << "Enter left child of " << value << ":\n";
  newNode->left = insertNode();

  cout << "Enter right child of " << value << ":\n";
  newNode->right = insertNode();

  return newNode;
}

int main() {
  cout << "Create the binary tree:\n";
  Node* root = insertNode();

  cout << "\nInorder traversal: ";
  inorderTraversal(root);

  cout << "\nPreorder traversal: ";
  preorderTraversal(root);

  cout << "\nPostorder traversal: ";
  postorderTraversal(root);

  return 0;
}
