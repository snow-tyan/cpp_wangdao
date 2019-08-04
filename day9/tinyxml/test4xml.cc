#include "tinyxml2.h"
#include <iostream>
#include <regex> //regular expression
#include <string>
#include <vector>
#include <fstream>
using std::cout;
using std::endl;
using std::ofstream;
using std::regex;
using std::string;
using std::vector;
using namespace tinyxml2;

struct RssItem
{
	string title;
	string link;
	string description;
	string content;
};

class RssReader
{
public:
	// RssReader(); //构造函数

	void parseRss(const char *filename); //解析
	void dump(const string &filename);   //输出
private:
	vector<RssItem> _rss;
};

void RssReader::parseRss(const char *filename)
{
	XMLDocument doc;
	doc.LoadFile(filename);
	if (doc.ErrorID())
	{
		cout << "doc load error!" << endl;
		return;
	}
	RssItem rssItem;
	XMLElement *itemElement;
	itemElement = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
	while(itemElement)
	{
		XMLElement *titleElement = itemElement->FirstChildElement("title");
		XMLElement *linkElement = itemElement->FirstChildElement("link");
		XMLElement *descriptionElement = itemElement->FirstChildElement("description");
		XMLElement *contentElement = itemElement->FirstChildElement("content:encoded");

		rssItem.title = titleElement->GetText();
		rssItem.link = linkElement->GetText();
		rssItem.description = descriptionElement->GetText();
		rssItem.content = contentElement->GetText();

		cout << "title:" << rssItem.title << endl
			 << endl;
		cout << "link:" << rssItem.link << endl
			 << endl;

		//过滤一下description和content
		regex reg("<[^>]*>");

		rssItem.description = regex_replace(rssItem.description, reg, "");
		rssItem.content = regex_replace(rssItem.content, reg, "");
		cout << "description:" << rssItem.description << endl
			 << endl;
		cout << "content: " << endl
			 << rssItem.content << endl;

		_rss.push_back(rssItem);
		itemElement = itemElement->NextSiblingElement("item");
	}
}

void RssReader::dump(const string &filename)
{
	ofstream ofs(filename);
	auto begin = _rss.cbegin();
	auto end = _rss.cend();
	int i = 0;
	while (begin != end)
	{
		ofs << "<doc>" << endl
			<< "<docid>" << ++i << "</docid>" << endl
			<< "<title>" << begin->title << "</title>" << endl
			<< "<link>" << begin->link << "</link>" << endl
			<< "<description>" << begin->description << "</description>" << endl
			<< "<content>" << begin->content << "</content>" << endl
			<< "</doc>" << endl
			<< endl;
		++begin;
	}

	ofs.close();
}

int main(void)
{
	RssReader rss;
	rss.parseRss("coolshell.xml");
	rss.dump("pagelib.dat");

	return 0;
}
