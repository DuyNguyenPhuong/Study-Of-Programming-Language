(define sum
  (lambda (nums)
    (if (null? nums)   
        0               
        (+ (car nums)    
           (sum (cdr nums))))))
