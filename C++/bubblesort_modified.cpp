//  array sorting (modified bubble)
//  Created by John Madison on 9/4/15.

#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

string isSorted(int a[], int size)
{
    string sorted = "yes";
    int i = 0;
    while ( i < size - 1 && sorted == "yes")
    {
        if (a[i] > a[i+1]) sorted = "no";
        i++;
    }
    return sorted;
}

void bubble(int a[], int size)
{
    bool swapped = 0;
    if(size == 0)
        return;
    for (int i = 0; i < size - 1; i++)
    {
        if (a[i + 1] < a[i])
        {
            swap(a[i], a[i+1]);
            swapped = 1;
        }
    }
    if (swapped == 0) return;
    bubble(a, size - 1);
}

void print(int a[], int size)
{
    for (int i = 0; i < size; i++) cout <<" "<< a[i] ;
    cout << endl;
}

void randomfill(int b[], int size)
{
    if (size > 0)
    {
        b[size] = rand()*clock()%100;
        randomfill(b,size-1);
    }
    else
        return;
}

int main()
{
    int a[] = {9, 8, 999, 9, 5, 4, 3, 2, 1,1,-5,34,23,64,69,44,3,4,567,3};
    int b[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int sizea = sizeof(a)/sizeof(a[0]);
    int sizeb = sizeof(b)/sizeof(b[0]);
    cout << sizea << " elements in array a" << endl;
    print(a,sizea);
    cout << "array sorted? = " << isSorted(a, sizea) << endl;
    bubble(a, sizea);
    print(a,sizea);
    cout << "array sorted? = " << isSorted(a, sizea) << endl << endl;
    cout << sizeb << " elements in array b" << endl;
    randomfill(b, sizeb);
    print(b, sizeb);
    cout << "array sorted? = " << isSorted(b, sizeb) << endl;
    bubble(b, sizeb);
    print(b,sizeb);
    cout << "array sorted? = " << isSorted(b, sizeb) << endl << endl;
    return 0;
}

