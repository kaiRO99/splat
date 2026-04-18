/**
 * @file print_usage.c
 * @brief Prints cli options
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#include "print_usage.h"
#include <stdio.h>

/**
 * @brief Prints options for cli
 * @note Triggered by -h flag
 * @param{*char} prog_name Name of program
 * */
void print_usage(const char *prog_name) {
    printf("Usage: %s [OPTIONS] [TARGET] SOURCE\n\n", prog_name);
    printf("Convert .ppm, .png, .jpeg and .jpg image files to .webp.\n\n");
    printf("Arguments:\n");
    printf("  SOURCE             File or directory to convert\n");
    printf("  TARGET             Output file or directory (optional)\n\n");
    printf("Options:\n");
    printf("  -o, --output PATH    Output directory for batch conversion\n");
    printf("  -q, --quality VALUE  Output directory for batch conversion\n");
    printf("  -r, --recursive      Process directories recursively\n");
    printf("  -f, --force          Overwrite existing files\n");
    printf("  -d, --dry-run        Show what would be done without doing it\n");
    printf("  -h, --help           Show this help message\n\n");
    printf("Examples:\n");
    printf("  %s input.jpeg                  Convert single file (output: "
           "input.webp)\n",
           prog_name);
    printf("  %s -o output.webp input.ppm    Convert with specific output "
           "name\n",
           prog_name);
    printf("  %s images/                     Convert all image files in "
           "directory\n",
           prog_name);
    printf("  %s -o out/ images/             Convert directory images/ to "
           "out/ \n",
           prog_name);
    printf("  %s -r images/                  Convert directory recursively\n",
           prog_name);
} // print_usage()
