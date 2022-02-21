; Author: Zachery Creech
; COSC365 Spring 2021
; HW9: hw9_pt1.scm
; Contains definitions for swap, avg, and min, as well as helper function
; avgHelp for avg.
; 04/23/2021

; return a cons pair of the passed arguments in ascending order
(define swap (lambda (x y)
	(if (< x y)
		(cons x y)
		(cons y x))))

; "helper" function for avg, recursively determine both the total sum and
; length of the list in one pass of the list. Returns a cons pair of the
; total sum and total length to avg, which then performs sum / length
(define avgHelp (lambda (l)
	(if (null? l)
		(list 0 0)
		(let ((pair (avgHelp (cdr l))))
			(list (+ (car l) (car pair)) (+ (cadr pair) 1))))))

; recursively computes the average of a list of numbers
(define avg (lambda (l)
	; if list is empty just return 0
	(if (null? l)
		0
		; otherwise recursively determine the sum and length
		; divide by 1.0 at the end to force output of float
		(let ((pair (avgHelp l)))
			(/ (/ (car pair) (cadr pair)) 1.0)))))

; determine the minimum number in a list using tail-recursion
(define min (lambda (l)
	(cond
		; if the list is empty return the empty list
		((null? l) '())
		; this is the last recursive call, the last remaining element in
		; the list should be the minimum
		((null? (cdr l)) (car l))
		; most calls will follow this statement:
		; get the first and second elements of the list
		(#t (let ((x (car l))
				  (y (cadr l)))
			; compare the elements, keep the smaller one and append the rest
			; of the list to it, then call min on this new list. Do this
			; repeatedly until only one element is left, which is the minimum
			(if (< x y)
				(min (append (list x) (cdr (cdr l))))
				(min (append (list y) (cdr (cdr l))))))))))
