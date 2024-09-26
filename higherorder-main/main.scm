;Input f: A function of three arguments.
;Return: A function, which is the curried version of f. For example,
;((((curry3 f) x) y) z) is equivalent to (f x y z).
(define curry3
  (lambda (f)
    (lambda (x)
      (lambda (y)
        (lambda (z)
          (f x y z))))))


;Input c: A function, which is the curried version of some function of three arguments.
;Return: A function of three arguments, which is the uncurried version of c. For example,
;((uncurry3 (curry3 f)) x y z) is equivalent to (f x y z).
(define uncurry3
  (lambda (c)
    (lambda (x y z)
      (((c x) y) z))))

(define my-filter
  (lambda (pred lyst)
    (cond
      ((null? lyst) '()) ; If the list is empty, return an empty list
      ((pred (car lyst)) ; If predicate fuction returns true for the first element
       (cons (car lyst) (my-filter pred (cdr lyst)))) ; Include the element and recurse on the rest of the list
      (else (my-filter pred (cdr lyst)))))) ; Else, skip the element and recurse

(define exists
  (lambda (pred lyst)
    (not (null? (my-filter pred lyst)))))  ; If the filtered list is non-empty, return #t

(define find-docs
  (lambda (symb docs)
    (map car ; Extract the keys from the filtered list
         (filter ; Use filter
          (lambda (doc)
            (memv symb (cadr doc))) ; Check whether symb is in the value
          docs))))


