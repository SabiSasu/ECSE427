Used Linux VM. Some assumptions:
- quit command exits the shell as said in assignement instructions.
    **However, if quit is used inside a script inside another script, it will simply close that script 
       and escalate errorcode -1 to initial script, which will then terminate the shell

- running the same script inside a script will result in infinite loop!
    *its the programmer's fault to make sure those things don't happen.