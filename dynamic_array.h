#ifndef ARRAY_H
#define ARRAY_H

#define DEFAULT_SIZE 1
#define DEFAULT_RESIZE_FACTOR 2

#define DEFAULT_PRINT_SIZE 30

typedef struct
{
    int allocated_size;
    int current_size;
    int resize_factor;
    int print_size;
    int *items;
} DynamicArray;

DynamicArray createEmpty();
DynamicArray createFromValues(int *array_start, int array_length);
void destroy(DynamicArray *array);
void print(DynamicArray *array);
int length(DynamicArray *array);
void push(DynamicArray *array, int value);
int pop(DynamicArray *array);
int shift(DynamicArray *array);
void unshift(DynamicArray *array, int value);
int last(DynamicArray *array);
int first(DynamicArray *array);
int get(DynamicArray *array, int index);
void set(DynamicArray *array, int index, int value);
void insertAt(DynamicArray *array, int index, int value);
int deleteAt(DynamicArray *array, int index);

#endif // ARRAY_H