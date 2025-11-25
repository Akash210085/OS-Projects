################################################################################
#   Author: Shiv Bhushan Tripathi                                       ########
#   Date: 18th August 2021                                              ########
################################################################################


#!/bin/bash

test () {

    # Execute the given ops pattern.
    RESULT=`echo "$($2)"`

    # If produced result and expected result is equal then test is passed.
    if [[ $RESULT -eq $3 ]] 
    then
        echo "TEST $1 PASSED"
         # Print the output
        echo "Output: $RESULT"
    else
        echo "TEST $1 FAILED"
         # Print the output
        echo "Output: $RESULT"
    fi

}


# Cleanup old executable 
[ -f root ] && rm root
[ -f double ] && rm double
[ -f square ] && rm square

# Compile
gcc -o root root.c -lm
gcc -o double double.c -lm
gcc -o square square.c -lm

# Tests
# test 1 "./root 5" 2
# test 2 "./double 2" 4
# test 3 "./root 4" 2
# test 4 "./double square 2" 8
# test 3 "./root square 4" 4
# test 4 "./double square 2" 16
# test 3 "./root square 4" 4

# test 1 "./root 8" 3
# test 2 "./square 3" 9
# test 3 "./double 4" 8
# test 4 "./root square 2" 2        # square(2) = 4, root(4) = 2
# test 5 "./double root 16" 8       # root(16)=4, double(4)=8
# test 6 "./square double 2" 16     # double(2)=4, square(4)=16
# test 7 "./square root double 8" 16      # double(8)=16, root(16)=4, square(4)=16
# test 8 "./root double square 4" 6       # square(4)=16, double(16)=32, root(32)=~5.66 rounded to 6 (rounded root 6, double 12, square 144 but chain ends at root)
# test 9 "./double double root 81" 36     # root(81)=9, double(9)=18, double(18)=36
# test 10 "./root square root double 16" 6  # double(16)=32, root(32)=~5.66 rounded to 6, square(6)=36, root(36)=6
# test 11 "./root double square root double square root double square root double square root double square root double square 16" 4
# test 12 "./double root square double root square double root square double root square double root square double root square double root square 4" 64
# test 13 "./square square double root double square root double square root double square root double square root double square root 9" 81
# test 14 "./root double square root double square 10000000000000000000" 10000000000000000000
# Open Test cases (total marks 6: each test case of 2 marks)
# Input followed by output
test 1 "./root 5" 2
test 2 "./double square 2" 16
test 3 "./root square 4" 4

# Hidden Test cases (total marks 14: each test case of 2 marks)
test 4 "./double double double double 1" 16
test 5 "./square square square square square 1" 1
test 6 "./root root root root root root root root root 1" 1
test 7 "./root square root square root square root square root square 1" 1
test 8 "./square double root double root square 3" 9
test 9 "./double root double root double root double root 5" 2
test 10 "./double root double root root root square root square root 5" 1