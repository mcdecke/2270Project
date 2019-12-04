// Driver program
#include<iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "hash.cpp"
using namespace std;

int chooseHash(){

  int hashMethod;

    cout << "Choose hashing Method 1 or 2." << endl;
    cin >> hashMethod;

    if (hashMethod == 1 || hashMethod == 2) {
      return hashMethod;
    } else {
      chooseHash();
    }
    return 1;
}

int main(int argc, char* argv[])
{

  int x = chooseHash();
  //set up tables
  int TABLE_SIZE = 10009;
  int pre[TABLE_SIZE];
  int post[TABLE_SIZE];

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

        cout <<"Inserting " << num << endl;

        if (x == 1) {
          ht.insertItem(num, 1);
        } else {
          ht.insertItem(num, 2);
        }
        counter++;
  }

  cout << "Inserted " << counter << " elements." << endl;

  ht.printTable();

    return 0;
}
