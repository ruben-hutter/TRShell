#ifndef CD_H
#define CD_H

#include <errno.h>

#include "../symbol_table.h"
#include "../string_utils.h"

#define BUFFER_SIZE 1024

void cd(int argc, char** argv);
void update_pwd(void);

#endif
