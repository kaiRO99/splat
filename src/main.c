/**
 * @file main.c
 * @brief Entry point for splat
 * @author Kai Ryall Ota
 * @date Feb 2026
 * */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <webp/decode.h>
#include <webp/encode.h>

/**
 * @brief Entry point for splat
 * @param{int} argc number of arguments passed.
 * @param{char*} argv
 * */
int main(int argc, char *argv[]) {

    FILE *in = fopen(argv[1], "rb");
    FILE *out = fopen("./tests/out.webp", "wb");
    if (!in) {
        printf("failed to open file\n");
        return 0;
    }
    // argv[1] is the filename
    char magic[3];
    int width, height, maxval;

    fscanf(in, "%2s %d %d %d ", magic, &width, &height, &maxval);

    printf("magic: %s\n", magic);
    printf("width: %d, height: %d, maxval: %d\n", width, height, maxval);

    uint8_t *pixels = malloc((size_t)height * width * 3);
    if (!pixels) {
        // alocation failed
        return 0;
    } // if
    /* fread(pixels, 3, width * height, in); */
    size_t read = fread(pixels, 3, width * height, in);
    printf("read %zu pixels\n", read);
    fclose(in);

    uint8_t *output = NULL;
    int stride = width * 3;
    // encode
    size_t size = WebPEncodeRGB(pixels, width, height, stride, 100, &output);
    free(pixels);
    if (size == 0) {
        // failed
        return 0;
    } // if

    /* fwrite to an output */
    fwrite(output, 1, size, out);
    fclose(out);
    WebPFree(output);
    return 1;
} // main()
