#include <unordered_map>
#include <list>
#include <iostream>

using namespace std;

class LruCache{
public:
    class CacheNode;
    LruCache(int max):max_count(max){}
    //直接从map缓存中找，如果key未找到，则返回-1.
    //若找到，将缓存更新到链表尾，即表示最新，同时更新map缓存
    int get(int key){
        if(mapSet.find(key) != mapSet.end()){
            auto pNode = mapSet[key];
            pListCache.push_back(*pNode);
            mapSet[key] = --pListCache.end();
            pListCache.erase(pNode);
            return pListCache.back().val;
        }

        return -1;
    }
    void put(int key,int val){
        //先从map缓存中找，若找到，更新value值，同时将缓存更新到链表尾，并且更新map缓存
        if(mapSet.find(key) != mapSet.end()){
            auto pNode = mapSet[key];
            pNode->val = val;
            pListCache.push_back(*pNode);
            mapSet[key] = --pListCache.end();
            pListCache.erase(pNode);
            return;
        }

        //如果缓存满，先删除最近最少被访问的缓存值，即链表头的缓存,同时删除相应map缓存
        if(max_count == pListCache.size()){//满了
            auto pNode = pListCache.begin();
            mapSet.erase(pNode->key);
            pListCache.pop_front();
        }

        pListCache.push_back(CacheNode(key,val));
        mapSet[key] = --pListCache.end();

    }
private:
    list<CacheNode> pListCache;
    const int max_count;
    unordered_map<int,list<CacheNode>::iterator> mapSet;
public:
    class CacheNode{
        public:
            CacheNode(int key,int val):key(key),val(val){}
        public:
            int key;
            int val;
    };
};

int main(void){
    LruCache lruCache(2);
    cout<<lruCache.get(2)<<endl;
    lruCache.put(2,6);
    cout<<lruCache.get(1)<<endl;
    lruCache.put(1,5);
    lruCache.put(1,2);
    cout<<lruCache.get(1)<<endl<<lruCache.get(2)<<endl;
    return 0;
}
