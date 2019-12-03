// Driver program
#include<iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "hash.hpp"
using namespace std;



int main()
{

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

    int number;
    int counter = 0;

    	while (getline(fs, number, ',')) {
        cout << counter << " + " << number << endl;
        counter++;
    //
    // // insert the keys into the hash table.

    // for (int i = 0; i < n; i++) {
    //     ht.insertItem(a[i]);
    // }
    //
    // cout<< "Contents of the hash table are"<<endl;
    // // SILVER TODO : Complete printTable() function
    // ht.printTable();
    //
    // cout<<endl;
    //
    // int searchFor = 9;
    // // SILVER TODO : Complete searchItem() function
    // if(ht.searchItem(searchFor))
    //  {
    //    cout<<searchFor<<" found in the hash table"<<endl;
    //  }
    // else{
    //   cout<<searchFor<<" not found in the hash table"<<endl;
    // }
    // cout<<"------------------------------------"<<endl;
    //
    // int sum = 19;
    //
    // // GOLD TODO Complete printPairs() function
    // printPairs(a,n,sum,ht);

    return 0;
}
