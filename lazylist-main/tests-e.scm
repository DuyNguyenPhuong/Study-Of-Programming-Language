;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

(test-equal "gen-list-single" '(3) (gen-list 3 3))
(test-equal "gen-list-empty" '() (gen-list 5 3))

(let ((one-lazy-item (gen-lazy-list 3 3)))
  (test-equal "gen-lazy-list-single" 3 (car one-lazy-item))
  (test-assert "gen-lazy-list-single-end-no-error" (null? ((cdr one-lazy-item)))))


(test-equal "neg-inf-seq1" -3 (car (inf-seq -3)))
(test-equal "neg-inf-seq2" -2 (car ((cdr (inf-seq -3)))))
(test-equal "first-n-edge1" '(3 4) (first-n (gen-lazy-list 3 4) 20))
(test-equal "first-n-edge2" '() (first-n (gen-lazy-list 3 2) 20))

(test-assert "nth-edgh1" (not (nth (gen-lazy-list 3 2) 5)))
(test-assert "nth-edge2" (not (nth (gen-lazy-list 3 5) 25)))

(test-equal
    "filter-mult-first-n-edge"
  '(5 6 8 9 10 11 12 13 15 16 17 18 19 20 22 23 24 25 26 27 29 30)
  (first-n (filter-multiples (gen-lazy-list 5 30) 7) 500))

(test-assert "gen-lazy-list-empty-no-error" (null? (gen-lazy-list 5 3)))

(test-assert "make-lazy-list-empty-no-error" (null? (make-lazy '())))
(test-assert "make-lazy-end-no-error" (null? ((cdr ((cdr ((cdr (make-lazy '(3 4 5))))))))))
