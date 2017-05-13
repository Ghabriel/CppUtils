# CppUtils
Utility functions and classes for C++, with emphasis on debug utilities.

Two header files are provided:
* `simple_debug.hpp`: simple version, with easy-to-copy echo and trace macros. Mainly used when you don't want an extra header file in your project for some reason and/or only need very basic functionality.
* `debug.hpp`: complete version. Simply `#include` the file and it's ready to use. Complete usage instructions below.

## Usage
* `ECHO`: any number of arguments. Prints them all with a line break after each of them.
* `ECHOI`: indented echo. Receives a number specifying the indentation (the number of tabs) and one or more extra arguments that are printed with the specified indentation.
* `TRACE`: two possible usages:
  1. `TRACE(expression)`: prints the expression itself and its value, followed by a line break. For example:
  ```C++
  char k = 'A';
  TRACE(k); // prints "k = A"
  ```
  2. `TRACE(expression, custom_formatter)`: similar to TRACE(expression), but prints the result of custom_formatter(expression) instead of the value of the expression itself. Anything with a valid operator()(expression) is allowed.
* `TRACE_L`: two possible usages:
  1. `TRACE_L(name, expression)`: equivalent to `TRACE(expression)`, but displays the value of `name` as if it was the name of `expression`.
  2. `TRACE_L(name, expression, custom_formatter)`: same as above, but using a custom formatter.
* `BLANK`: alias to `ECHO()`. Prints a line break.
* `DEBUG`: write this before a line of code to represent a "checkpoint". If the program breaks prematurely (e.g if a segfault occurs), the line number and the file name of the last usage of DEBUG is printed along with a string describing the problem. See `tests/debug_macro_test.cpp` for an example.
