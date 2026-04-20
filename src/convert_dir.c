/**
 * @file convert_dir.c
 * @brief Converts image files in a directory
 * @author Kai Ryall Ota
 * @date March 2026
 * */
#include "convert_dir.h"
#include "check_ext.h"
#include "config.h"
#include "convert_img.h"
#include "gen_out_path.h"
#include "is_dir.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * @brief Convert any image file in a directory.
 * @param {Config*} config Configuration to execute parsing.
 * @return{int} Completion status.
 * */
int convert_dir(Config *config) {
    DIR *dir = opendir(config->input_path);
    if (!dir) {
        fprintf(stderr, "Error: cannot open directory %s\n",
                config->input_path);
        return 1;
    } // if

    // create output dir
    if (!config->dry_run) {
        mkdir(config->output_path, 0755);
    } // if

    struct dirent *entry;
    int error_count = 0;
    int file_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        // skip . and ..
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        } // if

        // build full input path
        char input_path[1024];
        snprintf(input_path, sizeof(input_path), "%s/%s", config->input_path,
                 entry->d_name);

        // check if it is an
        if (is_supported(entry->d_name)) {
            // generate target path
            char *output_name = generate_output_path(entry->d_name);
            char output_path[1024];
            // if no -o flag, write next to source
            if (config->output_path) {
                snprintf(output_path, sizeof(output_path), "%s/%s",
                         config->output_path, output_name);
            } else {
                snprintf(output_path, sizeof(output_path), "%s/%s",
                         config->input_path, output_name);
            } // if else

            // convert
            if (convert_img(config, input_path, output_path) != 0) {
                error_count++;
            } else {
                file_count++;
            } // if else
            free(output_name);
        } else if (config->recursive && is_dir(input_path)) {
            if (config->output_path &&
                strcmp(input_path, config->output_path) == 0) {
                continue;
            } // if
            Config sub_config = *config;
            sub_config.input_path = input_path;

            // if out specified, create matching subdirectory
            // if not, leave as NULL so it outputs besiide input

            if (config->output_path) {
                char sub_output[1024];
                snprintf(sub_output, sizeof(sub_output), "%s/%s",
                         config->output_path, entry->d_name);
                sub_config.output_path = sub_output;
            } // if
            // temp config for recursion
            sub_config.output_path_allocated = 0; // no malloc used

            int result = convert_dir(&sub_config);
            if (result != 0) {
                error_count++;
            } // if
        } // else if
    } // while
    closedir(dir);
    if (!config->dry_run) {
        printf("Converted %d files from %s\n", file_count, config->input_path);
        if (error_count > 0) {
            printf("Failed: %d file(s)\n", error_count);
        } // if
    } // if
    return error_count > 0 ? 1 : 0;
} // convert_dir()
