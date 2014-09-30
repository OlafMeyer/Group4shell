// main.c
// Group 4
// Scott McKeefer, Tanner Cash, Olaf Meyer, Matt Truby

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int i, x, y, brk;
	int rptInx = 1;
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
			//case for an = sign
			case '=':
			printf("\n%s%s%s\n", string[x-1], string[x], string[x+1]);
			x++;
			break;

			case 'e':
			//code for an echo
			if(string[x][1] == 'c' && string[x][2] == 'h'){
				//code for echo
			}
			else if(string[x][1] == 'l' && string[x][2] == 's')//code for an else
			{ 
				printf("\n  %s\n    ", string[x]);
				brk=0;
				for(y=x+1; brk == 0; y++)
				{
					if(string[y][0] == 'f' && string[y][1] == 'i')
						brk = 1;
					else
						printf("%s ", string[y]);
				}
				x=y-2;
			}
			break;

			case 'f':
			//code for fi
			if(string[x][1] == 'i')
				printf("\n%s", string[x]);
			break;

			case 'i':
			//code for if
			if(string[x][1] == 'f')
			{
				printf("\n%s ", string[x]);
				for(y=x+1; string[y][0] != ']'; y++)
					printf("%s ", string[y]);
				printf("%s", string[y]);
				x=y;
			}
			break;

			case 'r':
			//printf("\nenter r\n");
			if(string[x][1] == 'e' && string[x][2] == 'p' && string[x][3] == 'e')
			{
				printf("\nrepeatIndex%d=0\n", rptInx);
				printf("\nwhile [ $reepetIndex%d -lt %s]\n", rptInx, string[x+1]);
				for(y=x; string[y][0] != '{'; y++)
					x++;
				printf("\n");
				for(y=x+1; string[y][0] != '}'; y++)
					printf("%s ", string[y]);
				printf("\n");
				printf("\nrepeatIndex%d=$[$repeatIndex%d+1]\n", rptInx, rptInx);
				printf("\ndone\n");
				x=y;
			}
			break;

			case 't':
			//code for then
			if(string[x][1] == 'h' && string[x][2] == 'e' && string[x][3] == 'n')
			{
				printf("\n  %s\n    ", string[x]);
				brk=0;
				for(y=x+1; brk == 0; y++)
				{
					if(string[y][0] == 'e' && string[y][1] == 'l' && string[y][2] == 's')
						brk = 1;
					else
						printf("%s ", string[y]);
				}
				x=y-2;
			}
			break;
		}
	}
	printf("\n");
	return 0;
}