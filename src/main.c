/**
 * @file main.c
 * @brief Entry point for splat
 * @author Kai Ryall Ota
 * @date Feb 2026
 * */

// clang-format off
#include "is_jpeg.h"
#include "is_ppm.h"
#include "is_png.h"
#include <png.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <webp/decode.h>
#include <webp/encode.h>
#include <jpeglib.h>
// clang-format on

// then read scanlines into your pixel buffer...
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
    int width, height, stride;
    int channels = 0; // track RGB or RGBA
    uint8_t *pixels = NULL;
    // TODO: put the filechecks in a function that calls the helper functions,
    // then call switch here? file check returns int
    // TODO: png
    // TODO: raw?

    if (is_jpeg(argv[1])) {
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;
        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_decompress(&cinfo);
        jpeg_stdio_src(&cinfo, in);
        jpeg_read_header(&cinfo, TRUE);
        jpeg_start_decompress(&cinfo);

        width = cinfo.output_width;
        height = cinfo.output_height;
        stride = width * 3;

        pixels = malloc((size_t)height * stride);
        if (!pixels) {
            // alocation failed
            return 0;
        } // if

        while (cinfo.output_scanline < cinfo.output_height) {
            uint8_t *row = pixels + cinfo.output_scanline * stride;
            jpeg_read_scanlines(&cinfo, &row, 1);
        }

        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        // at this point, raw data is in pixels
    }
    if (is_ppm(argv[1])) { // .ppm
        char magic[3];
        int maxval;

        fscanf(in, "%2s %d %d %d ", magic, &width, &height, &maxval);

        pixels = malloc((size_t)height * width * 3);
        if (!pixels) {
            // alocation failed
            return 0;
        } // if
        stride = width * 3;
        size_t read = fread(pixels, 3, width * height, in);
        if (read == 0) {
            return 0;
        } // if
    } // if
    if (is_png(argv[1])) {
        // .png
        png_structp png =
            png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        png_infop info = png_create_info_struct(png);
        png_init_io(png, in);
        png_read_info(png, info);

        width = png_get_image_width(png, info);
        height = png_get_image_height(png, info);

        // normalize to 8-bit rgb
        png_set_strip_16(png);
        png_set_packing(png);
        png_set_expand(png);
        png_read_update_info(png, info);

        channels = png_get_channels(png, info);
        stride = width * channels;
        pixels = malloc((size_t)height * stride);

        png_bytep rows[height];
        for (int i = 0; i < height; i++) {
            rows[i] = pixels + i * stride;
        }
        png_read_image(png, rows);
        png_destroy_read_struct(&png, &info, NULL);
    } // if

    // argv[1] is the filename
    fclose(in);

    uint8_t *output = NULL;
    size_t size;
    // encode
    if (channels == 4) {
        size = WebPEncodeRGBA(pixels, width, height, stride, 100, &output);
    } else {
        size = WebPEncodeRGB(pixels, width, height, stride, 100, &output);
    }

    if (pixels) {
        free(pixels);
    }

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
