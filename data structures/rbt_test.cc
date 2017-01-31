#include "rbt.h"

int main() {
  RBTree a;
  a.insert(5);
  a.insert(2);
  a.insert(10);
  a.insert(7);
  a.insert(8);
  a.insert(1);
  a.insert(3);
  a.insert(9);
  a.insert(11);
  a.insert(12);
  a.insert(13);
  a.insert(14);
  a.print();

  a.del(5);
  a.del(2);
  a.del(10);
  a.del(7);
  a.del(8);
  a.del(1);
  a.del(3);
  a.print();
  a.del(9);
  a.print();
  a.del(11);
  a.print();
  a.del(12);
  a.print();
  a.del(13);
  a.print();
  a.del(14);
  a.print();
  

  return 0;
}
