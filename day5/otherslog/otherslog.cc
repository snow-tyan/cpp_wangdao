#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <iostream>
using log4cpp::Category;
using log4cpp::FileAppender;
using log4cpp::OstreamAppender;
using log4cpp::PatternLayout;
using log4cpp::Priority;
using std::cout;
using std::endl;

class Mylogger
{
public:
    static Mylogger *getInstance()
    {
        if (NULL == _pMylog)
        {
            _pMylog = new Mylogger("myLog.txt");
        }
        return _pMylog;
    }

    static Mylogger *getInstance(const char *LogFileName)
    {
        if (NULL == _pMylog)
        {
            _pMylog = new Mylogger(LogFileName);
        }
        return _pMylog;
    }

    static void destory()
    {
        if (_pMylog)
        {
            Category::shutdown();
            delete _pMylog;
        }
    }

    void warn(const char *msg)
    {
        _mycategory.warn("%s", msg);
    }

    void warn(const char *msg, const char *file, const char *func, int line)
    {
        _mycategory.warn("%s@%s,%d : %s", func, file, line, msg);
    }

    void error(const char *msg)
    {
        _mycategory.error("%s", msg);
    }
    
    void error(const char *msg, const char *file, const char *func, int line)
    {
        _mycategory.error("%s@%s,%d : %s", func, file, line, msg);
    }

    void debug(const char *msg)
    {
        _mycategory.debug("%s", msg);
    }

    void debug(const char *msg, const char *file, const char *func, int line)
    {
        _mycategory.debug("%s@%s,%d : %s", func, file, line, msg);
    }

    void info(const char *msg)
    {
        _mycategory.info("%s", msg);
    }

    void info(const char *msg, const char *file, const char *func, int line)
    {
        _mycategory.info("%s@%s,%d : %s", func, file, line, msg);
    }

private:
    Mylogger(const char *LogFileName)
        : _ptnLayout1(new PatternLayout())
        , _ptnLayout2(new PatternLayout())
        , _osAppender(new OstreamAppender("osAppender", &cout))
        , _fAppender(new FileAppender("fAppender", LogFileName))
        , _mycategory(Category::getRoot().getInstance("mycategory"))
    {
        cout << "Mylogger()" << endl;
        _ptnLayout1->setConversionPattern("%d [%p] %m%n");
        _ptnLayout2->setConversionPattern("%d [%p] %m%n");
        _osAppender->setLayout(_ptnLayout1);
        _fAppender->setLayout(_ptnLayout2);
        _mycategory.setPriority(Priority::DEBUG);
        _mycategory.addAppender(_osAppender);
        _mycategory.addAppender(_fAppender);
    }

    ~Mylogger()
    {
        cout << "~Mylogger()" << endl;
    }

private:
    //data
    static Mylogger *_pMylog;
    PatternLayout *_ptnLayout1;
    PatternLayout *_ptnLayout2;
    OstreamAppender *_osAppender;
    FileAppender *_fAppender;
    Category &_mycategory;
};

Mylogger *Mylogger::_pMylog = NULL;

#define FILEN __FILE__
#define FUNC __FUNCTION__
#define LINE __LINE__
int main()
{
    Mylogger *log = Mylogger::getInstance();
    log->warn("This is warn msg!", FILEN, FUNC, LINE);
    log->error("This is error msg!", FILEN, FUNC, LINE);
    log->debug("This is debug msg!", FILEN, FUNC, LINE);
    log->info("This is info msg!", FILEN, FUNC, LINE);
    log->warn("This is warn msg!");
    log->error("This is error msg!");
    log->debug("This is debug msg!");
    log->info("This is info msg!");
    Mylogger::destory();

    return 0;
}
