#include <stdio.h>
#include "main.h"

/**
* _atoi - convert a string to integer
* @s:  take string to conv to integer
* Return: source string upon successful
*/
int _atoi(char *s)
{
	int lent = 0;
	int num = 0, i, type;
	int sign = 0, result;
	int next;

	while (s[lent] != '\0')
	{
		lent++;
	}
	for (i = 0; i < lent; i++)
	{
		type = s[i] - '0';
		next = s[i + 1] - '0';

		if ((sign == 0 && s[i] == 45) || (sign == 0 && s[i] == 43))
		{
			sign = s[i] == 45 ? 1 : 2;
		}

		if (type >= 0 && type <= 9)
		{
			if (num == 0)
				num = type;
			else
				num = (num * 10) + type;
			if (next >= 0 && next <= 9)
			{
			}
			else
			{
				break;
			}
		}
	}
	result = sign == 1 ? (num * -1) : num;

	return (result);
}
