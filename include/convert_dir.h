/**
 * @file convert_dir.h
 * @brief Converts image files in a directory
 * @author Kai Ryall Ota
 * @date March 2026
 * */
#ifndef CONVERT_DIR_H_
#define CONVERT_DIR_H_

#include "config.h"

/**
 * @brief Convert any image file in a directory.
 * @param {Config*} config Configuration to execute parsing.
 * @return{int} Completion status.
 * */
int convert_dir(Config *config);

#endif // CONVERT_DIR_H_
