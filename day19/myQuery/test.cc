#include "textQuery.hh"
#include "queryResult.hh"

int main()
{
    TextQuery tq("china_daily.txt");
    string qWord;
    cout<<" >pls input query word:";
    while (std::cin >> qWord)
    {
        QueryResult qRes = tq.query(qWord);
        print(cout, qRes);
        cout<<" >pls input query word:";
    }
    cout << "\nBye!" << endl;
    return 0;
}