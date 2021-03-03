# Game of Life
This program simulates life within a matrix depending on many options selected by  
the user. It provides multiple boundary modes, file inputting/saving, and other
parameters specific to the modes. It functions using malloc for 1d arrays that
represent 2d matrices. Was malloc worth it? Idk. The program runs until it becomes
empty, reaches stability, or just runs forever if the cells never achieve either.

* Using 1 late day



## Identifying Information

* Name: Scott Fitzpatrick
* Student ID: 2328196
* Email: sfitzpatrick@chapman.edu
* Course: CPSC 350
* Assignment: Game of Life

## Source Files  
* main.cpp
* Environment.h
* Environment.cpp
* input.txt

## References

* C++ ZyBooks Textbook
* Malloc idea/education: My dad
* For my sanity: https://youtu.be/c0_ejQQcrwI
* Arrays: http://www.cplusplus.com/doc/tutorial/arrays/
* Delete and free: https://www.geeksforgeeks.org/g-fact-30/
* Malloc: https://www.cplusplus.com/reference/cstdlib/malloc/
* Random numbers: https://www.cplusplus.com/reference/cstdlib/rand/
* getline: http://www.cplusplus.com/reference/string/string/getline/
* Constants: https://www.w3schools.com/cpp/cpp_variables_constants.asp
* File handling: https://www.geeksforgeeks.org/file-handling-c-classes/
* Rounding floats to ints: http://www.cplusplus.com/forum/beginner/60827/
* File reading: https://www.tutorialspoint.com/read-file-line-by-line-using-cplusplus
* Enter to continue: https://stackoverflow.com/questions/903221/press-enter-to-continue
* String to int: https://stackoverflow.com/questions/7663709/how-can-i-convert-a-stdstring-to-int
* isdigit: https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
* Float to int: https://stackoverflow.com/questions/2544394/c-floating-point-to-integer-type-conversions
* Check array for null: https://stackoverflow.com/questions/19132411/check-array-position-for-null-empty/19132509
* Random number probabilities: https://stackoverflow.com/questions/12885356/random-numbers-with-different-probabilities

## Known Errors
* Random cell life generator seems off

## Build Insructions
* g++ *.cpp

## Execution Instructions
* ./a.out
