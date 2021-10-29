#include <stdio.h>
#include <limits.h>
#include <string.h>

void main()
{
	char input[10], valid;
	int check = 0, output;  
	
	printf("Enter a data type: ");
	scanf("%s",input);
	printf("\n You entered: %s", input);
	while(check == 0)
	{
		printf("\n Is this correct?(y/n) \n");
		scanf(" %c", &valid);
		
		if(valid == 'y')
			check = 1; 
		else if(valid == 'n') 
			{
				printf("Please enter a data type: ");
				scanf("%s", input); 
				check = 0;
				 
				printf("\n You entered: %s", input);
			} 
		else 
			{
				printf("Please enter y or n \n");
				scanf(" %c", &valid);
			}
	}
	// dosent work how I hoped it might
//	output = sizeof(&input);
//	printf("\nThe size of %s is %d", &input, output);
	if(strcmp(input,"int") == 0)
		printf("The size of %s is: %d\n", input, sizeof(int));
	else if(strcmp(input,"char") == 0)
		printf("The size of %s is: %d\n", &input, sizeof(char));
	else if(strcmp(input,"long") == 0)
		printf("The size of %s is: %d\n", &input, sizeof(long));
	else if(strcmp(input,"double") == 0)
		printf("The size of %s is: %d\n", &input, sizeof(double));
	else if(strcmp(input,"short") == 0)
		printf("The size of %s is: %d\n", &input, sizeof(short));
	else if(strcmp(input,"float") == 0)
		printf("The size of %s is: %d\n", &input, sizeof(float));
	else 
		printf("\nNot a valid data type\n");
}
