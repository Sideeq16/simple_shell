#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
* *_strcmp - compare two string
* @s1: string 1
* @s2: string 2
* Return: postive or negative value
*/
int _strcmp(char *s1, char *s2)
{
	int i = 0, v1, v2;
	int countS1 = 0, countS2 = 0, n = 0;

	while (*(s1 + countS1) != '\0')
	{
		countS1++;
	}
	while (*(s2 + countS2) != '\0')
	{
		countS2++;
	}

	n = countS1 > countS2 ? countS1 : countS2;

	while (i < n)
	{
		if (*(s1 + i) != *(s2 + i))
		{
			v1 = (int) *(s1 + i);
			v2 = (int) *(s2 + i);
			if (v1 > v2)
			{
				return (v1 - v2);
			}
			else if (v1 < v2)
			{
				return (v1 - v2);
			}
		}
		i++;
	}

	return (0);
}
