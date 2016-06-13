Nes-Extract
======

Nes-Extract is a command line  application for extract PRG & CHR Nes/Famicom rom.
Result can be burned directly into an EPROM for real hardware test.


The features I have added are:

* Detect correct input file ( extract only if files have NES/FC Header).
* Create separate files for PRG & CHR or rewrite it if already exist..

Usage
-----

```
./NesExtract rom.nes
```

How it works
------------

* First read the header file and collect PRG and CHR size.
* Then malloc two buffer with collected size and send data inside.
* Finally write the result files with buffer content. 

![alt tag](https://github.com/X-death25/Nes-Extract/blob/master/Nes-Extract.png)
