#include <iostream>
#include <vector>
using namespace std;

class SegTree {
public:
  struct TreeNode { //holds indices
    int start;
    int end;
    int min_ind;
  };

  vector<TreeNode> tree;
  vector<int> array;
  vector<int> point_to_tree;
  
  inline int l(int n) const {
    return 2*n+1;
  }
  inline int r(int n) const {
    return 2*n+2;
  }
  inline int p(int n) const {
    return (n-1)/2;
  }

  SegTree(vector<int>& inp);
  void init_tree(int index, int range_start, int range_end);
  int query(int start, int end);
  int query_helper(int start, int end, int index);
  bool update_node(int index);
  int update(int index, int new_val);
};