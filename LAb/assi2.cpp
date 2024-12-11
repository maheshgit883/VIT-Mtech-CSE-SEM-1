#include <iostream>
#include <string>
using namespace std;

// Define the structure for a node
struct Node {
    int reg_no;
    string name;
    float marks[5];
    float average;
    Node* next;
};

// Function to create a new node by taking input from the user
Node* createNode() {
    Node* newNode = new Node;
    
    // Input student's registration number and name
    cout << "Enter student's registration number: ";
    cin >> newNode->reg_no;
    cout << "Enter student's name: ";
    cin.ignore();
    getline(cin, newNode->name);

    // Input 5 subject marks and calculate average
    float sum = 0;
    cout << "Enter 5 subject marks: ";
    for (int i = 0; i < 5; i++) {
        cin >> newNode->marks[i];
        sum += newNode->marks[i];
    }
    newNode->average = sum / 5.0;
    newNode->next = nullptr;

    return newNode;
}

// Function to insert a node at the end of the linked list
void insertNode(Node*& head) {
    Node* newNode = createNode();
    
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to display the list of students
void displayNodes(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << "Reg No: " << temp->reg_no << ", Name: " << temp->name << ", Average Marks: " << temp->average << endl;
        temp = temp->next;
    }
}

// Function to sort the linked list based on average marks using insertion sort
void sortNodesByAverage(Node*& head) {
    if (head == nullptr || head->next == nullptr) return;

    Node* sorted = nullptr;

    while (head != nullptr) {
        Node* current = head;
        head = head->next;

        if (sorted == nullptr || sorted->average > current->average) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->average < current->average) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
    head = sorted;
}

int main() {
    Node* head = nullptr;
    
    int n;
    cout << "Enter the number of students to insert: ";
    cin >> n;

    // Insert n student records
    for (int i = 0; i < n; i++) {
        cout << "\nInserting student " << i+1 << ":" << endl;
        insertNode(head);
    }
    
    cout << "\nBefore Sorting:" << endl;
    displayNodes(head);
    
    // Sort the linked list based on average marks
    sortNodesByAverage(head);
    
    cout << "\nAfter Sorting by Average Marks:" << endl;
    displayNodes(head);

    return 0;
}
