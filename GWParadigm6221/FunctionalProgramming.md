# Fuctional Programming
### Lambda
* It is a anonymous function which is defined without a name
* In python, a lambda function has the following syntax
#
    lambda arguments: expression
* e.g
#
    double = lambda x: x * 2
    print(double(5))
* Functional Forms
  * A higher-order function, or functional form, is one that either takes functions as parameters or yields a function as its result, or both.
### Fundamentals of Functional Programming Languages (FPL)
* The objective of the design of a FPL is to mimic mathematical functions to the greatest extent possible.
* The basic process of computation is fundamentally different in a FPL than in an imperative language
  * In an imperative language, operations are done and the results are stored in variables for later use
  * Management of variables is a constant
* In an FPL, variables are not necessary, as is the case in mathematics
* Referential Transparency - In an FPL, the evaluation of a function always produces the same result given the same parameters.

### Lisp Data Types and Structures
* Data object types: originally only atoms and lists
* List form: parenthesized collections of sublists and/or atoms  
  e.g (A B (C D) E)


### Summary
* Functional programming languages use function application, conditional expressions, recursion, and functional forms to control program execution.
* Lisp began as a purely functional language and later included imperative features.
* Scheme is a relatively simple dialect of lisp that uses static scoping exclusively
* Common Lisp is a large Lisp-based language
* ML is a static-scoped and strongly typed functional language that uses type inference.
* Haskell is a lazy functional language supporting infinite lists and set comprehension.
* F# is a .NET functional language that also supports imperative and object-oriented programming
* Some primarily imperative languages now incorporate some support for functional programming
* Purely functional languages have advatages over imperative alternatives, but still are not very widely used
