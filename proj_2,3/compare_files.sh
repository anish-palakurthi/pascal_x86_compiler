#!/bin/bash

# Directories
dir1="outputs"
dir2="samples"

# Extensions
ext1=".output"
ext2=".sample"

# Loop through files in the first directory
for file1 in "$dir1"/*"$ext1"; do
    # Construct the filename for the second directory
    base_name=$(basename "$file1" "$ext1")
    file2="$dir2/$base_name$ext2"

    # Check if the corresponding file exists in the second directory
    if [[ -e "$file2" ]]; then
        # Output the file names
        echo "Comparing $file1 and $file2 (ignoring specific patterns):"
        
        # Use sed to filter out memory addresses and version years after "CS 375 Compiler"
        # and grep to exclude lines with "Beginning of Generated Code"
        diff <(sed -E 's/9[0-9]{10,}//g;s/(CS 375 Compiler - Spring )[0-9]{4}/\1/g' "$file1") \
             <(sed -E 's/9[0-9]{10,}//g;s/(CS 375 Compiler - Spring )[0-9]{4}/\1/g' "$file2")
    else
        echo "No corresponding file for $file1 in $dir2"
    fi
done
