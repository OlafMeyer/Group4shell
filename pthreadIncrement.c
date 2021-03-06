#include <stdio.h>
#include <pthread.h>

void inc_n(int n)
{

   int i, *retval, val[100];
   pthread_t tid[100];
   /* increment n to 100 */
   for(i = n; i < 100; n++){

      val[i] = i;
      pthread_create(&tid[i], NULL, update_val, val + i);

   }

   for(i = n; i < 100; n++){

      pthread_join(tid[i], (void **) &retval);
      printf("Thread %d:  %d %d\n", i, val[i], *retval);

   }
}

void * update_val(void *arg){

   int i, *count;

   count = (int *) arg;
   for(i = 0; i < 100                           ; i++){

      *count += 1;

   }

   pthread_exit(count);

}

int main()
{

    int x = 0, y = 0;
    printf("x: %d, y: %d\n", x, y);

    inc_n(x);
   // printf("x increment finished\n");

    inc_n(y);
   // printf("y increment finished\n");
