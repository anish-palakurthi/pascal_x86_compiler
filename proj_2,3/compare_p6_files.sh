#!/bin/bash

# Directories
dir1="outputs"
dir2="samples"

# Extensions
ext1=".output"
ext2=".sample"

# Function to preprocess files
preprocess_file() {
    # Use awk for complex pattern recognition and manipulation
    awk '{
        # Replace long numbers that look like memory addresses
        gsub(/9[0-9]{10,}/, "");
        # Remove leading and trailing whitespace
        gsub(/^[ \t]+|[ \t]+$/, "");
        # Print lines, skipping processing if they contain "Beginning of Generated Code" or are empty
        if ($0 !~ /Beginning of Generated Code/ && $0 != "") {
            print;
        } else {
            # Handle special case where code and "Beginning of Generated Code" are on the same line
            sub(/#.*/, "");  # Remove comments starting with #
            if ($0 != "") print;  # Only print if the line is not empty after removal
        }
    }' "$1" | sed -E 's/(CS 375 Compiler - )[A-Za-z]+ [0-9]{4}/\1XXXX/g' 
}

# Compare files
compare_files() {
    local file1="$1"
    local file2="$2"

    echo "Comparing $file1 and $file2 (ignoring memory addresses, specific strings, and handling code splits):"
    diff <(preprocess_file "$file1") <(preprocess_file "$file2")
}

# Main loop
# for file1 in "$dir1"/*"$ext1"; do
#     base_name=$(basename "$file1" "$ext1")
#     file2="$dir2/$base_name$ext2"
#     if [[ -e "$file2" ]]; then
#         compare_files "$file1" "$file2"
#     else
#         echo "No corresponding file for $file1 in $dir2"
    compare_files "outputs/test22.output" "samples/test22.sample"
    # fi
# done | tee currentshOut.txt
