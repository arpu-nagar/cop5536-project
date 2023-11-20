// Implementing Red-Black Tree in C++

#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

class MinHeap {
   private:
    vector<int> heap;
    map<int, vector<int> > mp;
    // Helper function to maintain the heap property
    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] < heap[parentIndex]) {
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    // Helper function to maintain the heap property
    void heapifyDown(int index) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallestIndex = index;

        if (leftChildIndex < heap.size() &&
            heap[leftChildIndex] < heap[smallestIndex]) {
            smallestIndex = leftChildIndex;
        }

        if (rightChildIndex < heap.size() &&
            heap[rightChildIndex] < heap[smallestIndex]) {
            smallestIndex = rightChildIndex;
        }

        if (smallestIndex != index) {
            std::swap(heap[index], heap[smallestIndex]);
            heapifyDown(smallestIndex);
        }
    }

   public:
    // Insert a new element into the heap
    void insert(int key, int value) {
        mp[value].push_back(key);
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Extract the minimum element from the heap
    int sz() { return heap.size(); }

    void all_but_top() {
        map<int, int> rep;
        vector<int> answer;
        cout << '[';
        for (int i = 0; i < heap.size(); i++) {
            if (rep[heap[i]]) continue;
            for (auto t : mp[heap[i]]) answer.push_back(t);
            rep[heap[i]]++;
            // cout << mp[heap[i]] << ' ';
        }
        for (int i = 0; i < answer.size(); i++) {
            if (i != answer.size() - 1) {
                cout << answer[i] << ", ";
            } else
                cout << answer[i];
        }
        cout << ']';
        cout << endl;
    }

    void all_but_top_patron() {
        // cout << "Patron ";
        // cout << "heap size: " << heap.size() << endl;
        map<int, int> rep;
        vector<int> answer;
        for (int i = 0; i < heap.size(); i++) {
            // cout << "priotiy " << heap[i] << '=' << mp[heap[i]].size() <<
            // endl;
            if (rep[heap[i]]) continue;
            for (auto t : mp[heap[i]]) answer.push_back(t);
            rep[heap[i]]++;
            // cout << mp[heap[i]] << ' ';
        }

        for (int i = 0; i < answer.size(); i++) {
            if (i != answer.size() - 1) {
                cout << answer[i] << ", ";
            } else
                cout << answer[i];
        }

        // cout << endl;
    }

    int getMin() {
        if (heap.empty()) {
            std::cerr << "Heap is empty!" << std::endl;
            return -1;  // You may choose to handle this differently based on
            // your requirements
        }
        int minValue = heap[0];

        return mp[minValue][0];
    }

    int extractMin() {
        if (heap.empty()) {
            std::cerr << "Heap is empty!" << std::endl;
            return -1;  // You may choose to handle this differently based on
            // your requirements
        }

        int minValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        int p = mp[minValue][0];
        mp[minValue].erase(mp[minValue].begin());
        return p;
    }

    // Display the elements of the heap
    void display() {
        for (auto value : heap) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
};

struct Node {
    int BookId;               // Integer ID
    string BookName;          // Name of the book
    string AuthorName;        // Name of the Author
    bool AvailabilityStatus;  // To indicate whether it is currently borrowed
    int BorrowedBy;
    Node* parent;
    Node* left;
    Node* right;
    int color;
    MinHeap priority;
};

int flips = 0;  // analytics tool

typedef Node* NodePtr;

class RedBlackTree {
   public:
    NodePtr root;
    NodePtr TNULL;

    void initializeNULLNode(NodePtr node, NodePtr parent) {
        node->BookId = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }
    void rangeSearchHelper(NodePtr node, int left, int right) {
        if (node != TNULL) {
            rangeSearchHelper(node->left, left, right);
            if (node->BookId >= left && node->BookId <= right) {
                cout << "BookID = " << node->BookId << endl;
                cout << "Title = " << node->BookName << endl;
                cout << "Author = " << node->AuthorName << endl;
                cout << "Availability = "
                     << (node->AvailabilityStatus ? "\"Yes\"" : "\"No\"")
                     << endl;
                if (!node->AvailabilityStatus) {
                    cout << "BorrowedBy = " << node->BorrowedBy << endl;
                } else {
                    cout << "BorrowedBy = None" << endl;
                }

                if (node->priority.sz() >= 1) {
                    cout << "Reservations = ";
                    node->priority.all_but_top();
                } else {
                    cout << "Reservations = []" << endl;
                }
                cout << endl;
            }
            rangeSearchHelper(node->right, left, right);
        }
    }
    // Preorder
    void preOrderHelper(NodePtr node) {
        if (node != TNULL) {
            cout << node->BookId << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    // Inorder
    void inOrderHelper(NodePtr node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->BookId << " ";
            inOrderHelper(node->right);
        }
    }

    // Post order
    void postOrderHelper(NodePtr node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->BookId << " ";
        }
    }

    NodePtr searchTreeHelper(NodePtr node, int key) {
        if (node == TNULL || key == node->BookId) {
            return node;
        }

        if (key < node->BookId) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    // For balancing the tree after deletion
    void deleteFix(NodePtr x) {
        NodePtr s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    flips++;
                    change(x->parent->color, 1);
                    // cout << flips << "aaaaa" << endl;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    change(s->color, 1);
                    s->color = 1;
                    // flips++;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        change(s->left->color, 0);
                        s->left->color = 0;
                        change(s->color, 1);
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    change(s->color, x->parent->color);
                    s->color = x->parent->color;
                    change(x->parent->color, 0);
                    x->parent->color = 0;
                    change(s->right->color, 0);
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    flips++;
                    change(x->parent->color, 1);
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    change(s->color, 1);
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        change(s->right->color, 0);
                        s->right->color = 0;
                        change(s->color, 1);
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    change(s->color, x->parent->color);
                    s->color = x->parent->color;
                    change(x->parent->color, 0);
                    x->parent->color = 0;
                    change(s->left->color, 0);
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        // change(x->color, 0);
        x->color = 0;
    }

    void rbTransplant(NodePtr u, NodePtr v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key) {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL) {
            if (node->BookId == key) {
                z = node;
            }

            if (node->BookId <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            // cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            change(y->color, z->color);
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            deleteFix(x);
        }
    }

    // For balancing the tree after insertion
    void insertFix(NodePtr k) {
        NodePtr u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    flips++;
                    u->color = 0;
                    change(k->parent->color, 0);
                    k->parent->color = 0;
                    change(k->parent->parent->color, 1);
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    change(k->parent->color, 0);
                    k->parent->color = 0;
                    change(k->parent->parent->color, 1);
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;

                if (u->color == 1) {
                    flips++;
                    u->color = 0;
                    change(k->parent->color, 0);
                    k->parent->color = 0;
                    change(k->parent->parent->color, 1);
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    change(k->parent->color, 0);
                    k->parent->color = 0;
                    change(k->parent->parent->color, 1);
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        // change(root->color, 0);
        root->color = 0;
    }

    void printHelper(NodePtr root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->BookId << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    RedBlackTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }
    void change(int a, int b) {
        // cout << "poop" << endl;
        if (a != b) flips++;
    }
    void rangeSearch(int s, int k) { rangeSearchHelper(this->root, s, k); }

    void preorder() { preOrderHelper(this->root); }

    void inorder() { inOrderHelper(this->root); }

    void postorder() { postOrderHelper(this->root); }

    NodePtr searchTree(int k) { return searchTreeHelper(this->root, k); }

    NodePtr minimum(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    NodePtr successor(NodePtr x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void BorrowBook(int patronID, int bookID, int patronPriority) {
        // cout << "aa" << endl;
        Node* found = searchTree(bookID);
        if (found->AvailabilityStatus) {
            found->AvailabilityStatus = false;
            found->BorrowedBy = patronID;
            // cout << 'p' << ' ' << found->BorrowedBy << endl;
        } else {
            found->priority.insert(patronID, patronPriority);
        }
        found->AvailabilityStatus = false;
        if (found->priority.sz() == 0)
            cout << "Book " << bookID << " borrowed by Patron " << patronID
                 << endl
                 << endl;
        else
            cout << "Book " << bookID << " reserved by Patron " << patronID
                 << endl
                 << endl;

        // cout << "heap size " << found->priority.sz() << endl;
    }

    int ColorFlipCount() { return flips; }

    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void preOrderHelperDif1(NodePtr node, int bookId, int dif) {
        if (node != TNULL) {
            // *mx = min(*mx, abs(node->BookId - bookId));
            if (abs(node->BookId - bookId) == dif) {
                // cout << node->BookId << endl;
                NodePtr book = node;
                cout << "BookID = " << book->BookId << endl;
                cout << "Title = " << book->BookName << endl;
                cout << "Author = " << book->AuthorName << endl;
                cout << "Availability = "
                     << (book->AvailabilityStatus ? "\"Yes\"" : "\"No\"")
                     << endl;
                if (!book->AvailabilityStatus) {
                    cout << "BorrowedBy = " << book->BorrowedBy << endl;
                } else {
                    cout << "BorrowedBy = None" << endl;
                }

                if (book->priority.sz() >= 1) {
                    cout << "Reservations = ";
                    book->priority.all_but_top();
                } else {
                    cout << "Reservations = []" << endl;
                }
                cout << endl;
            }
            preOrderHelperDif1(node->left, bookId, dif);
            preOrderHelperDif1(node->right, bookId, dif);
        }
    }

    void preOrderHelperDif(NodePtr node, int bookId, int* mx) {
        if (node != TNULL) {
            // cout << node->BookId << endl;
            (*mx) = min(*mx, abs(node->BookId - bookId));
        } else
            return;
        preOrderHelperDif(node->left, bookId, mx);
        preOrderHelperDif(node->right, bookId, mx);
    }

    int FindClosestDif(int bookId) {
        int mx = 1000;
        NodePtr root = getRoot();
        preOrderHelperDif(root, bookId, &mx);
        // cout << mx << endl;
        return mx;
    }

    void FindClosestBooks(int bookId, int dif) {
        // cout << 'dif ' << dif << endl;
        // NodePtr root = getRoot();
        preOrderHelperDif1(this->root, bookId, dif);
    }

    void insert(int key, string BookName, string AuthorName,
                bool AvailabilityStatus) {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->BookId = key;
        node->BookName = BookName;      // Name of the book
        node->AuthorName = AuthorName;  // Name of the Author
        node->AvailabilityStatus = AvailabilityStatus;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->BookId < x->BookId) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->BookId < y->BookId) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFix(node);
    }

    void returnBook(int bookID) {
        Node* found = searchTree(bookID);

        int prev = found->BorrowedBy;
        // cout << "hi";
        cout << "Book " << bookID << " Returned by Patron " << prev << endl
             << endl;

        if (found->priority.sz() != 0) {
            int p = found->priority.extractMin();
            cout << "Book " << bookID << " Allotted to Patron " << p << endl
                 << endl;
            found->BorrowedBy = p;
            found->AvailabilityStatus = false;

        } else {
            found->AvailabilityStatus = true;
            found->BorrowedBy = -1;
        }
    }

    void DeleteBook(int bookID) {
        Node* found = searchTree(bookID);
        int sz = found->priority.sz();
        if (sz == 0) {
            cout << "Book " << bookID << " is no longer available";
        } else if (sz == 1) {
            cout << "Book " << bookID << " is no longer available. ";
            cout << "Reservation made by Patron ";
            found->priority.all_but_top_patron();
            cout << " has been cancelled!";
        } else {
            cout << "Book " << bookID << " is no longer available. ";
            cout << "Reservation made by Patrons ";
            found->priority.all_but_top_patron();
            cout << " have been cancelled!";
        }
        cout << endl << endl;
        ;
        deleteNode(bookID);
    }

    NodePtr getRoot() { return this->root; }

    void deleteNode(int BookId) { deleteNodeHelper(this->root, BookId); }

    void printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }
};

int main(int argc, char* argv[]) {
    RedBlackTree bst;
    flips = 0;  // initiating analytics
    char* inputFileName = argv[1];
    ifstream inputFile(inputFileName);
    // remove the .txt from input file name and store it in a new variable
    string newFileName = "";
    for (auto ch : string(inputFileName)) {
        if (ch == '.')
            break;
        else
            newFileName += ch;
    }
    string outputfile = string(newFileName) + string("_output_file.txt");
    freopen(outputfile.c_str(), "w", stdout);
    if (!inputFile.is_open()) {
        cerr << "Unable to open the file." << endl;
        return 1;
    }

    string line;
    regex functionRegex("([a-zA-Z_]+)\\(([^)]*)\\)");
    smatch match;

    while (getline(inputFile, line)) {
        if (regex_search(line, match, functionRegex)) {
            string functionName = match[1];
            // cout << "Function Name: " << functionName << endl;
            string parameters = match[2];
            // cout << "Parameters: " << parameters << endl;
            regex parameterRegex("\\s*,\\s*");
            sregex_token_iterator parameterIterator(
                parameters.begin(), parameters.end(), parameterRegex, -1);
            sregex_token_iterator end;

            if (functionName == "PrintBook") {
                int id = stoi(*parameterIterator);
                // for (; parameterIterator != end; ++parameterIterator) {
                // }
                // search and find book with ID: id
                NodePtr book = bst.searchTree(id);
                if (book->BookId == 0) {
                    cout << "Book " << id << " not found in the library."
                         << endl;
                    cout << endl;
                    continue;
                }
                if (book) {
                    cout << "BookID = " << book->BookId << endl;
                    cout << "Title = " << book->BookName << endl;
                    cout << "Author = " << book->AuthorName << endl;
                    cout << "Availability = "
                         << (book->AvailabilityStatus ? "\"Yes\"" : "\"No\"")
                         << endl;
                    if (!book->AvailabilityStatus) {
                        cout << "BorrowedBy = " << book->BorrowedBy << endl;
                    } else {
                        cout << "BorrowedBy = None" << endl;
                    }

                    if (book->priority.sz() >= 1) {
                        cout << "Reservations = ";
                        book->priority.all_but_top();
                    } else {
                        cout << "Reservations = []" << endl;
                    }
                    cout << endl;
                }
                // cout << book->AuthorName << endl;
                else
                    cout << "Book " << id << " not found in the Library" << endl
                         << endl;

            } else if (functionName == "PrintBooks") {
                int id_left = stoi(*parameterIterator++);
                int id_right = stoi(*parameterIterator);
                bst.rangeSearch(id_left, id_right);
            } else if (functionName == "InsertBook") {
                int bookID = stoi(*parameterIterator++);
                string bookName = *parameterIterator++;
                string authorName = *parameterIterator++;
                string availabilityStatus = *parameterIterator;
                bst.insert(bookID, bookName, authorName,
                           availabilityStatus == "\"Yes\"" ? true : false);
            } else if (functionName == "BorrowBook") {
                // cout << 'aaa' << endl;
                int patronID = stoi(*parameterIterator++);
                int bookID = stoi(*parameterIterator++);
                int patronPriority = stoi(*parameterIterator);
                bst.BorrowBook(patronID, bookID, patronPriority);
            } else if (functionName == "ReturnBook") {
                int patronID = stoi(*parameterIterator++);
                int bookID = stoi(*parameterIterator);
                // ReturnBook(patronID, bookID);
                bst.returnBook(bookID);
            } else if (functionName == "DeleteBook") {
                int bookID = stoi(*parameterIterator);
                bst.DeleteBook(bookID);
            } else if (functionName == "FindClosestBook") {
                // bst.printTree();
                int bookID = stoi(*parameterIterator);
                int diff = bst.FindClosestDif(bookID);
                bst.FindClosestBooks(bookID, diff);
            } else if (functionName == "ColorFlipCount") {
                // replace with flip count
                cout << "Color Flip Count: " << flips << endl;
                cout << endl;
            } else if (functionName == "Quit") {
                // replace with flip count
                cout << "Program Terminated!!" << endl;
                inputFile.close();
                return 0;
            }
        }
    }

    inputFile.close();
    return 0;
}