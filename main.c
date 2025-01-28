#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int test[5] = {1, 2, 3, 4, 5};
    DynamicArray dynamic_array = createFromValues(test, 5);
    insertAt(&dynamic_array, 30, 10);

    print(&dynamic_array);

    for (int i = 0; i < 100000000; i++)
    {
        push(&dynamic_array, i * i);
    }

    dynamic_array.print_size = 100;

    print(&dynamic_array);

    return 0;
}