// SortinNumsFromAFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<fstream>


void numbmerExtracter(int arr[], int len,int &counterLen, std::fstream& file) {
	int temp;
	int counter = 0;
	while (file>>temp) {
		arr[counter] = temp;
		++counter;
	}
	counterLen = counter-1;

}

/* C implementation QuickSort */
#include<stdio.h> 

// A utility function to swap two elements 
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
	int pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (arr[j] <= pivot)
		{
			i++;    // increment index of smaller element 
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low  --> Starting index,
high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}


//////////Read numbers from a file,sort them and write them back///////////////
int main()
{
	std::fstream myFile;
	myFile.open("TextFileWithNumbers.txt", std::ios::in);
	int arr[10],countNumbers;
	numbmerExtracter(arr, 10,countNumbers, myFile);
	quickSort(arr,0,countNumbers);
	myFile.close();
	myFile.open("TextFileWithNumbers.txt", std::ios::out);
	for (int i = 0; i < countNumbers; ++i) {
		myFile << arr[i] << " ";
	}
	myFile.close();

    return 0;
}

