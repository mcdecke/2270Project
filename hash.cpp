// CPP program to implement hashing with chaining
#include<iostream>
#include<ctime>
#include <math.h>
#include "hash.hpp"


using namespace std;


node* HashTable::createNode(int key, node* left)
{
    node* nw = new node;
    nw->key = key;
    nw->left = NULL;
    nw->right = NULL;
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    table2 = new node*[tableSize];
    for(int i=0;i<bsize;i++){
      table[i] = nullptr;
      table2[i] = nullptr;
    }

}

//function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
    return (key % tableSize);
}

//function to calculate hash function
unsigned int HashTable::hashFunction2(int key)
{
    return ((int) floor(key / tableSize) % tableSize);
}


node* HashTable::searchKeyHelper(node* currNode, int key){

    if(currNode == NULL){
        return NULL;
    }
    if(currNode->key == key){
      return currNode;
    }
    if(currNode->key > key){
      return searchKeyHelper(currNode->left, key);
    }
    return searchKeyHelper (currNode->right, key);
}



node* HashTable::searchItem(int index, int key, int hashType, int collRes)
{
  if (!table[index]) {
    return NULL;
  }

  if (table[index]->key == key){
    return table[index];
  }

  if (collRes == 1) {
    node* d = table[index];
      while (d->left != nullptr) {
        if (d->key == key){
          return d;
        }
        d = d->left;
      }
    }

    if (collRes == 2) {
      bstSearch(index, key, hashType, collRes);
    }

    if (collRes == 3) {
      int loop = index;
      while (index + 1 != loop) {
        // cout << index << " : "<<loop << endl;
          if (index >= tableSize) {
            // cout << "loopin" << endl;
            index = 0;
          }
          if (table[index] && table[index]->key == key) {
            // cout << "found - " << key << endl;
            return table[index];
          }
        index++;
      }
      // cout <<"table fully searched - not found" << endl;
      return NULL;
    }
    if (collRes == 4){
      int index1 = hashFunction(key); // == index
      int index2 = hashFunction2(key);
      //delete if first possible place.
      if (table[index1] && table[index1]->key == key){
        return table[index1];
      }
      else if(table[index2] && table[index2]->key == key){
        return table[index2];
      }
    }
  return NULL;
}

//////////////
//LINKED LIST
////////////

bool HashTable::llDelete(int index, int key, int hashType, int collRes){

  if (table[index]->key == key){
    cout << "deleted " <<key << endl;
    table[index]->key = -1;
    // cout << "returning true" << endl;
    return true;
  }

    node* d = table[index];
      while (d->left != nullptr) {
        // cout << d->key <<" , ";
          if (d->key == key){
            cout << "deleted " <<key << endl;
            d->key = -1;
            // cout << "returning true" << endl;
            return true;
          }
        d = d->left;
      }
      // cout << "returning false" << endl;
  return false;
}

void HashTable::llInsert(int key, int x, int hashType, int collRes){
    node* d = table[x];
      while (d->left != nullptr) {
        d = d->left;
      }
      if (d->left == nullptr){
        d->left = createNode(key, nullptr);
      }
  return;
}

//////
//BST
////

node* HashTable::searchNodeHelper(node* currNode, int data)
{
    if(currNode == NULL){
        return nullptr;
    }
    else if(currNode->key < data){
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key > data){
        currNode->left = addNodeHelper(currNode->left, data);
    }
    return currNode;
}

void HashTable::bstSearch(int index, int key, int hashType, int collRes){
  table[index] = searchNodeHelper(table[index], key);
  return;
}


node* HashTable::deleteNodeHelper(node* currNode, int data)
{
    if(currNode->key == data){
      cout << "deleted " << data << endl;
        currNode->key = -1;
    }
    else if(currNode->key < data){
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key > data){
        currNode->left = addNodeHelper(currNode->left, data);
    }
    return currNode;
}

void HashTable::bstDelete(int index, int key, int hashType, int collRes){
  table[index] = deleteNodeHelper(table[index], key);
  return;
}

node* HashTable::addNodeHelper(node* currNode, int data)
{
    if(currNode == NULL){
        return createNode(data, nullptr);
    }
    else if(currNode->key < data){
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key > data){
        currNode->left = addNodeHelper(currNode->left, data);
    }
    return currNode;
}

void HashTable::bstInsert(int key, int index, int hashType, int collRes){
  table[index] = addNodeHelper(table[index], key);
  return;
}

//////////////////
//Linear Probing
////////////////

bool HashTable::lpInsert(int key, int index, int loop, int hashType, int collRes){

  if (index >= tableSize) {
    cout << "loopin" << endl;
    index = -1;
  }
  if (index + 1 == loop) {
    cout <<"table full - insert denied" << endl;
    //resize array?
    return false;
    // exit(false);
  }
  if (!table[index + 1]){
    //insert in next slot
      table[index + 1] = createNode(key, nullptr);
      return true;
  }
  else {
    // cout << "movin'" << endl;
    lpInsert(key, index + 1, loop, hashType, collRes);
  }
  return false;
}

bool HashTable::lpDelete(int index, int key, int loop, int hashType, int collRes){

  while (index + 1 != loop) {
  // cout << index << " : "<<loop << endl;
      if (index >= tableSize) {
        // cout << "loopin" << endl;
        index = 0;
      }
      if (table[index] && table[index]->key == key) {
        cout << "deleted - " << table[index]->key << endl;
        table[index]->key = -1;
        return true;
      }
    index++;
  }
  // cout <<"table fully searched - not found" << endl;
  return false;
}


//////////////////
///Cuckoo hashing
////////////////

bool HashTable::cuckooDelete(int key, int index, int loop, int hashType, int collRes){

  int index1 = hashFunction(key); // == index
  int index2 = hashFunction2(key);
  //delete if first possible place.
  if (table[index1]){
    table[index1]->key = -1;
    return true;
  }
  else {
    //or delete the 2nd spot
    table[index2]->key = -1;
    return true;
  }
  //nothing to delete
  return false;
}

void HashTable::cuckooInsert(int key, int index, int loop, int hashType, int collRes){
    int index1 = hashFunction(key); // == index
    int index2 = hashFunction2(key);

  //if there are no collisions
  if(!table[index2])
  {
    // cout << "inserting to second spot" << key << endl;
    table[index2] = createNode(key, nullptr);
    return;
  }

  if (table[index2]) {
    //add to new table
    table2[index2] = createNode(key, nullptr);

    int temp = table[index1]->key;

    //new data goes to first spot
    table[index1]->key = key;
    //data that was in first spot goes to it's second

    if (!table[hashFunction2(temp)]) {
      table[hashFunction2(temp)]  = createNode(temp, nullptr);
      // cout << "moving kicked item, everything resolved." << endl;
      return;
    }

    else{
      temp = table[hashFunction2(temp)]->key;
      if(index == loop){
        cout << "Loop found, resize table" << endl;
        return;
      }
      cuckooInsert(temp, index, loop, hashType, collRes);
      return;
    }
  }

  return;
}





/////
//main delete function
///
bool HashTable::deleteItem(int key, int index, int hashType, int collRes)
{
    switch(collRes){
      case 1:
        llDelete(key, index, hashType, collRes);
        break;
      case 2:
        bstDelete(key, index, hashType, collRes);
        break;
      case 3:
        lpDelete(key, index, key, hashType, collRes);
        break;
      case 4:
        cuckooDelete(key, index, index, hashType, collRes);
        break;
      default:
        break;
    }
  return true;
}

////
//main insert function
//
bool HashTable::insertItem(int key, int hashType, int collRes)
{
  //Compute the index by hash function
  int index;
  if (hashType == 1) {
    index = hashFunction(key);
  } else {
    index = hashFunction2(key);
  }

  //if there are no collisions
  if(!table[index])
  {
    table[index] = createNode(key, nullptr);
  }
   //otherwise, switch on collision type.
  else {
    switch(collRes){
      case 1:
        llInsert(key, index, hashType, collRes);
        break;
      case 2:
        bstInsert(key, index, hashType, collRes);
        break;
      case 3:
        lpInsert(key, index, index, hashType, collRes);
        break;
      case 4:
        cuckooInsert(key, index, index, hashType, collRes);
        break;
      default:
        break;
    }
  }

  return true;
}


// function to display hash table
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i << " || " ;
        if (table[hashFunction(i)] != 0x0) {

          node* d = table[hashFunction(i)];
          cout << d->key;

          while (d->left != nullptr) {
            cout << ", " << d->left->key;
            d = d->left;
          }
        }
         cout << endl;
    }
    return;
 }
