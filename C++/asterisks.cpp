//  asterisks
//  Created by John Madison on 8/17/15.
#include <iostream>
#include <iomanip>
using namespace std;

//print a specified length of asterisks recursively.

void asterisks(int n)
{
    if (n < 0) cout << "error negative number"<<endl;
    else if (n != 0)
    {
    cout << '*';
    n --;
    asterisks(n);
    }
    else cout << endl;
}

//print a triangle recursively.

void trihelp(int n, int i)
{
    if (i >= 0)
    {
        asterisks(n-i);
        cout << endl;
        trihelp(n, i-1);
        asterisks(n-i);
        cout << endl;
    }
}

void triangle(int n)
{
    int i= n-1;
    trihelp(n,i);
}

//another triangle function

void trihelp2(int n, int current)
{
    if (current <= n)
    {
        asterisks(current);
        cout << endl;
        trihelp2(n, current +1);
        asterisks(current);
        cout <<endl;
    }
}

void tri2(int n)
{
    if (n>0) trihelp2(n,1);
}

int main()
{
    triangle(4);
    tri2(4);
}
