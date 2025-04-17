
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

### Here Doc Example
```bash
./pipex here_doc END "cat" "grep hello" "wc -l" output.txt
```
- Waits for user input until the limiter `END` is entered.
- Processes the typed input through `cat`, `grep`, and `wc`.
- Appends the result to `output.txt`.


  ---
  
## 📜 Understanding `dup`, `dup2`, and `dup3`

When working on projects that involve file descriptors and redirection (like `pipex`), the `dup`, `dup2`, and `dup3` system calls play a crucial role. Here's a breakdown of what they do and how they differ:

### `dup` (Duplicate File Descriptor)
- **Purpose**: Creates a copy of an existing file descriptor.
- **Behavior**:
  - Returns the lowest available file descriptor.
  - Both the original and the duplicate file descriptors point to the same file description (same offset, permissions, etc.).
- **Usage Example**:
  ```c
  int fd_copy = dup(fd);
  ```
- **Use Case**: Redirecting output/input by duplicating file descriptors.

---

### `dup2` (Duplicate File Descriptor to a Specific Target)
- **Purpose**: Copies an existing file descriptor to a specific target file descriptor.
- **Behavior**:
  - If the target file descriptor (`newfd`) is already open, it will close it first.
  - If `newfd` is the same as the source file descriptor, the system call does nothing and just returns `newfd`.
- **Usage Example**:
  ```c
  int result = dup2(fd, newfd);
  ```
- **Use Case**: Redirecting file descriptors to specific targets (e.g., making `STDOUT_FILENO` point to a file).

---

### `dup3` (Duplicate File Descriptor with Flags)
- **Purpose**: Like `dup2`, but allows additional flags for more control.
- **Behavior**:
  - Supports the `O_CLOEXEC` flag to set the close-on-exec property.
  - Safer than `dup2` as it avoids race conditions when setting the `O_CLOEXEC` flag manually.
- **Usage Example**:
  ```c
  int result = dup3(fd, newfd, O_CLOEXEC);
  ```
- **Use Case**: When you need to duplicate file descriptors with additional options for modern applications.

---

### 🔍 Key Differences
| Feature          | `dup`               | `dup2`              | `dup3`                          |
|------------------|---------------------|---------------------|---------------------------------|
| **Target FD**    | Chosen by the OS    | User-specified      | User-specified                  |
| **Closes Target**| No                  | Yes                 | Yes                             |
| **Flags Support**| No                  | No                  | Yes (`O_CLOEXEC`)               |
| **Use Case**     | General duplication | Redirecting streams | Advanced duplication with flags |

---

### 🛠 Example Code
```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Using dup
    int fd_dup = dup(fd);

    // Using dup2
    dup2(fd, STDOUT_FILENO);

    // Using dup3
    int fd_dup3 = dup3(fd, 100, O_CLOEXEC);

    // Now, you can write to fd_dup, STDOUT_FILENO, or fd_dup3
    write(fd_dup, "Hello from dup!\n", 16);
    write(STDOUT_FILENO, "Hello from dup2!\n", 18);
    write(fd_dup3, "Hello from dup3!\n", 18);

    close(fd);
    close(fd_dup);
    close(fd_dup3);
    return 0;
}
```

---

## Understanding `fork()`
The `fork()` system call is a fundamental concept in Unix-like operating systems. It is used to create a new process by duplicating the current process. Here’s everything you need to know about `fork()`:

---

### What is `fork()`?
- The `fork()` system call is used to create a **child process** that runs concurrently with the **parent process**.
- After calling `fork()`, two processes are created:
  1. **Parent Process**: The original process that called `fork()`.
  2. **Child Process**: A new process that is an exact copy of the parent process, except for a few differences (described below).

---

### How `fork()` Works
- When `fork()` is called:
  - The operating system creates a new process.
  - The child process receives a copy of the parent process’s memory space, file descriptors, and execution state.
- The `fork()` system call returns:
  - **0** to the child process.
  - **The child's process ID (PID)** to the parent process.
  - **-1** if the `fork()` call fails (e.g., due to resource limits).

---

### Example Code
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork(); // Create a new process

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Code executed by the child process
        printf("Hello from the child process! PID: %d\n", getpid());
    } else {
        // Code executed by the parent process
        printf("Hello from the parent process! PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
}
```

---

### 📊 Key Characteristics of `fork()`
| Feature                       | Parent Process                          | Child Process                          |
|-------------------------------|-----------------------------------------|-----------------------------------------|
| **Memory**                    | Shares a copy of its memory.            | Receives a copy of the parent’s memory. |
| **Process ID** (PID)          | Retains its original PID.               | Gets a new, unique PID.                |
| **File Descriptors**          | Shares file descriptors with the child. | Inherits the parent’s file descriptors.|
| **Execution**                 | Continues execution after `fork()`.     | Starts execution after `fork()`.       |

---

### Use Cases of `fork()`
1. **Creating a New Process**:
   - `fork()` is used to create a separate process for tasks like running a new program.
2. **Piping and Redirection**:
   - Commonly used in conjunction with `exec()` and `pipe()` to build features like shells and command pipelines.
3. **Concurrent Execution**:
   - Allows parallel execution of tasks in both parent and child processes.

---

### 🚩 Notes and Caveats
- **Resource Usage**:
  - Each `fork()` creates a new process, which consumes system resources like memory and CPU.
- **Zombie Processes**:
  - When a child process terminates, it becomes a "zombie" until the parent process calls `wait()` to retrieve its exit status.
- **Error Handling**:
  - Always check the return value of `fork()` to handle errors properly.

---

### 🔗 Related System Calls
1. **`exec()`**:
   - Replaces the current process image with a new program.
   - Often used in combination with `fork()` to run a new program in the child process.
2. **`wait()`**:
   - Used by the parent process to wait for the child process to terminate.
3. **`pipe()`**:
   - Used to establish inter-process communication between parent and child processes.

---

By mastering `fork()`, you gain the ability to build powerful concurrent applications, enabling features like multi-processing, efficient resource management, and inter-process communication. 🚀
