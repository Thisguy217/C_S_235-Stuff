#include <iostream>
#include <vector>
using namespace std;


void Swap(vector<int> &listUnsorted, int firstItem, int secondItem) {
  int tempVal = listUnsorted[firstItem];
  listUnsorted[firstItem] = listUnsorted[secondItem];
  listUnsorted[secondItem] = tempVal;
}

int main() {
  vector<int> unsortedList{23,14,65,3,19,2,71,12,8,61,5,25};

  for (int i = 0; i < unsortedList.size() - 2; i++) {
    int min = i;
    for (int j = (i + 1); j < unsortedList.size() - 1; j++) {
      if (unsortedList[j] < unsortedList[min]) {
        min = j;
      }  
    }
    Swap(unsortedList, i, min);
  }

  for (int i = 0; i < unsortedList.size(); i++) {
    cout << unsortedList[i] << ',' << ' ';
  }
  cout << endl;
}