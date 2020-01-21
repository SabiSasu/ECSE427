
int interpreter(char *words[]) { //assumes cmd switches args
   int errCode = 0;              //assumes words[0] is cmd

   //The user is asking to execute a script, equivalent to run??
   /*if (*(words[0]) == '.' && *(words[0] + 1) == '/'){
	   errCode = script(words);
   }*/

   //The user is asking to execute a single command
   if ((strncmp(words[0], "help", 4)) == 0)      errCode = help(words);
   else if (strncmp(words[0], "quit", 4) == 0)   errCode = quit(words);
   else if (strncmp(words[0], "set", 3) == 0)    errCode = set(words);
   else if (strncmp(words[0], "print", 5) == 0)  errCode = print(words);
   else if (strncmp(words[0], "run", 3) == 0)    errCode = run(words);
   else errCode = 1;

   return errCode;
}


