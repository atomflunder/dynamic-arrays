#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>

DynamicArray createEmpty()
{

    DynamicArray new;
    new.allocated_size = DEFAULT_SIZE;
    new.current_size = 0;
    new.resize_factor = DEFAULT_RESIZE_FACTOR;
    new.print_size = DEFAULT_PRINT_SIZE;
    new.items = malloc(DEFAULT_SIZE * sizeof(int));

    return new;
}

DynamicArray createFromValues(int *array_start, int array_length)
{
    DynamicArray new = createEmpty();

    for (int i = 0; i < array_length; i++)
    {
        push(&new, array_start[i]);
    }

    return new;
}

void destroy(DynamicArray *array)
{
    free(array->items);
}

void _check_allocation(DynamicArray *array)
{
    if (array->current_size < array->allocated_size)
        return;

    int new_size = array->current_size * array->resize_factor;
    int *new_array = malloc(new_size * sizeof(int));

    printf("New memory allocating at: %p\n", new_array);

    for (int i = 0; i < array->allocated_size; i++)
    {
        new_array[i] = array->items[i];
    }

    free(array->items);
    array->items = new_array;
    array->allocated_size = new_size;
}

int _shift_values_from(DynamicArray *array, int index)
{
    if (array->current_size == 0)
    {
        return -1;
    }

    array->current_size--;
    int value = array->items[index];

    for (int i = index + 1; i <= array->current_size; i++)
    {
        array->items[i - 1] = array->items[i];
    }
    array->items[array->current_size] = 0;

    return value;
}

void _unshift_values_from(DynamicArray *array, int index, int value)
{

    if (index >= array->current_size)
    {
        return;
    }

    _check_allocation(array);

    for (int i = array->current_size; i >= index + 1; i--)
    {
        array->items[i] = array->items[i - 1];
    }

    array->current_size++;
    array->items[index] = value;
}

void print(DynamicArray *array)
{
    printf("Array Size: %d\nAllocated: %d\nMemory Address: %p\nBytes Used: %d\n",
           array->current_size,
           array->allocated_size,
           array->items,
           array->allocated_size * sizeof(int));
    printf("Array Items: ");

    int print_size = array->current_size;

    if (print_size > array->print_size)
    {
        print_size = array->print_size;
    }

    for (int i = 0; i < print_size; i++)
    {
        printf("%d ", array->items[i]);
    }

    if (array->current_size > array->print_size)
    {
        printf("... (%d more)", array->current_size - array->print_size);
    }

    printf("\n\n");
}

int length(DynamicArray *array)
{
    return array->current_size;
}

void push(DynamicArray *array, int value)
{
    _check_allocation(array);

    array->items[array->current_size] = value;
    array->current_size++;
}

int pop(DynamicArray *array)
{
    if (array->current_size == 0)
    {
        return -1;
    }

    array->current_size--;
    int value = array->items[array->current_size];
    array->items[array->current_size] = 0;

    return value;
}

int shift(DynamicArray *array)
{
    return _shift_values_from(array, 0);
}

void unshift(DynamicArray *array, int value)
{
    _unshift_values_from(array, 0, value);
}

int last(DynamicArray *array)
{
    if (array->current_size == 0)
    {
        return -1;
    }

    return array->items[array->current_size - 1];
}

int first(DynamicArray *array)
{
    if (array->current_size == 0)
    {
        return -1;
    }

    return array->items[0];
}

int get(DynamicArray *array, int index)
{
    if (index >= array->current_size || index < 0)
    {
        return -1;
    }

    return array->items[index];
}

void set(DynamicArray *array, int index, int value)
{
    if (index >= array->current_size || index < 0)
    {
        return;
    }

    array->items[index] = value;
}

void insertAt(DynamicArray *array, int index, int value)
{
    if (index >= array->current_size)
    {
        return push(array, value);
    }
    else if (index < 0)
    {
        return unshift(array, value);
    }

    _unshift_values_from(array, index, value);
}

int deleteAt(DynamicArray *array, int index)
{
    if (index >= array->current_size)
    {
        return pop(array);
    }
    else if (index < 0)
    {
        return shift(array);
    }

    return _shift_values_from(array, index);
}