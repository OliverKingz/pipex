# Pipex  
[42 Cursus] A C program that mimics the behavior of shell pipes (`|`), allowing you to execute commands in a pipeline with input and output redirection.  
This project was designed to enhance skills in **process management**, **file handling**, and **C programming**.

---

## Features  
- Execute shell commands in a pipeline, similar to the `|` operator in Unix shells.  
- Redirect input and output using file descriptors.  
- Handle errors gracefully, ensuring no unexpected crashes or memory leaks.  
- Support for basic shell commands with arguments.  
- Clean and efficient memory management.  

### Bonus Features
- **Multiple Pipes**: Handle more than two commands in a pipeline (e.g., `cmd1 | cmd2 | cmd3`).  
- **Here Document**: Support for `<<` and `>>` redirection when the first parameter is `here_doc`.  
- **Advanced Error Handling**: Improved error messages and handling for edge cases.  

---

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

### Bonus Usage

For multiple pipes:

```bash
./pipex infile "cmd1" "cmd2" "cmd3" outfile
```

For here document:

```bash
./pipex here_doc LIMITER "cmd" "cmd1" outfile
```

---

## What I Learned  
This project was a great opportunity to deepen my understanding of:  
- **Process Management**: Using `fork()`, `execve()`, and `waitpid()` to manage processes.  
- **File Descriptors**: Working with `open()`, `close()`, `dup()`, and `dup2()` to handle input/output redirection.  
- **Pipes**: Creating and managing pipes with `pipe()` to connect processes.  
- **Error Handling**: Ensuring robust error management to avoid crashes and memory leaks.  
- **C Programming**: Writing clean, efficient, and maintainable C code.  

---

## Installation  
Requires a C compiler (e.g., `gcc`) and standard libraries.  

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

For bonus features, use the `bonus` rule in the Makefile:  
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
