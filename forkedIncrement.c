#include <sys/types.h> //pid_t
#include <sys/wait.h> //wait
#include <stdio.h>
#include <unistd.h> //fork

void inc_n(int *n)
{
   /* increment n to 100 */
   while(++(*n) < 1000000000);
}

int main()
{

    int status;
    int x = 0, y = 0;
    printf("hey x: %d, y: %d\n", x, y);
    pid_t pid = fork();
    
    if (pid == 0) {
      inc_n(&x);
      printf("x increment finished\n");
      inc_n(&y);
      printf("y increment finished\n");
    }
    else {
      wait(&status);
      printf("x: %d, y: %d\n", x, y);
    }
            
    return 1;
}
