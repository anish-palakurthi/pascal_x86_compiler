import difflib
import os

def compare_files(output_dir, sample_dir, result_file):
    with open(result_file, 'w') as outfile:
        # Handle the specific files pasrec.output and pasrec.sample
        compare_and_write_diff(outfile, output_dir, sample_dir, 'pasrec', 'pasrec')

        # Loop through the range of file numbers
        for i in range(16):  # Assuming it goes from 00 to 15
            num = f'{i:02}'  # Format the number with leading zeros
            compare_and_write_diff(outfile, output_dir, sample_dir, f'test{num}', f'test{num}')

def compare_and_write_diff(outfile, output_dir, sample_dir, output_prefix, sample_prefix):
    output_path = os.path.join(output_dir, f'{output_prefix}.output')
    sample_path = os.path.join(sample_dir, f'{sample_prefix}.sample')
    
    # Check if both files exist
    if os.path.exists(output_path) and os.path.exists(sample_path):
        # Read the contents of each file
        with open(output_path, 'r') as file1, open(sample_path, 'r') as file2:
            output_content = file1.readlines()
            sample_content = file2.readlines()

            # Generate the diff
            diff = difflib.unified_diff(
                output_content, sample_content,
                fromfile='output', tofile='sample',
                lineterm=''
            )

            # Write the header for the test case
            outfile.write(f'\n\n--- {output_prefix} Comparison ---\n')
            # Write diffs to the output file
            outfile.writelines(diff)
    else:
        outfile.write(f'\n\n--- {output_prefix} Comparison ---\n')
        outfile.write('One or both files are missing.\n')

# Specify the directories and output file
output_dir = '/u/anishp/compilers/proj_2,3/outputs'
sample_dir = '/u/anishp/compilers/proj_2,3/samples'
result_file = 'diff_result.txt'

compare_files(output_dir, sample_dir, result_file)
