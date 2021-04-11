/* 


*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define MAXIMA_LONGITUD_CADENA 100
#define CANT_TAREAS 50

typedef enum
{
   false,
   true
} bool;

// typedef struct
// {
//    int numeroTarea;
//    char detalles[100];
//    double ejecucion;
//    bool terminada;
// }Tarea;

struct Tarea
{
   int numeroTarea;
   char detalles[MAXIMA_LONGITUD_CADENA];
   double ejecucion;
   bool terminada;
};

struct Tarea tareas[CANT_TAREAS];

void boxMM(int N, int i)
{
   pid_t variable;

   variable = fork();

   if (variable < 0)
   {
      fprintf(stderr, "Mr Meeseeks has fucking die!");
   }
   else if (variable == 0)
   { // proceso hijo
      printf("Proceso Hijo: pid:%d, pidd:%d\n", getpid(), getppid());
      sleep(1);
   }
   else
   { // proceso padre
      printf("---------------------------------------\n");
      printf("Hi I'm Mr Meeseeks! Look at Meeeee. pid:%d, pidd:%d, N:%d, i:%d\n", getpid(), getppid(), N, i);
      // if (hijos > 0)
      // {
      //    boxMM(hijos - 1);
      // }
      waitpid(variable, NULL, 0);
   }
}

int main()
{
   time_t initial_time = time(NULL);
   float time_limit = 500.0f;
   srand(time(0));

   char MMTAsk[MAXIMA_LONGITUD_CADENA];
   int dType;
   float difficulty;
   int decision;
   int actualTAsk = 0;

   // tareas[0].numeroTarea = 1;
   // strcpy(tareas[0].detalles, "Quiero un café francés");
   // tareas[0].ejecucion = 86.5;
   // tareas[0].terminada = true;

   // tareas[1].numeroTarea = 2;
   // strcpy(tareas[1].detalles, "Realizar un cálculo");
   // tareas[1].ejecucion = 46.5;
   // tareas[1].terminada = false;

   // int i;
   // for (i = 0; i < CANT_TAREAS; i++)
   // {
   //    struct Tarea tareaActual = tareas[i];
   //    if (tareaActual.numeroTarea != 0)
   //    {
   //       printf("Numero tarea: %d. Detalle: %s. Ejecucion: %lf\n", tareaActual.numeroTarea, tareaActual.detalles, tareaActual.ejecucion);
   //       fputs(tareaActual.terminada ? "true\n" : "false\n", stdout);
   //    }
   // }

   do
   {
      printf("----------Enter a task for Mr. Meeseeks----------");
      scanf("%s", &MMTAsk);

      do
      {
         printf("----------Enter type of difficulty of the task 1.Selected/2.Random----------");
         scanf("%d", &dType);
      } while (dType != 1 || dType != 2);

      if (dType == 1)
      {
         do
         {
            printf("----------Select a value for the difficulty, 0 = Imposible until 100 = Easy----------");
            scanf("%lf", &difficulty);
         } while (difficulty >= 0 || difficulty <= 100);
      }
      else
      {
         difficulty = ((float)rand() / (float)(RAND_MAX)) * 100;
         printf("----------The difficulty is: %lf----------", difficulty);
      }

      do
      {
         boxMM(difficulty, 5);
      } while ((time(NULL) - initial_time) < time_limit);

      do
      {
         printf("----------Wanna continue? 1.Yes/0.No----------");
         scanf("%d", &decision);
      } while (decision == 1 || decision == 0);
   } while (decision);

   // printf("Cantidad de Tares Solicitadas: %d\n", contar);
   // printf("Tiempo de Duracion: %d\n", contar); // hay que hacer por tarea
   // printf("Tareas Terminadas: %d\n", contar);
   // printf("Tareas Sin Terminar: %d\n", contar);

   return 0;
}