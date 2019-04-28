#ifndef PAROPT_H
#define PAROPT_H

#include <stdint.h>

#define CHAR_BUFF_LENGTH 200

typedef enum
{
    B_FALSE, B_TRUE
} BOOL_TYPE;

typedef enum
{
    OP_MOVE, OP_DELETE
} OPERATOR_TYPE;

extern char srcdir[CHAR_BUFF_LENGTH];
extern char filepattern[CHAR_BUFF_LENGTH];
extern OPERATOR_TYPE operation;
extern BOOL_TYPE searchsubdirectories;
extern char dstdir[CHAR_BUFF_LENGTH];
extern uint32_t delaytime;

/* public function declarations*/
int parseOption(int argc, char **argv);

#endif
