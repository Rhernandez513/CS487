# Memory Safety Bugs Keynote Notes

Memory safety issues have been a long-standing problem and are still considered one of the most severe and dominant types of security issues. 

For example, use-after-free bugs have become particularly prevalent in Microsoft software. Memory safety bugs consistently represent 70% of all security bugs.

The current consensus is that memory safety problems are tightly coupled with programming languages and computer architecture. However, the speaker argues that memory safety is a fundamental concern of memory abstractions.

### Types of Memory Safety Issues
- **Spatial bugs**: Accessing memory out of bounds, such as memory not allocated to the process, or memory outside a data structure.
- **Temporal bugs**: Accessing memory after it has been freed. Python, for instance, prevents this by using pointers and checking if an element’s access was stopped by a prior deletion.

### Vulnerabilities and Format Strings
"Printf-oriented programming" has been shown to be Turing complete! Python’s format strings are vulnerable to similar attacks, which could lead to arbitrary reads, even up to the root dictionary, potentially exposing sensitive values.

Although Python does not classify these strictly as memory-unsafe bugs, they share characteristics with vulnerabilities found in C.

### Defining Memory Safety Bugs
A more general definition of memory safety bugs could treat a pointer as a "capability" to access memory. Each pointer would have its own capability to access a defined memory region, with attempts to access outside this region triggering a memory safety bug. However, this definition doesn’t fully address format string vulnerabilities.

Proposed definition: **Memory Safety Bugs are the unmanaged generation or use of an index to the language's storage abstraction.**
- **Unmanaged**: Not enforced by language rules (e.g., arbitrary pointer arithmetic in C).
- **Generation**: Fixing the bug at the point of creation.
- **Index to storage abstraction**: Refers to how languages abstract memory storage.

### Mitigation Techniques
1. Restrict `%n` usage, allowing it only when constructed from read-only memory.
2. Restrict positional arguments (`$`), commonly used in exploits, to make exploits more difficult.
3. Embrace `printf`-compatible format specifiers that compilers can verify at compile-time.

Rust, for example, uses compiler-checked format specifiers in its `printf` equivalent, which prevents certain classes of bugs at compile time.

### Memory Safety in Rust
Rust’s type system and lifetime checks prevent both spatial (e.g., buffer overflow) and temporal (e.g., dangling pointer) violations.
- **Expressive type system**: Supports explicit memory management and boundary checks (RAII).
- **Lifetime checks**: Enforces ownership and lifespan of values at compile time.

In Rust, each variable "owns" a value, and ownership is tightly related to memory management. When ownership transfers, Rust’s compiler automatically inserts commands to deallocate the previous memory.

When a variable goes out of scope, Rust deallocates it since it’s no longer accessible. Accessing a variable after its ownership has moved results in a compilation error. Rust also allows "borrowing" references with the `&` symbol (similar to `address-of` in C).

- **Borrowing**: Allows either reading (shared reference) or writing (mutable reference). However, multiple mutable references or a mix of shared and mutable references are not allowed simultaneously, preventing memory overlap issues (like those seen in `memcpy`).

### Key Principle
Rust achieves practical memory safety by making `unsafe` operations an explicit, opt-in choice. This ensures that unsafe memory operations are intentional, reducing the risk of accidental vulnerabilities. 