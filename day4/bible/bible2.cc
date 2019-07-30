#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::map;
using std::istringstream;

class Dictionary
{
public:
	void read(const char * filename) {
		ifstream ifs(filename);
		if (!ifs.good())
		{
			cout << "ifstream open file error" << endl;
			return;
		}
		string word;
		while (ifs >> word)
		{
			words[word]++;
		}
	}
	
	void store(const char * filename) {
		ofstream ofs(filename);
		map<string, int>::const_iterator i;
		int count = 0;
		for (i = words.begin(); i != words.end(); ++i)
		{
			ofs << i->first << "  " << i->second << endl;
			count += i->second;
		}
		cout << "共有" << count << "词" << endl;
		cout << "  >>end" << endl;
	}
private:
	map<string, int> words;
};


int main()
{
	Dictionary dictionary;
	dictionary.read("../The_Holy_Bible.txt");
	dictionary.store("test.txt");
	return 0;
}
