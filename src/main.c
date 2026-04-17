/**
 * @file main.c
 * @brief Entry point for splat
 * @author Kai Ryall Ota
 * @date Feb 2026
 * */

// clang-format off
#include "config.h"
#include "execute_conversion.h"
#include "parse_args.h"
#include <png.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>
// clang-format on

/**
 * @brief Entry point for splat
 * @param{int} argc number of arguments passed.
 * @param{char*} argv
 * */
int main(int argc, char *argv[]) {

    Config config;

    int parse = parse_args(argc, argv, &config);
    // 1 and -2 errors are handled in parse_args()
    if (parse != 0) {
        // exit
        exit(1);
    } // if

    int result = execute_conversion(&config);

    if (config.output_path_allocated) {
        free(config.output_path);
    }
    // execute conversion:
    return result;

} // main()
