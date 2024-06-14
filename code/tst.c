#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int main() {
    const char *device_path = "/dev/input/event0";
    int fd;
    struct input_event ev;

    fd = open(device_path, O_RDONLY);
    if (fd == -1) {
        perror("Unable to open device");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if (read(fd, &ev, sizeof(struct input_event)) == -1) {
            perror("Error reading event");
            exit(EXIT_FAILURE);
        }

        if (ev.type == EV_ABS) {
            if (ev.code == ABS_X) {
                printf("X: %d ", ev.value);
            } else if (ev.code == ABS_Y) {
                printf("Y: %d\n", ev.value);
            }
        }
    }

    close(fd);
    return 0;
}

