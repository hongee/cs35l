#!/usr/bin/python

"""
Implementation of `comm` in Python
"""

import random, sys, locale, string
from optparse import OptionParser

class filelines:
    def __init__(self, filename):
        if filename == "-":
            self.lines = sys.stdin.readlines
        else:
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()

    def issorted(self):
        return sorted(self.lines) == self.lines

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTIONS]... FILE1 [FILE2]

A Python implementation of the POSIX `comm` utility.
Reads FILE1 and FILE2 (or STDIN if FILE2 is unspecified),
and produces three text columns as output:
lines only in FILE1; lines only in FILE2; and lines in both files"""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",
                      action="store_true", dest="col1", default=False,
                      help="Suppress printing of column 1.")
    parser.add_option("-2",
                      action="store_true", dest="col2", default=False,
                      help="Suppress printing of column 2.")
    parser.add_option("-3",
                      action="store_true", dest="col3", default=False,
                      help="Suppress printing of column 3.")
    parser.add_option("-u",
                      action="store_true", dest="nosort", default=False,
                      help="Suppress printing of column 1.")
    (options, args) = parser.parse_args(sys.argv[1:])

    #Check for number of file arguments
    if len(args) != 2:
        parser.error("Wrong number of file inputs. Expects 2.")

    try:
        file1 = filelines(args[0])
        file2 = filelines(args[1])
    except IOError as (errno, strerror):
        parser.error("I/O error({0}): {1}".format(errno, strerror))

    if options.nosort == False and (not file1.issorted() or  not file2.issorted()):
        parser.error("Input files are not sorted!")

    col1 = []
    col2 = []
    col3 = []

    for line in file1.lines:
        if line in file2.lines:
            col3.append(line)
        else:
            col1.append(line)

    for line in file2.lines:
        if line not in file1.lines:
            col2.append(line)

    print (col1,col2,col3)
    '''
    try:
        numlines = int(options.numlines)
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    if len(args) != 1:
        parser.error("wrong number of operands")
    input_file = args[0]

    try:
        generator = randline(input_file)
        for index in range(numlines):
            sys.stdout.write(generator.chooseline())
    except IOError as (errno, strerror):
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))
    '''

if __name__ == "__main__":
    main()
