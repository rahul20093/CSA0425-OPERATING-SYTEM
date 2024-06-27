#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd, fd2;
    char buffer[256];

    // Create a file and write to it
    fd = open("example.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    write(fd, "Hello, World!\n", 14);
    close(fd);

    // Open the file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read from the file and display content
    read(fd, buffer, 256);
    printf("Contents of the file: %s\n", buffer);
    close(fd);

    // Copy the file to another file
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd2 = open("copy.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd2 == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (read(fd, buffer, 256) > 0) {
        write(fd2, buffer, 256);
    }

    close(fd);
    close(fd2);

    // Remove the original file
    if (unlink("example.txt") == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}

