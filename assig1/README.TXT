Used Windows machine. 
Some assumptions:
- quit command exits the shell as said in assignement instructions.
    *However, if quit is used inside a script, it will simply close 
      the file and return to the shell.
- running the same script inside a script will result in infinite loop!
    *its the programmer's fault to make sure those things don't happen.
    *However, because fopen reaches the memory limit, it will terminate the program 
     after a while so it can be used as the base case.
- print output is formatted the following way: variable = value.