;;=======================================
;; CS 2110 - Spring 2019
;; HW6 - Recursive Greatest Common Denominator
;;=======================================
;; Name:Shaotong Sun
;;=======================================

;; In this file, you must implement the 'gcd' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'gcd' label.


.orig x3000
HALT

gcd
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of GCD: integer a, integer b
;;
;; Psuedocode:
;; gcd(int a, int b) {
;;     if (a == b) {
;;         return a;
;;     } else if (a < b) {
;;         return gcd(b, a);
;;     } else {
;;         return gcd(a - b, b);
;;     }
;; }


;; YOUR CODE HERE
ADD R6,R6,-4
STR R5,R6,1;old FP
STR R7,R6,2;RA
ADD R5,R6,0;R5 point to gcd
ADD R6,R6,-5
STR R0,R5,-1
STR R1,R5,-2
STR R2,R5,-3
STR R3,R5,-4
STR R4,R5,-5
;===========
LDR R1,R5,4;R1=a
LDR R2,R5,5;R2=b

NOT R0,R2;R0=-b
ADD R0,R0,1
ADD R0,R0,R1
BRN ELSEIF
ADD R0,R0,0
BRP ELSE
STR R1,R5,0
BR END

ELSEIF
ADD R6,R6,-1;push(a)
LDR R1,R5,4
STR R1,R6,0
ADD R6,R6,-1;push(b)
LDR R2,R5,5
STR R2,R6,0
JSR gcd
LDR R0,R6,0;R0=gcd(b,a)
ADD R6,R6,3;pop 3
STR R0,R5,0
BR END

ELSE
ADD R6,R6,-1;push(b)
LDR R1,R5,4
LDR R2,R5,5
STR R2,R6,0
ADD R6,R6,-1;push(a-b)
NOT R0,R2
ADD R0,R0,1
ADD R0,R0,R1
STR R0,R6,0
JSR gcd
LDR R0,R6,0
ADD R6,R6,3;pop 3
STR R0,R5,0
BR END

END

;===========
LDR R0,R5,0
STR R0,R5,3
LDR R4,R5,-5
LDR R3,R5,-4
LDR R2,R5,-3
LDR R1,R5,-2
LDR R0,R5,-1
ADD R6,R5,0
LDR R5,R6,1
LDR R7,R6,2
ADD R6,R6,3

RET

; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end
