#!/usr/bin/env sh
# tests/test_force.sh
# @brief tests the force flag for file and dir

BINARY="./bin/splat"
INPUT_IMG="./tests/fixtures/KaiRyallOtajpg.jpg"
INPUT_DIR="./tests/fixtures"
OUTPUT_FLAG_IMG="./tests/fixtures/outputs/force_test.webp"
OUTPUT_IMG="./tests/fixtures/KaiRyallOtajpg.webp"
OUTPUT_DIR="./tests/fixtures/outputs"
EXPECTED_IMG="./tests/fixtures/expected/force_test.webp"

cleanUp(){
    rm -f "$OUTPUT_IMG"
    rm -rf "$OUTPUT_DIR"
}

setUp(){
    mkdir -p ./tests/fixtures/outputs # create output dir
    #copy expected outputs
    cp "$EXPECTED_IMG" ./tests/fixtures
    cp "$EXPECTED_IMG" ./tests/fixtures/outputs

    #rename force_test.webp to KaiRyallOtajpg.webp
    mv ./tests/fixtures/force_test.webp ./tests/fixtures/KaiRyallOtajpg.webp
}


#run tests
# --- single image ---
cleanUp
setUp
$BINARY -f "$INPUT_IMG"

# get sizes
EXPECTED_SIZE=$(stat -c%s "$EXPECTED_IMG")
OUT_SIZE=$(stat -c%s "$OUTPUT_IMG")

# --- check outputs for image ---
# if size of KaiRyallOtajpg.webp changes, it worked
if [ "$OUT_SIZE" -ne "$EXPECTED_SIZE" ]; then
    echo "PASS: force flag replaced the image."
else
    echo "FAIL: force flag did not replace the image."
    cleanUp
    exit 1
fi

# --- w/output flag ---
cleanUp
setUp
$BINARY -f -o "$OUTPUT_FLAG_IMG" "$INPUT_IMG"
OUT_SIZE=$(stat -c%s "$OUTPUT_FLAG_IMG")
# --- check outputs for image ---
# if size of KaiRyallOtajpg.webp changes, it worked
if [ "$OUT_SIZE" -ne "$EXPECTED_SIZE" ]; then
    echo "PASS: force flag replaced the image."
else
    echo "FAIL: force flag did not replace the image."
    cleanUp
    exit 1
fi

# --- w/dir as input ---
cleanUp
setUp
$BINARY -f "$INPUT_DIR"
OUT_SIZE=$(stat -c%s "$OUTPUT_IMG")
# --- check outputs for image ---
# if size of KaiRyallOtajpg.webp changes, it worked
if [ "$OUT_SIZE" -ne "$EXPECTED_SIZE" ]; then
    echo "PASS: force flag replaced the image."
else
    echo "FAIL: force flag did not replace the image."
    cleanUp
    exit 1
fi

echo "PASS: output test"
cleanUp
