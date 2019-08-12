#include "mylog4cpp.h"
#include <string>
using std::string;
using namespace myLogger;

void test0()
{
    mylogger *mylog = mylogger::getMylogger();
    mylog->warn(prefix("warn msg").c_str());
    mylog->error(prefix("error msg").c_str());
    mylog->debug(prefix("debug msg").c_str());
    mylog->info(prefix("info msg").c_str());
    mylogger::destory();
}
#if 0
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

void test2()
{

    logWarn("warn msg");
    logError("error msg");
    logDebug("debug msg, %s","helloworld");
    // printf("%d  %d\n",2,printf("%d\n",3));
    logInfo("1 + 1 = %d",1+1);
    char s1[]="helloworld";
    logInfo("%s",s1);
    printf("%s\n","goodbye");
    logInfo("%s","goodbye");
    logDestory;
}

int main()
{
    // test0();
    // test1();
    test2();

    return 0;
}