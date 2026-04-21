#!/usr/bin/env sh
# tests/test_force.sh
# @brief tests the force flag for file and dir
# @author Kai Ryall Ota
# @date April 2026

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

BINARY="./bin/splat"
INPUT_IMG="./tests/fixtures/testjpg.jpg"
INPUT_DIR="./tests/fixtures"
OUTPUT_FLAG_IMG="./tests/fixtures/outputs/test_force.webp"
OUTPUT_IMG="./tests/fixtures/testjpg.webp"
OUTPUT_DIR="./tests/fixtures/outputs"
EXPECTED_IMG="./tests/fixtures/expected/test_force.webp"

cleanUp(){
    rm -f "$OUTPUT_IMG"
    rm -rf "$OUTPUT_DIR"
} # cleanup()

setUp(){
    mkdir -p ./tests/fixtures/outputs # create output dir

    # grnerate expected image
    #copy expected outputs
    cp "$EXPECTED_IMG" ./tests/fixtures
    cp "$EXPECTED_IMG" ./tests/fixtures/outputs

    #rename test_force.webp to testjpg.webp
    mv ./tests/fixtures/test_force.webp ./tests/fixtures/testjpg.webp
} # setUp()

#run tests
# --- single image ---
cleanUp
setUp
$BINARY -f "$INPUT_IMG"

# get sizes
EXPECTED_SIZE=$(stat -c%s "$EXPECTED_IMG")
OUT_SIZE=$(stat -c%s "$OUTPUT_IMG")

# --- check outputs for image ---
# if size of testjpg.webp changes, it worked
if [ "$OUT_SIZE" -ne "$EXPECTED_SIZE" ]; then
    echo -e "${GREEN}PASS: force flag replaced the image.${NC}"
else
    echo -e "${RED}FAIL: force flag did not replace the image.${NC}"
    cleanUp
    exit 1
fi

# --- w/output flag ---
cleanUp
setUp
$BINARY -f -o "$OUTPUT_FLAG_IMG" "$INPUT_IMG"
OUT_SIZE=$(stat -c%s "$OUTPUT_FLAG_IMG")
# --- check outputs for image ---
# if size of testjpg.webp changes, it worked
if [ "$OUT_SIZE" -ne "$EXPECTED_SIZE" ]; then
    echo -e "${GREEN}PASS: force flag replaced the image.${NC}"
else
    echo -e "${RED}FAIL: force flag did not replace the image.${NC}"
    cleanUp
    exit 1
fi

# --- w/dir as input ---
cleanUp
setUp
$BINARY -f "$INPUT_DIR"
OUT_SIZE=$(stat -c%s "$OUTPUT_IMG")
# --- check outputs for image ---
# if size of testjpg.webp changes, it worked
if [ "$OUT_SIZE" -ne "$EXPECTED_SIZE" ]; then
    echo -e "${GREEN}PASS: force flag replaced the image.${NC}"
else
    echo -e "${RED}FAIL: force flag did not replace the image.${NC}"
    cleanUp
    exit 1
fi

echo -e "${GREEN}PASS: force test${NC}"
cleanUp
