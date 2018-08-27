#include<iostream>
#include<vector>
using namespace std;

template<class T>

struct Less
{
    bool operator()(const T& left,const T& right)
    {
        return left < right;
    }
};

template<class T>
struct Greater
{
    bool operator()(const T& left,const T& right)
    {
        return left > right;
    }
};

template<class T,class Comper = Greater<T> >
class Heap
{
public:
    Heap()
     :_a(0)
    {}

    Heap(T* a,size_t n)
    {
        _a.resize(n);
        //构造一个堆分为存储数据和调整数据
        for(size_t i = 0;i < n;i++)
        {
            _a[i] = a[i];
        }

        //调整数据，一个树有多少非叶子节点就进行多少次的调整
        //从最后一个非叶子节点调整
        for(int i = ((int)n -2)/2;i >= 0;i--)
        {
            _AdjustDown(i);
        }
    }

        size_t size()
        {
            return _a.size();
        }

        void Push(const T& x)
        {
            _a.push_back(x);
            _AdjustUp(_a.size() - 1);
        }

        void Pop()
        {
            swap(_a[0],_a[_a.size() - 1]);
            _a.pop_back();
            _AdjustDown(0);
        }

        const T& Top()
        {
            return _a[0];
        }
protected:
    void _AdjustUp(int child)
    {
        Comper com;
        int parent = (child - 1) / 2;
        int _child = child;
        while(parent >= 0)
        {
            if(com(_a[_child],_a[parent]))
            {
                swap(_a[_child],_a[parent]);
                _child = parent;
                parent = (_child - 1)/2;
            }
            else
            {
                break;
            }
        }
    }

    void _AdjustDown(int root)
    {
        Comper com;
        int parent = root;
        int child = 2 * parent + 1;//左孩子
        while(child < (int)_a.size())
        {
            //如果右孩子存在，且小于左孩子，使孩子指向右
            if(child + 1 < (int)_a.size() && com(_a[child + 1],_a[child]))
            {
                ++child;
            }
            if(com(_a[child],_a[parent]))
            {
                swap(_a[parent],_a[child]);
                parent = child;
                child = 2 * parent + 1;
            }
            else
            {
                break;
            }
        }
    }
protected:
      vector<T> _a;
};
