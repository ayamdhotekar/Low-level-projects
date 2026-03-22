# macOS File System Watcher (kqueue)

A simple file watcher built in C using macOS kqueue.

## Build
make

## Run
./watcher <file_or_directory>

## Features
- Detect file modifications
- Detect deletions
- Detect renames
- Uses native macOS event system (kqueue)
