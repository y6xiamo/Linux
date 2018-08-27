#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<algorithm>
#include<assert.h>
#include"huffman.hpp"
using namespace std;
struct CharInfo
{
    CharInfo(size_t count = 0)
        :_count(count)
    {}

    bool operator != (const CharInfo& info)
    {
        return _count != info._count;
    }

    bool operator == (const CharInfo& info)
    {
        return _count == info._count;
    }

    CharInfo operator + (const CharInfo& info)
    {
        CharInfo tmp(*this);
        tmp._count += info._count;
        return tmp;
    }

    bool operator < (const CharInfo& info)
    {
        return _count < info._count;
    }

    char _ch;//表示当前字符
    long long _count;//当前字符出现的次数
    string _strCode;//当前字符对应的编码
};

class FileCompress
{
public:
    //构造函数，对_charInfo进行初始化
    FileCompress()
    {
        for(size_t i = 0;i < 256;++i)
        {
            _charInfo[i]._ch = i;
            _charInfo[i]._count = 0; 
        }
    }


    void GetHuffManCode(HuffmanTreeNode<CharInfo>* pRoot)
    {
        if(pRoot)
        {
            GetHuffManCode(pRoot->_pLeft);
            GetHuffManCode(pRoot->_pRight);

            if(pRoot->_pLeft == NULL && pRoot->_pRight == NULL)
            {
                HuffmanTreeNode<CharInfo>* pCur = pRoot;
                HuffmanTreeNode<CharInfo>* pParent = pCur->_pParent;

                string& strCode = _charInfo[(unsigned char)pCur->_weight._ch]._strCode;
                while(1)
                {
                    if(pCur == pParent->_pLeft)
                    {
                        strCode += '0';
                    }
                    else
                    {
                        strCode += '1';
                    }
                    pCur = pParent;
                    pParent = pCur->_pParent;
                }
                reverse(strCode.begin(),strCode.end());
            }
        }

    }

    void CompressFile(const string& filePath)
    {
        //1.读取原文件，统计每个字符出现的次数
        FILE* fIn = fopen(filePath.c_str(),"r");
        if(NULL == fIn)
        {
            cout<<"打开文件失败"<<endl;
            return;
        }

        char* pReadBuff = new char[1024];
        while(true)
        {
            size_t readSize = fread(pReadBuff,1,1024,fIn);
            if(readSize == 0)
            {
                break;
            }

            for(size_t i = 0;i < readSize;++i)
            {
                _charInfo[(unsigned char)pReadBuff[i]]._count++;
            }
        }
            //2.以每个字符出现的次数为权值创建huffman树
            HuffmanTree<CharInfo> ht(_charInfo,256,CharInfo(0));

            //3.根据huffman树来获取huffman编码
            GetHuffManCode(ht.GetRoot());


            //写压缩文件的头部信息
            string filePostFix = GetFilePostFix(filePath);
            string strCodeInfo;
            char strCount[32] = {0};
            size_t LineCount = 0;;
            for(size_t i = 0;i < 256;++i)
            {
                if(_charInfo[i]._count != 0)
                {
                    strCodeInfo += _charInfo[i]._ch;
                    strCodeInfo += ',';
                  //  itoa(_charInfo[i]._count,strCount,10);
                    sprintf(strCount,"%d",(int)_charInfo[i]._count);
                    strCodeInfo += strCount;
                    strCodeInfo += '\n';
                    LineCount++;
                }
            }

            string strHeadInfo;
            strHeadInfo += filePostFix;
            strHeadInfo += '\n';
            //itoa(LineCount,strCount,10);
            sprintf(strCount,"%d",(int)LineCount);
            strCodeInfo += strCount;
            strHeadInfo += '\n';
            strHeadInfo += strCodeInfo;

            //4.用每个字符的编码重新改写原文件
            FILE *fOut = fopen("haha.txt","w");
            assert(fOut);
            //写压缩编码的信息
            fwrite(strHeadInfo.c_str(),1,strHeadInfo.length(),fOut);
            char* pWriteBuff = new char[1024];
            char c = 0; 

            char pos = 0;//标记
            size_t writeSize = 0;

            fseek(fIn,0,SEEK_SET);//重新设置，将文件指针指向开头
            while(true)
            {
                size_t readSize = fread(pReadBuff,1,1024,fIn);
                if(readSize == 0)
                {
                    break;
                }
              
                for(size_t i = 0;i < readSize;++i)
                {
                    string strCode = _charInfo[(unsigned char)pReadBuff[i]]._strCode;
                    for(size_t j = 0;j < strCode.size();++j)
                    {
                        c <<= 1;
                        pos++;
                        if(strCode[j] == '1')
                        {
                            c |= 1;
                        }
                        if(pos == 8)
                        {
                            pWriteBuff[writeSize++] = c;
                            if(writeSize == 1024)
                            {
                                fwrite(pWriteBuff,1,1024,fOut);
                                writeSize = 0;
                            }
                            pos = 0;
                        }
                    }
                }
            } 
        if(pos < 8)
        {
            pWriteBuff[writeSize++] = (c << (8-pos));
        }

        fwrite(pWriteBuff,1,writeSize,fOut);

        fclose(fIn);
        fclose(fOut);

        delete[] pReadBuff;
        delete[] pWriteBuff;
    }

    string GetFilePostFix(string FilePath)
    {
        size_t pos = FilePath.find_last_of('.');
        return FilePath.substr(pos);
    }

    string GetFilePath(string FilePath)
    {
        size_t pos = FilePath.find_last_of('.');
        return FilePath.substr(0,pos);
    }


    void UnCompressFile(const string filePath)
    {
        FILE* fIn = fopen(filePath.c_str(),"r");
        assert(fIn);

        string strFilePostFIx;
        ReadLine(fIn,strFilePostFIx);

        string strLineCount;
        ReadLine(fIn,strLineCount);

        string strCodeInfo;
        //这块也有坑
        size_t lineCount = atoi(strLineCount.c_str());
        for(size_t i = 0;i < lineCount;++i)
        {
            strCodeInfo = "";
            ReadLine(fIn,strCodeInfo);
            _charInfo[(unsigned char)strCodeInfo[0]]._count = atoi(strCodeInfo.c_str() + 2);
        }

        //构建哈夫曼树
        HuffmanTree<CharInfo> ht(_charInfo,256,CharInfo(0));

        HuffmanTreeNode<CharInfo>* pCur = ht.GetRoot();

        string compressFilePath = GetFilePath(filePath);

        compressFilePath += strFilePostFIx;
        FILE* fOut = fopen(compressFilePath.c_str(),"w");
        assert(fOut);

        //解压缩
        char* pReadBuff = new char[1024];
        char* pWriteBuff = new char[1024];
        size_t writeSize = 0;
        size_t pos = 8;
        size_t fileSize = pCur->_weight._count;
        while(true)
        {
            size_t readSize = fread(pReadBuff,1,1024,fIn);
            if(readSize == 0)
            {
                break;
            }

            for(size_t i = 0;i < readSize;++i)
            {
                pos = 8;
                while(pos--)
                {
                    if(pReadBuff[i] & (1 << pos))
                    {
                        pCur = pCur->_pRight;
                    }
                    else
                    {
                        pCur = pCur->_pLeft;
                    }
                    if(pCur->_pLeft == NULL && pCur->_pRight == NULL)
                    {
                        pWriteBuff[writeSize++] = pCur->_weight._ch;
                        if(writeSize == 1024)
                        {
                            fwrite(pWriteBuff,1,1024,fOut);
                            writeSize = 0;
                        }
                        if(--fileSize == 0)
                        {
                            fwrite(pWriteBuff,1,writeSize,fOut);
                            break;
                        }
                        pCur = ht.GetRoot();
                    }
                }
            }
        }
        fwrite(pWriteBuff,1,writeSize,fOut);
        delete[] pReadBuff;
        delete[] pWriteBuff;
        
        fclose(fIn);
        fclose(fOut);
    }
    

    //有坑
    void ReadLine(FILE* fIn,string& strInfo)
    {
        char c = fgetc(fIn);
        //读到文件结果
        if(c == EOF)
        {
            return;
        }

        while(c != '\n')
        {
           strInfo += c;
           c = fgetc(fIn);

           if(c == EOF)
           {
               return;
           }
        }
    }

private:
    CharInfo _charInfo[256];
};

void TestFileCompress()
{
    FileCompress fc;
    fc.CompressFile("test.txt");
}
