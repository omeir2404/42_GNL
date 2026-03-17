*This project has been created as part of the 42 curriculum by oharoon.*

# get_next_line

## Description
`get_next_line` is a 42 project where you implement a function that reads and returns one line at a time from a file descriptor.

Function prototype:

```c
char *get_next_line(int fd);
```

Expected behavior:
- Each call returns the next line from `fd`.
- The returned string includes the trailing `\n` when present in the input.
- If EOF is reached without remaining data, or if an error occurs, the function returns `NULL`.
- The function must work with files and standard input.

Project goals:
- Practice low-level file reading with `read`.
- Understand and use `static` storage to preserve state between calls.
- Build safe dynamic string assembly with `malloc`/`free`.

## Files
Mandatory:
- `get_next_line/get_next_line.c`
- `get_next_line/get_next_line_utils.c`
- `get_next_line/get_next_line.h`

Bonus:
- `get_next_line/get_next_line_bonus.c`
- `get_next_line/get_next_line_utils_bonus.c`
- `get_next_line/get_next_line_bonus.h`

## Instructions
### Compile (mandatory)
No Makefile is required for this project. Compile manually with the usual flags and a chosen buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  -c \
  get_next_line/get_next_line.c \
  get_next_line/get_next_line_utils.c
```

Then link with your test `main.c`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  main.c get_next_line.o get_next_line_utils.o -o gnl_test
```

### Compile (bonus)

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  -c \
  get_next_line/get_next_line_bonus.c \
  get_next_line/get_next_line_utils_bonus.c
```

Then link with your bonus test `main.c`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  main.c get_next_line_bonus.o get_next_line_utils_bonus.o -o gnl_test_bonus
```

### Minimal usage example

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line/get_next_line.h"

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Algorithm (Detailed and Justified)
### Mandatory implementation
The mandatory version in `get_next_line/get_next_line.c` uses a single static buffer:

```c
static char buff[BUFFER_SIZE + 1];
```

How it works:
1. `get_next_line` keeps unread remainder data in `buff` between calls.
2. While there is data in `buff` or `read` can fetch more, it appends characters into a heap-allocated `line` via `make_line`.
3. `make_line` appends only up to the first newline (or end of current buffer chunk), so each call returns exactly one logical line.
4. `ft_check_next_line` scans `buff`, zeroes consumed bytes, and shifts the bytes after `\n` to the beginning of `buff`.
5. If a newline is found, the loop breaks and returns the current `line`.
6. If no data remains, `NULL` is returned.

Why this approach:
- It avoids reading the entire file at once.
- It guarantees incremental line-by-line output.
- The static buffer is the minimal state needed to preserve leftovers across calls.

### Bonus implementation (multiple FDs)
The bonus version in `get_next_line/get_next_line_bonus.c` keeps one static storage object containing per-fd buffers:

```c
static char buff[FOPEN_MAX][BUFFER_SIZE + 1];
```

How it works:
- Each file descriptor uses its own slot (`buff[fd]`), so reading from interleaved descriptors does not mix states.
- The line-building and leftover-shifting logic is the same as mandatory, but indexed by `fd`.

Why this satisfies bonus intent:
- Multiple descriptors can be read in round-robin order.
- State is preserved independently for each descriptor.
- It still relies on one static variable declaration in the function.

## Constraints from the Subject
- Allowed external functions: `read`, `malloc`, `free`.
- Forbidden: `lseek`, global variables, using `libft` in this project.
- Must compile with and without `-D BUFFER_SIZE=<n>`.
- Undefined behavior is accepted by subject for binary files and for files modified during active read flow.

## Testing Notes
Recommended checks:
- `BUFFER_SIZE=1`, medium values (e.g. `42`), and very large values.
- Empty file, one-line file, file without trailing newline, many short lines, one very long line.
- Input from `stdin`.
- Bonus: interleaved reads across several open descriptors.

## Resources
- 42 project subject: `en.subject.pdf`
- `read(2)` manual: `man 2 read`
- Static storage duration (C): ISO C / cppreference overview
- Memory debugging tools: `valgrind`, `AddressSanitizer`

AI usage for this repository:
- AI was used to draft and structure this `README.md`.
- Algorithm and behavior descriptions were cross-checked against the local source files and the project subject text.
