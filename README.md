## shellLite

### Overview
**shellLite** is a simple shell program written in C. It accepts user commands, parses them, and executes them in a separate process, supporting basic command-line operations.

### Features
- **Prompt**: Displays a prompt (`metro@: >`) with fancy text color for user input.
- **Command Parsing**: Reads and tokenizes input commands into executable parts.
- **Execution**: Executes commands in child processes using `fork` and `execvp`.
- **Exit Command**: Supports the `"exit"` command to close the shell.
- **Error Handling**: Handles memory allocation and process creation errors.
- **Zombie Process Prevention**: Uses `waitpid` to ensure child processes are properly cleaned up.

### Project Structure
- **`cmd_t` Structure**: Stores command name and arguments.
- **Functions**:
  - `parse_cmd_arg()`: Reads input from the user, parses the user input into command and arguments.
  - `exec_cnd(Command *cmd)`: Executes parsed command in a new process.

### Compilation
To compile and run the program, run the provided shell script:
```bash
./build.sh
```

Example:
```plaintext
metro@: > ls -l
metro@: > echo Hello, World!
metro@: > exit
```

### Notes
- Commands are run in a child process.
- `exit` closes the shell program.
