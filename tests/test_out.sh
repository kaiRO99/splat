#!/usr/bin/env sh
# tests/test_out.sh
# @brief tests the output flag for file and dir
# @author Kai Ryall Ota
# @date April 2026

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

BINARY="./bin/splat"
INPUT_IMG="./tests/fixtures/testjpg.jpg"
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

cleanUp(){
    rm -f "$OUTPUT_IMG"
    rm -rf "$OUTPUT_DIR"
} # cleanUp()

# --- check outputs for image ---

# check for outputs
if [ ! -f "$OUTPUT_IMG" ]; then
    echo -e "${RED}FAIL: output file not created.${NC}"
    cleanUp
    exit 1
fi

# ensure output filr not empty
if [ ! -s "$OUTPUT_IMG" ]; then
    echo -e "${RED}FAIL: output file is empty.${NC}"
    cleanUp
    exit 1
fi

# check output is valid webp (first 4 bytes are RIFF, bytes 8-11 are WEBP)
MAGIC=$(xxd -p -l 4 "$OUTPUT_IMG")
if [ "$MAGIC" != "52494646" ]; then
    echo -e "${RED}FAIL: output is not a valid webp file.${NC}"
    cleanUp
    exit 1
fi

# --- check outputs for dir ---

# check for outputs
if [ ! -f "$OUTPUT_DIR/testjpg.webp" ]; then
    echo -e "${RED}FAIL: output file not created.${NC}"
    cleanUp
    exit 1
fi

# ensure output filr not empty
if [ ! -s "$OUTPUT_DIR/testjpg.webp" ]; then
    echo -e "${RED}FAIL: output file is empty.${NC}"
    cleanUp
    exit 1
fi

# check output is valid webp (first 4 bytes are RIFF, bytes 8-11 are WEBP)
MAGIC=$(xxd -p -l 4 "$OUTPUT_DIR/testjpg.webp")
if [ "$MAGIC" != "52494646" ]; then
    echo -e "${RED}FAIL: output is not a valid webp file.${NC}"
    cleanUp
    exit 1
fi

echo  -e "${GREEN}PASS: output test${NC}"
cleanUp
