/**
 * @file test_utils.c
 * @brief Tests for utility functions
 * @author Kai Ryall Ota
 * @date April 2026
 * */

#include "check_ext.h"
#include "gen_out_path.h"
#include "is_dir.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdlib.h>

/**
 * @brief Setup before each test.
 * */
void setUp(void) {}
/**
 * @brief Cleanup after each test.
 * */
void tearDown(void) {}

/**
 * @brief Tests for is_ppm.
 * @see is_ppm()
 * */
void ppm_ext_test(void) {
    TEST_ASSERT_EQUAL(1, is_ppm("test_ppm.ppm"));
    TEST_ASSERT_EQUAL(0, is_ppm("test_jpg.jpg"));
} // ppm_ext_test()

/**
 * @brief Tests for is_jpeg
 * @see is_jpeg()
 * */
void jpeg_ext_test(void) {
    // .jpeg
    TEST_ASSERT_EQUAL(1, is_jpeg("test_jpeg.jpeg"));
    TEST_ASSERT_EQUAL(0, is_jpeg("test_png.png"));
    // .jpg
    TEST_ASSERT_EQUAL(1, is_jpeg("test_jpg.jpg"));
    TEST_ASSERT_EQUAL(0, is_jpeg("test_pdf.pdf"));
} // jpeg_ext_test()

/**
 * @brief Tests for is_png
 * @see is_png()
 * */
void png_ext_test(void) {
    TEST_ASSERT_EQUAL(1, is_png("test_png.png"));
    TEST_ASSERT_EQUAL(0, is_png("test_jpeg.jpeg"));
} // png_ext_test()

/**
 * @brief Tests for is_webp
 * @see is_webp()
 * */
void webp_ext_test(void) {
    TEST_ASSERT_EQUAL(1, is_webp("testwebp.webp"));
    TEST_ASSERT_EQUAL(0, is_webp("testnotwebp.jpeg"));
} // webp_ext_test()

/**
 * @brief Tests for supported_ext.
 * @see supported_ext()
 * */
void supported_ext_test(void) {
    TEST_ASSERT_EQUAL(1, supported_ext(".jpeg"));
    TEST_ASSERT_EQUAL(1, supported_ext(".jpg"));
    TEST_ASSERT_EQUAL(1, supported_ext(".ppm"));
    TEST_ASSERT_EQUAL(1, supported_ext(".png"));
    TEST_ASSERT_EQUAL(0, supported_ext(".md"));
} // supported_ext_test()

/**
 * @brief Tests for is_supported.
 * @see is_supported()
 * */
void is_supported_test(void) {
    TEST_ASSERT_EQUAL(1, is_supported("testpng.png"));
    TEST_ASSERT_EQUAL(0, is_supported("testpdf.pdf"));
} // is_supported_test()

/**
 * @brief Tests for is_dir
 * @see is_dir()
 * */
void dir_test(void) {
    // must use real path that exists
    TEST_ASSERT_EQUAL(1, is_dir("tests"));
    TEST_ASSERT_EQUAL(1, is_dir("tests/"));
    TEST_ASSERT_EQUAL(0, is_dir("tests/test.png"));
    TEST_ASSERT_EQUAL(0, is_dir("nonexistent/"));
} // dir_test()

/**
 * @brief Tests for gen_out_path.
 * @see generate_output_path()
 * */
void gen_out_path_test(void) {
    char *input_path = "dir/filename.png";

    char *output_path = generate_output_path(input_path);

    free(output_path);

} // gen_out_path()

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(ppm_ext_test);
    RUN_TEST(jpeg_ext_test);
    RUN_TEST(png_ext_test);
    RUN_TEST(webp_ext_test);
    RUN_TEST(supported_ext_test);
    RUN_TEST(is_supported_test);
    RUN_TEST(dir_test);
    RUN_TEST(gen_out_path_test);
    return UNITY_END();

} // main()
