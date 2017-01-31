#include "segment_tree.h"

int main(){
  vector<int> inp = {2,1,5,7,8,9,3,4};
  SegTree st(inp);

  st.update(0,0);

  cout << st.query(0,7) << endl;
  cout << st.query(1,7) << endl;
  cout << st.query(2,7) << endl;

  return 0;
}

