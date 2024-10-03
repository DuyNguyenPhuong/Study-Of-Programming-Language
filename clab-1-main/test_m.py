import subprocess
import unittest
from gradescope_utils.autograder_utils.decorators import weight

def runcmd(cmd, input_text=None):
  splitcmd=cmd.split()
  return subprocess.run(splitcmd, stdout=subprocess.PIPE, input=input_text, check=True)


class HelloTests(unittest.TestCase):
  @weight(1)
  def testOutput(self):
    runcmd('clang -o hello hello.c')
    output = runcmd('./hello').stdout
    self.assertEqual(output, b'Hello, CS251!\n')



class PrintingTests(unittest.TestCase):
  @weight(1)
  def testOutput(self):
    runcmd('clang -o printing printing.c')
    output = runcmd('./printing').stdout

    # See if output contains correct answer somewhere
    self.assertNotEqual(-1, output.find(b"72"))

class TemperatureTests(unittest.TestCase):
  @weight(1)
  def testTemperature(self):
    runcmd('clang -o temperature temperature.c')
    output = runcmd('./temperature', input_text=b"97").stdout

    # See if output contains correct answer somewhere
    self.assertNotEqual(-1, output.find(b"36.1"))
