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
    char *source_path;
    char *target_path;
    int quality;
    int dry_run;
    int recursive;
    int force;
    int webp;
} Config;

#endif // CONFIG_H_
