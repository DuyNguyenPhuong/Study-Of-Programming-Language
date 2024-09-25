;Input bst: A binary search tree (possibly empty).
;Return: The integer key stored in bst's root node (or #f if bst is empty).
(define entry
  (lambda (bst)
    (if (and (list? bst) (= (length bst) 3) (list? (cadr bst)) (list? (caddr bst)))
        (car bst)
        #f)))


;Input bst: A binary search tree (possibly empty).
;Return: The left subtree of bst's root node (or #f if bst is empty).
(define left
  (lambda (bst)
    (if (and (list? bst) (= (length bst) 3) (list? (cadr bst))) ; Check if left subtree is valid
        (cadr bst)                                               ; Return the second element (left subtree)
        #f)))                                                    ; Return #f if it's empty or malformed

;Input bst: A binary search tree (possibly empty).
;Return: The right subtree of bst's root node (or #f if bst is empty).
(define right
  (lambda (bst)
    (if (and (list? bst) (= (length bst) 3) (list? (caddr bst))) ; Check if right subtree is valid
        (caddr bst)                                              ; Return the third element (right subtree)
        #f)))                                                    ; Return #f if it's empty or malformed

(define is-valid-bst
  (lambda (bst)
    (or (null? bst)
        (and (list? bst)
             (= (length bst) 3)
             (integer? (car bst))
             (is-valid-bst (cadr bst))
             (is-valid-bst (caddr bst))))))

;Input elt: An integer.
;Input left-bst: A binary search tree (possibly empty).
;Input right-bst: A binary search tree (possibly empty).
;Return: A binary search tree whose root contains elt as its key, and whose left and 
;right subtrees are left-bst and right-bst.
(define make-bst
  (lambda (elt left-bst right-bst)
    (if (and (integer? elt)
             (is-valid-bst left-bst)
             (is-valid-bst right-bst))
        (list elt left-bst right-bst)
        #f)))




;Input bst: A binary search tree (possibly empty).
;Return: A list of all entries in bst, ordered according to a preorder traversal.
(define preorder
  (lambda (bst)
    (if (null? bst) '()  ; Return empty list if bst is empty
        (append (list (entry bst))      ; Add root
                (preorder (left bst))   ; Preorder traversal on left subtree
                (preorder (right bst)))))) ; Preorder traversal on right subtree

;Input bst: A binary search tree (possibly empty).
;Return: A list of all entries in bst, ordered according to an inorder traversal.
(define inorder
  (lambda (bst)
    (if (null? bst) '()  ; Return empty list if bst is empty
        (append (inorder (left bst))   ; Inorder traversal on left subtree
                (list (entry bst))     ; Add root
                (inorder (right bst)))))) ; Inorder traversal on right subtree

;Input bst: A binary search tree (possibly empty).
;Return: A list of all entries in bst, ordered according to a postorder traversal.
(define postorder
  (lambda (bst)
    (if (null? bst) '()  ; Return empty list if bst is empty
        (append (postorder (left bst))  ; Postorder traversal on left subtree
                (postorder (right bst)) ; Postorder traversal on right subtree
                (list (entry bst))))))   ; Add root

;Input v: An integer.
;Input bst: A binary search tree (possibly empty).
;Return: A binary search tree, equal to the result of inserting v into bst. If bst 
;already contained v, then this result is identical to bst.
(define insert
  (lambda (v bst)
    (cond
      ((null? bst) (make-bst v '() '()))           ; If bst is empty, create a new node with v
      ((= v (entry bst)) bst)                      ; If v already exists, return bst unchanged
      ((< v (entry bst))                           ; If v is smaller, insert into left subtree
       (make-bst (entry bst) (insert v (left bst)) (right bst)))
      (else                                        ; If v is greater, insert into right subtree
       (make-bst (entry bst) (left bst) (insert v (right bst)))))))

