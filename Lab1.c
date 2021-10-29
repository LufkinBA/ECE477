/*ECE 477 Lab1
 *Blake Lufkin, Yuri Trusty, Sam King
 *The function of this program is to show the length in bytes
 *of different data types in C. 
 *
 *Also includes the max values of different data types. 
 */
#include <stdio.h> 
#include <limits.h>

void main()
{
	int c, s, i, l, f, d;
	
	c = sizeof(char);
	s = sizeof(short);
	i = sizeof(int);
	l = sizeof(long);
	f = sizeof(float);
	d = sizeof(double);
	
	printf("The length of a char in bytes is: %d \n",c);
	printf("The length of a short in bytes is: %d \n",s);
	printf("The length of an int in bytes is: %d \n",i);
	printf("The length of a long in bytes is: %d \n",l);
	printf("The length of a float in bytes is: %d \n",f);
	printf("The length of a double in bytes is: %d \n",d);

	printf("\n\n");

	printf("The value of INT_MAX in decimal is: %d and it's value in hex is: %x \n",INT_MAX,INT_MAX);	
	printf("The value of UINT_MAX in decimal is: %d and it's value in hex is: %x \n",UINT_MAX,UINT_MAX);
	printf("The value of LONG_MAX in decimal is: %d and it's value in hex is: %x \n",LONG_MAX,LONG_MAX);
	printf("The value of ULONG_MAX in decimal is: %d and it's value in hex is: %x \n",ULONG_MAX,ULONG_MAX);

}

/* Sample output on this machine
 *The length of a char in bytes is: 1 
 *The length of a short in bytes is: 2 
 *The length of an int in bytes is: 4 
 *The length of a long in bytes is: 4 
 *The length of a float in bytes is: 4 
 *The length of a double in bytes is: 8 
 *
 *
 *The value of INT_MAX in decimal is: 2147483647 and it's value in hex is: 7fffffff 
 *The value of UINT_MAX in decimal is: -1 and it's value in hex is: ffffffff 
 *The value of LONG_MAX in decimal is: 2147483647 and it's value in hex is: 7fffffff 
 *The value of ULONG_MAX in decimal is: -1 and it's value in hex is: ffffffff 
 */ 
