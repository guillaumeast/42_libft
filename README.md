# 🧱 **libft** — 42 Paris Project

> _Rebuilding the fundamental bricks of the C standard library and creating a personal reusable library for future 42 projects._

[![Language: C](https://img.shields.io/badge/language-C-lightgrey)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Type: Library](https://img.shields.io/badge/Type-Library-8b949e)](https://en.wikipedia.org/wiki/Library_(computing))
[![Platform: macOS/Linux](https://img.shields.io/badge/platform-macOS%20%26%20Linux-blue)](https://en.wikipedia.org/wiki/Unix-like)
[![Grade: 125/100](https://img.shields.io/badge/Grade-125%2F100-darkgreen)]()
[![Status: Updated after grading](https://img.shields.io/badge/status-Updated%20after%20grading-darkgreen)]()

---

## 🎓 Context

This project the very first milestone of the **42 Paris** curriculum.  
Its purpose is to **reimplement core functions of the C standard library** (`strlen`, `memcpy`, `strchr`, …), while progressively extending it with **higher-level utilities**, in order to build a **robust and reusable personal C library**: **libft**.

This library is designed to be reused across most 42 projects  
(`ft_printf`, `push_swap`, `minishell`, …)  
and to serve as a **long-term foundation** for all future C developments.

---

## ⚙️ Objectives

- Reimplement **libc fundamentals** (strings, memory, characters, conversions)
- Provide **safe and reusable abstractions** on top of low-level C APIs
- Add extended utilities beyond the mandatory subject:
  - dynamic buffers (`buff_*`)
  - linked lists
  - math helpers
  - formatted output helpers
- Ensure:
  - strict **42 Norm** compliance
  - **no memory leaks**
  - well-defined API contracts (ownership, lifetime, error handling)

---

## ✨ Highlights

- 📦 **Dynamic growable buffer API** (`buff_*`)  
  Designed to minimize reallocations and simplify string / I/O manipulation.

- 🧠 **Explicit memory contracts**  
  Ownership, borrowing, and lifetime rules are documented for all public APIs.

- 🛠 **Extended utility set**  
  Helpers that go beyond the libc scope while remaining dependency-free.

- 📚 **Fully documented public API**  
  Automatically generated documentation using **Doxygen**.

---

## 📚 Documentation

The full API documentation is generated from the source code using Doxygen.

➡️ **[Browse the libft API documentation](https://guillaumeast.github.io/42_libft/html/topics)**

> The documentation describes:
> - function contracts
> - ownership & lifetime rules
> - warnings and undefined behavior
> - public data structures

---

## 🗂️ Repository overview

```
libft/
├── libft.h            # Public API
├── src/               # Implementations
├── docs/
│   ├── Doxyfile       # Doxygen configuration
│   └── html/          # Generated API documentation
├── Makefile
└── README.md
```

---

## 🧰 Build

```bash
make        # build libft.a
make clean  # remove object files
make fclean # remove objects and library
make re     # full rebuild
```

To generate the documentation locally:
```bash
make doc
```

---

> _“Build your own standard library, and you’ll never fear undefined behavior again.”_ 🙃
