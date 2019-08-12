#include <iostream>
#include <string>
#include <stack>
using std::cout;
using std::endl;
using std::stack;
using std::string;

class Solution
{
public:
    bool isValid(string s)
    {
        if (s.empty())
        {
            return true;
        }
        if (s.size() % 2 != 0)
        {
            return false;
        }
        stack<char> stk;
        for (auto &c : s)
        {
            if (c == '{' || c == '[' || c == '(')
            {
                stk.push(c); //左括号入栈
            }
            else
            {
                if (!stk.empty())
                {
                    //右括号，且与栈顶元素匹配
                    if (c == ')' && stk.top() == '(' || c == ']' && stk.top() == '[' || c == '}' && stk.top() == '{')
                    {
                        stk.pop(); //出栈
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        }
        if (!stk.size())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    Solution solution;
    string s1 = "()";
    string s2;
    string s3 = "[()]";
    string s4 = "[)";
    string s5 = "({[{}()]})";
    string s6 = "({[{[()]}]";
    string s7 = "{[()]}";

    if (solution.isValid(s7))
    {
        cout << "Valid" << endl;
    }
    else
    {
        cout << "Invalid" << endl;
    }

    return 0;
}