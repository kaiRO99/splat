/**
 * @file execute_conversion.c
 * @Brief Handles execution of conversion logic
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#include "execute_conversion.h"
#include "config.h"
#include "convert_dir.h"
#include "convert_img.h"
#include "gen_out_path.h"
#include "is_dir.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/**
 * @brief Handles logic of conversion execution
 * @param{Config*} config Configuration object
 * @return{int} Status of completion
 * */
int execute_conversion(Config *config) {
    // check if input exists
    struct stat st;
    if (stat(config->input_path, &st) != 0) {
        fprintf(stderr, "Error: Input %s does not exist\n", config->input_path);
        return 1;
    } // if

    // check if input is file or dir
    if (is_dir(config->input_path)) {
        // Directory

        // else set output path
        return convert_dir(config);

    } else {
        // file
        // run convert_img()
        return convert_img(config, config->input_path, config->output_path);
    } // if else
} // execute_conversion()
