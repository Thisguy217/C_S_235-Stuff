#include <iostream>
#include <vector>
using namespace std;

void Exchange(vector<int> &Vector, int firstVal, int secondVal) {
  int tempVal = Vector[firstVal];
  Vector[firstVal] = Vector[secondVal];
  Vector[secondVal] = tempVal;
}

void MedianOfThree(vector<int> &Vector, int first, int last) {
  int middle = (last - first) / 2;
  if (Vector[first] > Vector[middle]) {
    Exchange(Vector, first, middle);
  }
  if (Vector[last] < Vector[middle]) {
    Exchange(Vector, last, middle);
  }
  if (Vector[middle] < Vector[first]) {
    Exchange(Vector, middle, first);
  }
}

int main() {
  vector<int> testVect{10,5,0,-5,-10};
  MedianOfThree(testVect, 0, 4);

  for (int i = 0; i < testVect.size(); i++) {
    cout << testVect[i] << " ";
  }
}