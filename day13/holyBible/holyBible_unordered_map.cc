#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::ifstream;
using std::unordered_map;
using std::pair;
using std::string;
using std::vector;

typedef pair<string, int> PAIR;

bool comp(const PAIR &it1, const PAIR &it2)
{
    return it1.second > it2.second;
}

void Sortunordered_map(const unordered_map<string, int> & fileMap)
{
    vector<PAIR> fileVec(fileMap.cbegin(), fileMap.cend());
    sort(fileVec.begin(), fileVec.end(), comp); //调用sort

    auto iter = fileVec.cbegin();
    for (size_t i = 0; i != 10; ++i)
    {
        cout << iter->first << "  " << iter->second << endl;
        ++iter;
    }
}

void readFile(const string &filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cout << "ifstream open file " << filename << " error" << endl;
        return;
    }

    time_t startTime,endTime;
    startTime=clock();
    unordered_map<string, int> fileMap;
    string word;
    while (ifs >> word)
    {
        //store to fileMap
        fileMap[word]++;
    }
    ifs.close();

    // cout<<"------Sort By Frequency------"<<endl;
    Sortunordered_map(fileMap);

    endTime=clock();
    cout << "use time = " << (endTime - startTime) / 1000 << " ms" << endl;
}

int main()
{
    //这里的Holy_Bible只有小写，标点都被替换成空格了
    // cout<<"Read File...."<<endl;
    readFile("The_Holy_Bible.txt");

    return 0;
}