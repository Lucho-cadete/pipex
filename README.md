This project has been created as part of the 42 curriculum by luimarti.

pipex
Description

pipex recreates the behaviour of a shell pipeline in C. Running

bash
./pipex infile "cmd1" "cmd2" outfile

produces the same result as

bash
< infile cmd1 | cmd2 > outfile

The project is an introduction to Unix process management. To pipe two commands you have to create a pipe, fork a child process for each command, redirect the standard input and output of each child onto the right end of the pipe with dup2, close every file descriptor you are not using, replace the child's image with execve, and have the parent wait for both children and propagate the exit status.

Most of the difficulty is in the parts that are invisible when it works: unclosed file descriptors cause the program to hang forever rather than fail loudly, and resolving a command name against the PATH environment variable has to be done by hand.

Instructions
bash
git clone https://github.com/Lucho-cadete/pipex.git
cd pipex
make

Usage:

bash
./pipex infile "grep hello" "wc -l" outfile
# equivalent to: < infile grep hello | wc -l > outfile
<!-- TODO: if you implemented the bonus (multiple pipes, here_doc), document it here, for example: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2 ./pipex here_doc LIMITER cmd1 cmd2 file -->
Resources
man 2 pipe, man 2 fork, man 2 execve, man 2 dup2, man 2 waitpid — this project is essentially a guided tour of these five pages.
Beej's Guide to Unix IPC — the clearest explanation of pipes and why descriptors must be closed on both ends.
The Linux Programming Interface, chapters 24–27 — process creation, program execution and process termination.
Use of AI

AI assistance was used for: understanding what a process is and what fork actually does, which was entirely new to me; explaining why a pipeline hangs forever when the write end of a pipe is left open, instead of failing with an error; clarifying how dup2 redirects a file descriptor and why every unused one must be closed; and reviewing my PATH resolution once written. The process logic, the redirection and the error handling are mine.