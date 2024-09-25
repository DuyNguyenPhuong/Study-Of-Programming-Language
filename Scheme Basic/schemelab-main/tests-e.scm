;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

(test-equal 0 (sum '()))

;; Assignment specifies empty list for too short/too long
(test-equal '() (keep-first-n 6 '(a b c d e)))
(test-equal '() (keep-first-n -1 '(a b c d e)))
(test-equal '() (keep-first-n 0 '(a b c)))



