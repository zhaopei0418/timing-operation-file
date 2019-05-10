#ifndef FILE_TOOL_H
#define FILE_TOOL_H
#include "../paropt/paropt.h"

#define MAX_PATH_LENGTH 200

void handleMatchFiles(const char *dir, const char *dstdir, BOOL_TYPE searchSubdirectories, const char *pattern, OPERATOR_TYPE oper,
                      void (*handleCallBack)(const char *path, const char *fileName, const char *dstdir, OPERATOR_TYPE oper));
char* mergePath(char *dstpath, const char *dir, const char *fileName);
#endif
