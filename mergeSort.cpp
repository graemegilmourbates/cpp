/*
  Author: Graeme Bates
  Date: 9/6/22
  Merge Sort
*/
#include <iostream>
using namespace std;

bool DEBUG = true;

//Defines and returns new array with length stored in position 0;
int* newArray(int length){
  int* array = new int[length+1];
  array[0] = length;
  return array;
}

//Iterates array and prints(skipping index 0 which stores length)
void printArray(int* array){
  int i = 0;
  while(i < array[0]){
    cout << array[i + 1] << endl;
    i++;
  }
  cout << endl;
}

//Given an array, a begining index and end index, will return a partial array
int* getPartialArray(int* array, int begining, int end){
  int arrayLength = (end-begining);
  int* newArr = newArray(arrayLength);
  int i = begining;
  int position = 1;
  newArr[0] = arrayLength;
  while(i < end){
    newArr[position] = array[i];
    position++;
    i++;
  }
  return newArr;
}

//Given two arrays, will merge lists in sorted order
int* merge(int* left, int* right){
  int finalLength = left[0] + right[0];
  int* merged = newArray(finalLength);
  int i = 1;
  int leftIndex = 1;
  int rightIndex = 1;
  while(leftIndex < left[0]+1 || rightIndex < right[0]+1){
    if(leftIndex > left[0]){
      merged[i] = right[rightIndex];
      i++;
      rightIndex+=1;
    } else if(rightIndex > right[0]){
      merged[i] = left[leftIndex];
      i++;
      leftIndex+=1;
    } else if(left[leftIndex] < right[rightIndex]){
      merged[i] = left[leftIndex];
      i++;
      leftIndex += 1;
    } else {
      merged[i] = right[rightIndex];
      i++;
      rightIndex += 1;
    }
  }
  delete[] left;
  delete[] right;
  return merged;
}

//Merge sort with recursive divide and conquer
int* mergeSort(int* unsorted){
  if(unsorted[0]>1){
    int middle = (unsorted[0]/2);
    int* left;
    int* right;
    left = getPartialArray(unsorted, 1, middle+1);
    right = getPartialArray(unsorted, middle+1, unsorted[0]+1);
    if(left[0] > 1){
      left = mergeSort(left);
    }
    if(right[0] > 1){
      right = mergeSort(right);
    }
    delete[] unsorted;
    return merge(left, right);
  } else {
    return unsorted;
  }
}

//Check if array is sorted
bool isSorted(int* arr){
  int i = 1;
  while(i < arr[0]){
    if(arr[i] > arr[i+1]){
      delete[] arr;
      return false;
    }
    i++;
  }
  delete[] arr;
  return true;
}

bool staticMergeTest(){
  int* testArr = newArray(5);
  testArr[1] = 5;
  testArr[2] = 3;
  testArr[3] = 4;
  testArr[4] = 2;
  testArr[5] = 1;
  testArr = mergeSort(testArr);
  return isSorted(testArr);
}

bool strangeCase(){
  int* testArr = newArray(10);
  testArr[1] = 15;
  testArr[2] = -44;
  testArr[3] = 0;
  testArr[4] = 0;
  testArr[5] = 4;
  testArr[6] = 16;
  testArr[7] = 4;
  testArr[8] = 3;
  testArr[9] = 10;
  testArr[10] = 12;
  testArr = mergeSort(testArr);
  return isSorted(testArr);
}

bool randomCase(){
  srand((unsigned) time(NULL));
  int random;
  int* testArr = newArray(10);
  int i = 0;
  while(i < testArr[0]){
    random = rand();
    testArr[i+1] = random;
    i ++;
  }
  testArr = mergeSort(testArr);
  return isSorted(testArr);
}

void mergeSortTests(){
  int passCount = 0;
  if(!staticMergeTest()){
    cout << "Static Merge Test Failed" << endl;
  } else {
    cout << "Static Merge Test Passed" << endl;
    passCount ++;
  }
  if(!strangeCase()){
    cout << "Strange Case Test Failed" << endl;
  } else {
    cout << "Strange Case Test Passed" << endl;
    passCount ++;
  }
  if(!randomCase()){
    cout << "Random Case Test Failed" << endl;
  } else {
    cout << "Random Case Test Passed" << endl;
    passCount ++;
  }
  cout << "Passed: " << passCount << " out of 3 test." << endl;

}

int main(){
  if(DEBUG == true){
    mergeSortTests();
  }
  return 0;
}
