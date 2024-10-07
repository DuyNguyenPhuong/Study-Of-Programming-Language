from gradescope_utils.autograder_utils.decorators import weight
import unittest
# Nothing exemplary to test this time, you get it automatically after
# meeting expectations
class Tests(unittest.TestCase):
    @weight(1)
    def testStub(self):
        return True
