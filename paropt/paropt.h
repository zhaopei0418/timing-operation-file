#ifndef PAROPT_H
#define PAROPT_H

#define CHAR_BUFF_LENGTH 100

extern char srcdir[CHAR_BUFF_LENGTH];
extern char filepattern[CHAR_BUFF_LENGTH];
extern char o;
extern char searchsubdirectories[CHAR_BUFF_LENGTH];
extern char dstdir[CHAR_BUFF_LENGTH];
extern int delaytime;

int parseOption(int argc, char **argv);

void help(const char *restrict cmdName);

static void calculationDelayTime(const char *delayTimeStr);

#endif
