# Pipex  
[42 Cursus] A C program that mimics the behavior of shell pipes (`|`), allowing you to execute commands in a pipeline with input and output redirection.  
This project was designed to enhance skills in **process management**, **file handling**, and **C programming**.

Keywords  
- **Pipes** 
- **Process Management**
- **File Descriptors**
- **Error Handling**
- **Input/Output Redirection**
- **Shell Commands**
- **Forking**
- **System Calls**

---

## Index

- [Overview](#overview)
- [Features](#features)
- [Bonus Features](#bonus-features)
- [Functions Allowed](#functions-allowed)
- [How It Works](#how-it-works)
  - [Basic Functionality Tests](#basic-functionality-tests)
  - [Error Handling Tests](#error-handling-tests)
  - [Bonus Functionality Tests](#bonus-functionality-tests)
- [What I Learned](#what-i-learned)
- [Installation](#installation)
- [Author](#author)
- [Acknowledgments](#acknowledgments)

---

## Overview  
The `pipex` project is a C program that simulates the behavior of shell pipes (`|`). It takes four arguments: two file names and two shell commands. The program executes the commands in a pipeline, redirecting the input and output as specified. This project was created to deepen understanding of Unix process management, file handling, and error handling in C.  

---

## Features  
- **Pipeline Execution**: Execute shell commands in a pipeline, similar to the `|` operator in Unix shells.  
- **Input/Output Redirection**: Redirect input from a file and output to another file using file descriptors.  
- **Error Handling**: Gracefully handle errors, ensuring no unexpected crashes or memory leaks.  
- **Basic Command Support**: Support for shell commands with arguments.  
- **Memory Management**: clean and efficient.

## Bonus Features  
- **Multiple Pipes**: Handle more than two commands in a pipeline (e.g., `cmd1 | cmd2 | cmd3`).  
- **Here Document**: Support for `<<` and `>>` redirection when the first parameter is `here_doc`.  
- **Advanced Error Handling**: Improved error messages and handling for edge cases.  

---

## Functions Allowed

The following functions are authorized for use in the `pipex` project. Each function is briefly described to explain its purpose and relevance to the project.

### 1. **File Handling**
- **`open()`**: Opens a file and returns a file descriptor. Used to read from or write to files.
- **`close()`**: Closes a file descriptor, freeing up resources.
- **`unlink()`**: Deletes a file from the filesystem. Useful for cleaning up temporary files.

### 2. **Process Management**
- **`fork()`**: Creates a new process by duplicating the calling process. Used to execute commands in child processes.
- **`execve()`**: Replaces the current process image with a new one. Used to execute shell commands.
- **`wait()`**: Waits for a child process to terminate. Useful for synchronizing parent and child processes.
- **`waitpid()`**: Waits for a specific child process to terminate. Provides more control than `wait()`.

### 3. **Pipes**
- **`pipe()`**: Creates a pipe, which is a unidirectional data channel for inter-process communication. Used to connect commands in a pipeline.
- **`dup()`**: Duplicates a file descriptor. Useful for redirecting input/output.
- **`dup2()`**: Duplicates a file descriptor and assigns it to a specified file descriptor number. Used to redirect input/output to/from pipes.

### 4. **Memory Management**
- **`malloc()`**: Allocates memory on the heap. Used for dynamic memory allocation.
- **`free()`**: Deallocates memory previously allocated by `malloc()`. Prevents memory leaks.

### 5. **Error Handling**
- **`perror()`**: Prints an error message to `stderr` based on the current value of `errno`. Useful for debugging.
- **`strerror()`**: Returns a string describing the error code stored in `errno`. Useful for generating custom error messages.

### 6. **Input/Output**
- **`read()`**: Reads data from a file descriptor into a buffer. Used to read input from files or pipes.
- **`write()`**: Writes data from a buffer to a file descriptor. Used to write output to files or pipes.

### 7. **Program Control**
- **`exit()`**: Terminates the program with a specified status code. Used to handle errors or normal termination.
- **`access()`**: Checks if a file exists or if the program has permission to access it. Useful for error handling.

## How It Works  
The program takes four arguments: two file names and two shell commands. It executes the commands in a pipeline, redirecting the input and output as specified.

### Example Usage  
```bash
./pipex infile "ls -l" "wc -l" outfile
```  
This behaves the same as the following shell command:  
```bash
< infile ls -l | wc -l > outfile
```

### Recommendations for Testing
1. **`time`**: Use `time` to measure the execution time of commands, especially when using `sleep`. This helps verify if commands are executed concurrently.
2. **`env`**: Use `env` to check if the environment variables (e.g., `PATH`) are correctly passed to the commands.
3. **`env -i`**: Use `env -i` to test how your program handles commands without environment variables.
4. **`echo $?`**: Use `echo $?` to capture and verify the exit status of commands.
6. **`which ls`**: Use `which` command to search the path of the commands, and to use absolute commands in our pipex. 
7. **`cp /usr/bin/ls .`**: use this command to copy an original command to our current directory, to test relative paths in our pipex.
8. **`unset PATH` or `export PATH=""`**: use one of these commands to test our pipex behaviour without PATH
5. **`valgrind --trace-children=yes --track-fds=yes`**: Use these flags to track if your are managing the children processes and fds correctly

---

### Basic Functionality Tests

| **Input Command**                                      | **Shell Equivalent**                          | **Description**                                                                 | **Expected Output**                                                                |
|--------------------------------------------------------|-----------------------------------------------|---------------------------------------------------------------------------------|------------------------------------------------------------------------------------|
| `./pipex empty "ls -l" "wc -l" outfile`                | `ls -l \| wc -l > outfile`                    | Lists files in the current directory and counts lines (no input file needed).   | Number of lines from `ls -l` written to `outfile`.                                 |
| `./pipex empty "echo Hello" "wc -c" outfile`           | `echo Hello \| wc -c > outfile`               | Echoes "Hello" and counts characters (no input file needed).                    | Number of characters in "Hello" written to `outfile`.                              |
| `./pipex empty "whoami" "tr 'a-z' 'A-Z'" outfile`      | `whoami \| tr 'a-z' 'A-Z' > outfile`          | Outputs the current username and converts it to uppercase.                      | Uppercase username written to `outfile`.                                           |
| `./pipex empty "seq 10" "tail -n 5" outfile`           | `seq 10 \| tail -n 5 > outfile`               | Generates numbers from 1 to 10 and extracts the last 5 numbers.                 | Numbers 6 to 10 written to `outfile`.                                              |
| `./pipex empty "env" "grep PATH" outfile`              | `env \| grep PATH > outfile`                  | Lists all environment variables and filters lines containing "PATH".            | Lines containing "PATH" written to `outfile`.                                      |
| `./pipex infile "cat -e" "cat -e" outfile`             | `< infile cat -e \| cat -e > outfile`         | Outputs the content of `infile` with `-e` flag applied twice.                   | Content of `infile` with `-e` flag applied twice written to `outfile`.             |
| `./pipex infile "ls -la" "cat -e" outfile`             | `< infile ls -la \| cat -e > outfile`         | Lists files in the current directory and applies `cat -e`.                      | Output of `ls -la` with `cat -e` applied written to `outfile`.                     |
| `./pipex infile "sleep 3" "ls" outfile`                | `< infile sleep 3 \| ls > outfile`            | Waits for 3 seconds and lists files in the current directory.                   | Output of `ls` written to `outfile`.                                               |
| `./pipex infile "grep ep" "wc -w" outfile`             | `< infile grep ep \| wc -w > outfile`         | Searches for lines containing "ep" in `infile` and counts words.                | Number of words in lines containing "a1" written to `outfile`.                     |
| `./pipex infile "sort" "uniq" outfile`                 | `< infile sort \| uniq > outfile`             | Sorts the content of `infile` and removes duplicate lines.                      | Sorted and deduplicated content written to `outfile`.                              |
| `./pipex infile "head -n 5" "tail -n 1" outfile`       | `< infile head -n 5 \| tail -n 1 > outfile`   | Extracts the first 5 lines of `infile` and then the last line of those 5.       | The 5th line of `infile` written to `outfile`.                                     |
| `./pipex infile "tr ' ' '\n'" "sort" outfile`          | `< infile tr ' ' '\n' \| sort > outfile`      | Splits words in `infile` by spaces and sorts them.                              | Sorted list of words written to `outfile`.                                         |
| `./pipex infile "grep pattern" "wc -l" outfile`        | `< infile grep pattern \| wc -l > outfile`    | Searches for "pattern" in `infile` and counts matching lines.                   | Number of lines containing "pattern" written to `outfile`.                         |

---

### Error Handling Tests

| **Input Command**                                        | **Shell Equivalent**                                | **Description**                                                         | **Expected Output**                                                                 |
|----------------------------------------------------------|-----------------------------------------------------|-------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| `./pipex non_existent_file "ls -l" "wc -l" outfile`      | `< non_existent_file ls -l \| wc -l > outfile`      | Tries to read from a non-existent file.                                 | `non_existent_file: No such file or directory`                                      |
| `./pipex infile "invalid_cmd" "wc -l" outfile`           | `< infile invalid_cmd \| wc -l > outfile`           | Tries to execute an invalid command.                                    | `invalid_cmd: command not found`                                                    |
| `./pipex infile "ls -l" "wc -l" unwritable_file`         | `< infile ls -l \| wc -l > unwritable_file`         | Tries to write to an unwritable file.                                   | `unwritable_file: Permission denied`                                                |
| `./pipex infile_nopermissions "cat -e" "cat -e" outfile` | `< infile_nopermissions cat -e \| cat -e > outfile` | Tries to read from a file without permissions.                          | `infile_nopermissions: Permission denied`                                           |
| `./pipex infile "cat -e" "cat -e" outfile_nopermissions` | `< infile cat -e \| cat -e > outfile_nopermissions` | Tries to write to a file without permissions.                           | `outfile_nopermissions: Permission denied`                                          |
| `./pipex infile "nonexistingcommand" "cat -e" outfile`   | `< infile nonexistingcommand \| cat -e > outfile`   | Tries to execute a non-existing command.                                | `nonexistingcommand: command not found`                                             |
| `./pipex infile "cat -e" "nonexistingcommand" outfile`   | `< infile cat -e \| nonexistingcommand > outfile`   | Tries to execute a non-existing command as the second command.          | `nonexistingcommand: command not found`                                             |
| `./pipex infile "cat -e" "cat -nonexistingflag" outfile` | `< infile cat -e \| cat -nonexistingflag > outfile` | Tries to use a non-existing flag with `cat`.                            | `cat: invalid option -- 'o'`                                                        |
| `./pipex "" "cat -e" "cat -e" outfile`                   | `< "" cat -e \| cat -e > outfile`                   | Missing input file argument.                                            | ` : No such file or directory`                                                 |

---

### Bonus Functionality Tests

| **Input Command**                                      | **Shell Equivalent**                          | **Description**                                                                 | **Expected Output**                                                                 |
|--------------------------------------------------------|-----------------------------------------------|---------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| `./pipex infile "cmd1" "cmd2" "cmd3" outfile`          | `< infile cmd1 \| cmd2 \| cmd3 > outfile`     | Executes three commands in a pipeline.                                          | Output of `cmd3` written to `outfile`.                                             |
| `./pipex here_doc LIMITER "cmd" "cmd1" outfile`        | `cmd << LIMITER \| cmd1 >> outfile`           | Uses `here_doc` to read input until `LIMITER` is found, then processes it.      | Output of `cmd1` appended to `outfile`.                                            |

---

## What I Learned  
- **Process Management**: Using `fork()`, `execve()`, and `waitpid()` to manage processes.  
- **File Descriptors**: Working with `open()`, `close()`, `dup()`, and `dup2()` to handle input/output redirection.  
- **Pipes**: Creating and managing pipes with `pipe()` to connect processes.  
- **Error Handling**: Ensuring robust error management to avoid crashes and memory leaks.  
- **C Programming**: Writing clean, efficient, and maintainable C code.  

---

## Installation  
### Requirements  
- A C compiler
- Standard libraries.  

### How to Run  
1. Clone this repository:  
   ```bash  
   git clone https://github.com/yourusername/pipex.git  
   cd pipex  
   ```  
2. Compile the project using the provided **Makefile**:  
   ```bash  
   make  
   ```  
3. Run the program with the required arguments:  
   ```bash  
   ./pipex infile "cmd1" "cmd2" outfile
   ```  

For bonus features, use the bonus rule in the Makefile:  
   ```bash  
   make bonus
   ```  

---

## Author  
- **Name**: Oliver King Zamora  
- **GitHub**: [oliverkingz](https://github.com/oliverkingz)  
- **42 Login**: ozamora-  

---

## Acknowledgments  
This project is part of the **42 Cursus**, a rigorous programming curriculum that emphasizes hands-on learning and problem-solving. Special thanks to the 42 team for providing this challenging and rewarding project!  

