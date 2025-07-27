

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED; 
    }
};

class Queue {
private:
    Node* data[100];
    int front, rear;
public:
    Queue() : front(-1), rear(-1) {}

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(Node* node) {
        if (rear == 99) return;  // Prevent overflow
        if (front == -1) front = 0;
        data[++rear] = node;
    }

    Node* dequeue() {
        if (isEmpty()) return nullptr;
        Node* node = data[front];
        if (front == rear) front = rear = -1;
        else front++;
        return node;
    }
};

class RBTree {
private:
    Node *root;

    void rotateLeft(Node *&root, Node *&pt) {
        Node *pt_right = pt->right;

        pt->right = pt_right->left;

        if (pt->right != nullptr)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_right;

        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;

        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rotateRight(Node *&root, Node *&pt) {
        Node *pt_left = pt->left;

        pt->left = pt_left->right;

        if (pt->left != nullptr)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_left;

        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;

        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixInsertion(Node *&root, Node *&pt) {
        Node *parent_pt = nullptr;
        Node *grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left) {
                Node *uncle_pt = grand_parent_pt->right;

                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            } else {
                Node *uncle_pt = grand_parent_pt->left;

                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK; 
    }

    Node* insertBST(Node* root, Node* pt) {
        if (root == nullptr)
            return pt;

        if (pt->data < root->data) {
            root->left = insertBST(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = insertBST(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void fixDeletion(Node *&root, Node *&pt) {
        if (pt == nullptr)
            return;

        if (pt == root && pt->left == nullptr && pt->right == nullptr) {
            root = nullptr;
            delete pt;
            return;
        }

        Node *sibling;

        while (pt != root && pt->color == BLACK) {
            if (pt == pt->parent->left) {
                sibling = pt->parent->right;

                if (sibling && sibling->color == RED) {
                    sibling->color = BLACK;
                    pt->parent->color = RED;
                    rotateLeft(root, pt->parent);
                    sibling = pt->parent->right;
                }

                if ((!sibling->left || sibling->left->color == BLACK) &&
                    (!sibling->right || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    pt = pt->parent;
                } else {
                    if (!sibling->right || sibling->right->color == BLACK) {
                        if (sibling->left) sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(root, sibling);
                        sibling = pt->parent->right;
                    }

                    sibling->color = pt->parent->color;
                    pt->parent->color = BLACK;
                    if (sibling->right) sibling->right->color = BLACK;
                    rotateLeft(root, pt->parent);
                    pt = root;
                }
            } else {
                sibling = pt->parent->left;

                if (sibling && sibling->color == RED) {
                    sibling->color = BLACK;
                    pt->parent->color = RED;
                    rotateRight(root, pt->parent);
                    sibling = pt->parent->left;
                }

                if ((!sibling->left || sibling->left->color == BLACK) &&
                    (!sibling->right || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    pt = pt->parent;
                } else {
                    if (!sibling->left || sibling->left->color == BLACK) {
                        if (sibling->right) sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(root, sibling);
                        sibling = pt->parent->left;
                    }

                    sibling->color = pt->parent->color;
                    pt->parent->color = BLACK;
                    if (sibling->left) sibling->left->color = BLACK;
                    rotateRight(root, pt->parent);
                    pt = root;
                }
            }
        }

        pt->color = BLACK;
    }

    Node* deleteBST(Node* root, int data) {
        if (root == nullptr)
            return root;

        if (data < root->data)
            root->left = deleteBST(root->left, data); 
        else if (data > root->data)
            root->right = deleteBST(root->right, data); 
        else {
            
            if (root->left == nullptr) {
                Node* temp = root->right;
                if (root == this->root) this->root = temp;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                if (root == this->root) this->root = temp;
                delete root;
                return temp;
            }

            
            Node* temp = minValueNode(root->right);

            root->data = temp->data;

            root->right = deleteBST(root->right, temp->data); 
        }

        return root;
    }

    Node* minValueNode(Node* node) {
        Node* ptr = node;

        while (ptr->left != nullptr)
            ptr = ptr->left;

        return ptr;
    }

    void levelOrderHelper(Node* root) {
        if (root == nullptr) return;

        Queue queue;
        queue.enqueue(root);

        while (!queue.isEmpty()) {
            Node* temp = queue.dequeue();

            cout << temp->data << "(" << (temp->color == RED ? "R" : "B") << ") ";

            if (temp->left != nullptr)
                queue.enqueue(temp->left);
            if (temp->right != nullptr)
                queue.enqueue(temp->right);
        }
        cout << endl;
    }

public:
    RBTree() { root = nullptr; }

    void insert(int data) {
        Node *pt = new Node(data);
        root = insertBST(root, pt);
        fixInsertion(root, pt);
    }

    void deleteNode(int data) {
        deleteBST(root, data);
        if (root != nullptr)
            fixDeletion(root, root);
    }

    void levelOrder() { levelOrderHelper(root); }
};

int main() {
    RBTree tree;
    int choice, value;

    cout << "Enter the number of nodes to insert: ";
    int n;
    cin >> n;
    cout << "Enter values: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        tree.insert(val);
    }

    do {
        cout << "\nMenu:\n1. Delete\n2. Print Level Order\n3. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter value to delete: ";
            cin >> value;
            tree.deleteNode(value);
            break;
        case 2:
            cout << "Level Order: ";
            tree.levelOrder();
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}