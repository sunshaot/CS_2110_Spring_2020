;; =============================================================
;; CS 2110 - Spring 2020
;; HW6 - Replace Values in Linked List
;; =============================================================
;; Name:Shaotong Sun
;; ============================================================

;; In this file, you must implement the 'mult' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'replaceValueLL' label.

.orig x3000
HALT
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of replaceValueLL: Node head, int r
;;
;; Psuedocode:
;; replaceValueLL(Node head, int r) {
;;     if (head == null) {
;;         return head;
;;     }
;;     if (head.data == r) {
;;         head.data = 0;
;;     } else {
;;         head.data = head.data * r;
;;     }
;;     replaceValueLL(head.next);
;;     return head;
;; }


;;important note!!
;R5 = Fram Pointer
;R6 = Stack Pointer
;R7 = Return Address

;;=======Caller Part========
;;replaceValueLL(Node head, int r)
LD R6,STACK
ADD R6,R6,-1;push(r)
LD R0,R
STR R0,R6,0

ADD R6,R6,-1;push(head)
LD R0,HEAD
STR R0,R6
;;==========================
;SP->	head  arg1
;		r     arg2
;
;;==========================
replaceValueLL
;***********************************copy paste part, only thing need to know is local variable number
ADD R6,R6,-4
STR R5,R6,1;old FP
STR R7,R6,2;RA
ADD R5,R6,0;R5 point to gcd
;;==========================
;SP/FP->???? 	lv0()  local variable 0
;		old R5 	Old FP
;		old R7  Return Address ->R5
;		???? 	Return value ->R7
;		head  	arg1
;		r     	arg2
;
;;==========================
ADD R6,R6,-5
STR R0,R5,-1
STR R1,R5,-2
STR R2,R5,-3
STR R3,R5,-4
STR R4,R5,-5
;;==========================
;SP->	save R4 SR4
;		save R3 SR3
;		save R2 SR2
;		save R1 SR1
;		save R0 SR0
;FP->	???? 	lv0()  local variable 0
;		old R5 	Old FP
;		old R7  Return Address ->R5
;		???? 	Return value ->R7
;		head  	arg1
;		r     	arg2
;
;;==========================
;***********************************function part
LDR R1,R5,4;R1=head
LDR R2,R5,5;R2=r

ADD R1,R1,0
BRNP IF; R1 = head != 0 to IF
STR R1,R5,0;store R1 to lv0
BR END;go to END

IF
LDR R3,R1,1;R3 = head.data
NOT R0,R3
ADD R0,R0,1;R0 = - head.data
ADD R0,R0,R2;R0 = - head.data + r
BRNP ELSE;if R0 != 0 go to ELSE
ADD R0,R1,1;R0 = data address
AND R3,R3,0;R3 = 0
STR R3,R0,0;store 0 to R0 address
AND R0,R0,0;reset R0 to 0
BR BACK;go to BACK

ELSE
LDR R3,R1,1;R3 = head,data
;;==========================
;;mult caller part
;;==========================
ADD R4,R2,0;R4 = r
ADD R6,R6,-1;push(r)
STR R4,R6,0
ADD R6,R6,-1;push(data)
STR R3,R6,0
;;==========================
;SP->	data 	arg1
;		r 		arg2
;		save R4 SR4
;		save R3 SR3
;		save R2 SR2
;		save R1 SR1
;		save R0 SR0
;FP->	???? 	lv0()  local variable 0
;		old R5 	Old FP
;		old R7  Return Address ->R5
;		???? 	Return value ->R7
;		head  	arg1
;		r     	arg2
;
;;==========================
JSR mult
;After run mult
;;==========================
;SP-> 	result  Return Value
;		data 	arg1
;		r 		arg2
;		save R4 SR4
;		save R3 SR3
;		save R2 SR2
;		save R1 SR1
;		save R0 SR0
;FP->	???? 	lv0()  local variable 0
;		old R5 	Old FP
;		old R7  Return Address ->R5
;		???? 	Return value ->R7
;		head  	arg1
;		r     	arg2
;
;;==========================
LDR R0,R6,0;R0 = result
ADD R6,R6,3;pop 3
;;==========================
;		result  Return Value
;		data 	arg1
;		r 		arg2
;SP-> 	save R4 SR4
;		save R3 SR3
;		save R2 SR2
;		save R1 SR1
;		save R0 SR0
;FP->	???? 	lv0()  local variable 0
;		old R5 	Old FP
;		old R7  Return Address ->R5
;		???? 	Return value ->R7
;		head  	arg1
;		r     	arg2
;
;;==========================
LDR R1,R5,4;R1 = head
STR R0,R1,1;data = result

BACK
ADD R6,R6,-1;push(r)
LDR R2,R5,5
STR R2,R6,0
ADD R6,R6,-1;push(head.next)
LDR R1,R5,4
LDR R1,R1,0;head.next
STR R1,R6,0
;;==========================
;SP-> 	next 	arg1
;		r 		arg2
;		save R4 SR4
;		save R3 SR3
;		save R2 SR2
;		save R1 SR1
;		save R0 SR0
;FP->	???? 	lv0()  local variable 0
;		old R5 	Old FP
;		old R7  Return Address ->R5
;		???? 	Return value ->R7
;		head  	arg1
;		r     	arg2
;
;;==========================
JSR replaceValueLL
;;==========================
;SP-> 	result  Return Value
;		next 	arg1
;		r 		arg2
;		save R4 SR4
;		save R3 SR3
;		save R2 SR2
;		save R1 SR1
;		save R0 SR0
;FP->	???? 	lv0()  local variable 0
;		old R5 	Old FP
;		old R7  Return Address ->R5
;		???? 	Return value ->R7
;		head  	arg1
;		r     	arg2
;
;;==========================
ADD R6,R6,3
LDR R1,R5,4;R1 = head
STR R1,R5,0;lv0 = R1 = head

END
;***********************************function part over(copy paste)
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

STACK .fill xF000

;; This is a mult subroutine that you can call to multiply numbers.
;; Note that this is not the same as the one you need to implement for Part 1 of this homework;
;; the one you implement there needs to be recursive, and must support negative numbers.
;; However, you can use this subroutine for this homework question.
;; Note that this subroutine does not follow the full calling convention; however, it will work fine if you properly follow the convention on the caller's side.
mult
;; Arguments: int a, int b
ADD R6, R6, -4
STR R0, R6, 0
STR R1, R6, 1
STR R2, R6, 2
AND R0, R0, 0
LDR R1, R6, 4
LDR R2, R6, 5
BRz 3
ADD R0, R0, R1
ADD R2, R2, -1
BRp -3
STR R0, R6, 3
LDR R0, R6, 0
LDR R1, R6, 1
LDR R2, R6, 2
ADD R6, R6, 3
RET
.end


;; The following is an example of a small linked list that starts at x4000.
;; The first number (offset 0) contains the address of the next node in the linked list, or zero if this is the final node.
;; The second number (offset 1) contains the data of this node.
.orig x4000
.fill x4008
.fill 5
.end

.orig x4008
.fill 0
.fill 12
.end
