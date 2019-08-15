#pragma once
#include "queryResult.hh"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::map;
using std::set;
using std::shared_ptr;
using std::string;
using std::vector;

class QueryResult;

class TextQuery
{
public:
    TextQuery(const string &filename);

    QueryResult query(const string &word);

private:
    static string cleanup_str(const string &word); //去除标点及大写

private:
    shared_ptr<vector<string>> _file;      //文件内容
    map<string, shared_ptr<set<int>>> _wm; //单词及行号
};

TextQuery::TextQuery(const string &filename)
    : _file(new vector<string>)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cout << "ifs open " << filename << " failed" << endl;
        exit(-1);
    }
    string text;
    while (std::getline(ifs, text))
    {
        _file->push_back(text);
        int lineNum = _file->size();
        istringstream iss(text);
        string word;
        while (iss >> word)
        {
            word = cleanup_str(word);
            auto &lines = _wm[word];
            if (!lines)
            {
                lines.reset(new set<int>());
            }
            lines->insert(lineNum);
        }
    }
}

string TextQuery::cleanup_str(const string &word)
{
    string ret;
    for (auto it = word.begin(); it != word.end(); ++it)
    {
        if (!ispunct(*it))
            ret += tolower(*it);
    }
    return ret;
}

QueryResult TextQuery::query(const string &word)
{
    static shared_ptr<set<int>> nodata(new set<int>);
    auto loc = _wm.find(cleanup_str(word));
    if (loc != _wm.end())
    {
        return QueryResult(word, loc->second, _file);
    }
    else
    {
        return QueryResult(word, nodata, _file);
    }
}
