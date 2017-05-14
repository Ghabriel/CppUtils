# CppUtils
Utility functions and classes for C++, with emphasis on debug utilities.

Three header files are provided:
* `simple_debug.hpp`: simple version, with easy-to-copy echo and trace macros. Mainly used when you don't want an extra header file in your project for some reason and/or only need very basic functionality.
* `debug.hpp`: complete version. Simply `#include` the file and it's ready to use. Complete usage instructions below.
* `xtrace.hpp`: optional add-on to the complete version. Usage instructions below.

## Usage
### Supported macros
* `ECHO`: any number of arguments. Prints them all with a line break after each of them.
* `ECHOI`: indented echo. Receives a number specifying the indentation (the number of tabs) and one or more extra arguments that are printed with the specified indentation.
* `TRACE`: two possible usages:
  1. `TRACE(expression)`: prints the expression itself and its value, followed by a line break. For example:
  ```C++
  char k = 'A';
  TRACE(k); // prints "k = A"
  ```
  2. `TRACE(expression, custom_formatter)`: similar to `TRACE(expression)`, but prints the result of custom_formatter(expression) instead of the value of the expression itself. Anything with a valid operator()(expression) is allowed.
* `TRACE_L`: two possible usages:
  1. `TRACE_L(name, expression)`: equivalent to `TRACE(expression)`, but displays the value of `name` as if it was the name of `expression`.
  2. `TRACE_L(name, expression, custom_formatter)`: same as above, but using a custom formatter.
* `BLANK`: alias to `ECHO()`. Prints a line break.
* `DEBUG`: write this before a line of code to represent a "checkpoint". If the program breaks prematurely (e.g if a segfault occurs), the line number and the file name of the last usage of `DEBUG` is printed along with a string describing the problem. See `tests/debug_macro_test.cpp` for an example.
* `DEBUG_REDIRECT`: redirects all the following debug output to a given output stream, which should be compatible with `decltype(std::cout)` or be a subclass of `dbg::ArbitraryStream`.
* `DEBUG_EXEC`: executes an arbitrary code. Useful to execute some code only if the debug mode is active.
* `XTRACE`: found only in `xtrace.hpp`. Use it like `XTRACE(expression)`. Works like `TRACE(expression)`, but it can pretty-print several other types like `std::vector`, `std::tuple`, etc.

### Other features
* The following macros can either be set directly in `debug.hpp` or overriden during compilation:
  * `ALLOW_DEBUG_USAGE`: if set to 0, every macro usage will do nothing but declare a unused variable inside a new block (to trigger "unused variable" warnings during compilation to make it easy to find all macro usages).
  * `DEBUG_ENABLED`: if set to 0, every macro usage will do nothing at all.
