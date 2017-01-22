#! /usr/local/bin/python
import sys
from random import randint

DELIM = ' '

def generate_test_cases(num_testcases, arr_length_range, arr_value_range,
                        input_file, output_file):
  input_file.write(str(num_testcases) + '\n')

  # Test case for empty arr:
  input_file.write('0\n')
  output_file.write('\n')

  # Test case for arr with only one element:
  input_file.write('1\n')
  input_file.write('1\n')
  output_file.write('1\n')

  # Random testcases:
  for i in range(2, num_testcases):
    l = randint(arr_length_range[0], arr_length_range[1])
    input_file.write(str(l) + '\n')
    arr = [ randint(arr_value_range[0], arr_value_range[1]) for _ in range(l) ]
    input_file.write(DELIM.join(map(str, arr)) + '\n')
    output_file.write(DELIM.join(map(str, sorted(arr))) + '\n')

def print_usage():
  print """\
Usage: ./generate_soring_test_cases.py <num_testcases> \\
  <arr_length_min> <arr_length_max> \\
  <arr_value_min> <arr_value_max> \\
  <input_path> <output_path>
Example:
./generate_soring_test_cases.py 10 2 20 -100 100 input output\
"""

if __name__ == '__main__':
  args = sys.argv[1:]
  nargs = len(args)
  if nargs is not 7:
    print_usage()
    exit(1)

  num_testcases = int(args[0])
  assert num_testcases >= 2

  arr_length_range = [ int(args[1]), int(args[2]) ]
  arr_value_range = [ int(args[3]), int(args[4]) ]
  input_path, output_path = args[5], args[6]

  with open(input_path, 'w') as input_file:
    with open(output_path, 'w') as output_file:
      generate_test_cases(num_testcases, arr_length_range, arr_value_range,
                          input_file, output_file)
