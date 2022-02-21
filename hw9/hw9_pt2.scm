; Author: Zachery Creech
; COSC365 Spring 2021
; HW9: hw9_pt2.scm
; Contains definitions for mergesort and filter, as well as helper functions split
; and merge for mergesort.
; 04/28/2021

;#4

; recursively splits the list by taking every other element and creating a new list
; to get the "first half" call split() on the list
; to get the "second half" call split() on (cdr list)
; this will effectively get l1 = '(0, 2, 4, ...) and l2 = '(1, 3, 5, ...)
(define split (lambda (l)
	(cond
		; if the current element is the last in the list, return it
		((null? (cdr l)) (list (car l)))
		; if the current element is the second last in the list, return it
		; this is to make sure not to call (cdr (cdr l) outside the bounds of the list
		; the last element will be taken by the other half of the list if skipped here
		((null? (cdr (cdr l))) (list (car l)))
		(else
			; create the list recursively from every other element
			(let ((a (car l)))
				(append (list a) (split (cdr (cdr l)))))))))

; recursively merges two sorted lists into one sorted list
(define merge (lambda (l1 l2)
	(cond
		; these are for catching if l1 and l2 have different parity
	    ((null? l1) l2)
		((null? l2) l1)
		; append the smaller number to the merged list then try again with the list
		; that wasn't smaller and the rest of the list that had the smaller element
		((<= (car l1) (car l2))
			(let ((a (car l1)))
				(append (list a) (merge (cdr l1) l2))))
		(else
			(let ((b (car l2)))
				(append (list b) (merge l1 (cdr l2))))))))

; recursively split a list into smaller lists to sort them in ascending order
(define mergesort (lambda (l)
	(cond
		; catch empty list
		((null? l) '())
		; base case where split has reduced the list into a single element
		((null? (cdr l)) (list (car l)))
		(else
			; split the list into two halves l1 and l2
			(let ((l1 (split l))
				  (l2 (split (cdr l))))
				; call mergesort on each of the halves
				; these will return either a single element each to be merged together
				; or it will return an intermediate merged list
				; either way, the returned lists are then merged, returning to the last
				; call to mergesort up the chain
				(let ((l1sorted (mergesort l1))
					  (l2sorted (mergesort l2)))
					(merge l1sorted l2sorted)))))))

;#5

; filters the elements in a list based on a predicate passed in the function call
(define filter (lambda (filt l)
	(cond
		; catch empty list
		((null? l) '())
		; base case: check if the last element in the list passes the filter
		; if it does, return it to be appended. Otherwise return the empty list
		((null? (cdr l)) 
			(if (filt (car l))
				(list (car l))
				'()))
		(else
			; if the current element passes, keep it and go on to the next element
			; otherwise just go on to the next element
			(let ((a (car l)))
				(if (filt a)
					(append (list a) (filter filt (cdr l)))
					(filter filt (cdr l))))))))
