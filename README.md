MonkeyDo
======

![MonkeySee Logo](http://iuliux.ro/monkeysee/images/monkeydo-logo.png)

## What is it?
A program that runs on a robo-car controlled by an `ATmega16` microcontorller. It reads `.mkd` (MonKeyDo) format files from an SD/MMC card and interprets the commands in that file.  
This is an academic project. It's written in AVR-C.

## The whole
This project is the recorder part of a record-play system. This is the MonkeyDo part of the [MonkeySee](https://github.com/iuliux/MonkeySee/) - MonkeyDo project developed as an assignment project in the "Design with microprocessors" class at Polytechnic University of Bucharest.

## Input language:
An example of the format:

    (^) 1126
    (v) 321
    (>v) 1483
    (^) 214
    (<^) 860
    (<-) 33
    (-) 1522

More can be found on the <span class="mini-icon ">UTF+f024</span> [MonkeySee](https://github.com/iuliux/MonkeySee/) page.

## Using OpenSource tools:
* [Petit FAT File System](http://elm-chan.org/fsw/ff/00index_p.html)
