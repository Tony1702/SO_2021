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

struct Tarea
{
   int numeroTarea;
   char detalles[MAXIMA_LONGITUD_CADENA];
   double ejecucion;
   bool terminada;
};

struct Tarea tareas[CANT_TAREAS];

void boxMM(int N, int * i, double difficulty)
{
   pid_t variable;
   
   variable = fork();
   // printf("%f \n", difficulty);
   if (variable < 0)
   {
      fprintf(stderr, "Mr Meeseeks has fucking die!");
   }
   else if (variable == 0)
   { // proceso hijo
      printf("Hi I'm Mr Meeseeks hijo! Look at Meeeee. pid:%d, pidd:%d, N:%d, i:%d\n", getpid(), getppid(), N+1, *i);
      sleep(1);
      pid_t extra;
      if (1<difficulty && difficulty<=85){
         int cantidadMeeseeks = 0;
         if (difficulty>45)
            cantidadMeeseeks = 3;
         else
            cantidadMeeseeks = 20;
         for (int j=1; j<cantidadMeeseeks; j++){
            *i++;
            extra = fork();
            if (extra == 0){
               printf("Hi I'm Mr Meeseeks! extra Look at Meeeee. pid:%d, pidd:%d, N:%d, i:%d\n", getpid(), getppid(), N+2, *i);
               exit(0);
            }
         }
         for (int j=1; j<cantidadMeeseeks; j++){
            wait(NULL);
         }
   }
      }
      
   else
   { // proceso padre
      printf("---------------------------------------\n");
      *i++;
      printf("Hi I'm Mr Meeseeks! Look at Meeeee. pid:%d, pidd:%d, N:%d, i:%d\n", getpid(), getppid(), N, *i);
      // if (hijos > 0)
      // {
      //    boxMM(hijos - 1);
      // }
      waitpid(variable, NULL, 0);
   }
}

bool programa(char *tarea)
{
   printf("-----The program is running-----\n");
   int init_size = strlen(tarea);
   char delim[] = " ";

   char *token = strtok(tarea, delim);

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
}

int main()
{
   time_t endwait;
   time_t start = time(NULL);
   time_t seconds = 300; // 5 minutos

   srand(time(0));

   char MMTAsk[MAXIMA_LONGITUD_CADENA];
   int dType, decision, actualTAsk;
   double difficulty;
   bool estado = false;
   int N = 1;
   int i = 0;
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
      printf("-----Enter a task for Mr. Meeseeks-----\n");
      scanf("%[^\n]s", MMTAsk);

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
         endwait = start + seconds;
         estado = programa(MMTAsk);
         boxMM(N, &i, difficulty);
      } while (start < endwait && estado == false);

      do
      {
         printf("-----Wanna continue? 1.Yes/0.No-----\n");
         scanf("%d", &decision);
      } while (decision != 1 && decision != 0);
   } while (decision);

   // printf("Cantidad de Tares Solicitadas: %d\n", contar);
   // printf("Tiempo de Duracion: %d\n", contar); // hay que hacer por tarea
   // printf("Tareas Terminadas: %d\n", contar);
   // printf("Tareas Sin Terminar: %d\n", contar);

   return 0;
}