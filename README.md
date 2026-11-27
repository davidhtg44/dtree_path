# dtree
NO AI

A C-based CLI utility that displays the directory tree using ANSI colors and Unicode lines.
Works on MacOs and Linux (requires `DT_DIR` support in `dirent.h`).

## Fast setup:

```bash
curl -fsSL [https://raw.githubusercontent.com/davidhtg44/dtree/main/main.c](https://raw.githubusercontent.com/davidhtg44/dtree/main/main.c) -o /tmp/dtree.c && \
gcc -Wall /tmp/dtree.c -o /usr/local/bin/dtree && \
rm /tmp/dtree.c
```
# How to use it:
dtree
dtree /dir

# Example:
```text
dir1
│  ├──file1.txt
│  └──dir1.1
│     ├──file2.txt
│     └──file3.txt
fileA.txt
fileB.txt
```
