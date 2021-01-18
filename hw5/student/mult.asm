;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Iterative Multiplication
;;=============================================================
;;Name: Shaotong Sun
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;a = (argument 1);
;;b = (argument 2);
;;ANSWER = 0;
;;while (b > 0) {
;;  ANSWER = ANSWER + a;
;;  b--;
;; }
;; note: when the while-loop ends, the value stored at ANSWER is a times b.

.orig x3000

    ;;YOUR CODE GOES HERE
    LD R1,A
    LD R2,B
    AND R3,R3,#0
 W  ADD R2,R2,#0
    BRNZ EW
    ADD R3,R3,R1
    ADD R2,R2,#-1
    BRNZP W
EW  ST R3,ANSWER
	HALT

A   .fill 5
B   .fill 15

ANSWER .blkw 1

.end
