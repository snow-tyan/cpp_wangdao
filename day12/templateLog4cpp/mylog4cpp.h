#pragma once
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
using namespace log4cpp;

namespace myLogger
{

class mylogger
{
public:
    static mylogger *getMylogger()
    {
        if (!_pMylogger)
            _pMylogger = new mylogger();
        return _pMylogger;
    }

    static void destory()
    {
        if (_pMylogger)
            delete _pMylogger;
    }

    template <typename... Args>
    void warn(Args... args)
    {
        _myCategory.warn(args...);
    }

    template <typename... Args>
    void error(Args... args)
    {
        _myCategory.error(args...);
    }

    template <typename... Args>
    void debug(Args... args)
    {
        _myCategory.debug(args...);
    }

    template <typename... Args>
    void info(Args... args)
    {
        _myCategory.info(args...);
    }

private:
    mylogger()
        : _myCategory(Category::getRoot().getInstance("myCategory"))
    {
        cout << "mylogger()" << endl;
        OstreamAppender *_osAppender;          //输出到ostream
        FileAppender *_fileAppender;           //输出到文件
        RollingFileAppender *_rollingAppender; //输出到回卷文件
        BasicLayout *_bscLayout;               //简单布局，过于单调
        //两个布局，一个输出到stdout，一个输出到文件
        PatternLayout *_ptnLayout1, *_ptnLayout2; //可设置成日志的输出格式

        _osAppender = new OstreamAppender("osAppender", &cout);
        _fileAppender = new FileAppender("fileAppender", "snow.log");
        _rollingAppender = new RollingFileAppender("rollingfileAppender", "rollsnow.log", 1024 * 5, 5);
        _bscLayout = new BasicLayout();
        _ptnLayout1 = new PatternLayout();
        _ptnLayout2 = new PatternLayout();

        _ptnLayout1->setConversionPattern("%d{%a %b %d %H:%M:%S %Y} %c [%p] %m%n");
        _ptnLayout2->setConversionPattern("%d{%a %b %d %H:%M:%S %Y} %c [%p] %m%n");
        _osAppender->setLayout(_ptnLayout1);
        _fileAppender->setLayout(_bscLayout);
        _rollingAppender->setLayout(_ptnLayout2);
        _myCategory.addAppender(_osAppender);
        _myCategory.addAppender(_fileAppender);
        _myCategory.addAppender(_rollingAppender);
        _myCategory.setPriority(Priority::DEBUG);
    }

    ~mylogger()
    {
        cout << "~mylogger()" << endl;
        Category::shutdown();
    };

private:
    static mylogger *_pMylogger;
    Category &_myCategory;
};

//放在头文件里，若类的声明和定义分在不同的文件 会造成多次编译的错误
mylogger *mylogger::_pMylogger = nullptr; //静态成员，类外初始化

//一些宏定义
#define prefix(msg) string("[").append(__FILE__).append(": ").append(__FUNCTION__).append(", ").append(std::to_string(__LINE__)).append("] ").append(msg)

#define logWarn(msg, ...) mylogger::getMylogger()->warn(prefix(msg).c_str(), ##__VA_ARGS__)
#define logError(msg, ...) mylogger::getMylogger()->error(prefix(msg).c_str(), ##__VA_ARGS__)
#define logDebug(msg, ...) mylogger::getMylogger()->debug(prefix(msg).c_str(), ##__VA_ARGS__)
#define logInfo(msg, ...) mylogger::getMylogger()->info(prefix(msg).c_str(), ##__VA_ARGS__)
#define logDestory mylogger::destory()

} //end of namespace myLogger
