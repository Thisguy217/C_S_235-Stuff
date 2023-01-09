#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;
int main(int argc, char *argv[]) {
  //initalize a bunch of variables, mostly stuff to parse and clean the original text
  vector<string> totalWords;
  set<string> uniqueWords;
  string line;
  // this grabs the filename, because I need it to be pretty
  string fileName = argv[1];
  ifstream in(argv[1]);
  int pops=0;
  while (pops < 4) {
    fileName.pop_back();
    pops++;
  }

  //this is the insertion to vector and set of all the strings
  while (getline(in, line)) {
    istringstream instream(line);
    string token;
    while (instream >> token) {
      string nopunct = "";
      for (auto &c : token) {
        if (isalpha(c)) {
          nopunct += c;
        }
      }
      totalWords.push_back(nopunct);
      uniqueWords.insert(nopunct);
    }
  }
  cout << "Number of words " << totalWords.size() << endl;
  cout << "Number of unique words " << uniqueWords.size() << endl;

  //this will store the set into a file
  ofstream setFile(fileName+"_set.txt");
  for (set<string>::iterator it=uniqueWords.begin(); it!=uniqueWords.end(); ++it)
    setFile << *it << endl;

  //this will store the vector into a file
  ofstream vectorFile(fileName+"_vector.txt");
  for (int i = 0; i < totalWords.size(); i++) {
    vectorFile << totalWords[i] << endl;
  }

  //this will generate the wordMap
  int M; //set my phrasing, to "I Nephi," because it is the first two words in the vector list.
  cout << "Enter number of words you want to start with: ";
  cin >> M;
  cout << endl;
  map<list<string>, vector<string>> wordMap; // I wanted to follow the fancy data types so I tried list and vector of strings.
  list<string> last; //this is a list to start the start, kind of funny but true
  for (int i = 0; i < M; i++) {
    last.push_back("");
  }
  for (vector<string>::iterator it=totalWords.begin(); it!=totalWords.end(); it++) {
    wordMap[last].push_back(*it);//this should be adding from the main vector totalWords it adds the string to the appropriate key in the wordMap (which is a list)
    last.push_back(*it); //this now adds the same item in the value to the last so that way it knows what to go to next
    last.pop_front(); //this then removes the first item so it is always using two words to keep moving into three word strings in this case.
  }

  //srand(time(NULL));
  list<string> state; //this should be the list that I put the actual sentence into, of course it will be replaced regularly
  for (int i = 0; i < M; i++) {
    state.push_back(""); //this prompts to give it a better look, kind of the same as before, just a fresh start
  }
  for (int i = 0; i < 100; i++) {
    //this randomly chooses a word to pull and print to console
    int ind = rand() % wordMap[state].size();
    cout << wordMap[state][ind] << " ";
    //this then prepares the next section of text
    state.push_back(wordMap[state][ind]);
    state.pop_front();
  }
  cout << endl;
}
