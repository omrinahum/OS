# Chess Simulator Utility

## Topic
**PGN Parsing and Terminal-Based Game Navigation**

## Description
Interactive chess game viewer that loads PGN files and allows step-by-step game navigation in the terminal. Two implementations: Python (robust) and Bash (educational).

**How it works:**
- Parse PGN headers and moves
- Convert moves to UCI format
- Display ASCII board with interactive controls
- Navigate through game moves

## Key Concepts
- **PGN Parsing**: `chess.pgn.read_game()` - Extract headers and moves
- **Move Formats**: SAN → UCI conversion and mainline traversal
- **Board State**: Maintain and update chess position
- **Terminal I/O**: Interactive input handling and ASCII rendering
- **Scripting vs Library**: Shell parsing vs library usage

## How to Run

### Install
```bash
pip3 install --user python-chess
```

### Run
```bash
# Python viewer (recommended)
python3 chess_sim.py capmemel24_1.pgn

# Bash viewer (Git Bash or WSL)
./chess_sim.sh capmemel24_1.pgn
```

**Requirements:**
- Python 3 with `python-chess` package
- Bash environment for shell viewer

### Test
```bash
bash tester/tester.sh
```

## Example Run

### Command
```bash
python3 chess_sim.py capmemel24_1.pgn
```

### Output
```
[Event "57th Capablanca Mem"]
[Site "Havana CUB"]
[Date "2024.05.03"]
[White "Andersen, Mad"]
[Black "Quesada Perez, Luis Ernesto"]

Move 0/40
  a b c d e f g h
8 r n b q k b n r 8
7 p p p p p p p p 7
6 . . . . . . . . 6
5 . . . . . . . . 5
4 . . . . . . . . 4
3 . . . . . . . . 3
2 P P P P P P P P 2
1 R N B Q K B N R 1
  a b c d e f g h

Press 'd' to move forward, 'a' to move back, 'w' to start, 's' to end, 'q' to quit:
```

### Result
Interactive terminal viewer - no files created, output printed to terminal.

## How It Works

1. **Validation**:
   - Check PGN file exists and is readable

2. **Parsing**:
   - Read PGN headers and moves
   - Convert moves to UCI format

3. **Playback**:
   - Apply moves sequentially to board
   - Update ASCII display on user commands
   - Navigate: forward (d), back (a), start (w), end (s), quit (q)

## Why This Approach?

- **Python**: Uses `python-chess` library for robust parsing and move validation
- **Bash**: Educational implementation showing low-level string parsing and board state management

## Files
- `chess_sim.py` - Python interactive viewer
- `chess_sim.sh` - Bash educational viewer
- `parse_moves.py` - UCI conversion helper

## Libraries
- `python-chess` - PGN parsing and board API
- Standard shell utilities: `sed`, `read`, `echo`

