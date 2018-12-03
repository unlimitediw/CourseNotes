
### Introduction
* Programs in a logic languages are expressed in a form of symbolic logic
* Use a logical inferencing process to produce results
* Declarative rather than procedural: Only specification of results are stated (not detailed procedures for producing them)

### Symbolic Logic
* Logic which can be used for the basic needs of formal logic:
  * Express propositions
  * Express relationships between propositions
  * Describe how new propositions can be inferred from other propositions
* Particular form of symbolic logic used for logic predicate calculus

### Object Representation
* Objects in propositions are representeed by simple terms: either constants or varibles
* Constant: a symbol that represents an object
* Variable: a symbol that can represent different objects at different time

### Compound Terms
* Atomic proposition consist of compound terms
* Compound term: one element of a mathematical relation, written like a mathermatical function
  * Mathematical function is a mapping
  * Can be written as a table
  
### Parts of a Compound Term
* Compound term composed of two parts
  * Functor: function symbol that names the relationship 
  * Ordered list of parameters(tuple)
* Examples:
  student(jon)
  like(seth,osx)
  like(nick,windows)
  like(jim,linux)

### Forms of a Propostion
* Propositions can be stated in two forms:
  * Fact: proposition is assumed to be true
  * Query: truth of proposition is to be determined
* Compound proposition:
  * Have two or more atomic proposition
  * Propositions are connected by operators
  
### Logical Operators, Quantifiers and Clausal Form
* [Page 11-13](https://github.com/unlimitediw/CourseNotes/blob/master/GWParadigm6221/GWU%20-%20Fall2015%20-%20Logic%20Programming.pdf)

### Resolution
* Unification: finding values for variables iin propositions that allows matching process to succed
* Instatiation: assigning temporary values to variables to allow unificatin to succeed
* After instatiating a variable with a value, if matching fails, may need to backtrack and instantate with a different value

### Proof by Contradiction and Therorem proving
* Hypotheses: a set of pertinent propositions
* Goal: neagtion of theorem stated as a proposition, theorem is proved by finding an inconsitency
* Horn clause:
  * Headed: single atomic proposition on left side
  * Headless: empty left side

### Overview of Logic Programming
* Declarative semantics: simple
* Programming is nonprocedural: Programs do not state now a result is to be computed but rather the form of the result

> Prolog
### Terms: Variables and Structure
* Variable: any string of letters, digits, and underscores beginning with an uppercase letter
* Instantiation: binding of a variable to a value, lasts only as long as it takes to satify one complete goal
* Structue: represents atomic proposition - functor (parameter list)

### Prolog Fact
* A fact is a predicate expression that makes a declarative statement about the problem domain. Whenever a variable occurs in a Prolog expression, it is assumed to be universally quantified. Note that all Prolog sentences must end with a period.
* Used for the hypotheses
* Headless Horn clauses

### Rules
* Horn clause notation: ":-" -> if
* Some Examples:
  * "left_hand_side :- right_hand_side" -> "left_hand_side if right_hand_side"
  * mother(X, Y) :- parent(X, Y), female(X)
  '''
  sister( X, Y) :-
      parent( Z, X),
      parent( Z, Y),
      female( X),
      different( X, Y).
      different(X,Y) :- not(X == Y)
  i.e., for all X and Y,
      X is the sister of Y if
      Z is a parent of X and
      Z is a parent of Y and
      X is female and
      X and Y are not the same person
  '''

  
