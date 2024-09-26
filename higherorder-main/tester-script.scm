;; Based on https://srfi.schemers.org/srfi-64/srfi-64.html Unit testing set up
;; code below. Ignore most of this; the important part to focus on is the tests
;; in the associated files.
(use-modules (ice-9 format))
(use-modules (srfi srfi-64))
(define (my-simple-runner)
  (let ((runner (test-runner-null))
        (num-passed 0)
        (num-failed 0))
    (test-runner-on-test-end! runner
      (lambda (runner)
        (case (test-result-kind runner)
          ((pass xpass) (set! num-passed (+ num-passed 1)))
          ((fail xfail)
           (format #t "FAILED:\n   ~s:line ~s\n   ~s\n"
                   (test-result-ref runner 'source-file)
                   (test-result-ref runner 'source-line)
                   (test-result-ref runner 'source-form))

           (set! num-failed (+ num-failed 1)))
          (else #t))))
    (test-runner-on-final! runner
      (lambda (runner)
        (format #t "Passing tests: ~d.~%Failing tests: ~d.~%"
                num-passed num-failed)))
    runner))

(load "main.scm")

(test-runner-factory
 (lambda () (my-simple-runner)))

(test-runner-current (test-runner-create))

(define test-file-name (cadr (command-line)))

(test-begin "test suite")
(load test-file-name)
(test-end "m test suite")

(exit (test-runner-fail-count (test-runner-current)))
