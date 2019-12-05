// Driver program
#include<iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "hash.cpp"
using namespace std;

int chooseHash(){

  int hashMethod;
    cout << "Choose hashing Method" << endl;
    cout <<  "1: h(x) = (x)mod(tableSize)" << endl;
    cout <<  "2: h'(x) = floor(x/table) mod x" << endl;
    cin >> hashMethod;

    if (hashMethod == 1 || hashMethod == 2) {
      return hashMethod;
    } else {
      chooseHash();
    }
    return hashMethod;
}

int chooseColl(){

  int collMethod;
    cout << "Choose collision Method" << endl;
    cout << "1: Linked List" << endl;
    cout << "2: Binary Search Tree" << endl;
    cout <<  "3: Linear Probing" << endl;
    cout <<  "4: Cuckoo Hash" << endl;
    cin >> collMethod;

    if (collMethod < 5 && 0 < collMethod) {
      return collMethod;
    } else {
      chooseColl();
    }
    return collMethod;
}

int main(int argc, char* argv[])
{

  int x = chooseHash();
  int y = chooseColl();
  //set up tables
  int TABLE_SIZE = 10009;

  HashTable ht(TABLE_SIZE);

    string filename = "";
  	if (argc < 2) {
  		cout << "Not enough arguments!\n";
  	} else if (argc > 2) {
  		cout << "Too many arguments\n";
  	} else {
  		filename = argv[1];
  	}

  	ifstream fs; // input stream OBJECT
  	fs.open(filename);

    //
    // // 10009 is count of buckets in hash table

    string number;
    int num;
    int place;
    int counter = 0;

    while (getline(fs, number, ',')) {
        num = stoi(number);
        // cout <<"Inserting " << num << endl;
        ht.insertItem(num, x, y);
        counter++;

        // if (counter > (TABLE_SIZE/2) - 1) {
        //   if (y == 3 || y == 4) {
        //     //resize table
        //     cout << "resize?" << endl;
        //   }
        // }

        // if (counter == TABLE_SIZE) {
        //   cout << "full" << endl;
        //   break;
        // }
    }

    cout << "Inserted " << counter << " elements." << endl;

    // ht.printTable();

    return 0;
}
