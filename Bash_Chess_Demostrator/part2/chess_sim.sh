    #!/bin/bash

    board=(
    r n b q k b n r  
    p p p p p p p p  
    . . . . . . . .  
    . . . . . . . .  
    . . . . . . . .  
    . . . . . . . .  
    P P P P P P P P  
    R N B Q K B N R  
    )

    current_move_index=0

    argument_verification(){
        local file_path="$1"

        if [[ $# -ne 1 ]]; then
            exit 0
        fi

        if [[ ! -f "$file_path" ]]; then
            echo "File does not exist: $file_path "
            exit 0
        fi
    }

    # Convert 2D coordinates to 1D array index
    index_calc() {
    local row=$1  
    local col=$2  
    echo $((row * 8 + col))
    }

    print_board() {
    echo "  a b c d e f g h"
    for row in {0..7}; do
        local left_col=$((8 - row))
        echo -n "$left_col "
        for col in {0..7}; do
        index=$(index_calc $row $col)
        echo -n "${board[$index]} "
        done
        echo "$left_col"
    done
    echo "  a b c d e f g h"
    }

    # Extract and display game metadata from PGN file
    print_metadata(){
        local file_path="$1"
        echo "Metadata from PGN file:"
        while IFS= read -r line || [[ -n "$line" ]]; do
        if [[ -z "$line" ]]; then
        break
        fi
        echo "$line"
        done < "$file_path"
        echo ""
    }

    # Extract moves section from PGN file
    extract_moves() {
    local file_path="$1"
    local metadata_ended=false
    local moves=""

    while IFS= read -r line || [[ -n "$line" ]]; do
        if [[ "$metadata_ended" = false ]]; then
        if [[ -z "$line" ]]; then
            metadata_ended=true
        fi
        else
        moves+="$line "
        fi
    done < "$file_path"

    echo "$moves"
    }


    # Handle user input and game navigation
    next_move(){
        local key="w"
        while true; do
            if [ "$key" = "d" ]; then
                if move_forward; then
                    echo "Move ${current_move_index}/${#moves_history[@]}"
                    print_board
                fi
            elif [ "$key" = "a" ]; then
                move_back
                echo "Move ${current_move_index}/${#moves_history[@]}"
                print_board
            elif [ "$key" = "w" ]; then
                current_move_index=0
                rebuild_board_until "$current_move_index"
                echo "Move ${current_move_index}/${#moves_history[@]}"
                print_board
            elif [ "$key" = "s" ]; then
                current_move_index=${#moves_history[@]}
                rebuild_board_until "$current_move_index"
                echo "Move ${current_move_index}/${#moves_history[@]}"
                print_board
            elif [ "$key" = "q" ]; then
                echo "Exiting."
                break
            else
                echo "Invalid key pressed: $key"
            fi
            echo "Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit:"
            read key
        done
    }

    move_back() {
        if ((current_move_index > 0)); then
            ((current_move_index--))
        rebuild_board_until "$current_move_index"
        fi
    }

    move_forward() {
        if (( current_move_index < ${#moves_history[@]} )); then
            ((current_move_index++))
            rebuild_board_until "$current_move_index"
            return 0 
        else
            echo "No more moves available."
            return 1  
        fi
    }

    move_on_board() {
        local move="$1"
        local start_col_letter="${move:0:1}"
        local start_row_number="${move:1:1}"
        local end_col_letter="${move:2:1}"
        local end_row_number="${move:3:1}"

        local start_col=$(file_to_col "$start_col_letter")
        local end_col=$(file_to_col "$end_col_letter")
        local start_row=$((8 - start_row_number))
        local end_row=$((8 - end_row_number))

        local from_index=$(index_calc "$start_row" "$start_col")
        local to_index=$(index_calc "$end_row" "$end_col")

        # Handle special moves before making the main move
        handle_special_moves "${board[$from_index]}" "$start_row" "$start_col" "$end_col" "$end_row" "$move" "$to_index"

        # Make the main move
        board[$to_index]="${board[$from_index]}"
        board[$from_index]="."
    }


    file_to_col() {
    local file="$1"
    if [[ $file == "a" ]]; then echo 0
    elif [[ $file == "b" ]]; then echo 1
    elif [[ $file == "c" ]]; then echo 2
    elif [[ $file == "d" ]]; then echo 3
    elif [[ $file == "e" ]]; then echo 4
    elif [[ $file == "f" ]]; then echo 5
    elif [[ $file == "g" ]]; then echo 6
    elif [[ $file == "h" ]]; then echo 7
    else echo "Invalid file" >&2; return 1
    fi
    }

    rebuild_board_until() {
    local target_index="$1"

    board=(
        r n b q k b n r
        p p p p p p p p
        . . . . . . . .
        . . . . . . . .
        . . . . . . . .
        . . . . . . . .
        P P P P P P P P
        R N B Q K B N R
    )

    local i=0
    while (( i < target_index )); do
        move_on_board "${moves_history[$i]}"
        ((i++))
    done
    }
   
    handle_special_moves() {
        local piece=$1
        local start_row=$2
        local start_col=$3
        local end_col=$4
        local move=$5

        # Castle handling
        if [[ $piece == "K" ]] || [[ $piece == "k" ]]; then
            # King moved two squares - it's a castle
            if [[ $end_col == $(($start_col + 2)) ]]; then
                # Move rook for kingside castle
                local rook_start=$(index_calc $start_row 7)
                local rook_end=$(index_calc $start_row 5)
                board[$rook_end]=${board[$rook_start]}
                board[$rook_start]="."
            fi
        fi
    }
   

    handle_special_moves() {
        local piece=$1
        local start_row=$2
        local start_col=$3
        local end_col=$4
        local end_row=$5
        local move=$6
        local to_index=$7

        # Castling (encastling)
        if [[ $piece =~ [Kk] ]] && [[ ${#move} == 4 ]]; then
            if [[ $move == "e1g1" ]] || [[ $move == "e8g8" ]]; then
                local rook_start=$(index_calc $start_row 7)
                local rook_end=$(index_calc $start_row 5)
                board[$rook_end]=${board[$rook_start]}
                board[$rook_start]="."
            fi
        fi

        # Pawn promotion
        if [[ $piece =~ [Pp] ]]; then
            if [[ $end_row == 0 ]] || [[ $end_row == 7 ]]; then
                if [[ $piece == "P" ]]; then
                    board[$to_index]="Q"  
                else
                    board[$to_index]="q"  
                fi
                return 1
            fi
        fi

        # En passant
        if [[ $piece =~ [Pp] ]] && (( start_col != end_col )) && [[ ${board[$to_index]} == "." ]]; then
            local captured_pawn=$(index_calc $start_row $end_col)
            board[$captured_pawn]="."
        fi

        return 0
    }


    argument_verification $@
    print_metadata $@
    pgn_moves=$(extract_moves "$1")
    moves_history_string=$(python3 parse_moves.py "$pgn_moves")
    read -ra moves_history <<< "$moves_history_string"
    next_move
    echo "End of game."

