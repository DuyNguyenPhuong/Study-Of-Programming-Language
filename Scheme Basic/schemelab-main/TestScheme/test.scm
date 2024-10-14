(define func1
    (lambda (x)
        (if (> x 0)
        1
        (if (< x 0)
        -1
        0)
        )
    )
)

(define rec
    (lambda (width)
    (let 
        ((
            phi
            (/ (+ (sqrt 5) 1) 2)
        ))
        (* width phi)
    )
    )
)

(define (most-beautiful-rectangle width)
  (let 
    ((
        golden-ratio 
        (/ (+ (sqrt 5) 1) 2)
    ))
    (* width golden-ratio)
    )
)

(define (is-even n)
    (cond
        ((= n 0) #t)
        ((= n 1) #f)
        (else (is-even (- n 2)))
    )
)

(define (x) 
    (lambda (x) (list x x))
) 

(
    ((
        car ((x) x x)
        )) 4

)

(define curried-plus
    (lambda (x)
        (lambda (y)
            (+ x y)
        )
    )
)

(define curried-map
  (lambda (func)
    (lambda (lst)
      (map func lst))))

(
    (curried-map 
        (lambda (x) (* x x))
    ) '(1 2 3 4)



)  ; Result: (1 4 9 16)
