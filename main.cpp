#include "skipList.h"
#include <time.h>

int main()
{
  srand(time(NULL));
  SkipList<int, int> list;
  for (int i = 1; i < 100; i++)
    list.insert(createNode(i, 10));
  for (int i = 1; i < 100; i += 2)
    list.remove(i);
  list.dump();

  int ret = -1;
  if (list.find(10, ret))
    std::cout << ret << std::endl;
  else
    std::cout << "Not found!" << std::endl;

  return 0;
}