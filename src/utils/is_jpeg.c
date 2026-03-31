/**
 * @file is_jpeg.c
 * @brief Checks if file extension is .jpeg or .jpg
 * @author Kai Ryall Ota
 * @date March 2026
 * */
#include "is_jpeg.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Checks if file has .jpeg or .jpg extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check
 * */
int is_jpeg(const char *filename) {
    if (!filename)
        return 0;
    const char *extension = NULL;
    size_t len = strlen(filename);
    // check for .jpg first
    if (len < 5)
        return 0; // shortest possible is x.jpg
    extension = filename + len - 4;
    if (strcmp(extension, ".jpg") == 0) {
        printf("is.jpg\n");
        return 1;
    } // if

    /* if (len < 6) */
    /*     return 0; // shortest possible is x.jpeg */

    // Check for .md (case insensitive)
    extension = filename + len - 5;
    if (strcmp(extension, ".jpeg") == 0) {
        return 1;
    } // if

    return 0;
} // is_jpeg()
