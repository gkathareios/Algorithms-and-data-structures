#include <iostream>
using namespace std;

class RBTree {
public:
  struct Node;
  static const bool RED   = false;
  static const bool BLACK = true;
  RBTree();

  Node* root;
  Node* nil;
  Node* new_node(int); //returns a newly allocated red node with the specified key, to be inserted to the tree
  void insert(int);
  void print();
  void print(Node*);
  Node* find(int);
  void del(int);
  Node* min_subtree(Node*);
  void fix_tree_insert(Node*);
  void fix_tree_del(Node*);
  void rotate_left(Node*);
  void rotate_right(Node*);
};

struct RBTree::Node {
  int  key;
  bool color;
  Node* l;
  Node* r;
  Node* p;
  Node(int, bool );
  bool is_left_child_of(Node*);
  bool is_right_child_of(Node*);
};
