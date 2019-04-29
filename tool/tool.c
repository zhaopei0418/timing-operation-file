#ifdef _WIN32
#include <windows.h>
#include "../regex/re.h"
#else
#include <regex.h>
#include <dirent.h>
#include <sys/stat.h>
#endif
#include <string.h>
#include <stdio.h>
#include "tool.h"
#include "../log/log.h"


static void handleFile(const char *path, const char *fileName, const char *dstdir, OPERATOR_TYPE oper);


void handleMatchFiles(const char *dir, const char *dstdir, BOOL_TYPE searchSubdirectories, const char *pattern, OPERATOR_TYPE oper,
                      void (*handleCallBack)(const char *path, const char *fileName, const char *dstdir, OPERATOR_TYPE oper))
{
    if (dir == NULL)
        return;
    char dirNew[CHAR_BUFF_LENGTH];
    log_info("dir is: %s", dir);
    log_info("pattern is %s", pattern);
#ifdef _WIN32
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    re_t filePattern;
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
                handleMatchFiles(dirNew, dstdir, B_TRUE, pattern, oper, handleCallBack);
            }
        } else {
            log_info("find file is: %s", findData.cFileName);
            if (pattern != NULL) {
                filePattern = re_compile(pattern);
                if ((match_idx = re_matchp(filePattern, findData.cFileName)) != -1) {
                    if (handleCallBack != NULL)
                        handleCallBack(dir, findData.cFileName, dstdir, oper);
                    else
                        handleFile(dir, findData.cFileName, dstdir, oper);
                } else {
                    log_info("%s not match pattern %s", findData.cFileName, pattern);
                }
            } else {
                log_info("no pattern not handle!");
            }
        }
    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);
#else
    DIR *dp;
    struct dirent *dirp;
    struct stat statbuf;
    regex_t oRegex;
    int retCode = 0;

    if ((dp = opendir(dir)) == NULL) {
        log_error("opendir error!");
        return;
    }

    while ((dirp = readdir(dp)) != NULL) {

        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        if (lstat(mergePath(dirNew, dir, dirp->d_name), &statbuf) == 0 && S_ISDIR(statbuf.st_mode)){
            log_info("%s \t<dir>", dirp->d_name);
            if (searchSubdirectories) {
                mergePath(dirNew, dir, dirp->d_name);
                handleMatchFiles(dirNew, dstdir, B_TRUE, pattern, oper, handleCallBack);
            }
        } else {
            log_info("find file is: %s", dirp->d_name);
            if (pattern != NULL) {
                if ((retCode = regcomp(&oRegex, pattern, REG_EXTENDED | REG_NEWLINE)) < 0) {
                    log_info("regcomp error!");
                    return;
                }

                if ((retCode = regexec(&oRegex, dirp->d_name, 0, NULL, 0)) == 0) {
                    if (handleCallBack != NULL)
                        handleCallBack(dir, dirp->d_name, dstdir, oper);
                    else
                        handleFile(dir, dirp->d_name, dstdir, oper);
                } else {
                    log_info("%s not match pattern %s", dirp->d_name, pattern);
                }
                regfree(&oRegex);
            } else {
                log_info("no pattern not handle!");
            }
        }
    }
    if (closedir(dp) < 0)
        log_error("closedir error!");
#endif
}

char* mergePath(char *dstpath, const char *dir, const char *fileName)
{
    strcpy(dstpath, dir);
#ifdef _WIN32
    strcat(dstpath, "\\");
#else
    strcat(dstpath, "/");
#endif
    strcat(dstpath, fileName);
    return dstpath;
}

static void handleFile(const char *path, const char *fileName, const char *dstdir, OPERATOR_TYPE oper)
{
    char filePath[CHAR_BUFF_LENGTH];
    char dstFilePath[CHAR_BUFF_LENGTH];
    mergePath(filePath, path, fileName);

    log_info("file absolute path is: %s", filePath);

    if (oper == OP_MOVE) {
        if (dstdir == NULL)
            return;
        else {
            mergePath(dstFilePath, dstdir, fileName);
            log_info("dst file absolute path: %s ", dstFilePath);
        }
#ifdef _WIN32
        if (MoveFile(filePath, dstFilePath)) {
#else
        if (rename(filePath, dstFilePath) == 0) {
#endif
            log_info("move file %s success!", filePath);
        } else {
            log_error("move file %s fail!", filePath);
        }
    } else {
#ifdef _WIN32
        if (DeleteFile(filePath)) {
#else
        if (remove(filePath) == 0) {
#endif
            log_info("delete file %s success!", filePath);
        } else {
            log_error("delete file %s fail!", filePath);
        }
    }
}
