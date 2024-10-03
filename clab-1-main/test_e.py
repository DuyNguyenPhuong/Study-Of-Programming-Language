import subprocess
import unittest
from gradescope_utils.autograder_utils.decorators import weight

def runcmd(cmd, input_text=None):
  splitcmd=cmd.split()
  return subprocess.run(splitcmd, stdout=subprocess.PIPE, input=input_text, check=True)


class TemperatureTests(unittest.TestCase):
  @weight(1)
  def testInvalidTemperature(self):
    runcmd('clang -o temperature temperature.c')
    output = runcmd('./temperature', input_text=b"-500").stdout

    # See if output contains correct output somewhere
    self.assertNotEqual(-1, output.find(b"Invalid temperature"))
