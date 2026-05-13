# Operating Systems Lab — C Programming Exercises

A collection of C programming exercises covering core Operating Systems concepts, structured as weekly labs progressing from basic I/O to advanced concurrency and inter-process communication.

---

## How It Works

Each lab folder targets a specific OS or systems programming concept. Exercises build on each other — early labs establish C fundamentals (functions, pointers, CLI arguments), while later labs introduce Linux system calls for process management, IPC, shared memory, threading, and synchronization. Code is written for Linux and compiled with GCC.

---

## Lab Breakdown

### Lab 1 — C Fundamentals
Basic C programming: unit conversions, functions, command-line arguments, loops, conditionals, pointers, and arrays.

| File | Description |
|---|---|
| `exer1/main.c` | Converts meters to kilometers (hardcoded) |
| `exer2/main.c` | Meter-to-km and Fahrenheit-to-Celsius conversion functions |
| `exer3/main.c` | Sums two integers passed as command-line arguments |
| `exer4/exer4p1.c` | Prints even numbers up to a user-supplied max |
| `exer4/exer4p2.c` | Finds the maximum of three integers (2 from CLI, 1 from stdin) |
| `exer4/lab1exercise1.c` | Minimal stub — uninitialized variable print |
| `exer5/main.c` | Multiplies three numbers (mix of CLI args and stdin) |
| `exer6/lab1pointer1.c` | Demonstrates pointer addresses and dereferencing |
| `exer6/lab1pointer2.c` | Variable swap without a function |
| `exer6/lab1pointer3.c` | Variable swap using pointers passed to a function |
| `exer7/main.c` | Reads n numbers and computes their average using a VLA |

---

### Lab 2 — Strings & I/O
String handling with `fgets`, `scanf`, and character arrays.

| File | Description |
|---|---|
| `exer1/exer2.c` | Reads a string with `fgets`, prints a fixed message |
| `exer2/exer2.c` | Reads and echoes both a string and an integer |
| `exer3/exer3.c` | Prints all suffixes of the string `"hello"` |

---

### Lab 3 — Processes & `fork()`
Process creation, parent/child relationships, `wait()`, and `exec()`.

| File | Description |
|---|---|
| `exer1/exer1.c` | Forks a child, demonstrates PID/PPID, checks exit status with `WIFEXITED` |
| `exer2/exer2.c` | Child replaces itself with `date` via `execlp()`; parent waits and reports exit code |

---

### Lab 4 — Pipes
Unidirectional and bidirectional inter-process communication using `pipe()`.

| File | Description |
|---|---|
| `exer1/exer1.c` | Bidirectional pipe: child sends a string, parent echoes back byte count, child verifies integrity |
| `exer2/exer2.c` | Child reads 10 integers and sends them through a pipe; parent computes and prints the sum |

---

### Lab 5 — `dup2()` & `exec()` Pipes
Redirecting standard I/O with `dup2` to chain processes like a shell pipeline.

| File | Description |
|---|---|
| `exer1.c` | Pipes `cat file.txt` into `grep word` by redirecting stdout/stdin with `dup2` and calling `execlp` |
| `file.txt` | Sample text file used by the `cat`/`grep` pipeline |

---

### Lab 6 — Sockets (TCP)
Client-server communication over TCP using the Berkeley sockets API.

| File | Description |
|---|---|
| `server.c` | TCP server on port 7777: receives "hello", replies "Hello back", then receives an integer array and sends back its sum |
| `client.c` | TCP client: sends "hello", reads the reply, sends a user-supplied array, and receives the computed sum |

---

### Lab 7 — Shared Memory (`mmap`)
Sharing data between parent and child processes using anonymous memory-mapped regions.

| File | Description |
|---|---|
| `exer1/main.c` | Child reads N strings into shared memory; parent converts them to uppercase and prints with lengths |
| `exer2/main.c` | Producer-consumer with a circular buffer in shared memory; no synchronization (race condition intentionally visible) |
| `exer3/main.c` | Child collects student grades into shared memory; parent writes them to a file supplied as a CLI argument |
| `exer3/StudentsGrades` | Sample output file from exer3 |

---

### Lab 8 — Threads (`pthreads`)
POSIX thread creation, joining, and returning values from threads.

| File | Description |
|---|---|
| `exer1/main.c` | Spawns one thread per CLI argument; each thread generates the Fibonacci sequence up to that limit |
| `exer2/main.c` | Spawns three threads on the same array to compute average, maximum, and minimum concurrently |

---

### Lab 9 — Thread Synchronization (Semaphores)
Demonstrating race conditions and fixing them with POSIX semaphores.

| File | Description |
|---|---|
| `exer1/main.c` | Three threads print parts of "How are you?" with no synchronization — output order is non-deterministic |
| `exer2/main.c` | Same three threads, now chained with semaphores to guarantee correct print order |

---

### Testing & Practice
Scratch files and midterm preparation.

| File | Description |
|---|---|
| `midtermPractice/main.c` | Palindrome checker: child reads a string, parent checks it and sends the result back via pipes |
| `test1/main.c` | Incomplete fork/exec scratch file (does not compile — `args` and `WAIT` are undefined) |
| `test1/main.s` | Compiled x86-64 Intel-syntax assembly from a previous shared-memory exercise |

---

## Strengths

- Covers a wide range of OS topics in a logical, progressive order — from C basics all the way to threads and synchronization
- Lab 9 is a particularly clean illustration of the race condition problem (exer1) and its semaphore fix (exer2), making the concept tangible side by side
- Lab 5's `dup2`/`exec` pipe exercise mirrors exactly how shells implement the `|` operator, giving real insight into how the OS works under the hood
- Proper resource cleanup in most exercises: pipes closed on unused ends, `munmap` called, threads joined

---

## Known Issues

- `testing/test1/main.c` does not compile — `args` (used in `execvp`) and `WAIT` are undefined; clearly an unfinished draft
- `lab7/exer2/main.c` has a `printf` after `break` that is dead (unreachable) code
- `lab1/exer4/lab1exercise1.c` prints an uninitialized variable — undefined behavior
- The producer-consumer in `lab7/exer2` has no mutex or semaphore on the shared counter, making it a known race condition (likely intentional for demonstration)
- `lab1/exer1/main.c` uses a `float` literal (`4500.5f`) assigned to a `double` — harmless but inconsistent with the declared type
