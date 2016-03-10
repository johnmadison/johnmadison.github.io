//
//  main.cpp
//  recursive
//
//  Created by John Madison on 10/26/15.
//  Copyright (c) 2015 cmu. All rights reserved.
//

#include <iostream>

using namespace std;

void f(int x){
    if (x > 0)
    {
        cout << '*' ;
        f (x-1);
        cout << '!';
    }
}

void p1(int x){
    if (x> 0){cout << "*"; p1(x-1);}
}
void p2(int x){
    if (x> 0){cout << "!"; p2(x-1);}
}
void p(int x){p1(x);p2(x);}

int main()
{
    p(3);
    return 0;
}
