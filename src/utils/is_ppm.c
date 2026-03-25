/**
 * @file is_ppm.c
 * @brief Checks if file extension is .ppm
 * @author Kai Ryall Ota
 * @date March 2026
 * */
#include "is_ppm.h"
#include <string.h>

/**
 * @brief Checks if file has .ppm extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check
 * */
int is_ppm(const char *filename) {
    if (!filename)
        return 0;

    size_t len = strlen(filename);

    if (len < 5)
        return 0; // shortest possible is x.ppm

    // Check for .ppm (case insensitive)
    const char *extension = filename + len - 4;
    if (strcmp(extension, ".ppm") == 0) {
        return 1;
    } // if

    return 0;
} // is_md()
