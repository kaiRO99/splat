/**
 * @file is_png.c
 * @brief Checks if file extension is .png
 * @author Kai Ryall Ota
 * @date March 2026
 * */
#include "is_ppm.h"
#include <string.h>

/**
 * @brief Checks if file has .png extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check
 * */
int is_png(const char *filename) {
    if (!filename)
        return 0;

    size_t len = strlen(filename);

    if (len < 5)
        return 0; // shortest possible is x.png

    // Check for .png (case insensitive)
    const char *extension = filename + len - 4;
    if (strcmp(extension, ".png") == 0) {
        return 1;
    } // if

    return 0;
} // is_png()
