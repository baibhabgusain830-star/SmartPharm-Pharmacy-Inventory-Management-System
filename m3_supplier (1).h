#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Supplier {
public:
    int supplierId;
    string name;
    string contact;

    Supplier(int id = 0, string n = "", string c = "") {
        supplierId = id;
        name = n;
        contact = c;
    }

    void display() {
        cout << "Supplier [" << supplierId << "]: " << name << " (" << contact << ")" << endl;
    }
};

class CircularQueue {
public:
    static const int CAPACITY = 100;
    Supplier orders[CAPACITY];
    int front, rear, count;

    CircularQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    void enqueue(Supplier s) {
        if (count == CAPACITY) {
            cout << "Order Queue is Full!" << endl;
            return;
        }
        rear = (rear + 1) % CAPACITY;
        orders[rear] = s;
        count++;
    }

    Supplier dequeue() {
        if (count == 0) {
            cout << "Order Queue is Empty!" << endl;
            return Supplier();
        }
        Supplier s = orders[front];
        front = (front + 1) % CAPACITY;
        count--;
        return s;
    }

    void displayQueue() {
        if (count == 0) {
            cout << "Supplier queue is empty." << endl;
            return;
        }
        for (int i = 0; i < count; i++) {
            int index = (front + i) % CAPACITY;
            orders[index].display();
        }
    }

    void saveSuppliersCSV() {
        ofstream fout("suppliers.csv");
        for (int i = 0; i < count; i++) {
            int index = (front + i) % CAPACITY;
            fout << orders[index].supplierId << " " << orders[index].name << " "
                 << orders[index].contact << endl;
        }
        fout.close();
    }

    void loadSuppliersCSV() {
        ifstream fin("suppliers.csv");
        if (!fin) return;
        front = 0; rear = -1; count = 0;
        int id; string n, c;
        while (fin >> id >> n >> c) {
            enqueue(Supplier(id, n, c));
        }
        fin.close();
    }
};

struct EdgeNode {
    int medId;
    EdgeNode* next;
    EdgeNode(int m) {
        medId = m;
        next = nullptr;
    }
};

class SupplierGraph {
public:
    static const int MAX_SUPPLIERS = 100;
    int supplierIds[MAX_SUPPLIERS];
    EdgeNode* adjList[MAX_SUPPLIERS];
    int vertexCount;

    SupplierGraph() {
        vertexCount = 0;
        for (int i = 0; i < MAX_SUPPLIERS; i++) adjList[i] = nullptr;
    }

    int findOrAddSupplierVertex(int supId) {
        for (int i = 0; i < vertexCount; i++) {
            if (supplierIds[i] == supId) return i;
        }
        if (vertexCount < MAX_SUPPLIERS) {
            supplierIds[vertexCount] = supId;
            adjList[vertexCount] = nullptr;
            return vertexCount++;
        }
        return -1;
    }

    void addLink(int supId, int medId) {
        int idx = findOrAddSupplierVertex(supId);
        if (idx == -1) return;
        EdgeNode* newEdge = new EdgeNode(medId);
        newEdge->next = adjList[idx];
        adjList[idx] = newEdge;
    }

    void dfsHelper(int idx, bool visited[]) {
        visited[idx] = true;
        cout << "Supplier ID " << supplierIds[idx] << " supplies Medicine IDs: ";
        EdgeNode* temp = adjList[idx];
        while (temp != nullptr) {
            cout << temp->medId << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void runDFS() {
        if (vertexCount == 0) {
            cout << "No supplier-medicine links in Graph." << endl;
            return;
        }
        bool visited[MAX_SUPPLIERS];
        for (int i = 0; i < MAX_SUPPLIERS; i++) visited[i] = false;

        cout << "\n--- Supplier-Medicine Graph (DFS Traversal) ---" << endl;
        for (int i = 0; i < vertexCount; i++) {
            if (!visited[i]) {
                dfsHelper(i, visited);
            }
        }
    }
};

#endif