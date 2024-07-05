# Arena Allocator

This repository contains a simple implementation of an arena allocator in C. An arena allocator, is a memory management system that allocates memory in large blocks, or "arenas", and allows for individual allocations within these blocks. This type of allocator is particularly useful in scenarios where many small allocations are made and freed in a predictable manner, since it can significantly reduce the overhead and fragmentation compared to traditional memory management methods.

## Features

- **Simple API**: Initialize, allocate, reset, and destroy.
- **Efficient Memory Usage**: Minimizes overhead by allocating large blocks of memory upfront.
- **Fast Allocations**: Allocation is a simple pointer increment in the common case.
- **Reset Capability**: Allows all allocations in the arena to be discarded instantaneously, making it ideal for temporary or scratch data.

## Usage

### Installation

This is a header only library. To use the arena allocator in your project, include the `arena_alloc.h` header file in your C source files and ensure it is in your compiler's include path.

### Functions

- **ARENA_Init(Arena *arena, size_t size)**: Initializes the arena with the specified amount of memory.
- **ARENA_Alloc(Arena *arena, size_t size)**: Allocates a block of memory from the arena. Returns `NULL` if there is insufficient memory.
- **ARENA_Reset(Arena *arena)**: Resets the arena's offset, making all previously allocated memory available again.
- **ARENA_Destroy(Arena *arena)**: Frees all memory associated with the arena and resets its structure.

### Example

Here is a basic example of how to use the arena allocator to manage different types of data:

```c
#include "arena_alloc.h"

int main() {
    Arena arena;
    ARENA_Init(&arena, 1024); // Initialize the arena with 1KB of memory

    int *numbers = (int *)ARENA_Alloc(&arena, 10 * sizeof(int)); // Allocate space for 10 integers
    if (!numbers) {
        return 1; // Alocation failed
    }
    for (int i = 0; i < 10; i++) {
        numbers[i] = i;
        printf("%d ", numbers[i]);
    }
    printf("\n");

    ARENA_Reset(&arena); // Reset the arena to reuse the memory

    char *text = (char *)ARENA_Alloc(&arena, 100 * sizeof(char)); // Allocate space for 100 characters
    if (!text) {
        return 1; // Allocation failed
    }
    strcpy(text, "Hello, Arena Allocator!");
    printf("%s\n", text);

    ARENA_Destroy(&arena); // Free the memory when done
    return 0;
}


