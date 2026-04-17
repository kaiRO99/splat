/**
 * @file output_img.c
 * @brief Output logic.
 * @author Kai Ryall Ota
 * @date April 2026
 * */

#include "output_img.h"
#include "config.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <webp/encode.h>

/**
 * @brief Encodes and prints raw RGB to .webp
 * @param{uint8_t*} pixels RGB to encode.
 * @param{Config*} config Configuration object.
 * @param{char*} output_path Path of file to print to.
 * @param{int} width
 * @param{int} height
 * @param{int} stride
 * @param{int} channels
 * */
int output_webp(uint8_t *pixels, Config *config, char *output_path, int width,
                int height, int stride, int channels) {
    // encode rgb into output
    uint8_t *webp = NULL;
    size_t size;
    // encode
    if (channels == 4) {
        size = WebPEncodeRGBA(pixels, width, height, stride, config->quality,
                              &webp);
    } else {
        size = WebPEncodeRGB(pixels, width, height, stride, config->quality,
                             &webp);
    } // if else
    // NOTE: ouput is malloced in WebpEncodeRGB

    // free pixels
    free(pixels);

    if (size == 0) {
        // failed
        return 1;
    } // if

    FILE *out = fopen(output_path, "wb");
    if (!out) {
        printf("failed to open file\n");
        WebPFree(webp);
        return 1;
    } // if

    fwrite(webp, 1, size, out);
    fclose(out);
    WebPFree(webp);
    return 0;
} // output_webp()
