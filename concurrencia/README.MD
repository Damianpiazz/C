# LIBRERIAS

- #include <unistd.h>
Proporciona acceso a funciones y constantes del sistema operativo Unix.

    - Lectura y escritura de archivos: read(), write()
    - Gestión de procesos: fork(), exec(), getpid()
    - Control de dispositivos: open(), close()
    - Manipulación de directorios: chdir(), getcwd()
    - Uso de identificadores de usuario y grupo: getuid(), getgip()

# EXPLICACION

## int pid = fork();
Creación de un Proceso Hijo: La función fork() crea un nuevo proceso llamado "proceso hijo". El proceso que llama a fork() se conoce como "proceso padre".

   - Valor de Retorno: fork() devuelve un valor entero que puede tener tres significados diferentes:

   - En el Proceso Padre: Devuelve el PID (Identificador de Proceso) del proceso hijo. Esto permite al proceso padre identificar y gestionar el proceso hijo.
        
   - En el Proceso Hijo: Devuelve 0. Esto indica que este es el proceso hijo que fue creado.
    
   - Error: Si ocurre un error al intentar crear el proceso (por ejemplo, si se ha alcanzado el límite de procesos), fork() devuelve -1.

## getpid();
Obtener el identificador del proceso actual.

   - Retorno: Cuando se llama a getpid(), devuelve un valor de tipo pid_t que representa el PID del proceso que está ejecutando la llamada. Este valor es un número entero único asignado a cada proceso por el sistema operativo.

   - Uso Común: getpid() se utiliza a menudo para identificar el proceso actual, especialmente en situaciones donde un programa crea múltiples procesos (por ejemplo, usando fork()). Es útil para la depuración, para mostrar información sobre el proceso en los registros, o para manejar lógica que depende del identificador del proceso.

## getppid();
Obtener el identificador del proceso padre del proceso actual.

   - Retorno: Cuando se llama a getppid(), devuelve un valor de tipo pid_t que representa el PID del proceso padre del proceso que está ejecutando la llamada. Esto es útil para saber quién creó el proceso actual.

   - Uso Común: getppid() se usa frecuentemente en programas que crean procesos hijos (por ejemplo, utilizando fork()). Permite a un proceso hijo conocer el identificador de su proceso padre, lo cual puede ser útil para registros, depuración o lógica de control en la ejecución.

## exit(0);
Finalización de un Proceso: Cuando un proceso llama a exit(0), se finaliza inmediatamente. Este proceso puede ser un proceso padre o hijo.

   - Código de Salida: El argumento pasado a exit(), como 0, indica el estado de finalización del proceso:

    - 0: Indica que el proceso ha terminado con éxito.
    - Cualquier valor distinto de 0: Indica que el proceso ha terminado debido a un error o condición excepcional. Esto permite a otros procesos o al sistema operativo conocer el resultado de la ejecución.

## exit(EXIT_FAILURE);
Cierra el proceso que fallo.

## perror("Error al crear el proceso H1");
Imprimir un mensaje de error que describe por qué una operación falló, basado en el valor actual de la variable global errno

## system("./script.sh");
Se utiliza para ejecutar un comando del sistema operativo desde un programa.

   - Cuando se llama a system(), el programa actual crea un nuevo proceso para ejecutar el comando especificado. Este proceso se ejecuta en el shell del sistema (como Bash en Linux).

   - Retorno: La función system() devuelve un valor entero: Si el comando se ejecuta correctamente, el valor devuelto es el código de salida del shell.
   Si hay un error al intentar ejecutar el comando (por ejemplo, si el comando no existe), el valor devuelto será un número negativo.

   - Bloqueo: La función system() bloquea la ejecución del programa original hasta que el comando especificado haya terminado de ejecutarse.

## execl("/bin/ls", "ls", NULL);
Reemplazar el proceso actual con un nuevo programa. En este caso, está ejecutando el comando ls, que lista el contenido de un directorio.

   - Argumentos:

   - path (Primero): La ruta completa del programa que deseas ejecutar. En este caso, "/bin/ls" es la ruta al ejecutable del comando ls.

   - arg0 (Segundo): El primer argumento es el nombre del programa tal como se verá en el proceso (usualmente se le pasa el mismo nombre del ejecutable).

   - ... (Tercero):  Puedes pasar una lista de argumentos adicionales que se le envían al programa. Cada argumento debe estar separado por comas.

   - NULL: Se debe finalizar la lista de argumentos con NULL para indicar el final.

   - **Comportamiento**

   - Reemplazo de Proceso: Cuando se llama a execl(), el proceso actual es reemplazado por el nuevo proceso que se está ejecutando. Esto significa que el código que sigue a la llamada a execl() no se ejecutará a menos que execl() falle.

   - No Retorno en Éxito: Si execl() se ejecuta correctamente, no devuelve al proceso original. Si hay un error (por ejemplo, si el archivo no existe), devuelve -1 y se puede usar errno para obtener el motivo del fallo.

## wait(NULL);
Se utiliza para que un proceso padre espere a que uno de sus procesos hijos termine su ejecución.

   - Argumentos:

   - status: Es un puntero a un entero que, si se proporciona, puede ser utilizado para almacenar el estado de terminación del proceso hijo. Al pasar NULL, simplemente indicas que no te interesa este estado.

   - Esperar un Hijo: Cuando el proceso padre llama a wait(NULL);, se bloquea y espera hasta que uno de sus procesos hijos termine. Si hay varios hijos, se puede esperar a que cualquiera de ellos termine.

   - Recuperación del PID: La función wait() devuelve el PID del hijo que terminó. Si no hay hijos que esperar (por ejemplo, si todos ya han terminado), wait() puede devolver -1 y establecer errno a ECHILD.

   - Uso del Estado: Si deseas saber cómo terminó el hijo (por ejemplo, si terminó con éxito o si hubo un error), puedes usar el puntero status para obtener esta información.

   - **Consideraciones**

   - Bloqueo: wait() bloqueará al proceso padre hasta que el hijo termine, lo que puede ser importante en situaciones donde el padre necesita esperar resultados o asegurarse de que un hijo haya completado su tarea.

   - Múltiples Hijos: Si hay múltiples hijos y deseas esperar a todos ellos, puedes usar wait() en un bucle o considerar waitpid() con el PID de cada hijo.