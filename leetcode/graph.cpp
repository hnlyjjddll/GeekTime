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
    bool Search(int s,int t,vector<int>& vecPath)const{
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
};

int main(void){
    //构建图
    Graph oGraph(9);
    oGraph.Add(1,2);
    oGraph.Add(1,4);
    //oGraph.Add(2,3);

    //oGraph.Add(2,5);
    oGraph.Add(5,4);
    //oGraph.Add(5,6);

    //oGraph.Add(5,7);
    oGraph.Add(3,6);
    oGraph.Add(6,8);
    oGraph.Add(7,8);

    oGraph.Print();

    //搜索1-8之间最短路径
    vector<int> vecPath;
    bool isFind = oGraph.Search(1,8,vecPath);
    if(isFind){
        cout<<"the shortest path is : ";
        vector<int>::const_reverse_iterator cit = vecPath.rbegin();
        for(;cit!=vecPath.rend();++cit){
            cout<<*cit<<"-";
        }
        cout<<endl;
    }else{
        cout<<"not find"<<endl;
    }

    return 0;
}