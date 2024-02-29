#include "BST.h"
#include "RBTree.h"
#include "SplayTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono> 
#include <array>

using namespace std::chrono;
using namespace std;

vector<long long> readLongLongValuesFromFile(const string& filePath);
template <typename T>
void measureTreeOperationTime(T &tree, const string& method,const string& filePath);
void doTreeOperations(const string& treeType);

int main() {
    cout << "__________ __________ __________" << endl;
    cout << "__________    bst     __________" << endl;
    cout << "__________ __________ __________" << endl;
    doTreeOperations("bst");
    cout << "" << endl;

    cout << "__________ __________ __________" << endl;
    cout << "__________    spTree  __________" << endl;
    cout << "__________ __________ __________" << endl;
    doTreeOperations("spTree");
    cout << "" << endl;

    cout << "__________ __________ __________" << endl;
    cout << "__________    rbt     __________" << endl;
    cout << "__________ __________ __________" << endl;
    doTreeOperations("rbt");
    cout << "" << endl;

    return 0;
}

vector<long long> readLongLongValuesFromFile(const string& filePath) {
    vector<long long> values;
    // Open the file
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return values;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            values.push_back(stoll(token)); 
        }
    }
    file.close();
    return values;
}

template <typename T>
void measureTreeOperationTime(T &tree, const string& method,const string& filePath) {
    vector<long long> keys = readLongLongValuesFromFile(filePath);
    auto start = high_resolution_clock::now(); // Start timing
    for (long long key : keys) {
        if (method == "insert"){
            tree.put(key, key); 
        }
        if(method == "search"){
            tree.contains(key); 
        }
        if(method == "delete"){
            tree.del(key); 
        }
    }
    auto stop = high_resolution_clock::now(); // Stop timing
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Estimated time: " << duration.count() << " microseconds" << endl;
}

void doTreeOperations(const string& treeType) {
    array<std::string, 3> operations = {"insert", "search", "delete"};
    array<std::string, 2> setList = {"set1", "set2"};
    array<std::string, 3> toOperationFilePathList = {"data_1.txt", "data_2.txt", "data_3.txt"};
    for (const std::string& setName : setList) {
        cout << "" << endl;
        cout << "----- "<<setName<<" -----" << endl;
        for (const std::string& toOperationFilePath : toOperationFilePathList) {
            cout << "" << endl;
            cout << "_ "<<toOperationFilePath<<" _" << endl;
            BST bst;
            SplayTree spTree;
            RBTree rbt;
            for (const std::string& operation : operations) {
                cout << "" << endl;
                cout << "___________ "<<operation<<" ___________" << endl;
                cout << "" << endl;
                string filePath = "../data/data/"+operation+"/"+setName+"/"+toOperationFilePath;
                cout << "filePath: "<<filePath<< endl;
                if(treeType=="bst"){
                    measureTreeOperationTime(bst,operation,filePath);
                }
                if(treeType=="spTree"){
                    measureTreeOperationTime(spTree,operation,filePath);
                }
                if(treeType=="rbt"){
                    measureTreeOperationTime(rbt,operation,filePath);
                }
            }
        }
    }
}