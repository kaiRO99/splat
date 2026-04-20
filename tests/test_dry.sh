#!/usr/bin/env sh
# tests/test_dry.sh
# @brief Tests the command line ouput from the dry run flag.
# @author Kai Ryall Ota
# @date April 2026

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

BINARY="./bin/splat"
INPUT_DIR="./tests/fixtures"

OUTPUT=$($BINARY -d $INPUT_DIR 2>&1) # checks stdout and stderr
EXIT_CODE=$? # exit code from last command

# check it prints the use (help flag)
# Only checks first couple lines
if echo "$OUTPUT" | grep -qF "[DRY RUN] Convert: ./tests/fixtures/KaiRyallOtajpg.jpg -> ./tests/fixtures/KaiRyallOtajpg.webp"; then
    echo "PASS: dry-run flag printed dry-run"
else
    echo "FAIL: dry-run flag did not print expected"
    echo "Got: $OUTPUT"
    exit 1
fi

# check exit code (should be 0)
if [ "$EXIT_CODE" -eq 0 ]; then
    echo "PASS: Dry-run flag retuns zero exit code"
else
    echo "FAIL: expected zero exit code, got $EXIT_CODE"
    exit 1
fi

echo -e "${GREEN}PASS: dry-run flag test${NC}"
