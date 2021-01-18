;;=======================================
;; CS 2110 - Spring 2019
;; HW6 - Recursive Multiplication
;;=======================================
;; Name:Shaotong Sun
;;=======================================

;; In this file, you must implement the 'mult' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'mult' label.


.orig x3000
HALT

mult
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of mult: integer a, integer b
;;
;; Psuedocode:
;; mult(int a, int b) {
;;     if (a == 0 || b == 0) {
;;         return 0;
;;     }
;;	
;;     // Since one number might be negative, we will only decrement the larger number.
;;     // This ensures that one parameter will eventually become zero.
;;     if (a > b) {
;;         var result = b + mult(a - 1, b);
;;         return result;
;;     } else {
;;         var result = a + mult(a, b - 1);
;;         return result;
;;     }
;; }

;; IMPORTANT NOTE: we recommend following the pseudocode exactly. Part of the autograder checks that your implementation is recursive.
;; This means that your implementation might fail this test if, when calculating mult(6,4), you recursively calculated mult(6,3) instead of mult(5,4).
;; In particular, make sure that if a == b, you calculate mult(a,b-1) and not mult(a-1,b), as the psuedocode says.
;; If you fail a test that expects you to calculate mult(5,4) and you instead calculated mult(4,5), try switching the arguments around when recursively calling mult.

;; YOUR CODE HERE
ADD R6,R6,-4
STR R5,R6,1;old FP
STR R7,R6,2;RA
ADD R5,R6,0;
ADD R6,R6,-5
STR R0,R5,-1
STR R1,R5,-2
STR R2,R5,-3
STR R3,R5,-4
STR R4,R5,-5
;===========
LDR R1,R5,4;R1=a
LDR R2,R5,5;R2=b

ADD R1,R1,0
BRZ IF1
ADD R2,R2,0
BRZ IF1
BR IF2
IF1
AND R0,R0,0
STR R0,R5,0
BR END

IF2
NOT R0,R2;R0=-b
ADD R0,R0,1
ADD R0,R1,R0
BRNZ ELSE
LDR R2,R5,5;push(b)
ADD R6,R6,-1
STR R2,R6,0
LDR R1,R5,4;push(a-1)
ADD R1,R1,-1
ADD R6,R6,-1
STR R1,R6,0
JSR mult
LDR R0,R6,0
ADD R6,R6,3;pop(b,a-1,mult(a-1,b))
LDR R2,R5,5;R2=b
ADD R0,R0,R2;R0=b+ mult(a-1,b)
STR R0,R5,0
BR END

ELSE
LDR R2,R5,5;push(b-1)
ADD R2,R2,-1
ADD R6,R6,-1
STR R2,R6,0
LDR R1,R5,4;push(a)
ADD R6,R6,-1
STR R1,R6,0
JSR mult
LDR R0,R6,0
ADD R6,R6,3;pop(b-1,a,mult(a,b-1))
LDR R1,R5,4;R1=a
ADD R0,R0,R1;R0=a+ mult(a,b-1)
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
