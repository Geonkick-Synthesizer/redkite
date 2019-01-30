#include <RkMain.h>
#include <RkLog.h>

RkMain::RkMain()
{
        RK_LOG_INFO("called");
}

RkMain::RkMain(int argc, char **argv)
{
       RK_UNUSED(argc);
       RK_UNUSED(argv);
       RK_LOG_INFO("called");
}

RkMain::~RkMain()
{
}

int RkMain::exec()
{
        RK_LOG_INFO("called");
        return 0;
}
