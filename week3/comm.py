#!/usr/bin/python

"""
Implementation of `comm` in Python
"""

import random, sys, locale, string
from optparse import OptionParser

class filelines:
    def __init__(self, filename):
        if filename == "-":
            self.lines = sys.stdin.read().split()
        else:
            f = open(filename, 'r')
            self.lines = f.read().split()
            f.close()

    def issorted(self):
        return sorted(self.lines) == self.lines

#lol
def leftpad(str, numtabs):
    for i in range(numtabs):
        str = "\t" + str
    return str

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTIONS]... FILE1 FILE2

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
    except IOError as e:
        parser.error("I/O error({0}): {1}".format(e.errno, e.strerror))

    if options.nosort == False and (not file1.issorted() or  not file2.issorted()):
        parser.error("Input files are not sorted!")

    col1tab = 0
    col2tab = 1
    col3tab = 2

    if options.col1 == True:
        col2tab = 0
        col3tab -= 1
    if options.col2 == True:
        col3tab -= 1

    #print file1.lines
    #print file2.lines

    #maxcount = max(len(file1.lines), len(file2.lines))
    if options.nosort == False:
        i = 0
        j = 0
        while i < len(file1.lines) or j < len(file2.lines):
            #print(i,j)
            if i >= len(file1.lines):
                #first file has ran out
                if not options.col2:
                    print(leftpad(file2.lines[j], col2tab))
                j += 1
            elif j >= len(file2.lines):
                #second file has ran out
                if not options.col1:
                    print(leftpad(file1.lines[i], col1tab))
                i += 1
            elif file1.lines[i] > file2.lines[j]:
                #file1.lines line is bigger, consider file2.lines line instead
                if not options.col2:
                    print(leftpad(file2.lines[j], col2tab))
                j += 1
            elif file1.lines[i] < file2.lines[j]:
                #file2.lines line is bigger, consider file1.lines line instead
                if not options.col1:
                    print(leftpad(file1.lines[i], col1tab))
                i += 1
            else:
                #lines equal
                if not options.col3:
                    print(leftpad(file1.lines[i], col3tab))
                i += 1
                j += 1
    else:
        #non-sorted comparison
        for line in file1.lines:
            if line in file2.lines:
                #line exists in file2
                file2.lines.remove(line)
                if not options.col3:
                    print(leftpad(line, col3tab))
            else:
                #line unique to file1
                if not options.col1:
                    print(leftpad(line, col1tab))
        if not options.col2:
            for line in file2.lines:
                print(leftpad(line, col2tab))

if __name__ == "__main__":
    main()
