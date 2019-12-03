// CPP program to implement hashing with chaining
#include<iostream>
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

// TODO Complete this function
//function to search
node* HashTable::searchItem(int key)
{
    //Compute the index by using the hash function
    int index = hashFunction(key);
    //TODO: Search the list at that specific index and return the node if found
    if (!table[index]) {
      return NULL;
    }
    return table[index];
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(int key)
{
  // TODO :
  // Use the hash function on the key to get the index/slot,

  int x = hashFunction(key);
    if(!searchItem(key))
    {
        // create a new node with the key and insert it in this slot's list
        table[x] = createNode(key, nullptr);;

     }
    else{
        if (table[x]->next != nullptr) {

        }
        else {
          table[x]->next = createNode(key, nullptr);
        }
        return false;
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
