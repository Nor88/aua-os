Pointers allow direct access to memory, making it possible to manage data efficiently and work closely with the hardware.
This report analyzes five assignments designed to help understand pointers step by step — from the basics to more advanced concepts like pointer arithmetic, 
pointers to functions, double pointers, and string manipulation.

Assignment 1: Basics of Pointers
  Pointers allow indirect access to variables and are fundamental for memory manipulation.
  
  .Understand how pointers store memory addresses.
  .Learn how to use the address-of (&) and dereferencing (*) operators.
  .Modify variable values through pointers.
  .Pointers store the address of another variable.
  .The & operator is used to get the address of a variable.
  .The * operator is used to access or change the value stored at that address.
  .We have learnt how to create pointers, print the memory address of a variable, chage the value of the variable using a pointer.


Assignment 2: Pointer Arithmetic
  Pointer arithmetic provides a powerful way to work with arrays efficiently and flexibly.

  .Learn how to move through arrays using pointer arithmetic.
  .Modify and access array elements using pointers instead of traditional indexing.
  .Pointers can be used to traverse arrays because the array name represents the address of its first element.
  .Incrementing a pointer moves it to the next element in memory.
  .This makes it possible to navigate and modify arrays without using arr[i].
  .The assignment focuses on printing the array elements by incrementing the pointer.


Assignment3: Pointers and Functions
  Pointers enable pass-by-reference, allowing changes made inside a function to affect variables outside of it.

  .Understand how to pass pointers to functions.
  .Allow functions to modify variables directly.
  .When a variable is passed to a function normally, only its value is copied.
  .By passing a pointer instead, the function can directly access and modify the original variable.


Assignment4: Pointers to Pointers
  Double pointers give more control over memory, especially in advanced programming scenarios.

  .Learn how to use double pointers, which store the address of another pointer.
  .The first pointer points to a variable.
  .The second pointer points to the first pointer.
  .Managing dynamic memory for 2D arrays.
  .Modifying pointers inside functions.
  .Handling complex data structures like linked lists.


Assignment 5: Strings and Character Pointers
  Pointers make string manipulation more efficient and flexible than traditional indexing methods.

  .Work with pointers to characters and string manipulation.
  .Traverse and process strings using pointer arithmetic.
  .Print a string character by character using a pointer.
  .Count the length of a string using pointer arithmetic instead of array indexing.
  .Strings in C are arrays of characters that end with a special character called the null terminator ('\0').
  .A character pointer can move through the string by incrementing itself until it reaches this null terminator.
  

Pointers are essential for direct memory access and efficient programming.
They are widely used in data structures, dynamic memory allocation, and low-level programming.
Understanding pointers step by step helps prevent common issues like segmentation faults and memory leaks.
These five assignments provide a structured way to learn pointers.
Starting from the basics and moving towards complex topics like double pointers and strings, 
they give a clear understanding of how pointers work and why they are so important in C programming.
Mastering pointers opens the door to advanced programming techniques and efficient memory management.
