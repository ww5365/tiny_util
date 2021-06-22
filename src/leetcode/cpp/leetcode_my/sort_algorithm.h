/*
 * sort_algorithm.h
 *
 *  Created on: Feb 6, 2018
 *      Author: wangwei69
 */

#include <vector>

using namespace std;



class Sort{

public:
    //归并排序
    static bool merge_sort(int vec[], size_t start, size_t end);
    static void merge(int vec[], size_t s, size_t mid, size_t e);

    //堆排序 vec从下标1开始排序
    static bool heap_sort(int vec[],int start, int end);
    static void heap_adjust(int vec[], int s, int e);

    //快速排序
    static void quick_sort(int vec[], int s, int e);
    static int partition(int vec[], int s, int e);

private:




};


