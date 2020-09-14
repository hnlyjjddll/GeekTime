#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>


using namespace std;

//无向图
class Graph{
public:
    Graph(int v):m_dwCnt(v){
        m_vecAdj.resize(v);
    }

    bool Add(int s,int t){//增加一条边st
        if(s<0 || t<0 || s>m_dwCnt || t>m_dwCnt){
            return false;
        }
        m_vecAdj[s][t] = true;
        m_vecAdj[t][s] = true;
        return true;
    }

    //删除边st
    bool Delete(int s,int t){
        if(s<0 || t<0 || s>m_dwCnt || t>m_dwCnt){
            return false;
        }
        m_vecAdj[s].erase(t);
        m_vecAdj[t].erase(s);
        return true;
    }

    //搜索s到t之间的最短路径，如果存在返回true，并且将路径保存到vecPath中返回
    bool Bfs(int s,int t,vector<int>& vecPath)const{
        if(s<0 || t<0 || s>m_dwCnt || t>m_dwCnt){
            return false;
        }

        if(s==t){
            vecPath.push_back(s);
            return true;
        }

        vector<bool> bVisited(m_dwCnt,false);
        vector<int> vecPrev(m_dwCnt,-1);
        queue<int> qVtex;
        qVtex.push(s);
        bVisited[s] = true;
        int dwLastLayerVtex = s;
        while(!qVtex.empty()){
            int dwVtex = qVtex.front();
            qVtex.pop();
            for(const auto& oPair: m_vecAdj[dwVtex]){
                if(!bVisited[oPair.first]){//顶点未访问
                    if(oPair.first == t){//目标顶点找到
                        vecPrev[oPair.first] = dwVtex;
                        _ConvertPrev2Path(vecPrev,s,t,vecPath);
                        return true;
                    }

                    bVisited[oPair.first] = true;
                    vecPrev[oPair.first] = dwVtex;
                    qVtex.push(oPair.first);
                }
            }
        }

         
        return false;
    }

    //搜索s到t之间的路径（不一定最短），如果存在则返回true，并将路径保存到vecPath中返回
    /*
    dfs采用的回溯的算法思想，但是同一般的回溯问题场景不同，这里在枚举搜索空间的时候，只要找到合适的就退出了，
    因此不能获得最优解。回溯算法要得到最优解，必须枚举整个搜索空间。因此回溯算法的时间复杂度是o(2^n)，通过
    剪枝方式来提高算法性能。
    */
    bool Dfs(int s,int t, vector<int>& vecPath) {
        if(s<0 || t<0 || s>m_dwCnt || t>m_dwCnt){
            return false;
        }

        if(s==t){
            vecPath.push_back(s);
            return true;
        }

        vector<bool> bVisited(m_dwCnt,false);
        vector<int> vecPrev(m_dwCnt,-1);
        bVisited[s] = true;
        m_bFind = false;

        _RecurDfs(vecPrev,bVisited,s,t);
        if(m_bFind){
            _ConvertPrev2Path(vecPrev,s,t,vecPath);
        }
        return m_bFind;
    }

    //打印图
    void Print() const{
        for(int i=1;i<m_vecAdj.size();++i){
            cout<<"vectex["<<i<<"] has edge: "<<endl;
            for(const auto& oPair: m_vecAdj[i]){
                cout<<i<<"-"<<oPair.first<<" ";
            }
            cout<<endl;
        }

        cout<<endl;
    }
private:
    void _RecurDfs(vector<int>& vecPrev,vector<bool>& bVisited,int s,int t){
        if(s == t){
            m_bFind = true;
            return;
        }

        for(const auto& oPair: m_vecAdj[s]){
            if(!bVisited[oPair.first]){
                //记录选择
                bVisited[oPair.first] = true;
                vecPrev[oPair.first] = s;
                //沿着选择的路径继续往下走
                _RecurDfs(vecPrev,bVisited,oPair.first,t);
                if(m_bFind) return;//目标已经找到，无需继续枚举搜索，中断退出
                /*
                是否需要撤销选择操作 取决于 走过的path是否需要进行回滚。这里不需要进行回滚的原因是：
                假设当前搜索顶点是n，那么不管是从哪个搜素顶点到达的n，即不管上一个访问顶点是谁。都不
                影响下一个决策，因此无需回滚。
                */
            }
        }
    }
    void _ConvertPrev2Path(const vector<int>& vecPrev,int s,int t,vector<int>& vecPath)const{
        vecPath.push_back(t);
        while(vecPrev[t] != -1 && t!=s){
            vecPath.push_back(vecPrev[t]);
            t = vecPrev[t];
        }
    }
private:
    int m_dwCnt; //图中顶点数,从1开始编号
    vector<map<int,bool> > m_vecAdj; //邻接表
    bool m_bFind;
};

int main(void){
    //构建图
    Graph oGraph(9);
    oGraph.Add(1,2);
    oGraph.Add(1,4);
    oGraph.Add(2,3);

    oGraph.Add(2,5);
    oGraph.Add(5,4);
    oGraph.Add(5,6);

    //oGraph.Add(5,7);
    oGraph.Add(3,6);
    oGraph.Add(6,8);
    oGraph.Add(7,8);

    oGraph.Print();

    //Bfs搜索1-8之间最短路径
    vector<int> vecPath;
    bool isFind = oGraph.Bfs(1,8,vecPath);
    if(isFind){
        cout<<"bfs find the shortest path is : ";
        vector<int>::const_reverse_iterator cit = vecPath.rbegin();
        for(;cit!=vecPath.rend();++cit){
            cout<<*cit<<"-";
        }
        cout<<endl;
    }else{
        cout<<"bfs not find"<<endl;
    }

    //Dfs
    vecPath.clear();
    isFind = oGraph.Dfs(1,8,vecPath);
    if(isFind){
        cout<<"dfs find the available path is : ";
        vector<int>::const_reverse_iterator cit = vecPath.rbegin();
        for(;cit!=vecPath.rend();++cit){
            cout<<*cit<<"-";
        }
        cout<<endl;
    }else{
        cout<<"dfs not find"<<endl;
    }

    return 0;
}