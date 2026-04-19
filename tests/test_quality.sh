#!/usr/bin/env sh

INPUT="./tests/fixtures/KaiRyallOtajpeg.jpeg"
LOW_Q="./tests/fixtures/outputs/low_q.webp"
HIGH_Q="./tests/fixtures/outputs/high_q.webp"

./bin/splat "$INPUT" -o "$LOW_Q" -q 10
./bin/splat "$INPUT" -o "$HIGH_Q" -q 90

LOW_SIZE=$(stat -c%s "$LOW_Q")
HIGH_SIZE=$(stat -c%s "$HIGH_Q")

if [ "$HIGH_SIZE" -gt "$LOW_SIZE" ]; then
    echo "PASS: quality flag works (low=$LOW_SIZE, high=$HIGH_SIZE)"
else
    echo "FAIL: quality flag did not work (low=$LOW_SIZE, high=$HIGH_SIZE)"
fi

rm -f "$LOW_Q" "$HIGH_Q"
