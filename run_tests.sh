#!/bin/bash

binary_path="cmake-build-debug-wsl/JSON_Parser_CPP"

build() {
    cmake -S . -B cmake-build-debug-wsl
    cmake --build cmake-build-debug-wsl
}

test_step_one() {
    local passed=0
    local failed=0

    for file in tests/step1/*json; do
        ./$binary_path $file
        local actual=$?

        local expected=0

        if [[ $file == *"invalid"* ]]; then
            expected=1
        fi

        if [[ $actual -eq $expected ]]; then
            ((passed++))
            echo "$file test passed"
        else
            ((failed++))
            echo "$file test failed"
        fi
    done

    echo "Step One Results:"
    echo "Failed: $failed"
    echo "Passed: $passed"

}

build
test_step_one
