/**
 * @file gen_out_path.c
 * @brief Generate the output path based on input path.
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#define _POSIX_C_SOURCE 200809L
#include "gen_out_path.h"
#include "check_ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Generate output file in same directory as input
 * file.(.jpeg/.jpg/.ppm/.png->.webp)
 * @param{*char} input_path
 * @return{char*} Filepath of target file.
 * */
char *generate_output_path(const char *input_path) {
    if (!input_path) {
        fprintf(stderr, "ERROR: input_path is NULL in generate_output_path\n");
        return NULL;
    }
    char *input_copy = strdup(input_path);
    // char *base = basename(input_copy); // if need to extract just filename

    // remove after .
    char *dot = strrchr(input_copy, '.');
    if (dot && supported_ext(dot)) {
        *dot = '\0';
    } // if

    // build outout path: same location, cjange extension
    char *output = malloc(strlen(input_copy) + 5);
    sprintf(output, "%s.webp", input_copy);

    free(input_copy);
    return output;
} // generate_target_path()
