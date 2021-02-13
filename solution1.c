#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

static int *Result;

int main()
{
   Result = mmap(NULL, sizeof *Result, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
   *Result = 0;
   pid_t wpid;
   int status = 0;

   int a = 0;
   a++;
   a--;
   int N = 5;

   int diamond = 3500;
   int ruby = 50;
   int sapphire = 1200;
   int emerald = 800;

   char chDiamond = 'd';
   char chRuby = 'r';
   char chSapphire = 's';
   char chEmerald = 'e';
   
   int count = 0;
   int countDiamond = 0;
   int countRuby = 0;
   int countSapphire = 0;
   int countEmerald = 0;

   int summationArray[N];

   int total=1;

   //Create N child processes
   for (int i = 0; i < N; i++) // runs N times
   {
      int summation = 0;
      int number = i;
      if (fork() == 0)
      {
         printf("\n[PID:%d] A new child has been created with PID: %d.", getppid(), getpid());

         //Read file
         char fileName[100] = "buckets/";
         char str[20];
         sprintf(str, "%d", number);
         strcat(fileName, str);
         strcat(fileName, ".txt");
         char line[600];

         FILE *f = fopen(fileName, "r");

         if (f == NULL)
         {
            printf("Error reading file\n");
            return 0;
         }
         else
         {
            while (fgets(line, sizeof(line), f))
            {
            //  printf("\n%s\n", line);
            }
         }

         //Search for characters 
         for (int i = 0; line[i] != '\0'; ++i)
         {
            if(i != 0 && i%24 == 0){ //sleep process
               int num = rand() % 201;
               num = num + 500;
               float msec = num/1000;
               sleep(msec);
               printf("\n[PID:%d] Tired. Going to sleep for %dmsec.", getpid(), num);
            }
            if (chDiamond == line[i]){
               ++countDiamond;
               summation = summation + diamond;
               printf("\n[PID:%d] Found %d. Diamond.", getpid(), countDiamond);
            }
            if (chRuby == line[i]){
               ++countRuby;
               summation = summation + ruby;
               printf("\n[PID:%d] Found %d. Ruby.", getpid(), countRuby);
            }
            if (chSapphire == line[i]){
               ++countSapphire;
               summation = summation + sapphire;
               printf("\n[PID:%d] Found %d. Sapphire.", getpid(), countSapphire);
            }
            if (chEmerald == line[i]){
               ++countEmerald;
               summation = summation + emerald;
               printf("\n[PID:%d] Found %d. Emerald.", getpid(), countEmerald);
            }
         }
         
         /*
         printf("\nFrequency of Diamond %c = %d\n", chDiamond, countDiamond);
         printf("Frequency of Ruby %c = %d\n", chRuby, countRuby);
         printf("Frequency of Sapphire %c = %d\n", chSapphire, countSapphire);
         printf("Frequency of Emerald %c = %d\n", chEmerald, countEmerald);*/
         
        summationArray[i] = summation;
        *Result += summationArray[i];         

         exit(0);
      }
    /*  else
      {
         wait(NULL);
         printf("\n[PID:%d] Parent \n", getpid());
         total = total + summationArray[i];
         printf("\nSubtotal %d %d\n", i, total); 
      }   */
   }

   //Parent Process - Get the result 
   while ((wpid = wait(&status)) > 0);
   printf("\n[PID:%d] Result %d\n",getpid(), *Result);
   munmap(Result, sizeof *Result);

   for (int i = 0; i < N; i++){// runs N times
      wait(NULL);
   }
  
   return 0;
}
