#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class LRUCache
{
public:
    LRUCache(int capacity) : _capacity(capacity) {}

    int get(int key)
    {
        auto it = _hashList.find(key); //查找到元素，O(1)
        if (it != _hashList.end())
        {
            int ret = it->second->value;
            //移动到头部
            _nodes.splice(_nodes.begin(), _nodes, it->second);//O(1)
            _hashList[key] = _nodes.begin();//O(1)
            return ret;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value)
    {
        auto it = _hashList.find(key);//O(1)
        if (it == _hashList.end())
        {
            //new node
            if (_nodes.size() == _capacity)
            {
                //淘汰结点
                int k = _nodes.back().key;
                _nodes.pop_back();
                _hashList.erase(k);
            }
            _nodes.push_front(CacheNode<int, int>(key, value));
            _hashList[key] = _nodes.begin();//O(1)
        }
        else
        {
            //更新value
            it->second->value = value;
            _nodes.splice(_nodes.begin(), _nodes, it->second);
            _hashList[key] = _nodes.begin();//O(1)
        }
    }

private:
    template <typename T1, typename T2>
    struct CacheNode
    {
        CacheNode(T1 k, T2 v) : key(k), value(v) {}
        T1 key;
        T2 value;
    };

private:
    int _capacity;
    list<CacheNode<int, int>> _nodes;
    unordered_map<int, list<CacheNode<int, int>>::iterator> _hashList; //用unordered_map存储 key, value是list中的位置
};

int main()
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; // 返回  1
    cache.put(3, 3);              // 该操作会使得密钥 2 作废
    cout << cache.get(2) << endl; // 返回 -1 (未找到)
    cache.put(4, 4);              // 该操作会使得密钥 1 作废
    cout << cache.get(1) << endl; // 返回 -1 (未找到)
    cout << cache.get(3) << endl; // 返回  3
    cout << cache.get(4) << endl; // 返回  4

    return 0;
}