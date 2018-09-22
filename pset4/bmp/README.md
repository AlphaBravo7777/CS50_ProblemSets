Description of files
===
    
    
whodunit.c
---

This program removes red and black pixels and makes the file klue.bmp usable for viewing

### Build

Run commands in console:

    $ cd pset4/bmp
    $ make whodunit

### Run

Run commands in console:

    $ cd pset4/bmp
    $ ./whodunit clue.bmp verdict.bmp


resize.c
---

This program enlarges the original image a specified number of times and saves it to a new file

### Build

Run commands in console:

    $ cd pset4/bmp
    $ make resize

### Run

Run commands in console:

    $ cd pset4/bmp
    $ ./resize 4 smiley.bmp resize.bmp


metadatabmp.c
---

This is an auxiliary program for viewing metadata from bmp files

### Build

Run commands in console:

    $ cd pset4/bmp
    $ make metadatabmp

### Run

Run commands in console:

    $ cd pset4/bmp
    $ ./metadatabmp clue.bmp


Other commands (resize.c for example)
---

### Test code

Run commands in console:

    $ cd pset4/bmp
    $ check50 cs50/2017/x/resize
    
### Submit code

Run commands in console:

    $ cd pset4/bmp
    $ submit50 cs50/2017/x/resize
