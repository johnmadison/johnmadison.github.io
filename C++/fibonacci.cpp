//
//  main.cpp
//  fibonacci
//
//  Created by John Madison on 9/2/15.
//  Copyright (c) 2015 cmu. All rights reserved.
//

#include <iostream>
#include <iomanip>
using namespace std;

int fib(int n)
{
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return fib(n-1)+fib(n-2);
}


int main()
{
    cout << fib(8) << endl;
    return 0;
}
