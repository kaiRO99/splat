/**
 * @file output_img.h
 * @brief Output logic.
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#ifndef OUTPUT_IMG_H_
#define OUTPUT_IMG_H_

#include "config.h"
#include <stdint.h>

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
                int height, int stride, int channels);

#endif // OUTPUT_IMG_H_
