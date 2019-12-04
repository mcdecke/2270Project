#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct node
{
    int key;
    struct node* next;
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    node* *table;

    node* createNode(int key, node* next);
public:
    HashTable(int bsize);  // Constructor

    // inserts a key into hash table
    bool insertItem(int key, int hashType);
    // bool insertItem2(int key, int hashType);

    // hash function to map values to key
    unsigned int hashFunction(int key);
    unsigned int hashFunction2(int key);

    void printTable();

    node* searchItem(int key, int hashType);
};

#endif
