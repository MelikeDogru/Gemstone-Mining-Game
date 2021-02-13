#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

//Global variables
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

int Result = 0;

void *readingFile(void *var)
{
   int t = (int)var;
   long threadID = (int unsigned long)pthread_self();

   printf("\nA new thread has been created with TID: %lu", threadID);

   int summation = 0;

   //Read file
   char fileName[100] = "buckets/";
   char str[20];
   sprintf(str, "%d", t);
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
        // printf("\n%s\n", line);
      }
   }

   //Search for characters
   for (int i = 0; line[i] != '\0'; ++i)
   {
      if (i != 0 && i % 24 == 0)
      { //sleep thread
         int num = rand() % 201;
         num = num + 500;
         float msec = num / 1000;
         sleep(msec);
         printf("\n[TID:%lu] Tired. Going to sleep for %dmsec.", threadID, num);
      }
      if (chDiamond == line[i])
      {
         ++countDiamond;
         summation = summation + diamond;
         printf("\n[TID:%lu] Found %d. Diamond.", threadID, countDiamond);
      }
      if (chRuby == line[i])
      {
         ++countRuby;
         summation = summation + ruby;
         printf("\n[TID:%lu] Found %d. Ruby.", threadID, countRuby);
      }
      if (chSapphire == line[i])
      {
         ++countSapphire;
         summation = summation + sapphire;
         printf("\n[TID:%lu] Found %d. Sapphire.", threadID, countSapphire);
      }
      if (chEmerald == line[i])
      {
         ++countEmerald;
         summation = summation + emerald;
         printf("\n[TID:%lu] Found %d. Emerald.", threadID, countEmerald);
      }
   }
   //printf("\n[TID:%lu] Summation %d.", threadID, summation);
   Result = Result + summation;
}

int main()
{
   int N = 5;
   pthread_t threadsArray[N];
   int reportArray[5];

   //Create threads
   for (int i = 0; i < N; i++)
   {
      reportArray[i] = pthread_create(&threadsArray[i], NULL, readingFile, (void *)i);
   }

   for (int i = 0; i < N; i++)
   {
      pthread_join(threadsArray[i], NULL);
   }

   printf("\nResult %d\n", Result);
   return 0;
}