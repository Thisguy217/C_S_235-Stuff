#ifndef TODO_LIST_H
#define TODO_LIST_H

#include "TodoListInterface.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TodoList : public TodoListInterface {
public:
  vector<string> tasks;
  TodoList() {
    ifstream infile("TODOList.txt");
    string line;
    if (infile.is_open()) {
      while (getline(infile, line)) {
        tasks.push_back(line);
      }
      infile.close();
    }
  }
  virtual ~TodoList() {
    ofstream outfile;
    outfile.open("TODOList.txt", ofstream::trunc | ofstream::out);
    for (int i = 0; i < tasks.size(); i++) {
      outfile << tasks[i] << endl;
    }
    outfile.close();
  }

  /*
   *   Adds an item to the todo list with the data specified by the string
   * "_duedate" and the task specified by "_task"
   */
  virtual void add(string _duedate, string _task) {
    tasks.push_back(_duedate + ' ' + _task);
  };

  /*
   *   Removes an item from the todo list with the specified task name
   *
   *   Returns 1 if it removes an item, 0 otherwise
   */
  virtual int remove(string _task) {
    for (int i = 0; i < tasks.size(); i++) {
      if (tasks[i].find(_task) != string::npos) {
        tasks.erase(tasks.begin() + i);
      }
    }
    return 1;
  };

  /*
   *   Prints out the full todo list to the console
   */
  virtual void printTodoList() {
    vector<string> copyTasks;
    copyTasks = tasks;
    vector<string> dates{"Sunday ",   "Monday ", "Tuesday ", "Wednesday ",
                         "Thursday ", "Friday ", "Saturday "};
    for (int i = 0; i < copyTasks.size(); i++) {
      for (int j = 0; j < dates.size(); j++) {
        string::size_type k = copyTasks[i].find(dates[j]);
        if (k != string::npos) {
          copyTasks[i].erase(k, dates[j].length());
        }
      }
    }
    for (int l = 0; l < copyTasks.size(); l++) {
      cout << copyTasks[l] << endl;
    }
  };

  /*
   *   Prints out all items of a todo list with a particular due date (specified
   * by _duedate)
   */
  virtual void printDaysTasks(string _date) {
    _date = _date + ' ';
    vector<string> copyTasks;
    copyTasks = tasks;
    vector<string> localPrint;
    for (int i = 0; i < copyTasks.size(); i++) {
      if (copyTasks[i].find(_date) != string::npos) {
        string::size_type k = copyTasks[i].find(_date);
        if (k != string::npos) {
          copyTasks[i].erase(k, _date.length());
          localPrint.push_back(copyTasks[i]);
        }
      }
    }
    cout << _date << endl;
    for (int l = 0; l < localPrint.size(); l++) {
      cout << localPrint[l] << endl;
    }
  };
};

#endif