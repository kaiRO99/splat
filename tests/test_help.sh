#!/usr/bin/env sh
# tests/test_utils.sh
# @brief Tests the command line ouput from utility functions.

BINARY="./bin/splat"

OUTPUT=$($BINARY -h 2>&1) # checks stdout and stderr
EXIT_CODE=$?

# check it prints the use (help flag)
# Only checks first couple lines
if echo "$OUTPUT" | grep -q "Convert .ppm, .png, .jpeg and .jpg image files to .webp."; then
    echo "PASS: help flag printed usage"
else
    echo "FAIL: help flag did not print usage"
    echo "Got: $OUTPUT"
    exit 1
fi

# check exit code (should be 0)
if [ "$EXIT_CODE" -eq 0 ]; then
    echo "PASS: help flag retuns zero exit code"
else
    echo "FAIL: expected zero exit code, got $EXIT_CODE"
    exit 1
fi

echo "PASS: help flag test"
