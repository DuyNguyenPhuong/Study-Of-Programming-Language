(define keep-first-n
  (lambda (n lyst)
    (cond
      ((or (<= n 0) (> n (length lyst))) '())
      (else (cons (car lyst)                   
                  (keep-first-n (- n 1) (cdr lyst)))))))
