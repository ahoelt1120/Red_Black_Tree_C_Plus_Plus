# Red_Black_Tree_C_Plus_Plus

This is a Red Black Tree implemented using C++ for CS 330. No code was provided other than
main.cc and the test scripts.

# Provided Instructions
Introduction

1. In this assignment you will be implementing

    a) a red-black tree (RBT) using C++ classes, inheritance, and upcasting.

2. Declaration for the required classes (rbt.h) are provided. These must not be changed, and your implementation must follow them.

3. First, read the BST (declared in bst.h) implementation and use the unittest_bst() function to test it. DO NOT CHANGE THIS CODE FOR YOUR SUBMISSION.

4. Implement the RBT and use the unittest_rbt() function to test it. DO NOT CHANGE THIS CODE FOR YOUR SUBMISSION, as it will be used to test your code against the answers (with different inputs).

    a) Implementations for some functions (e.g., min, max, succ, pred, walk, search) have already been provided - READ THEM CAREFULLY and understand them.

    b) Implement the insert function (i.e., void rb_insert_node()). This will also require you to implement the rb_insert_fixup(), and right_rotate() and  left_rotate() functions as well.

  c) Implement the delete function (i.e., void rb_delete_node()). This will also require you to implement the rb_delete_fixup() function.

5. Test your code against the provided input and output files.

    a) The provided answers for the RBT unit test are in "test_t7_s1" and "test_t12_s1". The s1 refers to the seed of 1 (-s 1), and t7/t12 refers to the number of elements to add to the RBT (-t 7 or -t 12).

6. Make sure your code has no memory leaks (using valgrind).

7. Your code should work beyond the provided unit tests. That is, even if it does work for all the given tests, if the code has an identifiable bug (i.e., by reading the source code), points WILL be deducted.
