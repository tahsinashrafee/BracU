#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_LENGTH 30

int main() {
    int fileDescriptor;
    ssize_t buffer;
    char input_line[MAX_LENGTH];
    int user_input = 0;

    
    fileDescriptor = open("myfile.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fileDescriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    
    while (user_input != -1) {
        fgets(input_line, MAX_LENGTH, stdin);
        sscanf(input_line, "%d", &user_input);
        if (user_input != -1) {
            buffer = write(fileDescriptor, input_line, sizeof(input_line));
            if (buffer == -1) {
                perror("Error writing to file");
                close(fileDescriptor);
                return 1;
            }
        }
    }

    
    if (close(fileDescriptor) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}

