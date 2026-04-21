#!/usr/bin/env sh
# tests/test_utils.sh
# @brief Tests the command line ouput from utility functions.
# @author Kai Ryall Ota
# @date April 2026


# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

BINARY="./bin/splat"

OUTPUT=$($BINARY -h 2>&1) # checks stdout and stderr
EXIT_CODE=$?

# check it prints the use (help flag)
# Only checks first couple lines
if echo "$OUTPUT" | grep -q "Convert .ppm, .png, .jpeg and .jpg image files to .webp."; then
    echo -e "${GREEN}PASS: help flag printed usage${NC}"
else
    echo -e "${RED}FAIL: help flag did not print usage${NC}"
    echo "Got: $OUTPUT"
    exit 1
fi

# check exit code (should be 0)
if [ "$EXIT_CODE" -eq 0 ]; then
    echo -e "${GREEN}PASS: help flag retuns zero exit code${NC}"
else
    echo -e "${RED}FAIL: expected zero exit code, got $EXIT_CODE ${NC}"
    exit 1
fi

echo -e "${GREEN}PASS: help flag test${NC}"
