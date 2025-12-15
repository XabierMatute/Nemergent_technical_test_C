#! /usr/bin/env python3

# This test script could be far more complete checking more exit errors and of course checking the output
# It could also check is the correct number of threads are created(if possible)
# It could also use valgrind to check for memory leaks, segmentation faults or data races

import subprocess
import sys

ERROR_ARGC = 0x10
ERROR_ARGV1 = 0x11
ERROR_ARGV2 = 0x12

def test_exit_code(args, expected_code):
    #TODO: redirect stdout and stderr to devnull
    result = subprocess.run(args)
    if result.returncode != expected_code:
        print(f"❌Test failed for args {args}: expected exit code {expected_code}, got {result.returncode}")
    else:
        print(f"✅Test passed for args {args}")

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 test.py <executable>")
        return 1

    executable = sys.argv[1]

    # Test cases
    test_exit_code([executable], ERROR_ARGC)
    test_exit_code([executable, "invalid_arg"], ERROR_ARGC)
    test_exit_code([executable, "42", "invalid_arg"], ERROR_ARGV2)
    test_exit_code([executable, "invalid_arg", "invalid_arg"], ERROR_ARGV1)
    test_exit_code([executable, "42", "24"], 0)

    return 0

if __name__ == "__main__":
    main()