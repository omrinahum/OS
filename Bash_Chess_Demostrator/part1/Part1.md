# Part 1 — PGN splitter

Description
-----------
Splits a multi-game PGN file into one PGN file per chess game. Useful for preparing data for analysis or testing.

Concepts demonstrated
----------------------
- File I/O and streaming text processing
- Simple parsing (detecting game boundaries)
- Shell scripting and small automation utilities

What it does
------------
- Reads a source PGN file and writes each game to a separate file named like `capmemel24_1.pgn`, `capmemel24_2.pgn`, … inside a destination directory.
- Creates the destination directory if missing and prints progress messages.

How to run (*This would only work on Linux*)
----------

```bash
./split_pgn.sh capmemel24.pgn out
```



Output: an `out/` directory containing `capmemel24_*.pgn` files.


