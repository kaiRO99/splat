#!/usr/bin/env sh
# tests/test_out.sh
# @brief tests the output flag for file and dir
# @author Kai Ryall Ota
# @date April 2026

BINARY="./bin/splat"
INPUT_IMG="./tests/fixtures/KaiRyallOtajpg.jpg"
INPUT_DIR="./tests/fixtures"
OUTPUT_IMG="./tests/fixtures/outputs/out.webp"
OUTPUT_DIR="./tests/fixtures/outputs/dir"

# cleanup before
rm -f "$OUTPUT_IMG"
rm -rf "$OUTPUT_DIR"

#run binary
# image
$BINARY -o "$OUTPUT_IMG" "$INPUT_IMG"
# directory
$BINARY -o "$OUTPUT_DIR" "$INPUT_DIR"

# --- check outputs for image ---

# check for outputs
if [ ! -f "$OUTPUT_IMG" ]; then
    echo "FAIL: output file not created."
    exit 1
fi

# ensure output filr not empty
if [ ! -s "$OUTPUT_IMG" ]; then
    echo "FAIL: output file is empty."
    exit 1
fi

# check output is valid webp (first 4 bytes are RIFF, bytes 8-11 are WEBP)
MAGIC=$(xxd -p -l 4 "$OUTPUT_IMG")
if [ "$MAGIC" != "52494646" ]; then
    echo "FAIL: output is not a valid webp file."
    exit 1
fi

# --- check outputs for dir ---

# check for outputs
if [ ! -f "$OUTPUT_DIR/KaiRyallOtajpg.webp" ]; then
    echo "FAIL: output file not created."
    exit 1
fi

# ensure output filr not empty
if [ ! -s "$OUTPUT_DIR/KaiRyallOtajpg.webp" ]; then
    echo "FAIL: output file is empty."
    exit 1
fi

# check output is valid webp (first 4 bytes are RIFF, bytes 8-11 are WEBP)
MAGIC=$(xxd -p -l 4 "$OUTPUT_DIR/KaiRyallOtajpg.webp")
if [ "$MAGIC" != "52494646" ]; then
    echo "FAIL: output is not a valid webp file."
    exit 1
fi

echo "PASS: output test"
rm -f "$OUTPUT_IMG"
rm -rf "$OUTPUT_DIR"
