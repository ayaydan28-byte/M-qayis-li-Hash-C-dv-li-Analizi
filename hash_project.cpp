#include <iostream>
#include <vector>
#include <list>
#include <chrono>
using namespace std;
using namespace chrono;

const int TABLE_SIZE = 1009;   // prime number

/* ===================== 1. SEPARATE CHAINING ===================== */

class ChainingHash {
private:
    vector<list<int>> table;

public:
    ChainingHash() {
        table.resize(TABLE_SIZE);
    }

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    bool search(int key) {
        int index = hashFunction(key);
        for (int x : table[index]) {
            if (x == key)
                return true;
        }
        return false;
    }
};

/* ===================== 2. LINEAR PROBING ===================== */

class LinearHash {
private:
    vector<int> table;

public:
    LinearHash() {
        table.assign(TABLE_SIZE, -1);
    }

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key) {
        int index = hashFunction(key);

        while (table[index] != -1) {
            index = (index + 1) % TABLE_SIZE;
        }

        table[index] = key;
    }

    bool search(int key) {
        int index = hashFunction(key);
        int start = index;

        while (table[index] != -1) {
            if (table[index] == key)
                return true;
            index = (index + 1) % TABLE_SIZE;

            if (index == start)
                break;
        }

        return false;
    }
};

/* ===================== 3. DOUBLE HASHING ===================== */

class DoubleHash {
private:
    vector<int> table;

public:
    DoubleHash() {
        table.assign(TABLE_SIZE, -1);
    }

    int hash1(int key) {
        return key % TABLE_SIZE;
    }

    int hash2(int key) {
        return 7 - (key % 7);
    }

    void insert(int key) {
        int index = hash1(key);
        int step = hash2(key);

        while (table[index] != -1) {
            index = (index + step) % TABLE_SIZE;
        }

        table[index] = key;
    }

    bool search(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int start = index;

        while (table[index] != -1) {
            if (table[index] == key)
                return true;

            index = (index + step) % TABLE_SIZE;

            if (index == start)
                break;
        }

        return false;
    }
};

/* ===================== 4. PERFORMANCE TEST ===================== */

void compareMethods() {
    const int N = 1000;

    ChainingHash chaining;
    LinearHash linear;
    DoubleHash dbl;

    // CHAINING TEST
    auto start = high_resolution_clock::now();
    for (int i = 1; i <= N; i++)
        chaining.insert(i);
    auto end = high_resolution_clock::now();

    auto chainingTime =
        duration_cast<microseconds>(end - start);

    // LINEAR TEST
    start = high_resolution_clock::now();
    for (int i = 1; i <= N; i++)
        linear.insert(i);
    end = high_resolution_clock::now();

    auto linearTime =
        duration_cast<microseconds>(end - start);

    // DOUBLE HASH TEST
    start = high_resolution_clock::now();
    for (int i = 1; i <= N; i++)
        dbl.insert(i);
    end = high_resolution_clock::now();

    auto doubleTime =
        duration_cast<microseconds>(end - start);

    cout << "\n===== PERFORMANCE COMPARISON =====\n";
    cout << "Separate Chaining: " << chainingTime.count() << " microseconds\n";
    cout << "Linear Probing:    " << linearTime.count() << " microseconds\n";
    cout << "Double Hashing:    " << doubleTime.count() << " microseconds\n";
}

/* ===================== MAIN ===================== */

int main() {
    cout << "PROJECT: Comparative Hash Table Analysis\n";

    compareMethods();

    return 0;
}
