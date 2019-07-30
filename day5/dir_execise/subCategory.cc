#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/Layout.hh>
#include <log4cpp/BasicLayout.hh>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;


int main(int argc, char** argv) {
	Appender *appender1 = new OstreamAppender("console", &cout);
	appender1->setLayout(new BasicLayout());

	Appender *appender2 = new FileAppender("default", "program.log");
	appender2->setLayout(new BasicLayout());

	Category& root = Category::getRoot();
	root.setPriority(Priority::NOTSET);
	root.addAppender(appender1);

	Category& sub1 = root.getInstance(string("sub1"));
    //不设定优先级默认最低
	sub1.addAppender(appender2);

	// use of functions for logging messages
	root.error("root error");
    root.warn("root warn");
    root.notice("root notice");
    root.info("root info");
	root.debug("root debug");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");
	//
	//// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");
	//
	//// use of streams for logging messages
	root << Priority::ERROR << "Streamed root error";
	root << Priority::INFO << "Streamed root info";
	sub1 << Priority::ERROR << "Streamed sub1 error";
	sub1 << Priority::WARN << "Streamed sub1 warn";
	//
	// or this way:
	root.errorStream() << "Another streamed error";

	return 0;
}
