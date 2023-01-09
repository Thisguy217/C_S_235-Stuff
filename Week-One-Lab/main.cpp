#include <iostream>
#include <string>
#include "TodoList.h"
using namespace std;

int main (int argc, char *argv[]) 
{
  try
  {
    TodoList myList;
    if (string(argv[1]) == "add")
    {
      myList.add(argv[2], argv[3]);
    }
    else if (string(argv[1]) == "remove")
    {
      myList.remove(argv[2]);
    }
    else if (string(argv[1]) == "printList")
    {
      myList.printTodoList();
    }
    else if (string(argv[1]) == "printDay")
    {
      myList.printDaysTasks(argv[2]);
    }
    else 
    {
      cout << "Invalid Agruments" << endl;
    }
  }
  catch (...)
  {
    cout << "No arguments given, terminating early" << endl;
  }
}