# Concurrent C

This is a paper to the course **Concurrent C Programming** in the ZHAW in Zurich.
Please find the whole documentation in the file doc.pdf in the root directory.

## Summary
The goal was to understand the problems of programming cuncurrent running executables in the language C. As in other languages there exist a bunch of helpful libraries, in C we have to implement this stuff on our own.

## Task
The task was to program a multiuser fileeditor with the protocol TCP. The server did not have to have a beautiful GUI - command line is enough. It was important that we implemented concurrent functionalities.

The server should respond to a couple of commands - findable in the file `documentations/Funktionen Editor`.

## Program
After you clone this repository you can run  
`$ make`  
Now you have the runnables **run** and **test**. First start the server by  
`$ ./run`  
Then start the testclient by  
`$ ./test`.  
The testclient will then perform some automated testing. If you want do some testing on your own you can start the client by  
`$ ./test -manual`  
which will start the client in manual mode.

## Restrictions
This program was written to run in a UNIX environment. Namely ubuntu 12.04 with POSIX configuration.

## Missing
The whole file modification functions are missing. This means the server and the testclient are fully functional but no file modification is done. In the code the respective lines are marked with the text `here comes the file modification`.

To make the server do file modifications one has to replace these lines with appropriate code.
