#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Transaction {
public:
    int transId;
    string type;
    int medId;
    int quantity;
    double amount;

    Transaction(int tId = 0, string t = "", int mId = 0, double amt = 0.0, int q = 1) {
        transId = tId;
        type = t;
        medId = mId;
        amount = amt;
        quantity = q;
    }

    void display() {
        cout << "TransID: " << transId << " | " << type
             << " | MedID: " << medId << " | Qty: " << quantity
             << " | Amount: Rs." << amount << endl;
    }
};

struct StackNode {
    Transaction data;
    StackNode* next;
    StackNode(Transaction t) {
        data = t;
        next = nullptr;
    }
};

class DualStack {
public:
    StackNode* undoTop;
    StackNode* redoTop;

    void push(StackNode* &top, Transaction t) {
        StackNode* newNode = new StackNode(t);
        newNode->next = top;
        top = newNode;
    }

    Transaction pop(StackNode* &top) {
        if (top == nullptr) return Transaction();
        StackNode* temp = top;
        Transaction t = temp->data;
        top = top->next;
        delete temp;
        return t;
    }

    DualStack() {
        undoTop = nullptr;
        redoTop = nullptr;
    }

    void recordAction(Transaction t) {
        push(undoTop, t);
    }

    Transaction undo() {
        if (undoTop == nullptr) {
            cout << "Nothing to undo!" << endl;
            return Transaction(0, "", 0, 0.0, 0);
        }
        Transaction t = pop(undoTop);
        push(redoTop, t);
        cout << "Undid Transaction ID: " << t.transId << endl;
        return t;
    }

    Transaction redo() {
        if (redoTop == nullptr) {
            cout << "Nothing to redo!" << endl;
            return Transaction(0, "", 0, 0.0, 0);
        }
        Transaction t = pop(redoTop);
        push(undoTop, t);
        cout << "Redid Transaction ID: " << t.transId << endl;
        return t;
    }
};

struct DLLNode {
    Transaction data;
    DLLNode* prev;
    DLLNode* next;
    DLLNode(Transaction t) {
        data = t;
        prev = nullptr;
        next = nullptr;
    }
};

class TransactionHistory {
public:
    DLLNode* head;
    DLLNode* tail;

    TransactionHistory() {
        head = nullptr;
        tail = nullptr;
    }

    void append(Transaction t) {
        DLLNode* newNode = new DLLNode(t);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void displayAll() {
        if (head == nullptr) {
            cout << "No transactions recorded." << endl;
            return;
        }
        DLLNode* temp = head;
        while (temp != nullptr) {
            temp->data.display();
            temp = temp->next;
        }
    }

    void quickSortArray(Transaction arr[], int low, int high) {
        if (low < high) {
            double pivot = arr[high].amount;
            int i = low - 1;
            for (int j = low; j < high; j++) {
                if (arr[j].amount > pivot) {
                    i++;
                    Transaction temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
            Transaction temp = arr[i + 1];
            arr[i + 1] = arr[high];
            arr[high] = temp;
            int pi = i + 1;

            quickSortArray(arr, low, pi - 1);
            quickSortArray(arr, pi + 1, high);
        }
    }

    void displayProfitRankingQuickSort() {
        Transaction* arr = new Transaction[2000];
        int count = 0;
        DLLNode* temp = head;
        while (temp != nullptr && count < 2000) {
            arr[count++] = temp->data;
            temp = temp->next;
        }
        if (count == 0) {
            cout << "No transactions to rank." << endl;
            delete[] arr;
            return;
        }
        quickSortArray(arr, 0, count - 1);
        cout << "\n--- Sales & Profit Ranking (Quick Sort Highest to Lowest) ---" << endl;
        for (int i = 0; i < count; i++) {
            arr[i].display();
        }
        delete[] arr;
    }

    void saveTransactionsCSV() {
        ofstream fout("transactions.csv");
        DLLNode* temp = head;
        while (temp != nullptr) {
            fout << temp->data.transId << " " << temp->data.type << " "
                 << temp->data.medId << " " << temp->data.amount << " "
                 << temp->data.quantity << endl;
            temp = temp->next;
        }
        fout.close();
    }

    void loadTransactionsCSV() {
        ifstream fin("transactions.csv");
        if (!fin) return;
        head = tail = nullptr;
        int tId, mId, q;
        string t;
        double amt;
        while (fin >> tId >> t >> mId >> amt >> q) {
            append(Transaction(tId, t, mId, amt, q));
        }
        fin.close();
    }
};

#endif