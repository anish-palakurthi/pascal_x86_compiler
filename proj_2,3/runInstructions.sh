#!/bin/bash


# Variables
directory_path="samples"
new_file="temporary_code.s"
driver_file="driver.c"  # Ensure this points to your driver C file

# Loop through each .output file in the directory
for original_file in "$directory_path"/*.{output,sample}; do    echo "Processing $original_file..."

    # Extract the necessary part of the file and write it to the temporary file
    awk '/\.file\s+"foo"/,0' "$original_file" > "$new_file"

    # Compile with the driver and run
    cc "$driver_file" "$new_file" -lm
    ./a.out

    echo "Finished processing $original_file"
done
