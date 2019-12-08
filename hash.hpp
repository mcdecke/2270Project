#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct node
{
    int key;
    struct node* next;
    struct node* left;
    struct node* right;
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)
    // Pointer to an array containing buckets
    node* *table;
    node* *table2;

    node* createNode(int key, node* next);
    node* createBSTNode(int key);

public:
    HashTable(int bsize);  // Constructor

    // inserts a key into hash table
    bool insertItem(int key,int hashType, int collRes);

    bool deleteItem(int key, int index, int hashType, int collRes);

    // hash function to map values to key
    unsigned int hashFunction(int key);
    unsigned int hashFunction2(int key);

    void printTable();
    void llInsert(int key, int index, int hashType, int collRes);
    void llDelete(int key, int index, int hashType, int collRes);
    void lpInsert(int key, int index, int loop, int hashType, int collRes);

    void cuckooInsert(int key, int index, int loop, int hashType, int collRes);


    void bstInsert(int key, int index, int hashType, int collRes);
    node* addNodeHelper(node* currNode, int key);

    node* searchItem(int index, int key, int hashType, int collRes);
    node* searchKeyHelper(node* currNode, int data);
};

#endif
