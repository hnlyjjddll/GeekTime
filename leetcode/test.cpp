#include <list>
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root){
            return "@";
        }

        string str("");
        queue<TreeNode*> qset;
        qset.push(root);
        TreeNode* lastNode = root;
        while(!qset.empty()){
            auto pNode = qset.front();
            qset.pop();
            if(!pNode){
                str = (str==""?"":str+"#") + "@";
                continue;
            }

            str = (str==""?"":str+"#") + to_string(pNode->val);
            
            qset.push(pNode->left);
            qset.push(pNode->right);
            
            if(pNode == lastNode && !qset.empty()){
                lastNode = qset.back();
            }
        }

        int i = str.rfind("@#",0);
        cout << i<<endl;
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.empty()){
            return nullptr;
        }

        vector<string> vecStr;
        _splitString2Vector(data,vecStr);
        return _resumeBinaryTree(vecStr);
    }
private:
    TreeNode* _resumeBinaryTree(const vector<string>& vecStr){
        if(vecStr.empty() || vecStr[0] == "@"){
            return nullptr;
        }

        TreeNode* root = new TreeNode(stoi(vecStr[0]));
        queue<TreeNode*> qset;
        qset.push(root);
        int curPos = 1;
        int size = vecStr.size();
        
        while(!qset.empty() && curPos<size){
            auto pNode = qset.front();
            qset.pop();
            if(curPos < size){
                if(vecStr[curPos] != "@"){
                    pNode->left = new TreeNode(stoi(vecStr[curPos]));
                    qset.push(pNode->left);
                }
                ++curPos;
                if(curPos < size){
                    if(vecStr[curPos] != "@"){
                        pNode->right = new TreeNode(stoi(vecStr[curPos]));
                        qset.push(pNode->right);
                    }
                }
                ++curPos;
            }
        }

        return root;
    }

    void _splitString2Vector(const string& data, vector<string>& vecStr){
        int i=0,j=0,size=data.size();
        for(;j<size;++j){
            if(data[j] == '#'){
                vecStr.push_back(data.substr(i,j-i));
                i = j+1;
            }
        }

        vecStr.push_back(data.substr(i,j-i));
    }
};

void PrintTreeNode(TreeNode* root){
    if(!root){
        return;
    }

    cout<<root->val<<" ";
    PrintTreeNode(root->left);
    PrintTreeNode(root->right);
}

int main(void){
    Codec s;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    
    string str = s.serialize(root);
    cout<<"serial string = "<<str<<endl;

    cout<<"preorder traverse deserial tree"<<endl;
    auto pNode = s.deserialize(str);
    PrintTreeNode(pNode);
    cout<<endl;
    return 0;
}