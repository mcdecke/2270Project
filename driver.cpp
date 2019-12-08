// Driver program
#include<iostream>
#include<fstream>
#include <string>
#include <sstream>
#include <fstream>
#include "hash.cpp"
using namespace std;

//Init globals
int positions[2];
int TABLE_SIZE = 10009;
HashTable ht(TABLE_SIZE);
HashTable ht2(TABLE_SIZE);

//timer functions
int start(){
  int startTime, endTime;
  startTime = clock();
  return startTime;
}

int stop(int startTime, ofstream& myfile){
  int endTime;
  double execTime;
  endTime = clock();
  execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
  cout << "execution time: " << execTime << endl;
  myfile << execTime << ",";
  return 0;
}

//creates file with numbers picked randomly from the dataset
void getRandom(int holder[], ofstream& randomFile){
  //grabs random items that might be in
  int rando[100];
  for (int i = 0; i < 100; i++) {
    int x = rand() % 40000;
    for (int j = 0; j < i; j++) {
      if (x == rando[j]) {
        cout << "already in array" << endl;
        break;
      }
    }
    cout << "added " << holder[x] << " to file." << endl;
    randomFile << holder[x] << ",";
  }
  return;
}

//Times the delete of 100 items from the list to see if they are in the load.
//Returns the time taken.
void deleter(ofstream& myfile, int hashType, int collRes){
  int holder[100];
  int t = start();
  int count = 0;
  int num;
  string number;

  //creates array from csv file.
  ifstream fs; // input stream OBJECT
  fs.open("random.csv");
  while (getline(fs, number, ',')) {
      num = stoi(number);
      holder[count] = num;
      count++;
  }

  //gets correct index based on hash
  count = 0;
    for (int i = 0; i < 100; i++) {
      int index;
      if (hashType == 1) {
        index = ht.hashFunction(holder[i]);
      } else {
        index = ht.hashFunction2(holder[i]);
      }
      //deletes if it is found.
      if (ht.searchItem(index, holder[i], hashType, collRes)) {
        count++;
        ht.deleteItem(holder[i], index, hashType, collRes);
      } else {
        cout <<  "didn't find "<<holder[i] << endl;
      }
    }
  cout << "deleted " << count << " items." << endl;
  stop(t, myfile);
}




//Times the lookup of 100 items from the list to see if they are in the load.
//Returns the time taken.
void lookUp(ofstream& myfile, int hashType, int collRes){
  int holder[100];
  int t = start();
  int count = 0;
  int num;
  string number;
  ifstream fs; // input stream OBJECT
  fs.open("random.csv");

  while (getline(fs, number, ',')) {
      num = stoi(number);
      holder[count] = num;
      count++;
  }

  count = 0;
    for (int i = 0; i < 100; i++) {
      int index;
      if (hashType == 1) {
        index = ht.hashFunction(holder[i]);
      } else {
        index = ht.hashFunction2(holder[i]);
      }

      if (ht.searchItem(index, holder[i], hashType, collRes)) {
        count++;
      } else {
        cout <<  "didn't find "<<holder[i] << endl;
      }
    }
    cout << count << " things in table" << endl;
  stop(t, myfile);
}





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

double chooseLoad(){

  double load;
    cout << "Enter load as decimal: " << endl;
    cin >> load;
    return load;
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

// int hash(int x, int key, int y){
//   switch (x){
//     case 1: ht.insertItem(key, x, y);
//     case 2: ht.insertItem(key, x, y);
//   }
// }

// void place(int key, int index, int cnt, int n){
//
//   if(cnt == n){
//     cout << "cycle present, resize" << endl;
//     return;
//   }
//
//   for (int i = 0; i < 2; i++) {
//     positions[i] = hash(i+1, key);
//     if (table[positions[i]] == key) {
//       return;
//     }
//   }
// }
//
// void cuckoo(int key, int n){
//   for (int i, count = 0; i < n; i++, count = 0;) {
//     place(key, 0, count, n);
//   }
// }




int main(int argc, char* argv[])
{

  int x = chooseHash();
  int y = chooseColl();
  double load = chooseLoad();

  //set up tables



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

    // // 10009 is count of buckets in hash table

    string number;
    int num;
    int place, timer;
    int counter, newCount = 0;
    int holder[40000];


    timer = start();
    ofstream myfile;
    myfile.open("output.csv", ios_base::app);

    while (getline(fs, number, ',')) {
        num = stoi(number);

        holder[counter] = num;

        ht.insertItem(num, x, y);
        counter++;
        double g = double(counter)/double(TABLE_SIZE);
        if ((load - .0001) < g && g < (load + .0001) && newCount == 0) {
          // start timer for insert once we reach load, within bounds
          // newCount++;
          // timer = start();

          //reached load
          break;
        }
        //times 100 inserts to avoid 0 time.
        // newCount++;
        // if (newCount == 100) {
        //
        //   stop(timer, myfile);
        // }
    }

    cout << "Inserted " << counter << " elements." << endl
    << "Starting lookup." << endl;


    // getRandom(holder, randomFile);



    lookUp(myfile, x, y);

    deleter(myfile, x, y);

    // ht.printTable();


    return 0;
}
