#ifndef ARENA_ALLOC_H
#define ARENA_ALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
  void *memory;
  size_t size;
  size_t offset;
} Arena;

void ARENA_Init(Arena *arena, size_t size) {
  arena->memory = (void *)malloc(size);
  if (arena->memory == NULL) {
    fprintf(stderr, "Arena Allocator failed to allocate memory.\n");
    exit(1);
  }
  arena->size = size;
  arena->offset = 0;
}

void *ARENA_Alloc(Arena *arena, size_t size) {
  if (arena->offset + size > arena->size) {
    fprintf(stderr, "Out of memor in arena allocator.\n");
    return NULL;
  }
  void* allocated_memory = arena->memory + arena->offset;
  arena->offset += size;
  return allocated_memory;
}

void ARENA_Reset(Arena *arena) {
  arena->offset = 0;
}

void ARENA_Destroy(Arena *arena) {
  free(arena->memory);
  arena->memory = NULL;
  arena->size = 0;
  arena->offset = 0;
}

// EXAMPLE USAGE OF ARENA ALLOCATOR
// int main() {
//     Arena arena;
//     ARENA_Init(&arena, 1024); // Initialize the arena with 1KB of memory
//     int *numbers = (int *)ARENA_Alloc(&arena, 10 * sizeof(int)); // Allocate space for 10 integers
//     if (!numbers) {
//         return 1; // Allocation failed
//     }
//     for (int i = 0; i < 10; i++) {
//         numbers[i] = i;
//         printf("%d ", numbers[i]);
//     }
//     printf("\n");
//     ARENA_Reset(&arena); // Reset the arena to reuse the memory
//     char *text = (char *)ARENA_Alloc(&arena, 100 * sizeof(char)); // Allocate space for 100 characters
//     if (!text) {
//         return 1; // Allocation failed
//     }
//     strcpy(text, "Hello, Arena Allocator!");
//     printf("%s\n", text);
//     ARENA_Destroy(&arena); // Free the memory when done
//     return 0;
// }

#endif // ARENA_ALLOC_H