/* Test the framebuffer device on STM32F469-Disco */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main() {
    int fb_fd = open("/dev/fb0", O_RDWR);
    if (fb_fd == -1) {
        perror("Error opening framebuffer device");
        return 1;
    }

    struct fb_fix_screeninfo finfo;
    if (ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo)) {
        perror("Error reading fixed information");
        close(fb_fd);
        return 1;
    }
    struct fb_var_screeninfo vinfo;
    if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo)) {
        perror("Error reading variable information");
        close(fb_fd);
        return 1;
    }
    printf("Screen size is %dx%d.\n", vinfo.xres_virtual, vinfo.yres_virtual);
    printf("Screen bits per pixel is %d.\n", vinfo.bits_per_pixel);
    printf("Screen line length is %d.\n", finfo.line_length);

    long screensize = vinfo.yres_virtual * finfo.line_length;
    unsigned char *fbp = mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
    if ((int)fbp == -1) {
        perror("Error mapping framebuffer device to memory");
        close(fb_fd);
        return 1;
    }

    int x, y;
    for (y = 100; y < 200; y++) {
        for (x = 100; x < 200; x++) {
            long location = x * (vinfo.bits_per_pixel / 8) + y * finfo.line_length;
            if (vinfo.bits_per_pixel == 16)
                *((unsigned short *)(fbp + location)) = 0xf7e0; // Yellow
            else
                *((unsigned int *)(fbp + location)) = 0xffffff; // White
        }
    }

    munmap(fbp, screensize);
    close(fb_fd);

    return 0;
}
