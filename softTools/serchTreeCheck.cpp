//
// Created by jdl on 2020/8/19.
//

#include <iostream>
#include <climits>
using namespace std;

struct TreeNode {
       int val;
       TreeNode *left;
       TreeNode *right;
       TreeNode(int x) : val(x), left(NULL), right(NULL) {}
   };

class Solution {
public:
  bool isValidBst(TreeNode* node, int& min,int& max){
    if(!node){
      max = INT_MIN;
      min = INT_MAX;
      return true;
    }

    int left_min,left_max;

    if(!isValidBst(node->left,left_min,left_max)){
      return false;
    }

    int right_min,right_max;
    if(!isValidBst(node->right,right_min,right_max)){
      return false;
    }

    if(node->val <= left_max || node->val >= right_min){
      return false;
    }

    if(left_max == INT_MIN){
      min = node->val;
    }else{
      min = left_min;
    }

    if(right_min == INT_MAX){
      max = node->val;
    }else{
      max = right_max;
    }

    return true;
  }
  bool isValidBST(TreeNode* root) {
    int min,max;
    return isValidBst(root,min,max);
  }
};

int main(void){
  TreeNode* node = new TreeNode(5);
  node->left = new TreeNode(1);
  node->right = new TreeNode(4);
  node->right->left = new TreeNode(3);
  node->right->right = new TreeNode(6);
  bool isBst = Solution().isValidBST(node);
  cout<<isBst<<endl;
  return 0;

}