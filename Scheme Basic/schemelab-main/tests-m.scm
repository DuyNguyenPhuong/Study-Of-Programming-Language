;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))


(test-equal 10 (sum '(4 5 0 1)))
(test-equal 5 (sum '(4 5 0 1 -2 -3)))
(test-equal 3 (sum '(3)))


(test-equal '(a b c) (keep-first-n 3 '(a b c d e)))
(test-equal '(a b) (keep-first-n 2 '(a b c d e)))
(test-equal '(a b c d e) (keep-first-n 5 '(a b c d e)))
(test-equal '(a) (keep-first-n 1 '(a b c d e)))
(test-equal '(d) (keep-first-n 1 '(d)))
