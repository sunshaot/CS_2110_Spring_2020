;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Make elements of a Linked List into a string
;;=============================================================
;;Name:
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;length = LL.length;
;;curr = LL.head; //HINT: What can an LDI instruction be used for?
;;ANSWER = char[length]; //This character array will already be setup for you
;;i = 0;
;;while (curr != null) {
;;  ANSWER[i] = curr.value;
;;  curr = curr.next;
;;  i++;
;;}


.orig x3000

;; YOUR CODE GOES HERE
	LD R0,ANSWER;					R0: ANSWER
	LD R1,LL;						R1: LL
	ADD R2,R1,#1
	LDR R2,R2,#1;					R2: length
	AND R3,R3,#0;					R3: i = 0
	LDI R4,LL;						R4: current.head

W   ADD R4,R4,#0
	BRZ EW
	LDR R5,R4,#0
	ADD R6,R0,R3;					R6:ANSWER[i]
	LDR R5,R4,#1;					R5: curr.value
	STR R5,R6,#0
	LDR R4,R4,#0
	ADD R3,R3,#1
	BRNZP W
EW	ADD R6,R0,R3
	STR R4,R6,#0
	HALT

LL .fill x6000
ANSWER .fill x5000
.end

.orig x4000
.fill x4008
.fill 98
.fill x400A
.fill 73
.fill x4002
.fill 103
.fill x0000 
.fill 114
.fill x4004
.fill 97
.fill x4006
.fill 116
.end

.orig x5000
.blkw 7
.end

.orig x6000
.fill x4000
.fill 6
.end
