/**
 * @file convert_img.c
 * @brief Handles conversion of single image file.
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#ifndef CONVERT_IMG_H_
#define CONVERT_IMG_H_

#include "config.h"

/**
 * @brief Handles logic for converting a single image file
 * @param{Config*} config Configuration object.
 * @param{char*} input_path File to convert.
 * @param{char*} output_path File to print to.
 * @return{int} Status of completion
 **/
int convert_img(Config *config, char *input_path, char *output_path);

#endif // CONVERT_IMG_H_
