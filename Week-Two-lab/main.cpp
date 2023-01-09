#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

void BoxCarAverage(queue<int> Queue, int Number, int extraPop) {
  float total = 0;

  if (extraPop != 0) {
    for (int i = 0; i < extraPop; i++) {
      Queue.pop();
    }
  }
  for (int i = 0; i < Number; i++) {
    queue<int> tempQueue;
    total += Queue.front();
    cout << Queue.front() << ",";
    Queue.pop();
  }

  cout << endl;

  cout << "Average " << floor(total / Number) << endl;
}

int main(int argc, char *argv[]) {
  queue<int> tempVals;
  string fileInput = argv[1];
  ifstream covidCases(fileInput);
  string line;
  int boxCarNumber = stoi(argv[2]);

  while (getline(covidCases, line)) {
    tempVals.push(stoi(line));
  }

  cout << "Using Data from " << fileInput << " with a " << boxCarNumber
       << " day rolling average" << endl;

  int cutLimit = tempVals.size() - boxCarNumber + 1;
  for (int i = 0; i < cutLimit; i++) {
    BoxCarAverage(tempVals, boxCarNumber, i);
  }
}