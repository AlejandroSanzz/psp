#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/* gestión de señales en proceso padre       */
void manejador( int numsenal )
{
 printf("Hijo recibe señal número..%d\n", numsenal);
 
}
void manejadorh( int numsenalh )
{
 printf("Padre recibe señal número..%d\n", numsenalh);
 
}

int main()
{
  int pid_hijo;  
  pid_hijo = fork(); //creamos hijo   
  int pid_padre;
  pid_padre = getppid();
  switch(pid_hijo)
  {
     case -1:
          printf( "Error al crear el proceso hijo...\n");
          exit( -1 );        
     case 0:   //HIJO     	         
          signal(SIGUSR1, manejador); //Función manejadora de la señal
          pause();
          printf("Voy a enviar el proceso padre %d\n", getppid());
          kill(pid_padre,SIGUSR1);
          pause();
          break;    
     default: //PADRE envia 1 señal
     	  
     	  printf("Soy el proceso %d padre \n", getpid());
          sleep(1);
          signal(SIGUSR1, manejadorh);
          printf("Voy a enviar señal al proceso hijo %d \n", pid_hijo);
          kill(pid_hijo, SIGUSR1);//ENVIA SEÑAL AL HIJO 
          sleep(1);
          
          pause();
          printf("Fin proceso padre \n");
          
          break;
  } 
  return 0;
}
