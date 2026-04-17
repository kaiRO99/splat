/**
 * @file parse_args.c
 * @brief Parses command line arguments.
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#include "parse_args.h"
#include "check_ext.h"
#include "config.h"
#include "gen_out_path.h"
#include "is_dir.h"
#include "print_usage.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Parses command line arguments.
 * @param{int} argc Number of command line arguments.
 * @param{char*} argv Array of command line arguments.
 * @param {Config*} config Configuration object to parse into.
 * @return {int} Staus of parse: 0:complete, 1: error, -2: --help flag
 * */
int parse_args(int argc, char *argv[], Config *config) {
    memset(config, 0, sizeof(Config));
    config->quality = 100; // default

    // long options
    static struct option long_options[] = {
        {"output", required_argument, 0, 'o'},
        {"quality", required_argument, 0, 'q'},
        {"recursive", no_argument, 0, 'r'},
        {"force", no_argument, 0, 'f'},
        {"dry-run", no_argument, 0, 'd'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}};

    int opt;
    optind = 1; // reset for testing
    long quality;
    char *end;

    // parse options:
    while ((opt = getopt_long(argc, argv, "o:q:rftpdh", long_options, NULL)) !=
           -1) {
        switch (opt) {
            case 'o':
                config->output_path = optarg;
                break;
            case 'q':
                quality = strtol(optarg, &end, 10);
                if (end == optarg || *end != '\0') {
                    fprintf(stderr, "error: quality value must be an integer\n");
                    return -2;
                } // if
                if (quality < 0 || quality > 100) {
                    fprintf(stderr, "error: quality must be between 0 and 100\n");
                    return -2;
                } // if
                config->quality = quality;
            break;
            case 'r':
                config->recursive = 1;
                break;
            case 'f':
                config->force = 1;
                break;
            case 'd':
                config->dry_run = 1;
                break;
            case 'h':
                print_usage(argv[0]);
                return -2;
            default:
                fprintf(stderr, "Error: Invalid arguments\n\n");
                print_usage(argv[0]);
            return 1;
        } // switch
    } // while

    int remaining_args = argc - optind;

    if (remaining_args < 1) {
        fprintf(stderr,
                "Error: No input or output file or directory specified\n\n");
        print_usage(argv[0]);
        return 1;
    } // if

    // check if input is accepted (dir or )
    if (is_dir(argv[optind])) {
        // is a directory
        config->input_path = argv[optind];
        // if there is an output, make sure it is directory too
        if (config->output_path && !is_dir(config->output_path)) {
            // error
            fprintf(stderr, "Error: Output path must be directory if input "
                    "path is directory.");
            print_usage(argv[0]);
            return 1;
        } // if
        if (!config->output_path) {
            config->output_path = argv[optind];
        } // if
          // make sure output is a path
    } else if (is_supported(argv[optind])) {
        // a file of accepted filetype
        config->input_path = argv[optind];
        if (config->output_path && !is_supported(config->output_path)) {
            // error
            fprintf(stderr, "Error: Output path must include filename with "
                    "supported extension input path is file.");
            print_usage(argv[0]);
            return 1;
        } // if
        if (!config->output_path) {
            config->output_path = generate_output_path(argv[optind]);
            config->output_path_allocated = 1;
        } // if
    } else {
        // error
        fprintf(stderr, "Error: Input path is not supported\n");
        print_usage(argv[0]);
        return 1;
    } // if else

    return 0;
} // parse_args()
