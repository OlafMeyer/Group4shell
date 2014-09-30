// main.c
// Group 4
// Scott McKeefer, Tanner Cash, Olaf Meyer, Matt Truby

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int i, x, y;
	int num = 500; 
	char **string;

	string = malloc(num * sizeof(char*));

	for (i = 0; i < num; i++){
    	string[i] = malloc((6+1) * sizeof(char));
	}

	i = 0;
	while(scanf("%s", string[i]) != EOF)
		i++;

	for(x = 0; x < num; x++)
	{
		switch(string[x][0])
		{
			case '=':
			printf("\n%s%s%s", string[x-1], string[x], string[x+1]);
			x++;
			break;

			case 'i':
			if(string[x][1] == 'f')
			{
				printf("\n%s ", string[x]);
				for(y=x+1; string[y][0] != ']'; y++)
					printf("%s ", string[y]);
				printf("%s", string[y]);
				x=y;
			}

			case 'e':
			if(string[x][1] == 'c' && string[x][2] == 'h')
				printf("\n    %s ", string[x]);
			else if(string[x][1] == 'l' && string[x][2] == 's')
				printf("\n  %s", string[x]);
			break;

			default:
			if(string[x+1][0] != '=' || string[x-1][0] != '=')
			{
				printf("%s ", string[x]);
			}
			break;
		}
	}

	return 0;
}