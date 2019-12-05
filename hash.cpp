// CPP program to implement hashing with chaining
#include<iostream>
#include <math.h>
#include "hash.hpp"


using namespace std;

// node* HashTable::createBSTNode(int key)
// {
//     node* newNode = new node;
//     newNode->key = key;
//     newNode->left = NULL;
//     newNode->right = NULL;
//     return newNode;
// }

node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    nw->left = NULL;
    nw->right = NULL;
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


node* HashTable::searchKeyHelper(node* currNode, int key){

    if(currNode == NULL){
        // cout << "NULI" << endl;
        return NULL;
    }
    if(currNode->key == key){
      return currNode;
    }
    if(currNode->key > key){
      // cout << "l" << endl;
      return searchKeyHelper(currNode->left, key);
    }
    return searchKeyHelper (currNode->right, key);
}



node* HashTable::searchItem(int key, int index, int hashType, int collRes)
{


  node* tree;
    switch(collRes){
      cout << "collision at: " << index << endl;
      case 1:
        if (!table[index]) {
          // cout << "Not in table" << endl;
          return NULL;
        }
        return table[index];
        break;
      case 2:
        if (!table[index]) {
          // cout << "Not in table" << endl;
          return NULL;
        }
        // else {
        //   tree = searchKeyHelper(table[index], key);
        //    if(tree != NULL) {
        //        cout << "found key" << endl;
        //        return tree;
        //    }
        // }
        // cout<<"Key not present in the tree"<<endl;
        return table[index];
        break;
      case 3:
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
    // cout << d->key;
      while (d->next != nullptr) {
        // cout << key <<  " collided with " << d->next->key << endl;
        d = d->next;
      }
      if (d->next == nullptr){
        d->next = createNode(key, nullptr);
        // cout << "post collision inserted " << key << endl;
      }
  return;
}


node* HashTable::addNodeHelper(node* currNode, int data)
{

    if(currNode == NULL){
        cout << "new" <<endl;
        return createNode(data, nullptr);
    }
    else if(currNode->key < data){
        cout << "left" <<endl;
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key > data){
        cout << "here!" <<endl;
        currNode->left = addNodeHelper(currNode->left, data);
    }

      cout << currNode->key << " : " << data <<endl;

    return currNode;
}

void HashTable::bstInsert(int key, int index, int hashType, int collRes){
  cout << "bst inserting" << endl;
  table[index] = addNodeHelper(table[index], key);
  cout<< key <<" has been added."<<endl;
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

  // cout << "index " << index << endl;
  //if there are no collisions
  if(!searchItem(key, index, hashType, collRes))
  {
    // cout << "inserting" << endl;
    table[index] = createNode(key, nullptr);
  }
   //otherwise, switch on coll type.
  else {
    cout << "collision res: " << collRes << endl;
    switch(collRes){
      case 1:
        llInsert(key, index, hashType, collRes);
        break;
      case 2:
        cout << key << " collision on " << index << endl;
        bstInsert(key, index, hashType, collRes);
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
