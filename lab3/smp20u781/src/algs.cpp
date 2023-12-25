#include "../inc/algs.hpp"

void heapify(int *array, int i, int n)
{
    int largest;
    int done = 0;
    int l, r;

    while((2 * i <= n) && !done)
    {
        l = 2 * i;
        r = 2 * i + 1;

        if (l == n)
        {
            largest = l;
        } else if (array[l] > array[r])
            largest = l;
        else
            largest = r;

        if (array[i] < array[largest])
        {
            int temp = array[i];
            array[i] = array[largest];
            array[largest] = temp;
            i = largest;
        }
        else
            done = 1;
    }
}

void heap_sort(int *array, int n)
{
    if (array != nullptr && n > 0)
    {
        for (int i = n / 2; i >= 0; i--)
        {
            heapify(array, i, n - 1);
        }

        for (int i = n - 1; i >= 1; i--)
        {
            int temp = array[0];
            array[0] = array[i];
            array[i] = temp;
            heapify(array, 0, i - 1);
        }
    }
}

int insert_sort(int *array, int len)
{
    for (int i = 1; i < len; i++)
    {
        for (int j = i; j > 0 && array[j - 1] > array[j]; j--)
        {
            int tmp = array[j - 1];
            array[j - 1] = array[j];
            array[j] = tmp;
        }
    }
    return 0;
}

void compAndSwap(int *array, int first_index, int second_index, int dir)
{
    int temp;
    if (dir == (array[first_index] > array[second_index]))
    {
        temp = array[first_index];
        array[first_index] = array[second_index];
        array[second_index] = temp;
    }
}

void bitonicMerge(int *array, int start, int len, int dir)
{
    if (len > 1)
    {
        int half_len = len / 2;
        for (int i = start; i < start + half_len; i++)
            compAndSwap(array, i, i + half_len, dir);
        bitonicMerge(array, start, half_len, dir);
        bitonicMerge(array, start + half_len, half_len, dir);
    }
}

void bitonicSort(int *array, int start, int len, int dir)
{
    if (len > 1)
    {
        int half_len = len / 2;

        bitonicSort(array, start, half_len, 1);

        bitonicSort(array, start + half_len, half_len, 0);

        bitonicMerge(array, start, len, dir);
    }
}

void bitonic_sort(int *array, int length, int up)
{
    bitonicSort(array, 0, length, up);
}
