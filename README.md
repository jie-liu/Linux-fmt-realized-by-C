$fmt written in c: commandline formatting tool
========

$fmt is used to format natural language text for humans to read. My implementation includes formating the file with specified width and also uniform space; in addition, help and version information are provided in shell interface




Author
------

Jie Liu, Department of Industrial and Systems Engineering, Lehigh University




Compilation
-----------

The project was built with Eclipse on Mac OS so there is folder called Debug. However, if Eclipse is not available in your machine, you can compile the src code (under "./src") by using command
                gcc fmt.c -o fmt




Command line/Shell Interface (Usage)
------------------------------------

Usage: fmt [OPTION]... [FILE]...
		Reformat each paragraph in the FILE(s), printing out results.
		Mandatory arguments to long options are mandatory for short options too.
		  -u, --uniform-spacing     one space between words, two after sentences.
		  -w, --width=WIDTH         maximum line width (default of 75 columns)
		      --help     display this help documentation.
		      --version  output version information.
		The largest value for -w to be set is 10000. This limit can be modified in line 29 of display_text.h .
		Note also that the largest number of characters in a word is 1000. This limit can be modified in line 30 of display_text.h .
		With no FILE, print error message indicating that input does not exist.
        In the case of a line, where the first word length >= width, e.g. -width=1, we keep only the first word in the line and then change to the next line.

Test: a sample example is included named as "test.txt", which is picked from a test article from wikipedia at:
https://en.wikipedia.org/wiki/Fmt
      To perform the test, under directory of the test file, type
             e.g.1     ./src fmt test.txt        (by default, this will print test.txt with width 75)
             e.g.2     ./src fmt test.txt -u        (print with uniform space)
             e.g.3     ./src fmt -u -width 50 test.txt or ./src fmt -u -width=50 test.txt   (print with width 50 and uniform space)




Support
-------

For reporting bugs, please contact Jie Liu at: jie.liu@lehigh.edu .




License
-------

The project is licensed under the GNU GPLv3 license.


