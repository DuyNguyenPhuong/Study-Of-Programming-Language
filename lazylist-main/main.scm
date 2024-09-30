;Input start: An integer.
;Input stop: An integer.
;Return: A list of all integers that are >= start and <= stop, in order. If start > stop, 
;then the list is empty.
(define gen-list
  (lambda (start stop)
    (if (> start stop) ; If start is larger than stop
        '()
        (cons start (gen-list (+ start 1) stop))))) ; add start and recurse with start +1 -> stop

;Input lyst: A list of integers.
;Input desired: An integer.
;Return: A Boolean, which is #t if there are two consecutive integers in the list that 
;add to the desired integer, and #f otherwise.
(define pair-sum?
  (lambda (lyst desired)
    (cond
      ; If the list has fewer than 2 elements, return #f
      ((or (null? lyst) (null? (cdr lyst))) #f)
      
      ; If the sum of the first two elements equals desired, return #t
      ((= (+ (car lyst) (cadr lyst)) desired) #t)
      
      ; Otherwise, recurse on the rest of the list (cdr lyst)
      (else (pair-sum? (cdr lyst) desired)))))

;Input start: An integer.
;Input stop: An integer.
;Return: A lazy list of all integers that are >= start and <= stop, in order. If 
;start > stop, then the list is empty.
(define gen-lazy-list
  (lambda (start stop)
    (if (> start stop) ; If start larger than stop return empty
        '()
        (cons start
              (lambda () (gen-lazy-list (+ start 1) stop)))))) ; add start + recurse with start + 1, stop

;Input first: An integer.
;Return: A lazy list consisting of all integers >= first.
(define inf-seq
  (lambda (first)
    (cons first
          (lambda () (inf-seq (+ first 1)))))) ; Add first and recurse with first + 1

;Input lyst: An ordinary list.
;Return: A lazy list consisting of the same elements in the same order.
(define make-lazy
  (lambda (lyst)
    (if (null? lyst) ; If lyst is empty return empty
        '()
        (cons (car lyst) 
              (lambda () (make-lazy (cdr lyst))))))) ; Add 1st element + add recurse

;Input lazy-list: A lazy list of integers.
;Input desired: An integer.
;Return: A Boolean, which is #t if there are two consecutive integers in the 
;list that add to the desired integer, and #f otherwise.
(define pair-sum-lazy?
  (lambda (lazy-list desired)
    (cond
      ; Base case: If lazy-list is empty or has smaller than two elements, return #f
      ((or (null? lazy-list) (null? ((cdr lazy-list)))) #f)
      
      ; Check if the sum of the first two elements equals the desired sum
      ((= (+ (car lazy-list) (car ((cdr lazy-list)))) desired) #t)
      
      ; Recurse to the next pair in the lazy list
      (else (pair-sum-lazy? ((cdr lazy-list)) desired)))))




;Input lazy-list: A lazy list.
;Input n: An integer >= 1.
;Return: An ordinary list consisting of the first n elements of the given lazy list. If 
;the lazy list contains fewer than n elements, then all of the values in the lazy list 
;are returned. If the lazy list is empty, then so is the returned list.
(define first-n
  (lambda (lazy-list n)
    (if (or (null? lazy-list) (= n 0))  ; Return empty list if the lazy list is empty or n = 0
        '()
        (cons (car lazy-list)           ; Add the first element to the list + recurse with n-1
              (first-n ((cdr lazy-list)) (- n 1))))))

;Input lazy-list: A lazy list.
;Input n: An integer >= 1.
;Return: The nth element of the lazy list, indexing from 1. If there are fewer than n 
;elements in the lazy list, then #f is returned.
(define nth
  (lambda (lazy-list n)
    (cond
      ((null? lazy-list) #f)             ; If the list is empty, return #f
      ((= n 1) (car lazy-list))          ; If n is 1, return the first element
      (else (nth ((cdr lazy-list)) (- n 1)))))) ; Else recurse with n-1

;Input lazy-list: A lazy list of integers.
;Input n: An integer >= 2.
;Return: A lazy list, which is just like the given lazy list, except that all integer 
;multiples of n have been removed. Warning: Unavoidably fails in certain situations where 
;the result is supposed to be empty.
(define filter-multiples
  (lambda (lazy-list n)
    (cond
      ; If the lazy list is empty, return an empty list
      ((null? lazy-list) '())
      
      ; If the current element is a multiple of n, skip it and recurse with the rest
      ((= 0 (modulo (car lazy-list) n)) (filter-multiples ((cdr lazy-list)) n))
      
      ; Else, include the element and filter the rest of the lazy list
      (else (cons (car lazy-list) (lambda () 
               (filter-multiples ((cdr lazy-list)) n)))))))  ; Recurse lazily to filter the rest of the list
