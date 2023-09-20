#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct node {
  node* left = nullptr;
  node* right = nullptr;
  int val;
};

class tree {
  private:
    node* root;
  public:
    //constructor
    tree() {
      root = nullptr;
    }
    //empty check
    bool empty() {
      return (root == nullptr);
    }
    //retrieve root
    node*& getRoot() {
      return root;
    }

    //insert (recursive)
    void insert(node*& cu, int key) {
      //inserts node at leaf 
      //also works if tree is empty
      if (cu == nullptr) {
        cu = new node;
        cu->val = key;
        cu->left = cu->right = nullptr;
      }
      else if (key > cu->val) {
        insert(cu->right, key);
      }
      else if (key < cu->val) {
        insert(cu->left, key);
      }
      //cannot have duplicate keys
      else if (key == cu->val) {
        exit(1);
      }
    }

    //Least Common Ancestor
    node* lca(node* rt, int v1, int v2) {
      //empty tree or 
      if(rt == nullptr) {
        return nullptr;
      }
      //if both values less than root, go left
      if(v1 < rt->val && v2 < rt-> val) {
        return lca(rt->left, v1, v2);
      }
      //if both values greater than root, go right
      if(v1 > rt->val && v2 > rt-> val) {
        return lca(rt->right, v1, v2);
      }

      //if LCA found, then both if statements are bypassed and lca returned as root
      return rt;
    }

    int distance(node* rt, int v) {
      if(rt->val == v) {return 0;}
      if(v < rt->val) {
        return 1 + distance(rt->left, v);
      }
      return 1 + distance(rt->right, v);
    }

    //print in-order 
    void inOrder(node* cu) {
      if (cu == nullptr) {
        return;
      }
      else {
        inOrder(cu->left);
        cout << cu->val << " ";
        inOrder(cu->right);
      }
    }
};

int main() {
  ifstream inFS("exin2.txt"); //DELETE IN SUBMISSION
  
  string array;
  int v1, v2; //values to calc shortest path distance to

  //REPLACE inFS WITH cin IN SUBMISSION
  getline(inFS, array); 
  inFS >> v1;
  inFS >> v2;
  inFS.close(); //DELETE
  
  stringstream inSS(array);
  
  tree bst; 
  int i;
  while(inSS >> i) {
    bst.insert(bst.getRoot(), i);
  }
  //2 steps:
  //1) Find Least Common Ancestor of two given nodes
  //2) Find distance between LCA and v1 && LCA and v2 and add
  
  node* lca = bst.lca(bst.getRoot(), v1, v2);
  
  cout << bst.distance(lca, v1) + bst.distance(lca, v2) << endl;
  return 0;
}
