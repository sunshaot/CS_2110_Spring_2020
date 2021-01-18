;;=============================================================
;;CS 2110 - Spring 2020
;;Homework 5 - Selection Sort
;;=============================================================
;;Name:
;;=============================================================
;;Pseudocode (see PDF for explanation)
;;x = 0;                         // current swapping index in the array
;;len = length of array;
;;while(x < len - 1) {
;;  z = x;                     // index of minimum value in unsorted portion of array
;;  y = x + 1;                 // current index in array
;;  while (y < len) {
;;      if (arr[y] < arr[z]) {
;;          z = y;             // update the index of the minimum value
;;      }
;;      y++;
;;  }
;;  if (z != x) {
;;      temp = arr[x];         // perform a swap
;;      arr[x] = arr[z];
;;      arr[z] = temp;
;;  }
;;      x++;
;;}
.orig x3000

;;PUT YOUR CODE HERE
	LD R0,ARRAY;			R0: array
	AND R1,R1,#0; 		    R1: x
    LD R2,LENGTH;           R2: len

W1  NOT R3,R2;              R3 = ~R2
	ADD R3,R3,#2;           R3 = - len + 1
	ADD R3,R3,R1;		    R3 = x - len + 1
	BRZP EW1;               R3 < 0

	ADD R4,R1,#0;           R4: z = x
	ADD R5,R1,#1;           R5: y = x + 1

W2  NOT R3,R2;              R3 = ~R2
	ADD R3,R3,#1;           R3 = - len
	ADD R3,R3,R5;           R3 = y - len
	BRZP EW2;               R3 < 0

	ADD R6,R0,R4
	LDR R6,R6,#0;           R6: arr[z]
	ADD R7,R0,R5
	LDR R7,R7,#0;           R7: arr[y]
	NOT R6,R6
	ADD R6,R6,#1;           R6: -arr[z]
	ADD R3,R6,R7;			R3 = arr[y] - arr[z]
	BRZP EI1;               R3 < 0

	ADD R4,R5,#0;		    R4(z) = y

EI1 ADD R5,R5,#1;           y++
	BRNZP W2;               }W2
EW2 NOT R3,R1
	ADD R3,R3,#1;           R3 = -x
	ADD R3,R3,R4;           R3 = z - x
	BRZ EI2;                R3 != 0

	ADD R6,R0,R1
	LDR R6,R6,#0;               R6: arr[x]
	ADD R3,R6,#0
	ADD R7,R0,R4
	LDR R7,R7,#0;               R7: arr[z]
	ADD R3,R0,R1
	STR R7,R3,#0
	ADD R3,R0,R4
	STR R6,R3,#0
EI2 ADD R1,R1,#1
	BRNZP W1
EW1 HALT

ARRAY .fill x4000
LENGTH .fill 3
.end

.orig x4000
.fill -14
.fill 4
.fill -22
.end
