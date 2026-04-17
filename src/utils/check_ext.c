/**
 * @file check_ext.c
 * @brief Functions used to check the extension of a file.
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#define _POSIX_C_SOURCE 200809L
#include "check_ext.h"
#include <string.h>

/**
 * @brief Checks if file has .png extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check
 * */
int is_png(const char *filename) {
    if (!filename)
        return 0;

    char *dot = strrchr(filename, '.');
    if (dot && strcmp(dot, ".png") == 0) {
        // is a .ppm
        return 1;
    } // if

    return 0;
} // is_png()

/**
 * @brief Checks if file has .ppm extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check (1:is ppm)
 * */
int is_ppm(const char *filename) {
    if (!filename)
        return 0;

    char *dot = strrchr(filename, '.');
    if (dot && strcmp(dot, ".ppm") == 0) {
        // is a .ppm
        return 1;
    } // if

    return 0;
} // is_ppm()

/**
 * @brief Checks if file has .jpeg or .jpg extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check(1:is jpeg/jpg)
 * */
int is_jpeg(const char *filename) {
    if (!filename)
        return 0;

    char *dot = strrchr(filename, '.');
    if (dot && (strcmp(dot, ".jpeg") == 0 || strcmp(dot, ".jpg") == 0)) {
        // is a .jpeg or .jpg
        return 1;
    } // if
    return 0;
} // is_jpeg()

/**
 * @brief Checks if file has .webp extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check(1:is jpeg/jpg)
 * */
int is_webp(const char *filename) {
    if (!filename)
        return 0;

    char *dot = strrchr(filename, '.');
    if (dot && strcmp(dot, ".webp") == 0) {
        // is a .jpeg or .jpg
        return 1;
    } // if
    return 0;
} // is_webp()

/**
 * @brief Checks if the extension of a filename is of the accepted type.
 * @param{char*} ext Extension to check.
 * @return{int} Status of comparison. (1:is supported, 0:not supported).
 * */
int supported_ext(char *ext) {
    return strcmp(ext, ".jpeg") == 0 || strcmp(ext, ".jpg") == 0 ||
           strcmp(ext, ".ppm") == 0 || strcmp(ext, ".png") == 0;
} // supported_ext()

/**
 * @brief Checks if file has .jpeg .jpg .ppm .png extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check(1:is supported)
 * */
int is_supported(const char *filename) {
    if (!filename)
        return 0;

    char *dot = strrchr(filename, '.');
    if (dot && supported_ext(dot)) {
        // is a .jpeg or .jpg
        return 1;
    } // if
    return 0;
} // is_webp()
