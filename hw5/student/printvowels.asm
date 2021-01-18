;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Print the Vowels in a String
;;=============================================================
;;Name:
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;string = "TWENTY ONE TEN";
;;i = 0;
;;while(string[i] != ’\0’){
;;  if(string[i] == ’A’ || string[i] == ’E’ ||
;;  string[i] == ’I’ || string[i] == ’O’ ||
;;  string[i] == ’U’){
;;      print(string[i]);
;;  }
;;i++;
;;}
.orig x3000

	;;INSERT CODE AT THIS LOCATION
	LD R3,STRING;					R3: string = STRING
	AND R1,R1,#0;					R1: i = 0
	LD R2,A;						R2: 'A'
W   AND R0,R0,#0
	ADD R4,R3,R1
	ADD R0,R0,R4
	LDR R0,R0,#0;					R7: string[i]
	BRZ EW

	ADD R4,R2,#0;					R4: 'A'
	NOT R5,R4
	ADD R5,R5,#1
	ADD R5,R5,R0
	BRZ TH

	ADD R4,R2,#4;					R4: 'E'
	NOT R5,R4
	ADD R5,R5,#1
	ADD R5,R5,R0
	BRZ TH

	ADD R4,R2,#8;					R4: 'I'
	NOT R5,R4
	ADD R5,R5,#1
	ADD R5,R5,R0
	BRZ TH

	ADD R4,R2,#14;					R4: 'O'
	NOT R5,R4
	ADD R5,R5,#1
	ADD R5,R5,R0
	BRZ TH

	ADD R4,R2,#14
	ADD R4,R4,#6;					R4: 'U'
	NOT R5,R4
	ADD R5,R5,#1
	ADD R5,R5,R0
	BRZ TH

	BRNZP EL

TH  OUT

EL  ADD R1,R1,#1
	BRNZP W
EW	HALT

A .fill x41    ;; A in ASII
STRING .fill x4000
.end

.orig x4000
.stringz "TWENTY ONE TEN"
.end
