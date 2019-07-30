#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

vector<string> file;

void printStreamStatus(ifstream &ifs)
{
    cout << "badbit=" << ifs.bad() << endl
         << "failbit=" << ifs.fail() << endl
         << "eofbit=" << ifs.eof() << endl
         << "goodbit=" << ifs.good() << endl;
}

void test0()
{
    ifstream ifs;
    ifs.open("../Makefile");
    // printStreamStatus(ifs);
    if (!ifs)
    {
        cout << "ifstream open error" << endl;
        return;
    }

    // string word;
    // while(ifs>>word)//默认以空格分隔
    // {
    //     cout<<word<<endl;
    // }

    //获取一行数据
    //1.使用成员函数ifs.getline(buf,1000)，这样又回到C风格了
    //2.使用std::getline(流，string &);
    string line;
    while (std::getline(ifs, line))
    {
        file.push_back(line);
        // cout<<line<<endl;
    }
    //范围for循环
    // for(auto &c:file)
    // {
    //     cout<<c<<endl;
    // }

    ifs.close();
}

void test1()
{
    ofstream ofs("test");
    if (!ofs)
    {
        cout << "ofstream open file error" << endl;
        return;
    }

    for (auto &c : file)
    {
        ofs << c << endl;
    }

    ofs.close();
}

void test2()
{
    ofstream ofs("test", std::ios::app);
    if (!ofs)
    {
        cout << "ofstream open file error" << endl;
        return;
    }

    ofs << "this is new line" << endl;

    ofs.close();
}

void test3()
{
    string filename("file");
    fstream fs(filename);
    if (!fs)
    {
        cout << "fstream open file error" << endl;
        return;
    }

    int val;
    for (size_t idx = 0; idx != 10; ++idx)
    {
        cin >> val;
        fs << val << " ";
    }
    cout << "当前文件位置：" << fs.tellg() << endl;

    fs.seekg(std::ios::beg);
    cout << "当前文件位置：" << fs.tellg() << endl;
    for (size_t idx = 0; idx != 10; ++idx)
    {
        fs >> val;
        cout << val << " ";
    }

    fs.close();
}

//把某文件中的内容一次性读完
void test4()
{
    string filename("test");
    ifstream ifs(filename, std::ios::ate);
    if (!ifs)
    {
        cout << "ifstream open file error" << endl;
        return;
    }
    // cout<<ifs.tellg()<<endl;
    int length = ifs.tellg();
    char *buf = new char[length + 1](); //直接调用ifs.tellg()+1会产生+运算符的二义性
    ifs.seekg(std::ios::beg);
    ifs.read(buf, length);
    // printf("%s\n",buf);
    string strTest(buf); //C风格的字符串封进C++风格字符串
    cout << strTest << endl;

    delete[] buf;
    ifs.close();
}

int main()
{
    // test0();
    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}