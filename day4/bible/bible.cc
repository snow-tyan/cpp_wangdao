#include <func.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm> 
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;

typedef struct
{
    int cnt;
    string word;
}word_t;



class Dict
{
public:
    //将圣经读取进来，所有的大写字母换成小写字母
    //所有的标点符号换成空格，处理完后存入temp中
    void read(const string & filename)
    {
        char ch;
        _in.open(filename.c_str(),std::ios::in);
        system("touch temp");
        _out.open("temp",std::ios::out);
        ch = _in.get();
        while(EOF!=ch)
        {
            if(ch >= 'A' && ch <='Z')
            {
                ch = ch+0x20;
            }else if (ch >= 'a' && ch <= 'z')
            {

            }
            else if (ch >='0' && ch <= '9')
            {

            }else if(ch == '\n')
            {
                _cntLines++;
            }else
            {
                ch = ' ';
            }
            _cntBytes++;
         //   cout << ch ;
            _out.put(ch);
            
            ch = _in.get();
            
        }
        _in.close();
        _out.close();
    
    }
    void store()
    {
        _in.open("temp",std::ios::in);
        word_t inWord = {0,""};
        int flag = 0;
        while(_in >> inWord.word)
        {
            flag = 1;
            for(auto &curWord:_allWords)
            {
                if(inWord.word == curWord.word)
                {
                    curWord.cnt++;
                    flag = 0;
                }
            }
            if(flag)
            {
                inWord.cnt = 1;
                _allWords.push_back(inWord);
            }
            _cntWords++;
        }
        _in.close();
        sort(_allWords.begin(),_allWords.end(),comp);
        system("rm temp");
    }

    //对vector里面存的数据进行排序后再输出
    static bool comp(const word_t &a,const word_t &b)
    {
        return a.cnt > b.cnt;
    }

    //查看所有的排序结果
    void showAllRes()
    {
        cout << "字节数："    << _cntBytes 
             << "  单词数："  << _cntWords
             << "  行数："    << _cntLines << endl;
        for(auto word : _allWords)
        {
            cout << "单词" << word.word << " 词频：" \
                << word.cnt << endl;
        }
    }
    //查看前N个词频最高的单词
    void showTopN(int n)
    {
        word_t cur;
        cout << "字节数："    << _cntBytes 
             << "  单词数："  << _cntWords
             << "  行数："    << _cntLines << endl;
        cout << "词频最高的" << n << "个词：" << endl;
        for(int i=0;i<n;i++)
        {
            cout << "名次:" << i+1 
                << "单词:" << _allWords[i].word \
                << " 词频:" << _allWords[i].cnt << endl; 
        }
    }
    Dict():_cntBytes(0),_cntWords(0),_cntLines(0){
    }
private:
    ifstream _in;
    ofstream _out;
    vector<word_t> _allWords;
    int _cntBytes;
    int _cntWords;
    int _cntLines;
};

//统计程序运行的时间
class RunTime{
public:
    void begin()
    {
        gettimeofday(&_begin,NULL);
    }
    void res()
    {
        gettimeofday(&_end,NULL);
        int sec,usec;
        sec = _end.tv_sec - _begin.tv_sec;
        if(_end.tv_usec >=_begin.tv_usec)
        {
            usec = _end.tv_usec - _begin.tv_usec;
        }else
        {
            usec = 1000000 -_end.tv_usec + _begin.tv_usec;
            sec --;
        }

        cout << "运行时间：" << sec << "s,"
            << usec << "us" << endl;
    }
private:
    timeval _begin;
    timeval _end;
};

int main(int argc,char *argv[])
{
    int num;
    if(argc > 2)
    {
        num = atoi(argv[1]);
    }else
    {
        num = 20;
    }
    RunTime record;
    Dict bible;
    record.begin();
    bible.read("../The_Holy_Bible.txt");
    bible.store();
  //  my.showAllRes();
    bible.showTopN(num);
    record.res();
    return 0;
}
