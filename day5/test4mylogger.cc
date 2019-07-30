#include "mylog4cpp.h"
#include <string>
using std::string;
using namespace myLogger;

//__FILE__ The name of the current source file
//__LINE__ The line number in the current source file
//__FUNCTION__ Defined as a string literal that contains the undecorated name of the enclosing function. 
// #define LOG_FORMAT __FILE__,__FUNCTION__,__LINE__ 

void test0()
{
    mylogger *mylog = mylogger::getMylogger();
    mylog->warn(prefix("warn msg").c_str());
    mylog->error(prefix("error msg").c_str());
    mylog->debug(prefix("debug msg").c_str());
    mylog->info(prefix("info msg").c_str());
    mylogger::destory();
}

void test1()
{
    //把test0()中的操作封成宏，类似pringf的操作执行打印。
    //暂不支持可变参数，以待以后添加。
    logWarn("warn msg");
    logError("error msg");
    logDebug("debug msg");
    logInfo("info msg");
    logDestory;
}

int main()
{
    // test0();
    test1();

    return 0;
}