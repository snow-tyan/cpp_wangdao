#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::map;
using std::shared_ptr;
using std::ostream;

class QueryResult
{
friend ostream& print(ostream&, const QueryResult&);

public:
    using iterator = set<int>::const_iterator;

    QueryResult(string word, shared_ptr<set<int>> line,
                shared_ptr<vector<string>> file)
        : _sought(word), _lines(line), _file(file)
    {}

    size_t size() const {  return _lines->size();   }
    iterator begin() const {    return _lines->begin(); }
    iterator end() const {  return _lines->end();   }

    shared_ptr<vector<string>> getFile() { return _file; }

private:
    string _sought;//查询的单词
    shared_ptr<set<int>> _lines;//行号
    shared_ptr<vector<string>> _file;//文件
};

ostream& print(ostream&os, const QueryResult&qResult)
{
    os << qResult._sought << " occurs " << qResult.size() << " times" << endl;
    for(auto it = qResult.begin(); it!=qResult.end();++it)
    {
        os << "    (line " << *it << ")"
           << *(qResult._file->begin() + *it - 1) << endl;
    }
    return os;
}