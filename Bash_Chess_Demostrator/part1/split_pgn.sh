#!/bin/bash

argument_verification(){
    local file_path="$1"
    local destination_dir="$2"

    if [[ $# -ne 2 ]]; then
        echo "Usage: $0 <source_pgn_file> <destination_directory>"
        exit 0
    fi

    if [[ ! -f "$file_path" ]]; then
        echo "Error: File '$input_file' does not exist."
        exit 0
    fi

    if [[ ! -d "$destination_dir" ]]; then
        mkdir -p "$destination_dir"
        echo "Created directory '$destination_dir'."
    fi

    return 1;
}

copy_file_to_destination() {
    local file_path="$1"
    local destination_dir="$2"

    local block_num=0
    local png_num=1
    local temp_file="$destination_dir/capmemel24_$png_num.pgn"
    > "$temp_file"

    while IFS= read -r line || [[ -n "$line" ]]; do
        if [[ -z "$line" ]]; then
            echo "" >> "$temp_file"
            ((block_num++))
            if [[ $block_num -eq 2 ]]; then
                read -r next_line
                if [[ -z "$next_line" ]]; then
                    echo "Saved game to $destination_directory$temp_file"
                    break  # Exit if no more content
                fi

                echo "Saved game to $destination_directory$temp_file"
                ((png_num++))
                block_num=0
                temp_file="$destination_dir/capmemel24_$png_num.pgn"
                > "$temp_file"

                if [[ -n "$next_line" ]]; then
                    echo "$next_line" >> "$temp_file"
                fi
            fi
        else
            echo "$line" >> "$temp_file"
        fi
    done < "$file_path"

    echo "All games have been split and saved to $destination_dir."
}

argument_verification $@
copy_file_to_destination $@