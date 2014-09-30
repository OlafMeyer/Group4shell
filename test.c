#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ID_LEN 5

int main()
{


int i;
int variableNumberOfElements = 500; 
char **orderedIds;

orderedIds = malloc(variableNumberOfElements * sizeof(char*));

for (i = 0; i < variableNumberOfElements; i++){
    orderedIds[i] = malloc((ID_LEN+1) * sizeof(char));
}

for(i=0; i < 10; i++)
{
		scanf("%s", orderedIds[i]);
}
for(i=9; i >= 0; i--)
printf("%s\n", orderedIds[i]);

return 0;
}