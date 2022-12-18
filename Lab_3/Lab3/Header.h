#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>

//�������� � InsertionSort �� QuickSort
constexpr int valueToUseInsertionSort = 16;

// �������� ���������� ���������
// �� ������ �������� �� �������� VALUE ������ ������� �������� �������� ������������������
// ����� �� ��������� ���������� ����� �� �������� �������� ������� ������������������ ������ �� ��� ���
// ���� �� ������ � ���� ������������������ ��������� ������� VALUE �� ������� ��������������� ������� ������������������
template<typename T, typename Compare>
void InsertionSort(T* first, T* last, Compare comp)
{
    if (first == last)
    {
        return;
    }
    T value;
    T* j;
    for (T* i = first + 1; i <= last; i++)
    {
        value = (*i);
        j = i;
        while (j > first && comp(value, *(j - 1)))
        {
            (*j) = std::move(*(j - 1));
            j--;
        }
        (*j) = std::move(value);
    }
}

// ������� ���������� ���������� ��������
template<typename T, typename Compare>
T FindMedian(T& a, T& b, T& c, Compare compare) {
    if ((compare(a, b) && compare(c, a)) || ((compare(a, c) && compare(b, a))))
    { // c < a < b ��� b < a < c
        return a;
    }
    else if ((compare(b, a) && compare(c, b)) || (compare(b, c) && compare(a, b)))
    { // c < b < a ��� a < b < c
        return b;
    }
    else
    {
        return c;
    }
}
// �������� ������� ����������
// ������ ���������: ������ ������� leftPtr = first, ������� rightPtr = last, � �������� ������� ������� pivot �� �������
// ����� �������� ������� leftPtr � rightRtr ���� � ����� �� ��� ���, ���� *leftPtr > pivot, � *rightPtr < pivot
// ��� ������ ����� �������� > *leftPtr � < *rightPtr ������ �� �������
// (�� ���� ������� �������� �� ��������� �����, � ��������� �������� �����)
// ��������� ��������� �� ��� ���, ���� �� ���������� leftPtr >= rightPtr
// (�� ���� ���� ��� ������� �� �����������)
// ����� ���������� ��������� �������� ������� ����������
template<typename T, typename Compare>
void QuickSort(T* first, T* last, Compare compare, bool useInsertionSort = true)
{
    while (first < last)
    {
        if (useInsertionSort) 
        {
            if ((last - first) < valueToUseInsertionSort)
            {
                InsertionSort(first, last, compare);
            }
        }
        T pivot = FindMedian(*first, *last, *(first + ((last - first) / 2)), compare);
        T* left = first;
        T* right = last;
        while (true) 
        {
            while (compare(*left, pivot)) 
            {
                left++;
            }
            while (compare(pivot, *right))
            {
                right--;
            }
            if (left >= right) 
            {
                break;
            }
            std::swap(*left, *right);
            left++;
            right--;
        }
        if (last - right > right - first) 
        {
            QuickSort(first, right, compare);
            first = right + 1;
        }
        else
        {
            QuickSort(right + 1, last, compare);
            last = right;
        }
    }
}
// ���������� ��� ������ ������� ���������� ������� InsertionSort � QuickSort
double PCFreq = 0.0;
__int64 CounterStart = 0;
void StartCounter() 
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li)) { std::cout << "QueryPerformanceFrequency failed!\n"; }
    PCFreq = double(li.QuadPart / 1000000.0);
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter() 
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}
// ��������������� ���������� ��� ������ ������� ���������� ������� InsertionSort � QuickSort
struct Performance 
{
    double insertionSortResult;
    double quickSortResult;
};
template<typename T, typename Compare>
Performance StartTest(int arraySize, Compare compare) 
{
    srand(time(nullptr));
    T* insertSortArray = new T[arraySize];
    T* quickSortArray = new T[arraySize];
    for (int i = 0; i < arraySize; i++) 
    {
        quickSortArray[i] = i;
        insertSortArray[i] = arraySize - i;
    }
    StartCounter();
    QuickSort(quickSortArray, quickSortArray + arraySize - 1, compare, false);
    double quickSortResult = GetCounter();
    StartCounter();
    InsertionSort(insertSortArray, insertSortArray + arraySize - 1, compare);
    double insertionSortResult = GetCounter();
    delete[] quickSortArray;
    delete[] insertSortArray;
    return { insertionSortResult, quickSortResult };
}

int main()
{
    std::fstream fs;
    //fs.open("./result.txt", std::fstream::out | std::ofstream::trunc);
    const int numberOfTests = 10000;
    for (int i = 0; i < 30; ++i) {
        double insertSum = 0;
        double quickSum = 0;
        for (int j = 0; j < numberOfTests; ++j) {
            Performance result = StartTest<int>(i, [](int a, int b) { return a < b; });
            insertSum += result.insertionSortResult;
            quickSum += result.quickSortResult;
        }
        fs << i << " " << insertSum / numberOfTests << " " << quickSum / numberOfTests << std::endl;
        std::cout << "Array size: " << i << std::endl;
        std::cout << " InsertionSort time: " << insertSum / numberOfTests << std::endl;
        std::cout << " QuickSort time: " << quickSum / numberOfTests << std::endl;
        if (insertSum / numberOfTests < quickSum / numberOfTests) {
            std::cout << "  FASTER - InsertionSort" << std::endl;
        }
        else {
            std::cout << "  FASTER - QuickSort" << std::endl;
        }
        std::cout << std::endl;
    }
    fs.close();
    return EXIT_SUCCESS;
}

