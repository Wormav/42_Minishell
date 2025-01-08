# Minishell



The **Minishell** project at 42 is designed to implement a simple Unix shell. The objective is to create a program that acts as a command-line interpreter, similar to Bash, but with fewer features. The project focuses on core concepts such as process creation, signal handling, parsing, and managing input/output redirection.

## Key Features of the Project:
1. **Command Parsing**: The shell needs to parse commands typed by the user and identify different components, such as command arguments, input/output redirections, and pipes.

2. **Execution of Commands**: After parsing, the shell should fork new processes to execute commands. The program needs to handle built-in commands (like `echo`, `cd`, and `exit`) and external commands by using `execve`.

3. **Pipes and Redirections**: The shell should support pipes (`|`) for chaining commands and redirections (`<`, `>`) for input/output redirection.

4. **Signals**: The shell must handle signals like `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\), ensuring the shell behaves correctly when interacting with the terminal.

5. **Environment Variables**: The shell needs to handle environment variables like `$PATH`, `$HOME`, and others, enabling the execution of commands from the environment.

6. **Built-in Commands**: The shell should implement at least three built-in commands: `cd`, `echo`, and `exit`. These commands should be handled by the shell itself, not by creating new processes.

7. **Error Handling**: Proper error messages must be provided for invalid commands or incorrect syntax, with exit codes reflecting the error type.

The project tests the ability to manage complex interactions between processes, manage memory efficiently, and handle edge cases, making it a comprehensive exercise in understanding Unix-like systems.

## Documentation:

### Architecture

```
/minishell
├── includes/
│   ├── ast.h
│   ├── debug.h
│   ├── minishell.h
│   ├── parser.h
│   └── token.h
├── libft/
│   ├── ft_strlen.c
│   └── ...
├── src/
│   ├── ast
│   ├── debug
│   ├── errors
│   |── parser
|	├── tokennizer
│   └── main.c
└── Makefile
```

### Doc:

[doc](./DOC.md)


## Contributors

- Swenn Tetrel
- Jérémy Lorette

Thank you all for your efforts and collaboration in the completion of this project. 😊
