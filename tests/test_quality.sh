#!/usr/bin/env sh
# tests/test_quality.sh
# @brief tests the force flag for file and dir
# @author Kai Ryall Ota
# @date April 2026

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

INPUT="./tests/fixtures/testjpeg.jpeg"
LOW_Q="./tests/fixtures/outputs/low_q.webp"
HIGH_Q="./tests/fixtures/outputs/high_q.webp"

./bin/splat "$INPUT" -o "$LOW_Q" -q 10
./bin/splat "$INPUT" -o "$HIGH_Q" -q 90

LOW_SIZE=$(stat -c%s "$LOW_Q")
HIGH_SIZE=$(stat -c%s "$HIGH_Q")

if [ "$HIGH_SIZE" -gt "$LOW_SIZE" ]; then
    echo -e "${GREEN}PASS: quality flag works (low=$LOW_SIZE, high=$HIGH_SIZE)${NC}"
else
    echo -e "${RED}FAIL: quality flag did not work (low=$LOW_SIZE, high=$HIGH_SIZE)${NC}"
fi

rm -f "$LOW_Q" "$HIGH_Q"
