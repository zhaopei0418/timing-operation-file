#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <signal.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "paropt/paropt.h"
#include "log/log.h"
#include "tool/tool.h"


#ifdef _WIN32
void Timeproc(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
{
    log_info("time reaching...");
    handleMatchFiles(srcdir, dstdir, searchsubdirectories, filepattern, operation, NULL);
}
#else
void signalHandler(int signo)
{
    switch (signo) {
        case SIGALRM:
            log_info("time reaching...");
            handleMatchFiles(srcdir, dstdir, searchsubdirectories, filepattern, operation, NULL);
            break;
    }
}
#endif

int main(int argc, char *argv[])
{
    if (parseOption(argc, argv) == 0) {
        log_info("log...%d", argc);
#ifdef _WIN32
        BOOL bRet;
        MSG msg;
        UINT uElapse = delaytime;

        UINT timerid = SetTimer(NULL, 0, uElapse, (TIMERPROC)Timeproc);

        while ((bRet= GetMessage(&msg, NULL, 0, 0)) != 0) {
            if (bRet == -1) {

            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
#else
        if (signal(SIGALRM, signalHandler) == SIG_ERR) {
            log_error("signal error!");
            exit(-1);
        }

        struct itimerval newValue;
        newValue.it_value.tv_sec = delaytime / 1000;
        newValue.it_value.tv_usec = (delaytime % 1000) * 1000;
        newValue.it_interval.tv_sec = delaytime / 1000;
        newValue.it_interval.tv_usec = (delaytime % 1000) * 1000;
        if (setitimer(ITIMER_REAL, &newValue, NULL) == -1) {
            log_error("setitimer error!");
            exit(-1);
        }

        while (1);
#endif
    }
    return 0;
}
