/*
 * sort_algorithm.cpp
 *
 *  Created on: Feb 6, 2018
 *      Author: wangwei69
 */

#include "sort_algorithm.h"
#include "test_main.h"
#include <iostream>

/*
 * 二路归并排序的实现
 */
bool Sort::merge_sort(int vec[], size_t start, size_t end){

    size_t mid = (start + end)/2;

    cout << "test" << " "<< start << ":" << mid << ":" << end << endl;

    if (start < end){
        merge_sort(vec, start, mid);
        merge_sort(vec, mid+1, end);
        merge(vec, start, mid, end);
    }
    return true;
}

/*
 * 将两个有序的list，合并成一个有序的list
 * L[s,mid] + L[mid+1,e] -> L[s,e]
 *
 */

void Sort::merge(int vec[], size_t s, size_t mid, size_t e){

    int *tmp = new int[e - s + 1];
    int i = s, j = mid + 1, k = 0;

    while(i <= mid && j <= e){
        if (vec[i] <= vec[j]){
            tmp[k++] = vec[i++];

        }else{
            tmp[k++] = vec[j++];
        }
    }

    while(i <= mid){
        tmp[k++] = (vec[i++]);
    }

    while(j <= e){
        tmp[k++]  = (vec[j++]);
    }

    size_t pos = s,tmp_pos = 0;

    while(pos <= e){
        vec[pos++] = tmp[tmp_pos++];
    }


    return;
}

/*
 * heap 调整
 * vec[s+1,e]之间的数据都是符合大顶堆的定义的；将vec[s,e]也调整成大顶堆;
 *
 * 这一步是堆排序的基础
 *
 */

void Sort::heap_adjust(int vec[], int s, int e){

    if (s>= e)
        return;

    int k, start;
    for(k = 2*s,start = s; k <= e; k *= 2){
        if ((k + 1 <= e)&&(vec[k] < vec[k + 1])){
            k++; //取较大的子点
        }
        if (k <= e && vec[start] > vec[k]){
            //已经是大顶堆了，不需要再调整了
            break;
        }
        if (k <= e && vec[start] < vec[k]){
            swap(vec[start],vec[k]);
            start = k;
        }
    }//end for
    return;
}

/*
 * 堆排序：
 * 1、依赖堆的调整，建立一个大顶堆。从n/2开始，是第一个非叶子节点，自下而上进行堆调整；
 * 2、将元素输出，同时进行堆调整
 *
 * start = 1;
 * end = length;
 */

bool Sort::heap_sort(int vec[],int start, int end){

    if (start >= end)
        return false;

    //从第一个非叶子节点开始建堆
    for(int pos = start + (end-start)/2; pos >= start; pos--){
        heap_adjust(vec, pos, end);
    }

    //输出，并重新调整；
    for(int pos = end; pos > start;){
        swap(vec[start],vec[pos--]);
        heap_adjust(vec, start, pos);
    }
    std::cout << "heap sort finished!" << std::endl;
}

/*
 * 快速排序： 一次划分; 返回轴点被放置的位置。
 *
 */
int Sort::partition(int vec[], int s, int e){

    if (s > e){
        return -1;
    }
    int low = s;
    int high = e;
    int pivotkey = vec[low];
    while(low < high){
        while(low < high && vec[high] >= pivotkey){
            high--;//high指向比轴点大的元素
        }
        if (low < high)
            vec[low] = vec[high];//发现比轴点小的元素，放到左边

        while(low < high && vec[low] <= pivotkey){
            low++;
        }
        if (low < high)
            vec[high] = vec[low];//发现比轴点大的元素，放到右边
    }

    //low就是最后轴点所在的位置
    vec[low] = pivotkey;
    return low;
}

/*
 * 算法：快速排序
 *
 */
void Sort::quick_sort(int vec[], int s, int e){

    if (s >= e)
        return;
    int pos = partition(vec, s, e);
    if (pos != -1){
        quick_sort(vec, s, pos);
        quick_sort(vec,pos + 1,e);
    }

}



void sort_algorithm_test(){

    //归并排序
    int arr[10] = {13, 14, 4, 8, 9, 10, 18, 23, 7, 3};
    Sort::merge_sort(arr,0,9);
    for(int i = 0 ; i < 10; i++){
        std::cout<< arr[i] << " ";
    }

    std::cout << std::endl;
    int arr2[] = {0,232,1,2,31,112};

    //堆排序
    Sort::heap_sort(arr2,1,5);
    for(int i = 0 ; i < 6; i++){
            std::cout<< arr2[i] << " ";
        }
    std::cout << std::endl;

    //快速排序
    int arr3[] = {0,232,1,2,31,112};
    Sort::heap_sort(arr3,0,5);
    for(int i = 0 ; i < 6; i++){
            std::cout<< arr3[i] << " ";
        }
    std::cout <<std::endl << "quick sort finished!"<<std::endl;



}





