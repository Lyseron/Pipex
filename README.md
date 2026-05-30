# Pipex

This project was created as part of the 42 curriculum by **lyaberge**.

## Description

Pipex is a C program that reproduces the behavior of a shell pipeline:

```bash
< infile cmd1 | cmd2 > outfile
```

The program creates a pipe and two child processes.

* The first child executes `cmd1`, reads its standard input from `infile`, and writes its standard output to the pipe.
* The second child executes `cmd2`, reads its standard input from the pipe, and writes its standard output to `outfile`.

The pipe is created using `pipe()`, which gives two new file descriptors:

* one for reading
* one for writing

Usually, these file descriptors are `3` and `4`, because the system uses the smallest available numbers after `stdin`, `stdout`, and `stderr`.

## How it works

In each child process, `dup2()` is used to redirect `stdin` and `stdout` to the correct file descriptor.

A file descriptor is a number used by the system to know where to read from or write to.

The parent process:

* creates the child processes using `fork()`
* closes unused file descriptors
* waits for both children to finish execution

The parent waits for:

* `cmd1` to avoid a zombie process
* `cmd2` to retrieve the final exit status

Like in the shell, the final exit status depends on the last command, which is `cmd2`.

A zombie process is a process that has finished executing, but whose parent has not yet retrieved its exit status.

## Exit codes

Depending on how a command fails, different exit codes are returned.

| Exit code      | Meaning                                                             |
| -------------- | ------------------------------------------------------------------- |
| `0`            | Success                                                             |
| `1`            | Program execution problem, for example a failed `open()`            |
| `126`          | Command exists but is not executable, for example permission denied |
| `127`          | Command not found                                                   |
| `128 + signal` | Command terminated by a signal, for example a segmentation fault    |

## Compilation

To compile the project:

```bash
make
```

This creates the `pipex` executable.

## Usage

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Example:

```bash
./pipex in "cat" "wc -l" out
```

This should behave like:

```bash
< in cat | wc -l > out
```

## Testing

### Check for leaks and file descriptors

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./pipex in "cat" "wc -l" out
```

To check the exit code:

```bash
echo $?
```

## Possible tests

### Count the number of lines in a file

```bash
./pipex in "cat" "wc -l" out
cat out
echo $?
```

Expected result:

* exit code should be `0`
* `out` should contain the number of lines from `in`

### First command does not exist, second command works

```bash
./pipex in "nonexistentcmd" "cat" out
cat out
echo $?
```

Expected result:

* exit code should be `0`, because the final command `cat` succeeds
* `out` should be empty because `cmd1` did not write anything to the pipe

### Second command does not exist

```bash
./pipex in "cat" "nonexistentcmd" out
echo $?
```

Expected result:

* exit code should be `127`, because the last command was not found

### Command exists but is not executable

```bash
printf "lily" > fake
chmod 644 fake
./pipex in "cat" "./fake" out
echo $?
```

Expected result:

* exit code should be `126`, because `fake` exists but is not executable

## Skills practiced

* Unix processes
* Pipes
* File descriptors
* `fork()`
* `pipe()`
* `dup2()`
* `execve()`
* `waitpid()`
* Error handling
* Exit status management
* Memory management
* Shell behavior

## Resources

I used resources to understand the concepts behind the project, not to copy code.

* 42 Cursus GitBook guide: Pipex
* Manual pages for functions such as `pipe()`, `fork()`, `dup2()`, `execve()`, and `waitpid()`
* YouTube videos about redirections and communication between processes

## AI use

I used AI as a learning and debugging tool, never to generate the final code.

I always started my prompts with a strict no-code rule, asking only for explanations, as if another student was teaching me.

I mostly used AI to:

* understand and fix Norminette structure issues when some functions were longer than 25 lines
* think about cleaner ways to split error handling into smaller helper functions
* debug exit status and logic errors
* understand what could go wrong in different crash or failure scenarios
* compare different exit codes and shell behaviors
* help write this README in English
