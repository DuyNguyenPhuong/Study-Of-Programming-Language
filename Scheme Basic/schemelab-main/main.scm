;Input nums: A list of numbers (possibly empty).
;Return: A number. The sum of the numbers in nums (0 if nums is empty).
(define sum
  (lambda (nums)
    ; If null return 0
    (if (null? nums)   
        0
        ; Plus the first element and call recursion               
        (+ (car nums)    
           (sum (cdr nums))))))

;Input n: An integer.
;Input lyst: A list.
;Return: A list consisting of the first n items from lyst.
;If n is 0, then the empty list is returned.
;If n is negative or greater than the length of lyst, then an empty list is returned.
(define keep-first-n
  (lambda (n lyst)
    (cond
      ; If n is negative or n largenr then length return 0
      ((or (<= n 0) (> n (length lyst))) '())
      ; Else call recursion
      (else (cons (car lyst)                 
                  (keep-first-n (- n 1) (cdr lyst)))))))




