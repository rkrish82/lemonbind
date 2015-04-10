The project aims to help in using the excellent LALR parser named Lemon in the C++ world.

At the moment this project is in the proof of concept stage. There are few unit tests demonstrating usage of Tokenizer (flex wrapper) and Parser (lemon wrapper) classes. The `Parser.NestedSelect` test parses a simple SQL query of nested SELECTs and builds the trivial AST.