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
    
### Functional Forms
* A higher-order function, or functional form, is one that either takes functions as parameters or yields a function as its result, or both.

### Fundamentals of Functional Programming Languages (FPL)
* The objective of the design of a FPL is to mimic mathematical functions to the greatest extent possible.
* The basic process of computation is fundamentally different in a FPL than in an imperative language
  * In an imperative language, operations are done and the results are stored in variables for later use
  * Management of variables is a constant
* In an FPL, variables are not necessary, as is the case in mathematics
* Referential Transparency - In an FPL, the evaluation of a function always produces the same result given the same parameters.

### Overvies of Concepts in Functional Programming
* First-class functions:
  * First-class functions can either accept another function as an argument or return a function. Being able to create functions and return them or pass them to other functions becomes extremely useful in code reusability and code abstractions.

* Pure functions:
  * Pure functions are functions that have no side effects. Side effects are actions a function may perform that are not solely contained within the function itself. When we think about side effects, we normally think about other functions, such as println or mutating a global variable. We can also see this when we pass in a variable and mutate it directly inside of that function.
  
* Recursion:
  * Recursion allows us to write smaller, more concies algorithms and to operate by looking only at the inputs to our functions. This means that our function is concerned only with the iteration it is on at the mement and whether it must continue.
  
* Immutable variables:
  * Immutable varibles, once set, cannot be changed. Although immutability seems very difficult to do, given the fact that the state must change within an application at some point, we'll see ways that we can accomplish it.
  
* Nonstrict evaluation:
  * Nonstrict evaluations allow us to have variables that have not been computed yet.On contrast, Strict evaluations assigning a variable as soon as it isdefined.
  
* Statements:
  * Statements are evaluable pieces of code that have a return value. Think about if statements that have a return value of some kind. Each line of code should be considered a statement, meaning there are very few side effects within application itself.
  
* Pattern matching:
  * Patter matching does't really appear in mathematics, but assists functional programming in decreasing the need for specific variables. In cod we usually encapsulate a group of variables together inside of an object. Patter matching allows us to better type-check and extract elements from an object, making for simpler and more concise statements with less need for variable definitions.

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
