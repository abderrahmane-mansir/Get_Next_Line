*This project has been created as part of the 42 curriculum by **amansir**.*

# get_next_line

## Description

The **get_next_line** project consists of implementing a function that reads a file
descriptor line by line and returns the next available line each time it is called.

The goal of this project is to gain a deep understanding of:
- File descriptors
- Static variables
- Memory management
- Buffered reading with `read()`
- Handling edge cases such as EOF, errors, and multiple file descriptors

The function must work efficiently and reliably, even when reading from multiple file
descriptors at the same time (bonus part).

---

## Instructions

### Compilation

This project provides the get_next_line function and does not include a default
main program.

Compile it together with your own test file:

````bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
````

To define a custom buffer size at compile time:


````bash
cc -D BUFFER_SIZE=42 -Wall -Wextra -Werror \
get_next_line.c get_next_line_utils.c main.c
````

### Bonus (Multiple File Descriptors)

For the bonus version that supports multiple file descriptors:

````bash
cc -Wall -Wextra -Werror \
get_next_line_bonus.c get_next_line_utils_bonus.c main.c
````

### Execution

Run the compiled binary:

````bash
./a.out
````

Example usage inside main.c:

````c
int fd;
char *line;

fd = open("file.txt", O_RDONLY);
while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
````

Each call to get_next_line returns:

A single line ending with \n (if present)

Or NULL when EOF is reached or an error occurs

Notes

BUFFER_SIZE must be strictly greater than 0

The function works with any valid file descriptor

Memory must be freed by the caller after each line

Bonus version supports interleaved reads across multiple file descriptors

## Resources

AI tools were used in a limited way, mainly to clarify certain concepts related to file descriptors and buffered reading, and to quickly verify understanding of edge cases. They were also occasionally consulted for documentation wording.<br>
[Static Variable](https://en.wikipedia.org/wiki/Static_variable)</br>
[File Descriptor](https://en.wikipedia.org/wiki/File_descriptor)</br>
[Read Function](https://man7.org/linux/man-pages/man2/read.2.html)</br>