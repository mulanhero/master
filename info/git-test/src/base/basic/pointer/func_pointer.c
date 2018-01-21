/*
 * func_pointer.c
 *
 *  Created on: Dec 27, 2012
 *      Author: caoj7
 */

#include <stdio.h>
#include <stdlib.h>

int get_bigger(int a, int b)
{
	return a > b ? a : b;
}
//==============================================
void test1(){
	int (*max) (int, int);

	max = get_bigger;

	printf("max(11,22) = %d\n", max(11,22));
	printf("(*max)(11,22) = %d\n", (*max)(11,22));
}
//==============================================
double add(double a, double b)
{
	return a + b;
}

double minus(double a, double b)
{
	return a - b;
}

double multiply(double a, double b)
{
	return a * b;
}

double devide(double a, double b)
{
	return a / b;
}
//==============================================
void test2()
{
	double (*func[]) (double a, double b) =
			{add, minus, multiply, devide};
	printf("func[0](6.6, 2.4) = %f\n", func[0](6.6, 2.4));
	printf("func[1](6.6, 2.4) = %f\n", func[1](6.6, 2.4));
	printf("func[2](6.6, 2.4) = %f\n", func[2](6.6, 2.4));
	printf("func[3](6.6, 2.4) = %f\n", func[3](6.6, 2.4));
}
//==============================================
int main()
{
	test1();
	puts("===============");
	test2();
	return 0;
}
