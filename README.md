# Double-Linked-List
Creates a linked list horizontally, each horizontal linked list has a vertical linked list with a random length

Consider the linked lists in Figure 1. Each node of the horizontal linked list has a pointer to a
singly-linked (SL) “bottom” list, or NULL. Call a structure of this type HB list,
from horizontal-bottom list.
Each node contains an integer key. In the horizontal and bottom lists, the keys are sorted in
non-decreasing order. The goal is to take a pointer to the beginning of an HB list and return a

5 -> 8 -> 21 -> 37 -> 42
7    8    42   Null   53
21   35               61
45   54
     61
Figure 1: Example of HB list

pointer to a SL list such that the keys are in non-decreasing order as in shown in Figure 2.
5 -> 7 -> 8 -> 8 -> 21 -> 21 -> 35 -> 37 -> 42 -> 42 -> 45 -> 53 -> 54 -> 61 -> 61

Figure 2: The flattened HB list as a SL list

*note: there are some errors that error with freeing memory when using valgrind
