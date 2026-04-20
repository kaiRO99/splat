#!/usr/bin/env sh
# tests/test_recursive.sh
# @brief tests the recursive flag

BINARY="./bin/splat"
INPUT_DIR="./tests/fixtures"
OUTPUT_LVL1="./tests/fixtures/KaiRyallOtajpeg.webp"
OUTPUT_LVL2="./tests/fixtures/lvl2/KaiRyallOtajpg.webp"
OUTPUT_FLAG_LVL1="./tests/fixtures/outputs/KaiRyallOtajpeg.webp"
OUTPUT_FLAG_LVL2="./tests/fixtures/outputs/lvl2/KaiRyallOtajpg.webp"
OUTPUT_DIR="./tests/fixtures/outputs"

cleanUp(){
    rm -rf "$OUTPUT_DIR"
    rm -f "$INPUT_DIR/*.webp"
    rm -rf "$INPUT_DIR/lvl2"
}

setUp(){
    mkdir -p ./tests/fixtures/outputs # create output dir
    mkdir -p ./tests/fixtures/lvl2
    #copy expected outputs
    cp ./tests/fixtures/KaiRyallOtajpg.jpg ./tests/fixtures/lvl2
}

#run tests
# --- directory ---
echo "pre test 1"
cleanUp
echo "after cleanup"
setUp
echo "after setup"
$BINARY -r "$INPUT_DIR"
echo "running test 1"
if [ -f "$OUTPUT_LVL1" ] && [ -f "$OUTPUT_LVL2" ]; then
    echo "PASS: recursive flag with no output flag."
else
    echo "FAIL: recursive flag with no ouput flag."
    cleanUp
    exit 1
fi

# --- directory w/ output flag ---
cleanUp
setUp
$BINARY -r -o "$OUTPUT_DIR" "$INPUT_DIR"
if [ -f "$OUTPUT_FLAG_LVL1" ] && [ -f "$OUTPUT_FLAG_LVL2" ]; then
    echo "PASS: recursive flag with output flag."
else
    echo "FAIL: recursive flag with ouput flag."
    cleanUp
    exit 1
fi

echo "PASS: output test"
cleanUp
