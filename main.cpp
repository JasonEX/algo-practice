#include "skipList.h"
#include <time.h>
using namespace std;

int main()
{
  srand(unsigned(time(NULL)));
  SkipList<int, int> list;
  for (int i = 1; i <= 100; i++)
    list.insert(createNode(i, 10));
  for (int i = 1; i <= 100; i += 2)
    list.remove(i);
  list.compact();
  list.dump();
  cout << list.size() << endl;

  int ret = -1;
  if (list.find(10, ret))
    std::cout << ret << std::endl;
  else
    std::cout << "10 Not found!" << std::endl;

  if (list.find(21, ret))
    std::cout << ret << std::endl;
  else
    std::cout << "21 Not found!" << std::endl;

  try
  {
    cout << list.find(30) << endl;
    cout << list.find(51) << endl;
  }
  catch (exception &e)
  {
    cout << e.what() << endl;
  }

  try
  {
    cout << list[40] << endl;
    list[40] = 40;
    cout << list[40] << endl;
    cout << list[61] << endl;
  }
  catch (exception &e)
  {
    cout << e.what() << endl;
  }

  return 0;
}