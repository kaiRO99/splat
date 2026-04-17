/**
 * @file config.h
 * @brief typedef of cli configuration
 * @author Kai Ryall Ota
 * @date March 2026
 * */
#ifndef CONFIG_H_
#define CONFIG_H_

// config structure
typedef struct {
    char *input_path;
    char *output_path;
    int output_path_allocated;
    int quality;
    int dry_run;
    int recursive;
    int force;
} Config;

#endif // CONFIG_H_
