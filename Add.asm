// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/06/add/Add.asm

// Computes R0 = 2 + 3  (R0 refers to RAM[0])

@20 // test
D+1=A //trie
@3
D=D+A
@0
MD=D-A ; JMP
@20 // test
D+1=A //trie
