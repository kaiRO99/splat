/**
 * @file parse_jpeg.c
 * @brief functions to parse jpeg,jpg ppm and png files.
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#include "parse_img.h"
#include <jpeglib.h>
#include <png.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Parses a jpeg or jpg file in to raw rgb.
 * @param{FILE*} in File to parse.
 * @param{int} width Width of image.
 * @param{int} height Height of image.
 * @param{int} stride Width * 3 (rbg).
 * @return{uint8_t*} Raw rbg buffer.
 * */
uint8_t *parse_jpeg(FILE *in, int *width, int *height, int *stride) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, in);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    *width = cinfo.output_width;
    *height = cinfo.output_height;
    *stride = *width * 3;

    uint8_t *pixels = malloc((size_t)(*height) * (*stride));
    if (!pixels) {
        // alocation failed
        return NULL;
    } // if

    while (cinfo.output_scanline < cinfo.output_height) {
        uint8_t *row = pixels + cinfo.output_scanline * (*stride);
        jpeg_read_scanlines(&cinfo, &row, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    // at this point, raw data is in pixels
    return pixels;
} // parse_jpg

/**
 * @brief Parses a ppm file in to raw rgb.
 * @param{FILE*} in File to parse.
 * @param{int} width Width of image.
 * @param{int} height Height of image.
 * @param{int} stride Width * 3 (rbg).
 * @return{uint8_t*} Raw rbg buffer.
 * */
uint8_t *parse_ppm(FILE *in, int *width, int *height, int *stride) {
    char magic[3];
    int maxval;

    fscanf(in, "%2s %d %d %d ", magic, width, height, &maxval);

    *stride = *width * 3;
    uint8_t *pixels = malloc((size_t)(*height) * (*stride));
    if (!pixels) {
        // alocation failed
        return NULL;
    } // if

    size_t read = fread(pixels, 3, (*width) * (*height), in);
    if (read == 0) {
        free(pixels);
        return NULL;
    } // if
    return pixels;

} // parse_ppm

/**
 * @brief Parses a png file in to raw rgb.
 * @param{FILE*} in File to parse.
 * @param{int} width Width of image.
 * @param{int} height Height of image.
 * @param{int} stride Width * 3 (rbg).
 * @param{int} channels Tracks channels for encoding (3 or 4)
 * @return{uint8_t*} Raw rbg buffer.
 * */
uint8_t *parse_png(FILE *in, int *width, int *height, int *stride,
                   int *channels) {
    // .png
    png_structp png =
        png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    png_init_io(png, in);
    png_read_info(png, info);

    *width = png_get_image_width(png, info);
    *height = png_get_image_height(png, info);

    // normalize to 8-bit rgb
    png_set_strip_16(png);
    png_set_packing(png);
    png_set_expand(png);
    png_read_update_info(png, info);

    *channels = png_get_channels(png, info);
    *stride = *width * (*channels);
    uint8_t *pixels = malloc((size_t)(*height) * (*stride));
    if (!pixels) {
        // alocation failed
        return NULL;
    } // if

    png_bytep rows[*height];
    for (int i = 0; i < (*height); i++) {
        rows[i] = pixels + i * (*stride);
    }
    png_read_image(png, rows);
    png_destroy_read_struct(&png, &info, NULL);

    return pixels;

} // parse_png
