/**
 * @file gen_out_path.c
 * @brief Generate the output path based on input path.
 * @author Kai Ryall Ota
 * @date April 2026
 * */
#ifndef GEN_OUT_PATH_H_
#define GEN_OUT_PATH_H_

/**
 * @brief Generate output file in same directory as input
 * file.(.jpeg/.jpg/.ppm/.png->.webp)
 * @param{*char} input_path
 * @return{char*} Filepath of target file.
 * */
char *generate_output_path(const char *input_path);

#endif // GEN_OUT_PATH_H_
