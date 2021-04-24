/* 


*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define MAXIMA 100
#define CANT_TAREAS 50

typedef enum
{
   false,
   true
} bool;

struct Tarea
{
   int numeroTarea;
   char detalles[MAXIMA];
   double ejecucion;
   bool terminada;
};

struct Tarea tareas[CANT_TAREAS];

bool programa(char *tarea)
{
   printf("-----The program is running-----\n");
   int init_size = strlen(tarea);
   char delim[] = " ";
   char *token = strtok(tarea, delim);
   // clock_t start, end;
   // double taskTime;
   // start = clock();
   if (init_size == 5)
   {
      int num1, num2, cont = 0;
      char operacion;

      while (token != NULL)
      {
         if (cont == 0)
            num1 = atoi(token);
         else if (cont == 1)
            operacion = *token;
         else if (cont == 2)
            num2 = atoi(token);
         cont++;
         token = strtok(NULL, delim);
      }

      int division_por_cero = 0;
      int operacion_valida = 1;
      double resultado;
      switch (operacion)
      {
      case '+':
         resultado = num1 + num2;
         break;
      case '-':
         resultado = num1 - num2;
         break;
      case '*':
         resultado = num1 * num2;
         break;
      case '/':
         if (num2 == 0)
            division_por_cero = 1;
         else
         {
            resultado = num1 / num2;
         }
         break;
      default:
         operacion_valida = 0;
         printf("La operación no es válida\n");
      }
      if (operacion_valida)
         if (division_por_cero)
         {
            printf("No se puede dividir entre cero\n");
            return false;
         }
         else
         {
            printf("El resultado es: %.2f\n", resultado);
            return true;
         }
   }
   else
   {
      while (token != NULL)
      {
         printf("'%s'\n", token);
         token = strtok(NULL, delim);
      }
      return true;
   }
   printf("Se cayo aqui\n");
   // end = clock();
   // taskTime = ((double) (end - start)) / CLOCKS_PER_SEC;
   // if (taskTime > 300){
   //    printf("'%s'\n", "La tarea tardo mas de 5 minutos");
   // }
}

bool boxMM(int N, int *i, double difficulty, char *tarea)
{
   pid_t variable;

   variable = fork();

   if (variable < 0)
   {
      fprintf(stderr, "Mr Meeseeks has fucking die!");
   }
   else if (variable == 0)
   { // proceso hijo
      printf("Hi I'm Mr Meeseeks hijo! Look at Meeeee. pid:%d, pidd:%d, N:%d, i:%d\n", getpid(), getppid(), N + 1, *i);
      sleep(1);
      pid_t extra;
      // bool resultado = programa(tarea);
      if (1 < difficulty && difficulty <= 85)
      {
         int cantidadMeeseeks = 0;
         if (difficulty > 45)
            cantidadMeeseeks = 3;
         else
            cantidadMeeseeks = 20;
         for (int j = 1; j < cantidadMeeseeks; j++)
         {
            *i += 1;
            extra = fork();
            if (extra == 0)
            {
               printf("Hi I'm Mr Meeseeks! extra Look at Meeeee. pid:%d, pidd:%d, N:%d, i:%d\n", getpid(), getppid(), N + 2, *i);
               // bool resultado = programa(tarea);
               exit(0);
            }
         }
         for (int j = 1; j < cantidadMeeseeks; j++)
         {
            wait(NULL);
         }
      }
      exit(0);
   }
   else
   { // proceso padre
      printf("---------------------------------------\n");
      *i += 1;
      printf("Hi I'm Mr Meeseeks! Look at Meeeee. pid:%d, pidd:%d, N:%d, i:%d\n", getpid(), getppid(), N, *i);
      waitpid(variable, NULL, 0);
   }
   return true;
}

int main()
{
   clock_t timer;

   srand(time(0));

   char MMTAsk[MAXIMA];             // "String" donde se guarda la tarea
   int dType, decision, actualTAsk; // El tipo de dificultad y si continuar con otra tarea
   double difficulty;               // Valor de la dificultad
   bool estado = false;             // Booleano que indicara si se completo un Task
   int N = 1;                       // Niveles
   int instancias = 0;              // Instancias de Meeseeks
   int *i = &instancias;
   int contadorT, completadas = 0;  // Contador de las Tasks, Tareas Completadas

   char *p;                         // Quitar saltos de linea en el Task
   int c;                           // Quitar saltos de linea en el Task

   do
   {
      tareas[contadorT].numeroTarea = contadorT + 1;
      printf("-----Enter a task for Mr. Meeseeks-----\n"); 

      fgets(MMTAsk, MAXIMA, stdin);
      if ((p = strchr(MMTAsk, '\n')) != NULL)
         *p = '\0';
      strcpy(tareas[contadorT].detalles, MMTAsk);

      do
      {
         printf("-----Enter type of difficulty of the task 1.Selected/2.Random-----\n");
         scanf("%d", &dType);
      } while (dType != 1 && dType != 2);

      if (dType == 1)
      {
         do
         {
            printf("-----Select a value for the difficulty, 0 = Imposible until 100 = Easy-----\n");
            scanf("%lf", &difficulty);
         } while (difficulty < 0 || difficulty > 100);
      }
      else
      {
         difficulty = ((float)rand() / (float)(RAND_MAX)) * 100;
         printf("-----The difficulty is: %lf-----\n", difficulty);
      }

      do
      {
         timer = clock();
         //estado = programa(MMTAsk);
         estado = boxMM(N, i, difficulty, MMTAsk);
         timer = clock() - timer;
         double time_taken = ((double)timer) / CLOCKS_PER_SEC;
         tareas[contadorT].ejecucion = time_taken;
         tareas[contadorT].terminada = estado;
      } while (estado == false);

      do
      {
         printf("-----Wanna continue? 1.Yes/0.No-----\n");
         scanf("%d", &decision);
      } while (decision != 1 && decision != 0);

      contadorT++;
      while ((c = getchar()) != '\n' && c != EOF);
   } while (decision);

   printf("-----Datos de la Tarea-----\n");
   printf("Cantidad de Tareas Solicitadas: %d\n", contadorT);
   printf("---------------------------\n");
   for (int i = 0; i < contadorT; i++)
   {
      struct Tarea tareaActual = tareas[i];
      printf("Numero de la Tarea: %d\n", tareaActual.numeroTarea);
      printf("Detalle de la Tarea: %s\n", tareaActual.detalles);
      printf("Tiempo de Ejecucion de la Tarea: %lf\n", tareaActual.ejecucion);
      if (tareaActual.terminada)
      {
         printf("Estado de la Tarea: Completa\n");
         completadas += 1;
      }
      else
      {
         printf("Estado de la Tarea: Incompleta\n");
      }
      printf("---------------------------\n");
      // fputs(tareaActual.terminada ? "true\n" : "false\n", stdout);
   }

   printf("Tareas Terminadas: %d\n", completadas);
   printf("---------------------------\n");
   printf("Tareas Sin Terminar: %d\n", contadorT - completadas);
   printf("---------------------------\n");

   return 0;
}