# File Sync Utility

## Topic
**Directory Synchronization and Process Management**

## Description
Intelligent directory sync tool that copies only new or modified files, preserving the most recent versions.

**How it works:**
- Scans source directory
- Compares files using `diff`
- Checks timestamps with `stat()`
- Updates only if source is newer

## Key Concepts
- **Directory Operations**: `opendir()`, `readdir()`, `closedir()`
- **Process Management**: `fork()`, `exec()`, `wait()`
- **File Comparison**: `diff` via child process
- **File Metadata**: `stat()` for timestamp comparison

## How to Run

### Compile
```bash
gcc -o file_sync file_sync.c
```

### Hot To Run (*This would only work on Linux*)
```bash
./file_sync source_directory destination_directory
```

**Requirements:** Linux/WSL, source must exist, destination created automatically

## Example Run

### First Run (New Files)
```bash
./file_sync example_src_dir destination_directory
```

**Output:**
```
Created destination directory 'destination_directory'.
New file found: example1.pgn
New file found: example2.pgn
New file found: example3.pgn
```

### Check It After Modifying File
```bash
# Edit a1/capmemel24_4.pgn
./file_sync example_src_dir destination_directory
```

**Output:**
```
File example1.pgn is newer in source. Updating...
File example2 .pgn is identical. Skipping...
File example3.pgn is identical. Skipping...
```

## How It Works

1. **Validation**: Check source exists, create destination if needed
2. **Scan**: Read all regular files from source
3. **For Each File**:
   - **New** → Copy to destination
   - **Exists** → Compare with `diff`
   - **Different** → Check timestamps, update if source newer
   - **Identical** → Skip

## Why This Approach?

- Only copies when necessary (efficient)
- Preserves newer destination files
- Demonstrates process management (`fork`/`exec`/`wait`)

## System Calls
- `opendir()`, `readdir()`, `closedir()` - Directory traversal
- `fork()`, `exec()`, `wait()` - Process management
- `stat()` - File metadata/timestamps
- `mkdir()` - Create directories
