;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

(test-equal "curry1" 30 ((((curry3 *) 2) 3) 5))
(test-equal "uncurry1" 30 ((uncurry3 (curry3 *)) 2 3 5))
(test-equal "uncurry2" '(9 8 7) ((uncurry3 (curry3 list)) 9 8 7))

(test-equal "myfilter1" '(1 3 4) (my-filter positive? '(1 -2 3 4 -5)))
(test-equal "myfilter2" '() (my-filter positive? '(-1 -2 -3 -4 -5)))

(test-equal "exists1" #t (exists (lambda (x) (< x 3)) '(9 2 1 8 7)))
(test-equal "exists2" #t (not (exists (lambda (x) (< x -5)) '(-1 0 1))))

(let ((doclist '((cs (Welcome to the Carleton CS department))
                  (art (The department consists of two separate majors))
                  (geology (The geology department retains a spirit of exploration))
                  (president (Alison R Byerly is Carleton College’s 12th president)))))

  (test-equal "find-docs1" '(cs art geology) (find-docs 'department doclist))
  (test-equal "find-docs2" '(cs president)   (find-docs 'Carleton doclist)))
