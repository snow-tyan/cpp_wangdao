#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::stringstream;
using std::vector;

struct Info
{
    //构造函数
    Info(const string &key, const string &val)
        : _key(key), _value(val) {}

    string _key;
    string _value;
};

void test0()
{
    stringstream ss; //相当于一个缓冲区，sizeof(ss)==某个值
    // cout<<sizeof(ss)<<endl;
    int number1 = 100, number2 = 200;
    ss << "number1 = " << number1 << endl
       << "number2 = " << number2 << endl;

    string line = ss.str(); //转成字符串
    cout << line;
}

void test1()
{
    stringstream ss;
    int number1 = 100, number2 = 200;
    ss << "number1 " << number1
       << "number2 " << number2;

    string key;
    int value;
    while (!ss.eof())
    {
        ss >> key >> value; //以空格、tab、换行分隔
        cout << key << "--->" << value << endl;
    }
}

void readConfig(const string &filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cout << "ifstream open file error" << endl;
        return;
    }

    string line;
    vector<struct Info> config;
    while (getline(ifs, line))
    {
        istringstream iss(line); //创建一个字符串输入流，保存line内容
        string key, value;
        while (!iss.eof())
        {
            iss >> key >> value;
            struct Info info(key, value); //创建一个Info对象，传递key,value
            config.push_back(info);
        }
    }

    for (auto &c : config)
    {
        cout << c._key << "--->" << c._value << endl;
    }
    cout << endl;
}

void test2()
{
    string filename = "server.conf";
    readConfig(filename);
}

int main()
{
    // test0();
    // test1();
    test2();

    return 0;
}