# C Text Editor (Word-Based) with Undo/Redo

## Overview
This project is a **menu-driven C program** that loads a text from a file, stores it as an array of words, and lets you:
- **Insert** new words/sentences
- **Remove** words/sentences
- Perform **Undo** and **Redo**
- Save the updated text to an output file

Undo/Redo is implemented using **two stacks** (Undo stack and Redo stack). Insert/Delete operations are tracked as actions so they can be reversed later.

---

## Features (Program Menu)
1. Load the input file  
2. Print the loaded text  
3. Insert strings to the text  
4. Remove strings from the text  
5. Perform Undo operation  
6. Perform Redo operation  
7. Print the Undo and the Redo stack  
8. Save the updated text to the output file  
9. Print the updated text  
10. Exit  

---

## Data Structures
- **Undo Stack**: stores actions (word, operation type, and position info)
- **Redo Stack**: stores undone actions so they can be redone
- **Queue**: used to process multi-word sentences (split input sentence into words and apply them in order)

---

## Input / Output Files
### Input file
By default, the program reads from:
- `read.txt`

The file should contain normal text (words separated by spaces/newlines).  
The program loads up to **1000 words**.

### Output file
When you choose **Save**, the program writes to:
- `output.txt`

---

## How Insert Works
- You enter a **word/sentence** to insert.
- Then you choose **after which existing word** to insert it.
- If the chosen word appears multiple times, the program asks which occurrence (ranking) to use.
- Press **Enter** at the “after which word” prompt to insert at the **beginning**.

---

## How Remove Works
- You enter a **word/sentence** to delete.
- The program deletes each word (one by one) if it exists in the current text.

---

## How Undo / Redo Works
- **Undo** reverses the last insert/remove operation.
- **Redo** reapplies the last undone operation.
- New edits after an undo may invalidate the redo history (common editor behavior).

---

## Compile & Run

### Windows (MinGW / gcc)
```bash
gcc Project2.c -o Project2
Project2.exe
```

### Linux / macOS
```bash
gcc Project2.c -o Project2
./Project2
```

Make sure `read.txt` is in the same folder as the executable.

---

## Files
- `Project2.c` — main source code
- `read.txt` — input text file (provide your own)
- `output.txt` — generated output file (created/overwritten)

---

## Notes
- `output.txt` is generated automatically; you may choose **not** to upload it to GitHub.
- If you want a sample input, include a small `read.txt` in the repo.

---

## Author
- Aws Hammad (1221697)
