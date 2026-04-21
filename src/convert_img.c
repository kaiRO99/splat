/**
 * @file convert_img.c
 * @brief Handles conversion of single image file.
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#include "convert_img.h"
#include "check_ext.h"
#include "config.h"
#include "output_img.h"
#include "parse_img.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <webp/decode.h>
#include <webp/encode.h>

/**
 * @brief Handles logic for converting a single image file
 * @param{Config*} config Configuration object.
 * @param{char*} input_path File to convert.
 * @param{char*} output_path File to print to.
 * @return{int} Status of completion
 **/
int convert_img(Config *config, char *input_path, char *output_path) {

    if (config->dry_run) {
        // print and return
        printf("[DRY RUN] Convert: %s -> %s\n", input_path, output_path);
        return 0;
    } // if

    if (!config->force) {
        FILE *check = fopen(output_path, "r");
        if (check) {
            fclose(check);
            fprintf(
                stderr,
                "Skipping %s, output already exists (use -f to overwrite)\n",
                output_path);
            return 0;
        } // if
    } // if

    FILE *in = fopen(input_path, "rb");
    if (!in) {
        printf("failed to open file\n");
        return 1;
    }
    int width, height, stride;
    int channels = 0; // track RGB or RGBA
    uint8_t *pixels =
        NULL; // NOTE: malloced at if else, free() in output_webp()

    if (is_jpeg(input_path)) {
        // is a jpeg or jpg
        // parse_jpeg()
        pixels = parse_jpeg(in, &width, &height, &stride);
        if (!pixels) {
            // error
            fclose(in);
            fprintf(stderr, "Error: Unable to parse input image %s\n",
                    input_path);
            return 1;
        } // if
        // can output

    } else if (is_ppm(input_path)) {
        // is a ppm
        pixels = parse_ppm(in, &width, &height, &stride);
        if (!pixels) {
            // error
            fclose(in);
            fprintf(stderr, "Error: Unable to parse input image %s\n",
                    input_path);
            return 1;
        } // if
        // can output

    } else if (is_png(input_path)) {
        // is png
        pixels = parse_png(in, &width, &height, &stride, &channels);
        if (!pixels) {
            // error
            fclose(in);
            fprintf(stderr, "Error: Unable to parse input image %s\n",
                    input_path);
            return 1;
        } // if
    } else {
        fprintf(stderr,
                "Error: Input file must be .jpeg, .jpg, .ppm, or .png\n");
        fprintf(stderr, "Got: %s\n", input_path);
        fprintf(stderr, "DEBUG input_path: '%s'\n", input_path);
        fprintf(stderr, "DEBUG is_jpeg: %d\n", is_jpeg(input_path));
        return 1;
    } // if else
    fclose(in);
    // encode webp
    // print to output

    int result = output_webp(pixels, config, output_path, width, height, stride,
                             channels);

    if (config->output_path && config->output_path_allocated) {
        free(config->output_path);
    } // if
    return result;

} // convert_img()
