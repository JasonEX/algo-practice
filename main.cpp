#include "skipList.h"
#include <time.h>

int main()
{
  srand(time(NULL));
  SkipList<int, int> list;
  for (int i = 1; i < 100; i++)
    list.insert(createNode(i, 10));
  list.dump();

  return 0;
}