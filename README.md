
Pipex is a powerful utility program that mimics the shell's piping and redirection capabilities, allowing you to execute commands with input and output redirection seamlessly. It supports both mandatory and bonus features for added flexibility.

---

## 💡 Features

### Mandatory Program
- Redirects standard input (STDIN) and standard output (STDOUT) using `<` and `>`.
- Executes two commands (`cmd1` and `cmd2`) with input and output redirection.
- Mimics the behavior of the shell command:
  ```bash
  < infile cmd1 | cmd2 > outfile
  ```
- Usage:
  ```bash
  ./pipex <infile> <cmd1> <cmd2> <outfile>
  ```

### Bonus Program
- Allows redirection of STDIN (`<`) and STDOUT (`>`) with support for **multiple commands**.
- Mimics the behavior of the shell command:
  ```bash
  < infile cmd1 | cmd2 | cmd3 ... > outfile
  ```
- Supports **appending** to the output file using `>>` (double angle bracket) and overwriting using `>` (single angle bracket).
- Advanced `here_doc` feature:
  - Allows you to provide input directly in the terminal until a specified `limiter` is reached.
  - Executes commands with the typed input as STDIN.
  - Mimics the shell behavior:
    ```bash
    << limiter cmd1 | cmd2 | cmd3 ... >> outfile
    ```
- Usage:
  ```bash
  ./pipex here_doc <limiter> <cmd1> <cmd2> <cmd3> ... <outfile>
  ```

---

## 🚀 How to Use

### Mandatory Program
1. Compile the project using the following command:
   ```bash
   make
   ```
2. Run the program:
   ```bash
   ./pipex <infile> <cmd1> <cmd2> <outfile>
   ```
   Example:
   ```bash
   ./pipex input.txt "grep hello" "wc -l" output.txt
   ```

2. Run the program with multiple commands:
   ```bash
   ./pipex <infile> <cmd1> <cmd2> <cmd3> ... <outfile>
   ```
   Example:
   ```bash
   ./pipex input.txt "cat" "grep hello" "wc -l" output.txt
   ```

3. Use the `here_doc` feature:
   ```bash
   ./pipex here_doc <limiter> <cmd1> <cmd2> <cmd3> ... <outfile>
   ```
   Example:
   ```bash
   ./pipex here_doc END "cat" "grep hello" "wc -l" output.txt
   ```
   Start typing your input, and terminate it by entering the limiter (e.g., `END`).

---

## 🛠️ How It Works

### Key Features
1. **Redirection**:
   - `< infile`: Redirects input from a file.
   - `> outfile`: Redirects output to a file (overwrites the file).
   - `>> outfile`: Appends output to a file (bonus).

2. **Piping**:
   - Connects the output of one command to the input of the next.

3. **Here Document**:
   - Redirects input directly from the terminal until a specific `limiter` is reached (bonus).

---

## 📂 File Structure

- `pipex.c`: Core implementation of the program.
- `bonus/`: Contains the bonus program logic.
- `Makefile`: Build automation tool.

---

## 🧪 Examples

### Mandatory Example
```bash
./pipex input.txt "ls -l" "grep pipex" output.txt
```
- Takes `input.txt` as input.
- Executes `ls -l` and pipes the output to `grep pipex`.
- Saves the result to `output.txt`.

### Bonus Example
```bash
./pipex input.txt "cat" "grep hello" "wc -l" output.txt
```
- Processes `input.txt` through `cat`, `grep`, and `wc`.
- Saves the result to `output.txt`.

### Here Document Example
```bash
./pipex here_doc END "cat" "grep hello" "wc -l" output.txt
```
- Waits for user input until the limiter `END` is entered.
- Processes the typed input through `cat`, `grep`, and `wc`.
- Appends the result to `output.txt`.


  
