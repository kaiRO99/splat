/**
 * @file check_ext.h
 * @brief Functions used to check the extension of a file.
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#ifndef CHECK_EXT_H_
#define CHECK_EXT_H_

/**
 * @brief Checks if file has .png extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check
 * */
int is_png(const char *filename);

/**
 * @brief Checks if file has .ppm extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check (1:is ppm)
 * */
int is_ppm(const char *filename);

/**
 * @brief Checks if file has .jpeg or .jpg extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check(1:is jpeg/jpg)
 * */
int is_jpeg(const char *filename);

/**
 * @brief Checks if file has .webp extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check(1:is jpeg/jpg)
 * */
int is_webp(const char *filename);

/**
 * @brief Checks if the extension of a filename is of the accepted type.
 * @param{char*} ext Extension to check.
 * @return{int} Status of comparison. (1:is supported, 0:not supported).
 * */
int supported_ext(char *ext);

/**
 * @brief Checks if file has .jpeg .jpg .ppm .png extension
 * @param{char*} filename Filename to check.
 * @return{int} Status of check(1:is supported)
 * */
int is_supported(const char *filename);

#endif // CHECK_EXT_H_
