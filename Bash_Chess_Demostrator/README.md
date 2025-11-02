# Chess Utilities

## Topic
**File Processing and Terminal-Based Applications**

## Description
Chess utilities demonstrating file I/O, text parsing, and interactive terminal applications. Includes PGN file splitting and an interactive game viewer.

---

## Part 1: PGN Splitter

### Description
Splits a multi-game PGN file into individual game files.

**How it works:**
- Reads source PGN, detects game boundaries
- Writes each game to separate file
- Creates output directory automatically

### Key Concepts
- **File I/O**: Stream processing
- **Text Parsing**: Game boundary detection
- **Shell Scripting**: Bash automation

### How to Run

```bash
./part1/split_pgn.sh capmemel24.pgn output_directory
```

**Requirements:** Linux/WSL/Git Bash, source PGN file must exist

### Example

```bash
./part1/split_pgn.sh capmemel24.pgn out
```

**Output:**
```
Creating directory: out
Created: out/capmemel24_1.pgn
Created: out/capmemel24_2.pgn
...
Split complete: 150 games
```

---

## Part 2: Chess Simulator

### Description
Interactive chess game viewer for step-by-step navigation. Python (robust) and Bash (educational) implementations.

**How it works:**
- Parse PGN headers and moves
- Convert to UCI format, display ASCII board
- Navigate with keyboard controls

### Key Concepts
- **PGN Parsing**: `chess.pgn.read_game()` - Extract headers/moves
- **Move Formats**: SAN → UCI conversion
- **Terminal I/O**: Interactive input and ASCII rendering

### How to Run

**Install:**
```bash
pip3 install --user python-chess
```

**Python (Recommended):**
```bash
python3 part2/chess_sim.py part2/capmemel24_1.pgn
```

**Bash (Educational):**
```bash
./part2/chess_sim.sh part2/capmemel24_1.pgn
```

### Example

```bash
python3 part2/chess_sim.py part2/capmemel24_1.pgn
```

**Output:**
```
[Event "57th Capablanca Mem"]
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

'd' forward | 'a' back | 'w' start | 's' end | 'q' quit
```

**Controls:** `d` forward, `a` back, `w` start, `s` end, `q` quit

---

## Combined Workflow

```bash
# Split PGN file
./part1/split_pgn.sh capmemel24.pgn games

# View individual game
python3 part2/chess_sim.py games/capmemel24_1.pgn
```

## Tools
- `python-chess` - PGN parsing and board API
- Bash utilities: `sed`, `read`, `echo`
