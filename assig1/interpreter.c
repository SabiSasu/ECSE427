/* Shell written by Sabina Sasu, 260803977*/
/* ECSE427 Mcgill Winter 2020 */

#include "interpreter.h"
#include <string.h>

int interpreter(char *words[]) {
   int errCode = 0;

   //The user is asking to execute a single command
   if (strcmp(words[0], "help") == 0)        errCode = help(words);
   else if (strcmp(words[0], "quit") == 0)   errCode = quit(words);
   else if (strcmp(words[0], "set") == 0)    errCode = set(words);
   else if (strcmp(words[0], "print") == 0)  errCode = print(words);
   else if (strcmp(words[0], "run") == 0)    errCode = run(words);
   else errCode = 1;

   return errCode;
}

