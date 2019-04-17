#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "paropt/paropt.h"
#include "log/log.h"


void handleFile(const char *path, const char *fileName)
{
    /* char filePath[200]; */
    /* char dstFilePath[200]; */
    /* strcpy(filePath, path); */
    /* strcat(filePath, "\\"); */
    /* strcat(filePath, fileName); */

    /* strcpy(dstFilePath, FLAGS_dstDir.c_str()); */
    /* strcat(dstFilePath, "\\"); */
    /* strcat(dstFilePath, fileName); */
    /* LOG_F(INFO, "path: %s fileName: %s", path, fileName); */
    /* LOG_F(INFO, "file absolute path is: %s", filePath); */
    /* LOG_F(INFO, "dst file absolute path: %s ", dstFilePath); */
    /* LOG_F(INFO, "filePattern: %s ", FLAGS_filePattern.c_str()); */

    /* std::regex fileRegex(FLAGS_filePattern); */
    /* std::string targetFile = fileName; */

    /* if (!std::regex_search(targetFile, fileRegex)) { */
    /*     LOG_F(ERROR, "%s not match %s, exit", fileName, FLAGS_filePattern.c_str()); */
    /*     return; */
    /* } */

    /* if (MoveFile(filePath, dstFilePath)) { */
    /*     LOG_F(INFO, "move file %s success!", filePath); */
    /* } else { */
    /*     LOG_F(INFO, "move file %s fail!", filePath); */
    /* } */
}

void Timeproc(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
{
    /* LOG_SCOPE_FUNCTION(INFO); */
    char mbstr[100];
    /* char dir[100]; */
    time_t now = time(NULL);

    strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("now is %s time reaching ...\n", mbstr);
    /* strcpy(dir, FLAGS_srcDir.c_str()); */
    /* handleMatchFiles(dir, FLAGS_searchSubdirectories, "*", &handleFile); */
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
