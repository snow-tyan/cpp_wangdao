#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <iostream>
using std::cout;
using std::endl;
using namespace log4cpp;
 
int main(void)
{
	PatternLayout * ptnLayout1 = new PatternLayout();
	ptnLayout1->setConversionPattern("%d %c [%p] %m%n");
 
	// PatternLayout * ptnLayout2 = new PatternLayout();
	// ptnLayout2->setConversionPattern("%d %c [%p] %m%n");

	PatternLayout * ptnLayout3 = new PatternLayout();
	ptnLayout3->setConversionPattern("%d %c [%p] %m%n");

	OstreamAppender * ostreamAppender = new OstreamAppender(
		"ostreamAppender",
		&cout);
	ostreamAppender->setLayout(ptnLayout1);

	// FileAppender * fileAppender = new FileAppender(
	// 	"fileAppender",
	// 	"wangdao.log");
	// fileAppender->setLayout(ptnLayout2);

	RollingFileAppender * rollingFileAppender = new RollingFileAppender(
		"rollingFileAppender",
		"rollsnow.log",
		5*1024,
		5);
	rollingFileAppender->setLayout(ptnLayout3);

	Category & mycategory = Category::getRoot().getInstance("mycategory");
	mycategory.setPriority(Priority::DEBUG);
	mycategory.addAppender(ostreamAppender);
	// mycategory.addAppender(fileAppender);
	mycategory.addAppender(rollingFileAppender);
	
	for(int idx = 0; idx != 50; ++idx) {
		mycategory.alert("%d this is alert message", idx);
		mycategory.crit("%d this is crit message", idx);
		mycategory.error("%d this is error message",idx);
		mycategory.warn("%d this is warn message", idx);
		mycategory.info("%d this is info message", idx);
		mycategory.notice("%d this is notice message", idx);
	}

	Category::shutdown();

	return 0;
}
