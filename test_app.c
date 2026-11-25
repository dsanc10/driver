#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 100

int main(void)
{
    char input[SIZE] = "Test string sent from user space app";
    char output[SIZE] = {0};

    int fd;
    int ret;
    int message_length;

    fd = open("/dev/test_mod01", O_RDWR);

    if (fd == -1)
    {
        printf("ERROR opening device\n");
        return -1;
    }

    printf("Start write:\n%s\n\n", input);

    message_length = strlen(input);
    ret = write(fd, input, message_length);

    if (ret < 0)
    {
        printf("WRITE ERROR\n");
        close(fd);
        return -1;
    }

    printf("Reading from device:\n");

    for (int i = 0; i < ret; i += 10)
    {
        int bytes_to_read = ret - i;

        if (bytes_to_read > 10)
            bytes_to_read = 10;

        memset(output, 0, sizeof(output));

        int bytes_read = read(fd, output, bytes_to_read);

        if (bytes_read < 0)
        {
            printf("READ ERROR\n");
            close(fd);
            return -1;
        }

        output[bytes_read] = '\0';
        printf("%s\n", output);
    }

    close(fd);

    return 0;
}
