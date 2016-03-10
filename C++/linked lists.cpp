//  linked list //  Created by John Madison on 8/24/15.
#include <iostream>
using namespace std;
struct node{
    int value;
    node* next;};
node a;

//return the length of linked list

int length(node* a){
    if (a != NULL) return 1 + length(a -> next);
    else return 0;}
//print linked list.

void print(node* a){
    if (a != NULL){
        cout << a -> value << " ";
        print (a -> next);}
    else cout << endl;}

//print in reverse.

void printrev(node* a){
    if (a != NULL){
        print (a -> next);
        cout << a -> value << " ";}
    else cout << endl;}

//get value at the nth node.

int nth(node* a, int n){
    if (a == NULL) return NULL;
    else if (n-1 == 0) return a-> value;
    else return nth(a-> next, n-1);}
struct node *push( struct node *list, int value ){
    struct node *p = new node;
    if ( p != NULL ){
        p->value = value;
        p->next = list;
        list = p;}
    return list;}

//append two linked lists together.

void append(node *& first, node* second){
    if (first == NULL) first = second;
    else append(first->next, second);}

//return the highest value in a linked list.

int maxhelp(node* list, int max){
    if (list == NULL) return max;
    else if (list -> value > max) return maxhelp(list -> next, list->value);
    else return maxhelp(list -> next, max);}
int max(node* list){
    return maxhelp(list -> next, list -> value);}

//recursively reverse a linked list.

void reverse(node*& p)
{
    if (!p) return;
    node* remaining = p->next;
    if (!remaining) return;
    reverse(remaining);
    p->next->next = p;
    p->next = NULL;
    p = remaining;
}

//another append function. 

void appendhelp(node* list1, node* list2)
{
    if(list1->next==NULL)list1->next=list2;
    else
        appendhelp(list1->next, list2);
}

node* append2(node* list1, node* list2)
{
    if(list1==NULL)return list2;
    else
    {
        appendhelp(list1, list2);
        return list1;
    }
}



node* reverse2(node* list)
{
    if ( list == NULL) return NULL;
    else
    {
        node* nextNode = list -> next;
        list -> next = NULL;
        return append2(reverse2(nextNode), list);
    }
}





int main(){
    struct node *list1 = NULL, *list2 = NULL;
    int i;
    for ( i = 0; i < 5; i++ ) list1 = push( list1, rand() % 10);
    for ( i = 0; i < 5; i++ ) list2 = push( list2, rand() % 10);
    cout << "list1: ";
    print(list1);
    cout << "list2: ";
    print(list2);
    cout << endl<<"Appended List:" << endl;
    append(list1,list2);
    print(list1);
    reverse(list1);
    cout << endl << "Reversed List:" << endl;
    print(list1);
    cout << endl<<"max value of list1 = " << max(list1) << endl;
    return 0;}

