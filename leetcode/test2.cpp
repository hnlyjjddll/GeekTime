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

	/* 
		借用一个队列，弹一个元素入左右子树
	*/
	string serialize(TreeNode* root) {

		string r;
		queue<TreeNode*> q;

		q.push(root);

		while (!q.empty()) {
			auto c = q.front();
			if (c != nullptr) {
				q.push(c->left);
				q.push(c->right);
			}

			q.pop();

			if (c == nullptr) {
				r.append("x");
			}
			else {
				r.append(to_string(c->val));
			}

			r.append(",");
		}

		return r;
	}

	// sring to queue
	void trans(queue<string> & v, const  string & s)
	{
		auto begin = 0;
		auto pos = s.find_first_of(',', 0);

		if (pos == s.npos) {
			v.push(s);
			return;
		}

		auto i = 0;
		while (pos != s.npos) {
			v.emplace(std::move(s.substr(begin,pos - begin)));
			begin = ++pos;
			pos = s.find_first_of(',', pos);
		}
	}
    
	/*
	借用两个队列，我们按层生成树
	q_ceng：当前层节点
	q_next: 下一层节点
	*/
	TreeNode* make(queue<string> & v)
	{
		TreeNode* r = nullptr;

		queue<TreeNode*> q_ceng;
		queue<TreeNode*> q_next_ceng;

		auto head = v.front();
		if (head != "x") {
			auto thead = new TreeNode(atoi(head.c_str()));
			q_ceng.push(thead);
			r = thead;		
		}

		v.pop();

		while (!v.empty())
		{		
			while (!q_ceng.empty()) 
			{
				auto t = q_ceng.front();

				auto l_t = v.front();
				v.pop();
				auto r_t = v.front();
				v.pop();

				if (l_t != "x") {
					t->left = new TreeNode(atoi(l_t.c_str()));
					q_next_ceng.push(t->left);
				}

				if (r_t != "x") {
					t->right = new TreeNode(atoi(r_t.c_str()));
					q_next_ceng.push(t->right);
				}

				q_ceng.pop();
			}

			while (!q_next_ceng.empty()) {
				q_ceng.push(q_next_ceng.front());
				q_next_ceng.pop();
			}
		}

		return r;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		queue<string> v;
		Codec().trans(v, data);
		return make(v);
	}
};



// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));