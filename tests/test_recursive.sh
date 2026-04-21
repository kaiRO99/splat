#!/usr/bin/env sh
# tests/test_recursive.sh
# @brief tests the recursive flag
# @author Kai Ryall Ota
# @date April 2026

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

BINARY="./bin/splat"
INPUT_DIR="./tests/fixtures"
OUTPUT_LVL1="./tests/fixtures/testjpeg.webp"
OUTPUT_LVL2="./tests/fixtures/lvl2/testjpg.webp"
OUTPUT_FLAG_LVL1="./tests/fixtures/outputs/testjpeg.webp"
OUTPUT_FLAG_LVL2="./tests/fixtures/outputs/lvl2/testjpg.webp"
OUTPUT_DIR="./tests/fixtures/outputs"

cleanUp(){
    rm -rf "$OUTPUT_DIR"
    rm -f "$INPUT_DIR/*.webp"
    rm -rf "$INPUT_DIR/lvl2"
}

setUp(){
    mkdir -p ./tests/fixtures/outputs # create output dir
    mkdir -p ./tests/fixtures/lvl2
    #copy to lvl 2
    cp ./tests/fixtures/testjpg.jpg ./tests/fixtures/lvl2
}

#run tests
# --- directory ---
cleanUp
setUp
$BINARY -r "$INPUT_DIR"
if [ -f "$OUTPUT_LVL1" ] && [ -f "$OUTPUT_LVL2" ]; then
    echo -e "${GREEN}PASS: recursive flag with no output flag.${NC}"
else
    echo -e "${RED}FAIL: recursive flag with no ouput flag.${NC}"
    cleanUp
    exit 1
fi

# --- directory w/ output flag ---
cleanUp
setUp
$BINARY -r -o "$OUTPUT_DIR" "$INPUT_DIR"
if [ -f "$OUTPUT_FLAG_LVL1" ] && [ -f "$OUTPUT_FLAG_LVL2" ]; then
    echo -e "${GREEN}PASS: recursive flag with output flag.${NC}"
else
    echo -e "${RED}FAIL: recursive flag with ouput flag.${NC}"
    cleanUp
    exit 1
fi

echo -e "${GREEN}PASS: output test${NC}"
cleanUp
