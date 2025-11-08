# ProgrammingLanguages

This repository contains the coursework and project files for the **Programming Languages** class.  
It includes all the necessary configuration to run the environment inside a **Docker container**, so you can develop, build, and test your language implementation directly in **VS Code**.

---

## Project Overview

We are **recreating a Scheme-inspired programming language**, implemented in **C**.  
The goal is to explore how interpreters and language runtimes work, including:

- Parsing expressions and handling syntax trees  
- Implementing environments and variable scopes  
- Supporting multiple built-in functions (arithmetic, conditionals, recursion, etc.)  
- Enabling function definitions, higher-order functions, and dynamic evaluation  

This language aims to capture the **minimal core of Scheme** while being built from the ground up in **C**, emphasizing memory management, recursion, and functional semantics.

---

## Key Features (Planned / Implemented)

- Basic REPL (Read–Eval–Print Loop)
- Tokenizer and recursive-descent parser
- Expression tree evaluation
- First-class functions and closures
- Built-in functions: `+`, `-`, `*`, `/`, `if`, `define`, `lambda`, etc.
- Tail recursion optimization (stretch goal)
- Garbage collection or memory reuse (optional extension)

---

## Development Environment (Docker + VS Code)

This project is pre-configured to run in a **Dockerized VS Code environment**, so you don’t have to install compilers or dependencies manually.

### Setup Steps

1. **Clone the repository**
   ```bash
   git clone https://github.com/<your-username>/ProgrammingLanguages.git
   cd ProgrammingLanguages
