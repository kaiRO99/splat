/**
 * @file is_jpeg.c
 * @brief Checks if file extension is .jpeg
 * @author Kai Ryall Ota
 * @date March 2026
 * */
#include "is_jpeg.h"
#include <string.h>

/**
 * @brief Checks if file has .jpeg extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check
 * */
int is_jpeg(const char *filename) {
    if (!filename)
        return 0;

    size_t len = strlen(filename);

    // check for .md
    if (len < 6)
        return 0; // shortest possible is x.jpeg

    // Check for .md (case insensitive)
    const char *extension = filename + len - 5;
    if (strcmp(extension, ".jpeg") == 0) {
        return 1;
    } // if

    return 0;
} // is_md()
