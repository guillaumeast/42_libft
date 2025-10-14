# 🧱 **libft** — 42 Paris Project

> _Rebuilding the fundamental bricks of the C standard library and creating a personal reusable library for all future 42 projects._

---

## 🎓 **Context**

This project is one of the very first steps of the **[42 Paris](https://42.fr/)** curriculum.  
Its goal is to **reimplement essential C standard library functions** (`strlen`, `memcpy`, `strchr`, etc.) as well as a few extra utilities, in order to build a **personal base library**: **libft**.

This library will be **reused in all upcoming 42 projects** (like `ft_printf`, `minishell`, `push_swap`, etc.) and serves as the foundation for all future C exercises.

---

## ⚙️ **Objective**

- Recreate basic string, memory, and character manipulation functions.  
- Implement additional utility functions (`ft_split`, `ft_strjoin`, `ft_itoa`, etc.).  
- Add linked list management functions (`ft_lst*`) for the **bonus part**.  
- Provide a reliable, optimized, and memory-leak-free static library.

---

## 🗂️ **Repository structure**

```
libft/
├── Makefile                     # Compiles the lib, tests, and memcheck binaries
├── libft.h                      # Main header file
├── ft_*.c                       # All lib functions (mandatory + bonus)
├── subject/                     # Official 42 subject
│   └── 2022.libft.en.subject.pdf
└── tests/
    ├── mandatory_unit_tests/    # Criterion tests for mandatory functions
    ├── bonus_unit_tests/        # Criterion tests for bonus functions
    ├── mandatory_memcheck.c     # Main for memory leak tests (mandatory part)
    ├── bonus_memcheck.c         # Main for memory leak tests (bonus part)
    └── run_*                    # Generated executables (tests & memcheck)
```

The naming strictly follows 42 subject conventions:  
`ft_functionname.c` for each function and `libft.h` as the main entry point.

---

## 🧰 **Available Make commands**

| Command              | Description |
|----------------------|-------------|
| `make`              | Build **libft.a** (mandatory functions only). |
| `make bonus`        | Add **bonus objects** (`ft_lst*`) to **libft.a**. |
| `make test`         | Build & run **Criterion tests** (mandatory). |
| `make test_bonus`   | Build & run **Criterion tests** (mandatory + bonus). |
| `make leaks`        | Build a **memcheck binary** (mandatory) and run `leaks` (macOS) or `valgrind` (Linux). |
| `make leaks_bonus`  | Same as above for the **bonus part**. |
| `make clean`        | Remove only object files (`.o`). |
| `make fclean`       | Remove all objects and binaries (`libft.a`, `run_tests`, `run_memcheck`). |
| `make re`           | Clean everything and rebuild from scratch. |
| `make help`         | Display available commands, OS detection, compiler flags, and Criterion libraries. |

> 💡 `make help` also displays:
> - The detected OS (macOS / Linux)
> - The Criterion flags and linked libraries
> - A summary of all useful targets

---

## 🧪 **Unit tests**

All tests are written using the **[Criterion](https://github.com/Snaipe/Criterion)** framework.  
They check each function independently, including edge cases and segmentation faults.

Two test suites exist:
- `mandatory_unit_tests/` → standard libc-like functions  
- `bonus_unit_tests/` → linked list (`ft_lst*`) functions

### 📦 Compilation
```bash
make test
# or
make test_bonus
```

### 🧹 Memory leak verification
```bash
make leaks
# or
make leaks_bonus
```

---

## 🔧 **Installing dependencies**

### 🧪 Criterion

#### macOS (via Homebrew)
```bash
brew install criterion
```

#### Ubuntu / Debian
```bash
sudo apt update
sudo apt install libcriterion-dev
```

---

### 🧠 Memory check tools

#### macOS
`leaks` is included with the **Xcode Command Line Tools**.
```bash
xcode-select --install
```

#### Ubuntu / Debian
```bash
sudo apt install valgrind
```

The Makefile automatically detects the correct tool using `uname`:
- macOS → uses `leaks`
- Linux → uses `valgrind`

---

> _“Build your own standard library, and you’ll never fear undefined behavior again.”_ 🙃
