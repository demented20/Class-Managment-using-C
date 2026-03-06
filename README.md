> 💡 Curious about the thought process behind this project? See [About This Project](#about-this-project).


# Class Management in C

A lightweight class management system written in C, built around a custom dynamic array with an embedded metadata header. Supports adding and deleting students, displaying individual and class-wide statistics, ranking, and per-subject averages.

---

## Features

- Add students with ID, full name, and 5 subject grades
- Delete students by ID
- Display individual student info
- Display all students
- Class statistics (average, highest, lowest)
- Ranking by average grade
- Per-subject class averages

---

## How to Compile and Run

Make sure you have `gcc` installed.

```bash
gcc src/main.c src/student.c src/database_and_dynarray.c src/other_features.c -o class_mgmt
./class_mgmt
```

---

## Usage

When you launch the program, you are prompted to create a class first. Once created, a menu appears:

```
═════════════════════════════════
   CLASS MANAGEMENT SYSTEM
═════════════════════════════════
  1. Add student
  2. Delete student
  3. Display one student
  4. Display all students
  5. Class stats
  6. Ranking
  7. Averages per subject
  0. Exit
═════════════════════════════════
```

Navigate by entering the number corresponding to the action you want. Each operation prompts you for the necessary input (student ID, name, grades, etc.).

---

## Project Structure

```
src/
├── main.c                      # Entry point, menu loop, user input
├── student.c / student.h       # Students struct and display functions
├── database_and_dynarray.c     # Dynamic array implementation
├── database_and_dynarray.h     # Header struct and function declarations
├── other_features.c            # Stats, ranking, subject averages
└── other_features.h            # Declarations for other_features.c
```

---

## Design Decisions

### 1. Storing Metadata in a Header Before the Array

The core data structure of this project is a contiguous memory block laid out as follows:

```
[ Header | Student[0] | Student[1] | ... | Student[n-1] ]
          ^
          pointer returned to the caller
```

The `Header` struct holds the metadata of the array — `count`, `capacity`, and `items` — and is allocated immediately before the student data in a single `malloc` call:

```c
Header *h = malloc(sizeof(Header) + sizeof(Students) * capacity);
```

The caller only ever holds a pointer to the first student (`Students *`), and the header is accessed internally by casting and subtracting one header-sized offset:

```c
Header *header = ((Header *)pointer_to_first_student) - 1;
```

This design is inspired by how some real-world allocators and string implementations (like C++'s `std::string` in certain implementations) embed metadata directly before the data pointer. The main advantage is **locality** — the metadata and the data live in the same memory block, so there is no extra pointer indirection and no risk of the two getting out of sync. The tradeoff is that the caller must always reassign their pointer after any operation that may trigger a `realloc`, since the entire block can move to a new address.

---

### 2. Deletion by Swapping with the Last Element

When a student is deleted, rather than shifting all subsequent elements left (which is O(n)), the deleted slot is filled by copying the last element into it and decrementing the count:

```
Before: [ A | B | C | D | E ]   delete C (index 2)
After:  [ A | B | E | D ]       E moved to index 2, count--
```

```c
items[target] = items[count - 1];
count--;
```

This makes deletion **O(1)** regardless of where in the array the element is. The tradeoff is that insertion order is not preserved — but for a class roster where students are looked up by ID and displayed by ranking rather than insertion order, this is perfectly acceptable. The swap is skipped entirely when the target is already the last element, avoiding a needless self-copy.

---

### 3. Memory Shrinking When Count Drops Below Half Capacity

To avoid holding on to large amounts of unused memory after many deletions, the array shrinks when the number of students drops below half the current capacity:

```c
if (count < capacity / 2 && capacity > MIN_CAPACITY) {
    new_capacity = capacity / 2;
    realloc(...);
}
```

A minimum capacity floor of `32` is enforced — the array never shrinks below 32 slots. This prevents degenerate behavior at small sizes, particularly important because the growth strategy uses `capacity * 1.5`, which truncates to the same value at very small capacities and could cause an infinite realloc loop without the floor.

The shrink feature is wrapped in a `#ifdef FREE_UNNECESSARY_CAPACITY` macro, making it **opt-in**. If memory usage is not a concern, simply comment out the `#define` and the array will never shrink, which slightly improves performance in scenarios with frequent add/delete cycles.

---

## Macros

| Macro | Default | Effect |
|---|---|---|
| `MIN_CAPACITY` | `32` | Minimum array capacity, never shrinks below this |
| `FREE_UNNECESSARY_CAPACITY` | defined | Enables automatic shrinking when count < capacity/2 |
---
## Notes

- Grades are stored as `float` — letter grades are computed from the integer part of the average
- Student names support spaces (captured with `fgets`)
- All functions return the (possibly new) `Header *` after any `realloc` — the caller must always reassign their pointer after a push or delete
---


## About This Project

### Why I Built It

After learning C through online documentation, I wanted to move beyond reading and actually build something tangible. This project was my way of bridging the gap between writing syntax and building features. From start to finish, it took about one week of combined learning and coding.

### What I Learned

My main goal going in was to avoid simply reusing existing data structures and instead think about the problem from a different angle. That led me to the header-array approach — embedding the array's metadata directly before the data in memory — which turned out to be one of the most interesting parts of the project , an other interesting point worth mentionning is that this project was not just to make the code work, but to make it work efficiently. For example, deletion is handled by swapping the target element with the last one in the array - an O(1) operation — rather than shifting all subsequent elements left, which would be O(n). Working in C forced me to think carefully about every byte: how memory is laid out, when it moves, and what that means for every pointer in the program. It also pushed me to think outside the object-oriented perspective — there are no classes, no constructors, no automatic cleanup — and yet it is still possible to write code that is well-structured, readable, and solid. That shift in thinking was probably the most valuable thing I took away from this.

### Future Plans

The next step is to expand the feature set with more advanced functionality, and eventually add a graphical interface using a library like **GTK** to give the program a proper GUI layer. The core data structure is already solid enough to build on — the goal is to keep extending it without compromising the simplicity of the current design.

---

## Author

**Madani Alaoui Youness** — [@demented20](https://github.com/demented20)
