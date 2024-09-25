;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

;; Testing entry / left /right
(test-equal 1
             (entry '(1 () ())))
(test-equal '(2 () ())
             (left '(1 (2 () ()) (3 () ()))))
(test-equal '(3 () ())
             (right '(1 (2 () ()) (3 () ()))))

;; Testing make-bst
(test-equal '(3 () ())
             (make-bst 3 '() '()))

(test-equal '(3 (1 () (2 () ())) (6 (4 () ()) (18 () ())))
             (make-bst 3 '(1 () (2 () ())) '(6 (4 () ()) (18 () ()))))

;; Testing orderings
(test-equal '(1 2 3)
             (preorder '(1 (2 () ()) (3 () ()))))

;; Testing insert
(test-equal '(5 () ())
             (insert 5 '()) )
(test-equal  '(6 (5 () ()) ())
              (insert 5 '(6 () ())))
(test-equal  '(4 () (5 () ()))
              (insert 5 '(4 () ())))
(test-equal '(8 (4 () (6 () (7 () ()))) (28 (22 (10 () ()) (23 () ())) ()))
             (insert 10 '(8 (4 () (6 () (7 () ()))) (28 (22 () (23 () ())) ()))))

;; Testing orders
(let ((test-tree '(8 (4 () (6 () (7 () ())))
                     (28 (22 () (23 () ())) ()))))
  (test-equal  '(8 4 6 7 28 22 23)
                (preorder test-tree))
  )

