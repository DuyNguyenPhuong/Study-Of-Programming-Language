;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

;; Testing entry / left /right error checking
(test-assert (not (entry '(a b c))))
(test-assert (not (left '(a b c))))
(test-assert (not (right '(a b c))))
(test-assert (not (entry '())))
(test-assert (not (left '())))
(test-assert (not (right '())))


;; Testing make-bst error checking
(test-assert (not (make-bst 1 2 3)))
(test-assert (not (make-bst 1.5 '() '())))
(test-assert (not (make-bst 'a '() '())))
(test-assert (not (make-bst 1 '(2) '())))
(test-assert (not (make-bst 1 '() '(3))))
(test-assert (not (make-bst 1 '(5 6 7) '(2 3 4))))

;; inorder and postorder testing
(test-equal '(2 1 3)
  (inorder '(1 (2 () ()) (3 () ()))))

(test-equal '(2 3 1)
  (postorder '(1 (2 () ()) (3 () ()))))

;; Testing orderings edge cases
(test-equal '(1)
  (preorder '(1 () ())))
(test-equal '(1)
  (inorder '(1 () ())))
(test-equal '(1)
  (postorder '(1 () ())))
(test-equal '()
  (preorder '()))
(test-equal '()
  (inorder '()))
(test-equal '()
  (postorder '()))

;; Testing orders
(let ((test-tree '(8 (4 () (6 () (7 () ())))
                     (28 (22 () (23 () ())) ()))))
  (test-equal '(4 6 7 8 22 23 28)
    (inorder test-tree))
  (test-equal '(7 6 4 23 22 28 8)
    (postorder test-tree) )

  )