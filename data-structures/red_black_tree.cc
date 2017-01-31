#include "rbt.h"

bool RBTree::Node::is_left_child_of(Node* n) {
  return this == n->l;
}

bool RBTree::Node::is_right_child_of(Node* n) {
  return this == n->r;
}


RBTree::Node::Node(int k, bool c) {
  key = k;
  color = c;
  l = NULL;
  r = NULL;
  p = NULL;
}

RBTree::RBTree() {
  nil = new Node(0,BLACK);
  root = nil;
}

RBTree::Node* RBTree::new_node(int n) {
  Node* node = new Node(n, RED);
  node->l = nil;
  node->r = nil;
  node->p = nil;
  return node;
}

void RBTree::insert(int n) {
  Node* n_node = new_node(n);
  if (root == nil) {
    root = n_node;
    n_node->p = nil;
  }
  else {
    Node* curr_node = root;
    Node* curr_node_par = root->p;
    while(curr_node != nil) {
      curr_node_par = curr_node;
      if (n_node->key <= curr_node->key)
        curr_node = curr_node->l;
      else
        curr_node = curr_node->r;
    }

    if (n_node->key <= curr_node_par->key)
      curr_node_par->l = n_node;
    else
      curr_node_par->r = n_node;
    n_node->p = curr_node_par;
  }
  fix_tree_insert(n_node);
}

RBTree::Node* RBTree::find(int n) {
  Node* curr_node = root;
  while(curr_node != nil && curr_node->key != n) {
    if (n < curr_node->key)
      curr_node = curr_node->l;
    else
      curr_node = curr_node->r;
  }
  return curr_node;
}

RBTree::Node* RBTree::min_subtree(RBTree::Node* r) {
  while (r->l != nil)
    r = r->l;
  return r;
}

void RBTree::del(int n) {
  Node* to_del = find(n);
  Node* to_fix;
  bool deleted_node_color = to_del->color;
  if (to_del == nil)
    return;
  // case 1: to_del has no children - just delete the node
  if (to_del->l == nil && to_del->r == nil) {
    to_fix = nil;
    to_fix->p = to_del->p;
    if (to_del->p == nil) { //special subcase if it is the root
      root = nil;
    }
    else {
      if (to_del->is_left_child_of(to_del->p))
        to_del->p->l = nil;
      else
        to_del->p->r = nil;
    }
    delete(to_del);
  }
  // case 2.1: to del has only a right child
  else if (to_del->l == nil) {
    to_fix = to_del->r;
    to_fix->p = to_del;
    if (to_del == root) { //special subcase if it is the root
      root = to_del->r;
      root->p = nil;
    }
    else {
      if (to_del->is_left_child_of(to_del->p))
        to_del->p->l = to_del->r;
      else
        to_del->p->r = to_del->r;
      to_del->r->p = to_del->p;
    }
    delete(to_del);
  }
  // case 2.2: to del has only a left child
  else if (to_del->r == nil) {
    to_fix = to_del->l;
    to_fix->p = to_del;
    if (to_del == root) { //special subcase if it is the root
      root = to_del->l;
      root->p = nil;
    }
    else {
      if (to_del->is_left_child_of(to_del->p))
        to_del->p->l = to_del->l;
      else
        to_del->p->r = to_del->l;
      to_del->l->p = to_del->p;
    }
    delete(to_del);
  }
  // case 3: to del has two children
  else {
    Node* successor = min_subtree(to_del->r); 
    deleted_node_color = successor->color;
    to_fix = successor->r;
    to_fix->p = successor;
    // case 3.1 : successor is the right child of to_del
    if (successor == to_del->r) {
      // first change the parent
      successor->p = to_del->p;
      if (to_del->p == nil) { // check is to_del is the root
        root = successor;
      }
      else {
        if (to_del->is_left_child_of(to_del->p))
          to_del->p->l = successor; 
        else
          to_del->p->r = successor; 
      }
      //then move the left child of to_del
      successor->l = to_del->l;
      to_del->l->p = successor;
      successor->color = to_del->color;
    }
    // case 3.2 : successor is further down the right subtree of to_del
    else {
      //delete successor from the tree by moving up its right subtree (left is empty by definition)
      if (successor->is_left_child_of(successor->p))
        successor->p->l = successor->r;
      else
        successor->p->r = successor->r;
      successor->r->p = successor->p;
      // now replace to_del with its successor
      // first fix the parent
      successor->p = to_del->p;
      if (to_del->p == nil) { // check if it is the root
        root = successor;
      }
      else {
        if (to_del->is_left_child_of(to_del->p))
          to_del->p->l = successor;
        else
          to_del->p->r = successor;
      }
      // then fix the children
      successor->r = to_del->r;
      to_del->r->p = successor;
      successor->l = to_del->l;
      to_del->l->p = successor;
      successor->color = to_del->color;
    }
    delete(to_del);
  }
  if (deleted_node_color==BLACK)
    fix_tree_del(to_fix);
}

void RBTree::fix_tree_del(RBTree::Node* x) {
  while(x!=root && x->color!=RED) {
    if (x->is_left_child_of(x->p)) {
      Node* b = x->p->r;
      if (b->color == RED) {
        x->p->color = RED;
        b->color = BLACK;
        rotate_left(x->p);
        b = x->p->r;
      }
      // at this point b->color is always black
      if(b->l->color == BLACK && b->r->color == BLACK) {
        b->color = RED;
        x = x->p;
      }
      else if (b->r->color == RED) {
        b->r->color = BLACK;
        b->color = x->p->color;
        x->p->color = BLACK;
        rotate_left(x->p);
        x = root; //we are done
      }
      else {
        b->color = RED;
        b->l->color = BLACK;
        rotate_right(b);
      }
    }
    else {
      Node* b = x->p->l;
      if (b->color == RED) {
        x->p->color = RED;
        b->color = BLACK;
        rotate_right(x->p);
        b = x->p->l;
      }
      // at this point b->color is always black
      if(b->l->color == BLACK && b->r->color == BLACK) {
        b->color = RED;
        x = x->p;
      }
      else if (b->l->color == RED) {
        b->l->color = BLACK;
        b->color = x->p->color;
        x->p->color = BLACK;
        rotate_right(x->p);
        x = root; //we are done
      }
      else {
        b->color = RED;
        b->r->color = BLACK;
        rotate_left(b);
      }
    }
  }
  x->color = BLACK;
}


void RBTree::print() {
  print(root);
  cout << endl;
}

void RBTree::print(Node* node) {
  if (node!=nil) {
    print(node->l);
    cout << node->key;
    if (node->color == RED)
      cout << 'r';
    else
      cout << 'b';
    cout << node->p->key << "_" <<node->l->key << "_" <<node->r->key << " ";
    print(node->r);
  }
}

void RBTree::rotate_left(Node* n) {
  if (n->r == nil) {
    cout << "Warning, trying to rotate left without a right child" << endl;
    return;
  }
  Node* m = n->r;
  // exchange parents
  m->p = n->p;
  if (n->p == nil)
    root = m;
  else if (n->is_left_child_of(n->p))
    n->p->l = m;
  else
    n->p->r = m;

  n->p = m;

  // exchange children
  n->r = m->l;
  m->l->p = n;

  m->l = n;
}

void RBTree::rotate_right(Node* n) {
  if (n->l == nil) {
    cout << "Warning, trying to rotate right without a right child" << endl;
    return;
  }
  Node* m = n->l;
  // exchange parents
  m->p = n->p;
  if (n->p == nil)
    root = m;
  else if (n->is_left_child_of(n->p))
    n->p->l = m;
  else
    n->p->r = m;

  n->p = m;

  // exchange children
  n->l = m->r;
  m->r->p = n;

  m->r = n;
}

void RBTree::fix_tree_insert(RBTree::Node* n) {
  while((n->color == RED) && (n->p->color == RED)) {
    if (n->p->is_left_child_of(n->p->p)) {
      Node* u = n->p->p->r;
      if (u->color == RED) {
        u->color = BLACK;
        n->p->color = BLACK;
        n->p->p->color = RED;
        n = n->p->p;
      }
      else {
        if (n->is_right_child_of(n->p)) {
          n = n->p;
          rotate_left(n);
        }
        n->p->color = BLACK;
        n->p->p->color = RED;
        rotate_right(n->p->p);
      }
    }
    else {
      Node* u = n->p->p->l;
      if (u->color == RED) {
        u->color = BLACK;
        n->p->color = BLACK;
        n->p->p->color = RED;
        n = n->p->p;
      }
      else {
        if (n->is_left_child_of(n->p)) {
          n = n->p;
          rotate_right(n);
        }
        n->p->color = BLACK;
        n->p->p->color = RED;
        rotate_left(n->p->p);
      }
    }
  }
  if (n == root)
    n->color = BLACK;
}

