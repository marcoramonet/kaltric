# Kaltric
Kaltric is a programming language as a study on compiler design and construction. 
Currently it is in an early stage, but eventually it will become a playground for lexical and syntactical exploration.

## TODOs: 
### Lexer:
- Implement special characters within string literals (\", \', \\)
- Implement hex, oct, and binary numerals

#### Lex refactor
- Check for valid state before making operations in state dependent functions
- MAYBE: Make overloaded version of tokenize (with string parameter) state-independent
- Right now lexer is disposable



### BUGs:
- Token position:
    - Bug in newline: newline and incrementing are out of phase
    - Implement consume() function.

- Use get() instead of peek() and seekg()