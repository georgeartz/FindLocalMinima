//
//  main.cpp
//  TestMinima
//
//  Created by George Artz on 10/12/15.
//
//

#include <iostream>
#include <iomanip>

using namespace std;

int binarySearch(int a[], int aSize, int target)
{
    int low = 0, high = aSize;
    int mid;
    if (!aSize)
        return -1;
    while (low <= high)
    {
        mid = low + (high-low)/2;
        if (a[mid] == target)
            return mid;
        else
            if (a[mid] < target)
                low = mid + 1;
            else
                high = mid - 1;
    }
    return -1;
}

// Question: 10/12/2015 phone interview with Jignashu Parikh
//
// Find a local minima in an array. local minima is an element a[i] where a[i] < a[i+1] and a[i] < a[i-1].
// Assume unique positive integers and only one local minima. If [i-1] or [i+1] doesn’t exist, ignore that check.
//
// Examples:
// 8 7 6 9 10 14 -> 6
// 17 16 15 11 13 14 -> 11
// 8 9 -> 8
// 8 -> 8
//
// findLocalMinimaOrderN... O(n) solution
//
// Input:
// a[]..... array of ints
// start... index of first int in array to be checked
// end..... index of last int in array to be checked
//
// Return:
// >= 0.... minima int in array
// <0...... minima not found
//
int findLocalMinimaOrderN(int a[], int start, int end)
{
    for (int i=start; i <= end; i++)
    {
        if ((a[i-2] > a[i-1]) && (a[i-1] < a[i]))
            return a[i-1];
    }
    return -1;
}

// findLocalMinimaOrderLogN... O(log n) solution
//
// Input:
// a[]..... array of ints
// start... index of first int in array to be checked
// end..... index of last int in array to be checked
//
// Return:
// >= 0.... minima int in array
// <0...... minima not found
//
int findLocalMinimaOrderLogN(int a[], int start, int end)
{
    if ((start < 0) || (start > end))
        return -1;
    int mid = (start + end) / 2;    // mid is index of middle
    int i1 = a[mid-2];
    int i2 = a[mid-1];
    int i3 = a[mid];
    if (i1 > i2)
    {
        if (i2 < i3)
            return i2;          // found minima
        // Descending sequence (i1>i2>i3)
        // If i3 < a[end] then minima must be in right half of array
        // minima is middle int of three int sequence "i1>i2 and i2<i3"
        if (i3 < a[end])
            return findLocalMinimaOrderLogN(a, mid+1, end);
    }
    else
    {
        // i1 < i2 at this point
        if (i2 < i3)
        {
            // Ascending sequence  (i1<i2<i3)
            // if i1 < a[start] then minima must be in left half
            // minima is middle int of three int sequence "i1>i2 and i2<i3"
            if (i1 < a[start])
                return findLocalMinimaOrderLogN(a, start, mid-1);
        }
    }
    // Minima could be in either half of array so we need to check both
    int minima = findLocalMinimaOrderLogN(a, start, mid - 1);
    if (minima >= 0)
        return minima;
    return findLocalMinimaOrderLogN(a, mid+1, end);
}

// Return minimal value or -1
int findLocalMinima(int a[], int aSize)
{
    if (!aSize)
        return -1;
    if (aSize == 1)
        return a[0];
    if (aSize == 2)
        return (a[0] < a[1]) ? a[0] : -1;
    //
    // Pass index of first and last ints to be checked.
    // if ((a[i-2] > a[i-1) && (a[i-1] < a[i]))
    // then a[i-1] is minima
    //
    // Test both O(n) and O(log n) solutions
    int minimaOrderN    = findLocalMinimaOrderN(a, 2, aSize-1);
    int minimaOrderLogN = findLocalMinimaOrderLogN(a, 2, aSize-1);
    
    if (minimaOrderN != minimaOrderLogN)
        cout << "findLocalMinima: err. O(n) minima " << minimaOrderN << " O(log n) " << minimaOrderLogN << endl;
    
    return minimaOrderN;
}
 


int main(int argc, const char * argv[]) {
    
    // int nums[] = {8,7,6,9,10,14};
    int nums[] = {17, 16, 15, 11, 13, 14};
    // int nums[] = {8,9};
    // int nums[] = {8};
    // int nums[] = {7, 6, 5, 4};  // ret -1
    // int nums[] = {7, 6, 5};     // ret -1
    int numsCount = sizeof(nums)/sizeof(nums[0]);
    
    cout << std::dec << "input array  {";
    for (int i=0; i<numsCount; i++)
        cout << setw(3) << nums[i];
    cout << "}" << endl;
    
    int minima  = findLocalMinima(nums, numsCount);
    
    cout << "findLocalMinima returned  " << minima << endl;
 
    int target = 11;
    int res = binarySearch(nums, sizeof(nums)/sizeof(nums[0]), target);
    
    if (res < 0)
        cout << "binarySearch target " << target << " not found in array" << endl;
    else
        cout << "binarySearch found target at array[" << res << "]" <<  endl;
    
    return 0;
}

