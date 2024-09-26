;Input bst: A binary search tree (possibly empty).
;Return: The integer key stored in bst's root node (or #f if bst is empty).
(define entry
  (lambda (bst)
    ; Check if bst is null first
    (if (null? bst)
        #f
        ; Check if bst has length of 3 and all elements are lists
        (if (and (list? bst) (= (length bst) 3) (list? (cadr bst)) (list? (caddr bst)))
            (car bst)
            #f))))

;Input bst: A binary search tree (possibly empty).
;Return: The left subtree of bst's root node (or #f if bst is empty).
(define left
  (lambda (bst)
    ; Check if left subtree is valid and return the 2nd element
    (if (and (list? bst) (= (length bst) 3) (list? (cadr bst))) 
        (cadr bst)                                               
        #f)))                                                   

;Input bst: A binary search tree (possibly empty).
;Return: The right subtree of bst's root node (or #f if bst is empty).
(define right
  (lambda (bst)
    ; Check if left subtree is valid and return the 3rd element
    (if (and (list? bst) (= (length bst) 3) (list? (caddr bst))) 
        (caddr bst)                                              
        #f)))                                                   

;Input elt: An integer.
;Input left-bst: A binary search tree (possibly empty).
;Input right-bst: A binary search tree (possibly empty).
;Return: A binary search tree whose root contains elt as its key, and whose left and 
;right subtrees are left-bst and right-bst.
(define make-bst
  (lambda (elt left-bst right-bst)
    (if (and (integer? elt)
              ; Check if it is empty subtree or valid subtree
             (or (null? left-bst) (not (eq? (entry left-bst) #f)))  
             (or (null? right-bst) (not (eq? (entry right-bst) #f))))
        (list elt left-bst right-bst)
        #f)))


;Input bst: A binary search tree (possibly empty).
;Return: A list of all entries in bst, ordered according to a preorder traversal.
(define preorder
  (lambda (bst)
  ; Return empty list if bst is empty
    (if (null? bst) '()  
        ; Root -> left -> right
        (append (list (entry bst))    
                (preorder (left bst))   
                (preorder (right bst))))))

;Input bst: A binary search tree (possibly empty).
;Return: A list of all entries in bst, ordered according to an inorder traversal.
(define inorder
  (lambda (bst)
    ; Return empty list if bst is empty
    (if (null? bst) '()  
        ; left -> root -> right
        (append (inorder (left bst))  
                (list (entry bst))     
                (inorder (right bst))))))

;Input bst: A binary search tree (possibly empty).
;Return: A list of all entries in bst, ordered according to a postorder traversal.
(define postorder
  (lambda (bst)
    ; Return empty list if bst is empty
    (if (null? bst) '()  
        ; left -> right -> root
        (append (postorder (left bst)) 
                (postorder (right bst)) 
                (list (entry bst)))))) 

;Input v: An integer.
;Input bst: A binary search tree (possibly empty).
;Return: A binary search tree, equal to the result of inserting v into bst. If bst 
;already contained v, then this result is identical to bst.
(define insert
  (lambda (v bst)
    (cond
      ; If bst is empty, create a new node with v
      ((null? bst) (make-bst v '() '()))          
      ((= v (entry bst)) bst) ; If v already exists, return bst unchanged                     
      ((< v (entry bst)) ; If v is smaller, insert into left subtree
       (make-bst (entry bst) (insert v (left bst)) (right bst)))
      (else ; If v is larger, insert into right subtree
       (make-bst (entry bst) (left bst) (insert v (right bst)))))))

