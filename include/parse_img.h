/**
 * @file parse_img.h
 * @brief Functions for image parsing of jpeg, jpg, ppm and png formats.
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#ifndef PARSE_IMG_H_
#define PARSE_IMG_H_

#include <stdint.h>
#include <stdio.h>

/**
 * @brief Parses a jpeg or jpg file in to raw rgb.
 * @param{FILE*} in File to parse.
 * @param{int} width Width of image.
 * @param{int} height Height of image.
 * @param{int} stride Width * 3 (rbg).
 * @return{int} status of parsing
 * */
uint8_t *parse_jpeg(FILE *in, int *width, int *height, int *stride);

/**
 * @brief Parses a ppm file in to raw rgb.
 * @param{FILE*} in File to parse.
 * @param{int} width Width of image.
 * @param{int} height Height of image.
 * @param{int} stride Width * 3 (rbg).
 * @return{uint8_t*} Raw rbg buffer.
 * */
uint8_t *parse_ppm(FILE *in, int *width, int *height, int *stride);

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
                   int *channels);

#endif // PARSE_IMG_H_
