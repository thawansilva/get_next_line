# get_next_line
A C function that reads a line from a file descriptor, developed as part of the 42 school curriculum.

## Description
[`get_next_line`](get_next_line.c) is a function that reads a line from a file descriptor, one line at a time. The function returns the line that was read, or NULL if there is nothing else to read or if an error occurred.

## Evaluation 

<img src="/public/img/moulinette_eval.png" alt="Screenshot showing the Moulinette evaluation results for get_next_line project. The screen displays a table with columns for criteria such as norm, compilation, memory leaks, and functionality. Each row contains green checkmarks indicating successful completion of each criterion. The overall tone is positive, suggesting a successful project submission. The background is a typical web interface with navigation elements and a header displaying the project name and evaluation status.">

### Features
- Reads from multiple file descriptors simultaneously (bonus version)
- Dynamic buffer size through BUFFER_SIZE macro
- Memory efficient with proper allocation and deallocation
- Handles standard input, files, and redirection

## Function Prototype
```c
char *get_next_line(int fd);
```

### Parameters
- `fd`: The file descriptor to read from

### Return Value
- Returns a string containing the line read from the file descriptor
- Returns NULL if there is nothing else to read or if an error occurred

## Technical Details

### Buffer Management
The function uses a static buffer to store the remainder of reads between function calls. This allows it to maintain state between multiple calls to read the same file descriptor.

### Memory Management
The function properly manages memory by:
- Using [`ft_calloc`](get_next_line_utils.c) for safe memory allocation
- Freeing allocated memory when appropriate
- Handling memory allocation failures

### Utility Functions
The project includes several utility functions:
- [`ft_strlen`](get_next_line_utils.c): Calculate string length
- [`ft_strjoin`](get_next_line_utils.c): Join two strings
- [`ft_strchr`](get_next_line_utils.c): Find character in string
- [`ft_strlcpy`](get_next_line_utils.c): Copy string with size limitation

## Usage

Create a main.c file with this code below or the bonus version;

### Basic Version
```c
#include "get_next_line.h"

int main(void)
{
    int fd = open("example.txt", O_RDONLY); // You will need to create a example.txt file
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Bonus Version (Multiple FD)
```c
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY); // You will need to create both files
    int fd2 = open("file2.txt", O_RDONLY);
    char *line;

    // Read alternatively from both files
    line = get_next_line(fd1);
    printf("File 1: %s", line);
    free(line);

    line = get_next_line(fd2);
    printf("File 2: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```

## Compilation
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<size> main.c get_next_line.c get_next_line_utils.c
```

For bonus part:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<size> main.c get_next_line_bonus.c get_next_line_utils_bonus.c
```
'<size>' - represents the size of your buffer in bytes that you want to read;

## Notes
- BUFFER_SIZE can be modified during compilation
- The function handles files up to OPEN_MAX file descriptors in bonus version
- Proper error handling for invalid file descriptors and memory allocation failures

## License
This project is part of the 42 school curriculum.
