*Este proyecto ha sido creado como parte del currículo de 42 por guilfran.*

# Get Next Line

## Description
**Get_Next_Line** is a core project of the 42 cursus. Its primary objective is to program a function that returns a line read from a file descriptor (`fd`). Whether reading from a file or from the standard input (`stdin`), the function must be able to return the next line in each successive call until the end of the file (EOF) is reached.

This project introduces foundational concepts in C, specifically the management of **static variables**. It teaches how to retain information across different calls to the same function without losing data from previous buffer reads, handling arbitrary buffer sizes efficiently.

## Detailed Function Description
The `get_next_line` function reads from a file descriptor chunk by chunk using a defined `BUFFER_SIZE`, accumulating the characters until a newline character (`\n`) or EOF is encountered. It extracts the current line while keeping the remaining bytes stored in a static variable for future calls.

### Core Components / Helpers

**`get_next_line`** - The main entry point.<br>
  * *Behavior:* Validates inputs, handles the reading loop via `read()`, manages buffer strings, and extracts the final line to return.<br><br>

**`ft_line`** - Line extraction helper.<br>
  * *Behavior:* Parses the accumulated static string and isolates everything up to and including the first newline character (`\n`) to be returned as the result.<br><br>

**`ft_strjoin`** - String concatenation helper.<br>
  * *Behavior:* Appends the newly read buffer onto the existing static content safely, handling dynamic memory allocation and cleanup of old pointers.<br><br>

**`ft_lenchr`** - Utility helper.<br>
  * *Behavior:* Handles length calculation and newline detection depending on the requested mode.<br><br>

*Note: The function returns the line that was read, or `NULL` if there is nothing else to read or if an error occurred.*

### Algoritmo y Estructuras de Datos
As required by the project guidelines, the technical decisions made are detailed below:

*   **Algorithm:** The function relies on a **static variable (`static char *line`)** acting as a persistent buffer (stash) between function calls. A `while` loop reads data from the file descriptor using `read()` with size `BUFFER_SIZE`, appending each chunk to the static variable using `ft_strjoin` until a newline (`\n`) is found or `read` returns `0` (EOF). Then, an extraction function slices the line up to `\n`, and a temporary pointer updates the static variable with the remaining leftover text for the next call.

# Instructions

### Prerequisites
To compile and test this project, you will need:
*   A C compiler (`cc`)
*   Make

### Compilation
The project does not include a default Makefile on its own, but you can compile your files directly along with your tests by defining the `BUFFER_SIZE` macro using the `-D` flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <archivos.c>
```

### Run / Usage
To use `get_next_line` in your program, include the header file and call the function inside a loop:

```c
int main(void)
{
    int fd = open("archivo.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

# Resources

### Classic References
*   **Youtube tutorial:** [(Link 1)](https://www.youtube.com/watch?v=eX8UyJGAv9g) - [(Link 2)](https://www.youtube.com/watch?v=-Mt2FdJjVno)

### AI Usage

Artificial Intelligence tools were used in this project for the following tasks:
*   **Concept Review:** As a tutoring assistant to understand the logic flow of static variables and buffer management across multiple function calls.
*   **Documentation:** To help structure, format, and generate the Markdown content for this `README.md` file matching the required course standards.