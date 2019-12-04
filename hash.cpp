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
    // cout << "floor returning " << (int) floor(key / tableSize) % tableSize << endl;
    return ((int) floor(key / tableSize) % tableSize);
}




node* HashTable::searchItem(int key, int index, int hashType, int collRes)
{
    switch(collRes){
      case 1:
        // cout << "index " << index << endl;
        // not in table
        if (!table[index]) {
          // cout << "Not in table" << endl;
          return NULL;
        }
        return table[index];
        break;
      case 2:
        break;
      case 3:
        // cout << "index " << index << endl;
        // not in table
        if (!table[index]) {
          // cout << "Not in table" << endl;
          return NULL;
        }
        return table[index];
        break;
      case 4:
        break;
    }
    return NULL;
}

void HashTable::llInsert(int key, int x, int hashType, int collRes){
    node* d = table[x];
    cout << d->key;
      while (d->next != nullptr) {
        cout << key <<  " collided with " << d->next->key << endl;
        d = d->next;
      }
      if (d->next == nullptr){
        d->next = createNode(key, nullptr);
        cout << "post collision inserted " << key << endl;
      }
  return;
}


void HashTable::lpInsert(int key, int index, int loop, int hashType, int collRes){

  if (index + 1 == tableSize) {
    // cout << "outta room" << endl;
    index = -1;
  }

  if (index + 1 == loop) {
    // cout << "looked everywhere" << endl;
    return;
  }

  if (!table[index + 1]){
      node* d = createNode(key, nullptr);
      // cout << "post collision inserted " << key << endl;
      return;
  }
  else {
    lpInsert(key, index + 1, loop, hashType, collRes);
  }
  return;
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(int key, int hashType, int collRes)
{
  int index;
  //Compute the index by hash function
  if (hashType == 1) {
    index = hashFunction(key);
  } else {
    index = hashFunction2(key);
  }
  //if there are no collisions
  if(!searchItem(key, index, hashType, collRes))
  {
  // create a new node with the key and insert it in this slot's list
  table[index] = createNode(key, nullptr);;
  // cout << "inserted " << key << " at " << index << endl;
  }
   //otherwise, switch on coll type.
  else {
    cout << "collision res: " << collRes << endl;
    switch(collRes){
      case 1:
        llInsert(key, index, hashType, collRes);
        break;
      case 2:

        break;
      case 3:
        lpInsert(key, index, index, hashType, collRes);
        break;
      case 4:
        break;
      default:
        break;
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
