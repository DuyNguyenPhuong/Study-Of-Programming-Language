#!/usr/bin/python3

import subprocess
import unittest
from gradescope_utils.autograder_utils.decorators import weight

def runcmd(cmd, input_text=None):
  splitcmd=cmd.split()
  return subprocess.run(splitcmd, stdout=subprocess.PIPE, input=input_text,
                        check=True, universal_newlines=True)

class Tests(unittest.TestCase):
  @weight(1)
  def testGuess1(self):
    runcmd('clang -o guess guess.c')
    test_input = \
      '''
      225577
      50
      75
      83
      89
      95
      92
      94
      '''

    output = runcmd('./guess', input_text=test_input).stdout

    # See if output contains correct output somewhere
    self.assertNotEqual(-1, output.find("Too low!"))
    self.assertNotEqual(-1, output.find("Too high!"))
    self.assertNotEqual(-1, output.find("Total guesses = 7"))

  @weight(1)
  def testGuess2(self):
    runcmd('clang -o guess guess.c')
    test_input = \
      '''
      3
      47
      '''

    output = runcmd('./guess', input_text=test_input).stdout

    # See if output contains correct output somewhere
    self.assertEqual(-1, output.find("Too low!"))
    self.assertEqual(-1, output.find("Too high!"))
    self.assertNotEqual(-1, output.find("Total guesses = 1"))

  @weight(1)
  def testGuess3(self):
    runcmd('clang -o guess guess.c')
    test_input = \
      '''
      3
      50
      42
      48
      44
      49
      41
      47
      '''

    output = runcmd('./guess', input_text=test_input).stdout

    # See if output contains correct output somewhere
    self.assertNotEqual(-1, output.find("Too low!"))
    self.assertNotEqual(-1, output.find("Too high!"))
    self.assertNotEqual(-1, output.find("Total guesses = 7"))

  @weight(1)
  def testArrays(self):
    runcmd('clang -o arrays arrays.c')
    output = runcmd('./arrays').stdout
    self.assertNotEqual(-1, output.find("45"))

  @weight(1)
  def testPointers(self):
    runcmd('clang -o pointers pointers.c')
    output = runcmd('./pointers').stdout
    self.assertNotEqual(-1, output.find("lower"))

  @weight(1)
  def testComplex(self):
    runcmd('clang -o complex complex.c')
    test_input = \
      '''
      2
      5
      3
      4
      '''

    output = runcmd('./complex', input_text=test_input).stdout

    # See if output contains correct output somewhere
    self.assertNotEqual(-1, output.find("-14.00 +"))
    self.assertNotEqual(-1, output.find("23.00 i"))
