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