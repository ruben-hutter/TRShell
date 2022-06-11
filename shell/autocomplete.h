#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "string_utils.h"
#include "history.h"

// tries to autocomplete the approach and returns the completed version if found
// if no single answer is found all answers are printed to the terminal and the received approach is copied to the new buffer
char* autocomplete(char* approach);
char* querry_history(char* approach);


#endif