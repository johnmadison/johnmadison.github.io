//  Array Testing - Recursion Examples
//  Created by John Madison on 8/19/15.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// recursively gets the minimum and maximum values of the array

int minvalue(int a[], int length)
{
    if (length == 1) return a[0];
    else if (a[length-1] < minvalue(a, length-1)) return a[length-1];
    else return minvalue( a, length-1);
}

int maxvalue(int a[], int length)
{
    if (length == 1) return a[0];
    else if (a[length-1] > maxvalue(a, length-1)) return a[length-1];
    else return maxvalue( a, length-1);
}

// recursively gets the sum of all values in the array

int sum(int a[], int length)
{
    if (length == 0) return 0;
    else return a[length -1] + sum(a, length-1);
}

// another sum method using recursion and a helper function.

int sumhelp( int a[], int length, int start)
{
    if (start == length)  return 0;
    else return sumhelp(a, length, start+1) + a[start];
}

int sum2(int a[], int length)
{
    return sumhelp(a, length, 0);
}

// is a target integer in an array?

string member( int a[], int length, int target)
{
    if (length == 0) return "no";
    else if (a[length-1] == target) return "yes";
    else return member(a, length-1, target);
}

// recursively count how many of a certain target integer

int count(int a[], int length, int target)
{
    if (length == 0) return 0;
    return (target == *a) + count(a+1,length-1, target);
}

// recursively print the array into the console.

void display(int a[], int size)
{
    if(size == 1)
        cout<<a[0]<<" ";
    else
    {
        display(a, size - 1);
        cout<<a[size - 1]<<" ";
    } 
}

int main()
{
    int a [] = {1,3,4,5,6,7,8,9,11,7,-99,-44,7,34,56, 1337};
    int size = sizeof(a)/sizeof(a[0]);
    int sumz = sum(a,size);
    cout <<endl<< right << setw(32) << "THE ARRAY" << endl;
    display(a, size);
    cout << endl << endl;
    cout << left<<setw(50)<<"min value is " << minvalue(a,size)<< endl;
    cout << setw(50)<<"max value is " << maxvalue(a,size)<< endl;
    cout << setw(50)<<"range of array is "<< maxvalue(a,size)-minvalue(a,size)<<endl;
    cout << setw(50)<<"number of elements in array " <<size<< endl;
    cout << setw(50)<<"the sum of the array is " << sum(a,size)<< endl;
    cout << setw(50)<<"the alternately calculated sum of the array is " << sum2(a, size)<< endl;
    cout << setw(50)<<"Is the number 2 in the array? " << member(a, size, 2) << endl;
    cout << setw(50)<<"Is the number 3 in the array? " << member(a, size, 3) << endl;
    cout << setw(50)<<"How many 2s are in the array? " << count(a, size, 2) << endl;
    cout << setw(50)<<"How many 7s are in the array? " << count(a, size, 7) << endl;
    cout << setw(50)<<"How many 1337s are in the array? " << count(a, size, 1337) << endl;
    cout << setw(50)<<"The average value of elements is " << sumz / size <<endl;
    return 0;
}




