#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream; //字符串流将每行string分解为word
using std::map;
using std::set;
using std::string;
using std::vector;

class TextQuery
{
public:
    void readFile(const string filename)
    {
        ifstream ifs(filename);
        string text;
        while (getline(ifs, text)) //读取每一行文本入vector
        {
            _text.push_back(text);
            int line = _text.size(); //行号
            istringstream iss(text);
            string word;
            while (iss >> word) //提取每一个word
            {
                auto &lines = _map[word]; //返回一个set<int>的引用
                lines.insert(line);       //插入行号入set
            }
        }
    }

    void query(const string &word)
    {
        auto result = _map.find(word); //返回一个迭代器
        if (result != _map.end())
        {
            //查找成功，打印结果
            cout << result->first << endl;
            for (auto &line : result->second)
            {
                cout << "    (line " << line << "): ";
                cout << _text[line - 1] << endl;
            }
        }
        else
        {
            cout << "Text has no this word!" << endl;
        }
    }

private:
    vector<string> _text;       //保存整个输入文件的拷贝，一行算作一个string，下标即行号
    map<string, set<int>> _map; //单词及对应行号
};

//程序测试用例
int main()
{
    string qWord;
    cout << " > input query word: ";
    while (std::cin >> qWord)
    {
        string queryWord(qWord);
        TextQuery tq;
        // tq.readFile("test.txt");
        tq.readFile("china_daily.txt");
        tq.query(queryWord);
        cout << " > input query word: ";
    }
    cout << "\nBye!" << endl;

    return 0;
}