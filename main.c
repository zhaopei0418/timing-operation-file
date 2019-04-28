#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "paropt/paropt.h"
#include "log/log.h"
#include "tool/tool.h"


void Timeproc(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
{
    /* char mbstr[100]; */
    /* char dir[100]; */
    /* time_t now = time(NULL); */

    /* strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", localtime(&now)); */
    log_info("time reaching...");
    handleMatchFiles(srcdir, searchsubdirectories, filepattern, operation, NULL);
}

int main(int argc, char *argv[])
{
    if (parseOption(argc, argv) == 0) {
        log_info("log...%d", argc);
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

    }
    return 0;
}
