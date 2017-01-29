#include <stdio.h>
#include <string.h>

struct info
{
	int a;
	float b;
	char name[20];
}

int main()
{
struct info x = {0};

x.a = 1;
x.b = 1.2;
strcpy(x.name, "Melvin");

printf("x.a is: %i \n", x.a);
printf("x.b is: %f \n", x.b);
printf("x.name is: %s \n", x.name);

struct info y = x;

printf("y.a is: %i \n", y.a);
printf("y.b is: %f \n", y.b);
printf("y.name is: %s \n", y.name);


return 0;
}