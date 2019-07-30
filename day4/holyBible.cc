#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

typedef struct Words
{
    int _cnt = 0;
    string _words = "";
} word_t;

bool comp(const word_t &words1, const word_t &words2)
{
    return words1._cnt > words2._cnt;
}

void readFile(const string &filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cout << "ifstream open file " << filename << " error" << endl;
        return;
    }

    vector<word_t> file;
    word_t ifsWord;
    int flag = 0; //标识是否为新单词，1表示是新单词
    while (ifs >> ifsWord._words)
    {
        flag = 1;
        for (auto &fileWord : file)
        {
            if (ifsWord._words == fileWord._words)
            {
                fileWord._cnt++;
                flag = 0; //不是新单词
            }
        }
        if (flag)
        {
            ifsWord._cnt = 1;
            file.push_back(ifsWord);
        }
    }
    sort(file.begin(), file.end(), comp); //调用qsort

    for (size_t idx = 0; idx != 10; ++idx)
    {
        cout << file[idx]._words << "  " << file[idx]._cnt << endl;
    }

    ifs.close();
}

int main()
{
    //这里的Holy_Bible只有小写，标点都被替换成空格了
    readFile("The_Holy_Bible.txt");

    return 0;
}