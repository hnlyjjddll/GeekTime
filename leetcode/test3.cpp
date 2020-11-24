#include <list>
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <unordered_map>

using namespace std;
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int,int> mapPos;
        for(int i=0; i<inorder.size();++i){
            mapPos[inorder[i]] = i;
        }

        return _doBuildTree(mapPos,inorder,0,inorder.size()-1,postorder,inorder.size()-1);
    }

private:
    TreeNode* _doBuildTree(const unordered_map<int,int>& mapPos,const vector<int>& inorder,int iBeg,int iEnd,const vector<int>& postorder,int pEnd){
        if(iBeg > iEnd){
            return nullptr;
        }

        TreeNode* root = new TreeNode(postorder[pEnd]);
        cout<<"iBeg="<<iBeg<<" iEnd="<<iEnd<<endl;
        cout<<" pEnd="<<pEnd<<endl; 
        int pos = mapPos.at(postorder[pEnd]);
        cout<<"pos="<<pos<<endl;
        root->left = _doBuildTree(mapPos,inorder,iBeg,pos-1,postorder,pEnd-(iEnd-pos)-1);
        root->right = _doBuildTree(mapPos,inorder,pos+1,iEnd,postorder,pEnd-1);
        return root;
    }
};

void Print(TreeNode* root){
    if(!root) return;
    cout<<root->val<<endl;
    Print(root->left);
    Print(root->right);
}

int main(void){
    vector<int> inorder{9,3,15,20,7};
    vector<int> postorder{9,15,7,20,3};
    auto root = Solution().buildTree(inorder,postorder);
    Print(root);
    return 0;
}
