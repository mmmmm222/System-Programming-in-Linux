# Linux Utilities: `zcat`, `zmv`, `zcp`, `zpwd` and `zecho`

#### This document provides an overview of the `zcat`, `zmv`, `zcp`, `zpwd` and `zecho` utilities in Linux, including their purpose, usage, and examples.

---

## 1. `zcat` -  Display Files

### Purpose:
The `zcat` command is used to display the contents of a file.

### Usage:
```bash
gcc zcat.c -o zcat.exe
./zcat.exe [FILE]...
```
---
---

## 2. `zmv` - Move or Rename Files

### Purpose:
The `zmv` command is used to move or rename files.

### Usage:
```bash
gcc zmv.c -o zmv.exe
./zmv.exe  [SOURCE] [DEST]
```
**Examples:**

#### Move a file to another directory:
```bash
./zmv.exe file.txt /path/to/destination/
```

#### Rename a file:
```bash
./zmv.exe oldname.txt newname.txt
```
#### Move and rename a file:
```bash
./zmv file.txt /path/to/destination/newname.txt
```
---
---

## 3. `zcp` - Copy Files 
### Purpose:
The `zcp` command is used to copy files.

### Usage:
```bash
gcc zcp.c -o zcp.exe
./zcp [SOURCE] [DEST]
```
**Examples:**

#### Copy a file to another directory:

```bash
./zcp file.txt /path/to/destination/
```

#### Copy and rename a file:
```bash
./zcp file.txt /path/to/destination/newname.txt
```

#### Make a Copy of The File With Another Name In The Same Directory:
```bash
./zcp.exe oldname.txt newname.txt
```
---
---

## 4. `zpwd` - Print Working Directory
### Purpose:
The pwd command prints the absolute path of the current working directory.

### Usage:
```bash
gcc zpwd.c -o zpwd.exe
./zpwd
```
---
---
## 5. `zecho` -  Print The Enterd text

### Purpose:
The `zecho` command is used to display a line of text or a string passed as an argument.

### Usage:
```bash
gcc zecho.c -o zecho.exe
./zecho.exe [text]
```
---
---

## Summary of Commands

| **Command Example**      | **Purpose**                                  |**Usage Example**
| -----------------------  | -------------------------------------------- | ---------------------------------------- 
| `zcat`                   | Display file contents                        |`./zcat file.txt`                            |
| `zmv`                    | Move or rename files                         | `./zmv file.txt /path/to/destination/`      |
| `zcp`                    | Copy files                                   | `./zcp file.txt /path/to/destination/`      |
| `zpwd`                   | Print the current working directory          | `./zpwd`                                    |
| `zecho`                  | display a line of text                       | `./zeco`                                    |




