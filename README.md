This project has been created as part of the 42 curriculum by lyaberge

DESCRIPTION :
Pipex is a program that try to reproduce the behavior of the shell pipeline (cmd1 < infile | cmd2 > outfile) 
The program creates a pipe and two child processes.
The first child executes cmd1 reads it's standard input from the file "infile" and write it's standard output to the pipe.
The second child executes cmd2, read it's standard input from the pipe and write it's standard output to the file "outfile".
The pipe is created using pipe(), which give me 2 new file descriptor, for reading and writing (usually 3 and 4, smallest one available).
In the child processes, dup2() is used to rederect the stdin/stdout to the appropriate file descriptor.
File descriptor --> is a number that the system use to know where to read or write.
The parent process creates the child processes using fork(), properly close unused file descriptor, and wait for both children to finish execution.
	- cmd1 --> to avoid a zombie process
	- cmd2 --> to retieve the exit status
(like in the shell behavior, the exit status depend on the last cmd (here cmd2)).\
Zombie process --> process that is done executing but the parent didn't get the exit code
Depending on how a cmd fail, different exit code are returned:
	- 127 --> cmd not found (exemple : cmd does not exist)
	- 126 --> cmd exist but is not executable (exemple : denied permission)
	- 128 + exit code --> cmd terminated by a signal (exemple : SEGFAULT)
	- 0 --> success
	- 1 --> the program got a execution problem (exemple : a fail open)


INSTRUCTION & POSSIBLE TEST:
make --> to compile and create the pipex ececutable
valgrind --leak-check-full --show-leak-kinds=all --track-fds=yes
echo $? -> to get the exit code

	- count nb of newline in "in"
valgrind ./pipex in "cat" "wc -l" out
cat out
echo $?
------> the exit should be 0 (succes)
	- cmd1 nonexistant, cmd2 ok 
valgrind ./pipex in "nonexistantcmd" "cat" out
cat out
echo $?
------> exit should be 0 (since cmd2 exit is succes)
------> cat out should be empty cause cmd1 didn't write anything
	- cmd2 nonexistant, cmd1 ok
valgrind ./pipex in "cat" "nonexistantcmd" out
echo $?
------> exit should be 127 (cmd not found)
	- cmd exit but is not executable
printf "lily" > fake
chmod 644 fake
valgrind ./pipex in "cat "./fake" out
echo $?
------> exit should be 126 cause the cmd is a non executable file


RESSOURCES:
Multiple online guides (I only looked at the guide to better understand the concept never the code):
	- https://42-cursus.gitbook.io/guide/2-rank-02/pipex
Man page for the different new function like pipe(), fork() ect...
Youtube videos on redirection and communication between process :
	- https://www.youtube.com/watch?v=Mqb2dVRe0uo
	- https://www.youtube.com/watch?v=6u_iPGVkfZ4
	- https://www.youtube.com/watch?v=tcYo6hipaSA
	- ect .. the whole serie


AI USES :
I used AI as a learning and debugging tool, never to generate code. I always start my prompt with a strict no-code rule only explanations like it was another student teaching me.
	I use it mostly for:
		- Help find a solution for the norminette error because I had too many fontion of more than 25 lines so AI propose help me put handle some errors when I try to put everything into mini fonction.
		- Help with exit and logic errors by explaining what could go wrong and pointing out weaknesses by giving scenarios of where the program could crash, and in what case this exit wa for compare to another.
		- Help write this README in English.
Thank you.