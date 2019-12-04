// CPP program to implement hashing with chaining
#include<iostream>
#include <math.h>
#include "hash.hpp"


using namespace std;

node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
    return (key % tableSize);
}

//function to calculate hash function
unsigned int HashTable::hashFunction2(int key)
{
    cout << "floor returning " << (int) floor(key / tableSize) % tableSize << endl;
    return ((int) floor(key / tableSize) % tableSize);
}

node* HashTable::searchItem(int key, int hashType)
{
    int index;
    //Compute the index by using the hash function
    if (hashType == 1) {
      index = hashFunction(key);
    } else {
      index = hashFunction2(key);
    }


    cout << "index " << index << endl;
    // not in table
    if (!table[index]) {
      cout << "Not in table" << endl;
      return NULL;
    }

    return table[index];
}


//TODO Complete this function
//function to insert
bool HashTable::insertItem(int key, int hashType)
{

  int x;

  if (hashType == 1) {
    x = hashFunction(key);
  } else {
    x = hashFunction2(key);
  }

  cout << "insert index: " << x << endl;

  // Use the first hash function on the key to get the index/slot,

    if(!searchItem(key, hashType))
    {
        // create a new node with the key and insert it in this slot's list
        table[x] = createNode(key, nullptr);;
        cout << "inserted " << key << " at " << x << endl;
     }
    else{
        while (table[x]->next != nullptr) {
          cout << key <<  " collided with " << table[x]->key << endl;
          table[x] = table[x]->next;
        }
        if (table[x]->next == nullptr){

          table[x]->next = createNode(key, nullptr);
          cout << "post collision inserted " << key << endl;
        }
    }
    return true;
}

//TODO Complete this function
// function to display hash table
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i << " || " ;
        if (table[hashFunction(i)] != 0x0) {

          node* d = table[hashFunction(i)];
          cout << d->key;

          while (d->next != nullptr) {
            cout << ", " << d->next->key;
            d = d->next;
          }
        }
         cout << endl;
    }
    return;
 }
