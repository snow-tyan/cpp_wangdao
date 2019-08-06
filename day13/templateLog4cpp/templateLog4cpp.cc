#include "mylog4cpp.h"
#include <string>
using std::string;
using namespace myLogger;
#if 0
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
    //把test0()中的操作封成宏，类似printf的操作执行打印。
    //暂不支持可变参数，以待以后添加。
    logWarn("warn msg");
    logError("error msg");
    logDebug("debug msg");
    logInfo("info msg");
    logDestory;
}
#endif

template<typename... Args>
string Prefix(Args... args)
{
    
}
void test2()
{
    //测试可变参数
    int num = 10;
    // mylogger::getMylogger()->info("num = %d",num);
    mylogger::getMylogger()->info(Prefix("num = %d",num).c_str());

}

int main()
{
    // test0();
    // test1();
    test2();

    return 0;
}