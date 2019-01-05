Question 1: Show formulas Satifiable (where f is a 2-place function symbol and R a 2-place relation symbol
* ∧ : and
* ∨ : or
* ⌝ : logical negation
* N : natural number
* Structure: a structure A for a language is non-empty set A, called domain of the structure.
  1. For each function symbol fnm in L there is a function fnmA: An -> A
  2. For each relation symbol Rnm in L, there is a subset RAnm of An
  3. For each constant symbol ck in L there is an element cAk
  Structures format <A, ..., fAnm, ..., ...RAnm..., ...cAk...>
  
  In general, a subset of An is called an n-place relation on A, so that the subsets RAnm are just described as the relations on A. so that the subsets RAnm are just described as the relations on A. and the cAKs are called constants of A. The functions fAnm reelations RAnm and constants cAk are called the interpretations in the structure A of the corresponding symbols of L.
* Normal structure: Let L be a language with equality. A structure for L is said to be normal if the interpretation of = is equality on its domain.
* Satifiable formula: Let Phi(x1, x2, ..., xn) be a formula in a language L with free variables contained in the list x1, x2, ..., xn. Phi is satisfiable if there is some structure A for L and some interpretation of the variables x1, x2 x3.... respectively. "⊧": double turnstile - sequence consequence. "⊢": turnstile - single consequence
. A ⊧ phi(x1, x2, ..., xn). 设A为任一命题公式，若A在各种真值指派下至少存在一组成真指派，则A是可满足式，反之为矛盾式.


