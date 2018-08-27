#include"Heap.h"
template<class W>
struct HuffmanTreeNode
{
    HuffmanTreeNode(const W& weight)
        :_pLeft(NULL)
        ,_pRight(NULL)
        ,_pParent(NULL)
        ,_weight(weight)
    {}

    HuffmanTreeNode<W>* _pLeft;
    HuffmanTreeNode<W>* _pRight;
    HuffmanTreeNode<W>* _pParent;
    W _weight;
};

template<class W>
class HuffmanTree
{
    typedef HuffmanTreeNode<W> pNode;    

public:
    //构造函数
    HuffmanTree()
        :_pRoot(NULL)
    {}

    HuffmanTree(W* array,size_t size,const W& invalid)
    {
        _CreateHuffmanTree(array,size,invalid);
    }

    void _Destroy(pNode* pRoot)
    {
        if(pRoot == NULL)
        {
            return;
        }
        _Destroy(pRoot->_pLeft);
        _Destroy(pRoot->_pRight);
        delete pRoot;
    }

    //析构函数
    ~HuffmanTree()
    {
        _Destroy(_pRoot);
        _pRoot == NULL;
    }

    pNode* GetRoot()
    {
        return _pRoot;
    }


    void _CreateHuffmanTree(W* array,size_t  size,const W& invalid)
    {
        //贪心算法
        struct Compare
        {
            bool operator()(pNode* pLeft,pNode* pRight)
            {
                return pLeft->_weight < pRight->_weight;
            }
        };

        //建小堆
        Heap<pNode*,Compare> hp;
        for(size_t i = 0;i < size;++i)
        {
            if(array[i] != invalid)
            {
                hp.Push(new pNode(array[i]));
            }
        }

        //每次取最小的两个节点
        //直到只剩下一个节点时
        while(hp.size() > 1)
        {
            pNode* num1 = hp.Top();
            hp.Pop();
            pNode* num2 = hp.Top();
            hp.Pop();

            pNode* tmp = new pNode(num1->_weight + num2->_weight);

            tmp->_pLeft = num1;
            tmp->_pRight = num2;
            num1->_pParent = tmp;
            num2->_pParent = tmp;

            hp.Push(tmp);
        }
        _pRoot = hp.Top();
    }
private:
    pNode* _pRoot;
};
