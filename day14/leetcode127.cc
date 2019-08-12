#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <map>
#include <queue>
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::queue;
using std::string;
using std::unordered_set;

class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &dic)
    {
        unordered_set<string> dict{dic.begin(), dic.end()};
        map<string, int> dis;
        dis[beginWord] = 1;

        queue<string> q;
        q.push(beginWord);

        while (!q.empty())
        {

            string word = q.front();
            q.pop();

            if (word == endWord)
            {
                break;
            }

            for (int i = 0; i < word.size(); i++)
            {
                string temp = word;
                for (char c = 'a'; c <= 'z'; c++)
                {
                    temp[i] = c;
                    if (dict.count(temp) > 0 && dis.count(temp) == 0)
                    {
                        dis[temp] = dis[word] + 1;
                        q.push(temp);
                    }
                }
            }
        }
        return (dis.count(endWord) == 0) ? 0 : dis[endWord];
    }
};

int main()
{
    Solution solution;
    string beginWord = "hit";
    string endWordWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    cout << solution.ladderLength(beginWord, endWordWord, wordList) << endl;

    string beginWord2 = "hit";
    string endWordWord2 = "cog";
    vector<string> wordList2 = {"hot", "dot", "dog", "lot", "log"};
    cout << solution.ladderLength(beginWord2, endWordWord2, wordList2) << endl;

    return 0;
}