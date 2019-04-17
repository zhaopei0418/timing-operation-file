#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "paropt.h"
#include "../log/log.h"

char srcdir[CHAR_BUFF_LENGTH];
char filepattern[CHAR_BUFF_LENGTH];
char o;
char searchsubdirectories[CHAR_BUFF_LENGTH];
char dstdir[CHAR_BUFF_LENGTH];
int delaytime;

void help(const char *restrict cmdName)
{
    printf("Usage: %s [OPTION]\n\n", cmdName);
    printf("    -s --srcdir <value>                 source dir\n");
    printf("    -f --filepattern <pattern>          match file pattern\n");
    printf("    -o --operation <value>              how to deal with files, m:move, d:delte\n");
    printf("    -S --searchsubdirectories <value>   whether to search subdirectories, 1: yes, 0: no\n");
    printf("    -d --dstdir <value>                 dstination dir\n");
    printf("    -t --delaytime <time>               time str descrption 1s,1m,1h,1d...\n");
    printf("    -h --help                           help\n");
}

static void calculationDelayTime(const char *delayTimeStr)
{
    if (NULL == delayTimeStr)
        return;
    log_info("delayTimeStr is: %s", delayTimeStr);
    size_t length = strlen(delayTimeStr);
    char timeUnit = delayTimeStr[length - 1];
    char *time = malloc(length * sizeof(char));
    strcpy(time, delayTimeStr);
    time[length - 1] = '\0';

    switch (timeUnit) {
    case 's':
        delaytime = atoi(time) * 1000;
        break;
    default:
        log_error("delaytime format error");
    }

    free(time);
}

int parseOption(int argc, char **argv)
{
    char *cmd = argv[0];
    int result = 0;
    if (argc == 1) {
        help(cmd);
        return -1;
    }
    while (1) {
        int option_index = 0;
        struct option long_options[] = {
                                        {"srcdir"                 , required_argument, 0,   's'},
                                        {"filepattern"            , required_argument, 0,   'f'},
                                        {"operation"              , required_argument, 0,   'o'},
                                        {"searchsubdirectories"   , required_argument, 0,   'S'},
                                        {"dstdir"                 , required_argument, 0,   'd'},
                                        {"delaytime"              , required_argument, 0,   't'},
                                        {"help"                   , no_argument,       0,   'h'},
                                        {NULL                     , 0,                 NULL, 0}
        };
        int c;

        /*注意这里的冒号，有冒号就需要加参数值，没有冒号就不用加参数值*/
        c = getopt_long(argc, argv, "i:p:f:t:h",long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 's':
            strncpy(srcdir, optarg, CHAR_BUFF_LENGTH);
            break;
        case 'f':
            strncpy(filepattern, optarg, CHAR_BUFF_LENGTH);
            break;
        case 'o':
            o = optarg[0];
            break;
        case 'S':
            strncpy(searchsubdirectories, optarg, CHAR_BUFF_LENGTH);
            break;
        case 'd':
            strncpy(dstdir, optarg, CHAR_BUFF_LENGTH);
            break;
        case 't':
            calculationDelayTime(optarg);
            break;
        case 'h':
        default:
            result = -1;
            help(cmd);
            break;
        }
    }

    log_info("resut is: %d", result);
    return result;
}
