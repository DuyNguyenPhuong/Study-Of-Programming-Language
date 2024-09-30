;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

(test-assert "gen-big-lazy-if-never-returns-likely-implemented-eager-list"
     (gen-lazy-list 1 1000000000000)) ; this shouldn't hang

(test-assert "gen-list-exists" (lambda () gen-list))
(test-equal "gen-list-many" '(1 2 3 4 5 6 7 8 9 10) (gen-list 1 10))

(test-assert "pair-sum-exists" (lambda () pair-sum?))
(test-equal "pair-sum-first-two" #t (pair-sum? '(1 2 3) 3))
(test-equal "pair-sum-last-two" #t (pair-sum? '(1 2 3) 5))
(test-equal "pair-sum-big-true" #t (pair-sum? (gen-list 1 100) 199))
(test-equal "pair-sum-small-true" #t (pair-sum? (gen-list 1 10) 17))

(test-assert "pair-sum-nonexistent-no-error"  (not (pair-sum? '(1 2 3) 1)))
(test-assert "pair-sum-big-false-no-error" (not (pair-sum? (gen-list 1 100) 201)))
(test-assert "pair-sum-small-false-no-error" (not (pair-sum? (gen-list 1 10) 32)))




(define one-lazy-item (gen-lazy-list 3 5))
(test-equal "gen-lazy-list-single" 3 (car one-lazy-item))
(test-equal "gen-lazy-list-single-end" 4 (car ((cdr one-lazy-item))))


(test-assert "pair-sum-lazy-exists" (lambda () pair-sum-lazy?))
(test-equal "pair-sum-lazy-first-two" #t (pair-sum-lazy? (gen-lazy-list 1 3) 3))
(test-equal "pair-sum-lazy-last-two" #t (pair-sum-lazy? (gen-lazy-list 1 3) 5))
(test-equal "pair-sum-lazy-big-true" #t (pair-sum-lazy? (gen-lazy-list 1 100) 199))
(test-equal "pair-sum-lazy-small-true" #t (pair-sum-lazy? (gen-lazy-list 1 10) 17))

(test-assert "pair-sum-lazy-nonexistent-no-error" (not (pair-sum-lazy? (gen-lazy-list 1 3) 1)))
(test-assert "pair-sum-lazy-big-false-no-error" (not (pair-sum-lazy? (gen-lazy-list 1 100) 201)))
(test-assert "pair-sum-lazy-small-false-no-error" (not (pair-sum-lazy? (gen-lazy-list 1 10) 32)))

(let ((y (inf-seq 15)))
  (test-equal "basics3" 15 (car y))
  (test-equal "basics4" 16 (car ((cdr y))))
  (test-equal "basics5"  '(15 16 17 18 19 20) (first-n y 6))
  (test-equal "basics6" 22 (nth y 8)))

(test-equal "filter-mult1" '(3 5) (first-n (filter-multiples (inf-seq 2) 2) 2) )
(test-equal "filter-mult2"  '(4 5 7 8 10 11) (first-n (filter-multiples (inf-seq 3) 3) 6))
(test-equal "filter-mult3"  '(5 7 8 9 10 11 13 14 15 16 17 19) (first-n (filter-multiples (inf-seq 5) 6) 12))
(test-equal "filter-mult4"  '(5 6 8 9 10 11 12 13 15 16 17 18 19) (first-n (filter-multiples (gen-lazy-list 5 30) 7) 13))

(test-assert "make-lazy-exists" (lambda () make-lazy))
(test-equal "make-lazy-single" 3 (car (make-lazy '(3 4 5))))
(test-equal "make-lazy-second" 4 (car ((cdr (make-lazy '(3 4 5))))))
(test-equal "make-lazy-third" 5 (car ((cdr ((cdr (make-lazy '(3 4 5))))))))
(test-equal "make-lazy-done" '() ((cdr ((cdr ((cdr (make-lazy '(3 4 5)))))))))
