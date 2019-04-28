#include <windows.h>
#include <string.h>
#include "tool.h"
#include "../log/log.h"
#include "../regex/re.h"

void handleMatchFiles(const char *dir, BOOL_TYPE searchSubdirectories, const char *pattern, OPERATOR_TYPE oper,
                      void (*handleCallBack)(const char *path, const char *fileName, OPERATOR_TYPE oper))
{
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    char dirNew[CHAR_BUFF_LENGTH];
    log_info("dir is: %s", dir);
    log_info("pattern is %s", pattern);
    re_t filePattern = re_compile(pattern);
    int match_idx = -1;

    strcpy(dirNew, dir);
    strcat(dirNew, "\\*.*");
    hFind = FindFirstFile(dirNew, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        log_error("Failed to find first file!");
        return;
    }

    do {
        match_idx = -1;
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            log_info("%s \t<dir>", findData.cFileName);
            if (searchSubdirectories) {
                mergePath(dirNew, dir, findData.cFileName);
                handleMatchFiles(dirNew, B_TRUE, pattern, oper, handleCallBack);
            }
        } else {
            log_info("find file is: %s", findData.cFileName);
            if ((match_idx = re_matchp(filePattern, findData.cFileName)) != -1) {
                if (handleCallBack != NULL)
                    handleCallBack(dir, findData.cFileName, oper);
                else
                    handleFile(dir, findData.cFileName, oper);
            } else {
                log_info("%s not match pattern %s", findData.cFileName, pattern);
            }
        }
    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);
}

char* mergePath(char *dstpath, const char *dir, const char *fileName)
{
    strcpy(dstpath, dir);
    strcat(dstpath, "\\");
    strcat(dstpath, fileName);
    return dstpath;
}

static void handleFile(const char *path, const char *fileName, OPERATOR_TYPE oper)
{
    char filePath[CHAR_BUFF_LENGTH];
    char dstFilePath[CHAR_BUFF_LENGTH];
    mergePath(filePath, path, fileName);

    mergePath(dstFilePath, dstdir, fileName);
    log_info("file absolute path is: %s", filePath);
    log_info("dst file absolute path: %s ", dstFilePath);
    log_info("filePattern: %s ", filepattern);

    if (oper == OP_MOVE) {
        if (MoveFile(filePath, dstFilePath)) {
            log_info("move file %s success!", filePath);
        } else {
            log_error("move file %s fail!", filePath);
        }
    } else {
        if (DeleteFile(filePath)) {
            log_info("delete file %s success!", filePath);
        } else {
            log_error("delete file %s fail!", filePath);
        }
    }
}
