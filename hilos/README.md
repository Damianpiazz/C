# LIBRERIAS

- #include <unistd.h>
Proporciona acceso a funciones y constantes del sistema operativo Unix.

    - Lectura y escritura de archivos: read(), write()
    - Gestión de procesos: fork(), exec(), getpid()
    - Control de dispositivos: open(), close()
    - Manipulación de directorios: chdir(), getcwd()
    - Uso de identificadores de usuario y grupo: getuid(), getgip()

- #include <pthread.h>
Proporciona una interfaz para trabajar con hilos (threads) en programas que utilizan la programación concurrente. Permite crear y gestionar múltiples hilos dentro de un proceso, facilitando la ejecución paralela de tareas.

    - Creación y terminación de hilos:

        - pthread_create(): crea un nuevo hilo.
        - pthread_exit(): termina el hilo que lo llama.

    - Sincronización:

        - pthread_join(): espera a que un hilo termine.
        - pthread_mutex_lock() y pthread_mutex_unlock(): gestionan el acceso a recursos compartidos mediante mutexes.
        - pthread_cond_wait() y pthread_cond_signal(): permiten la sincronización basada en condiciones.

    - Atributos de hilos:

        - pthread_attr_init(), pthread_attr_setdetachstate(): para establecer atributos específicos de los hilos, como el estado de separación (joinable o detached).

- #include <semaphore.h>
Proporciona funciones para trabajar con semáforos, que son herramientas de sincronización utilizadas para controlar el acceso a recursos compartidos en entornos concurrentes.

    - Inicialización y destrucción de semáforos:

        - sem_init(): inicializa un semáforo.
        - sem_destroy(): destruye un semáforo.

    - Operaciones sobre semáforos:

        - sem_wait(): decrementa el valor del semáforo; si el valor es cero, el hilo se bloquea hasta que el semáforo sea mayor que cero.
        - sem_post(): incrementa el valor del semáforo, liberando a cualquier hilo bloqueado si el valor era cero.

    - Funciones de consulta:

        - sem_getvalue(): obtiene el valor actual del semáforo.
        
#   EXPLICACION

## sem_t sem; 
sem_t es un tipo de dato definido en la biblioteca de semáforos POSIX (usualmente en <semaphore.h>). Este tipo se utiliza para declarar semáforos, que son mecanismos de sincronización que permiten controlar el acceso a recursos compartidos en programas concurrentes o multihilo.
> sem_t se usa para semáforos.

## pthread_t hilo1, hilo2;  
pthread_t es un tipo de dato utilizado para representar identificadores de hilos en la biblioteca POSIX de hilos (generalmente en <pthread.h>). Los objetos de tipo pthread_t se utilizan para crear y manejar hilos en un programa que usa la programación multihilo.
> pthread_t se usa para identificadores de hilos.

## static void *function_hilo_1();
La declaración static void *funcion() indica que la función funcion es de tipo void *, lo que significa que devuelve un puntero genérico a cualquier tipo de dato. 
En resumen, static void *funcion() define una función que puede ser utilizada únicamente dentro de su archivo de origen y que devuelve un puntero que puede ser convertido a cualquier otro tipo de puntero según sea necesario.

    Explico cada parte:

    - static: Este calificativo significa que la función tiene un enlace interno, lo que implica que solo es accesible dentro del archivo donde está definida. No puede ser llamada desde otros archivos.

    - void *: Este es el tipo de retorno de la función. Un puntero void * puede apuntar a cualquier tipo de dato, pero no se puede desreferenciar directamente sin hacer una conversión (casting) a otro tipo de puntero.

    function_hilo_1(): Es el nombre de la función y los paréntesis indican que no toma argumentos.


## pthread_create(&hilo1, NULL, *function_hilo_1, NULL);

    - Desglose de los parámetros:

        - &hilo1 y &hilo2: Se pasan como punteros a pthread_t, que son los identificadores de los hilos que se están creando. Esto permite a pthread_create almacenar el ID del hilo recién creado en estas variables.

        - NULL (segundo argumento): Este es el atributo del hilo. Al pasar NULL, se utiliza el conjunto de atributos predeterminado para el hilo.

        - *function_hilo_1 y *function_hilo_2: Es la dirección de la función que se va a ejecutar en el nuevo hilo.

        - NULL (cuarto argumento): Este es el argumento que se pasa a la función del hilo. Si no necesitas pasar nada, puedes usar NULL.

## sem_init(&sem, 0, 0);
Se utiliza para inicializar un semáforo en programación concurrente.

    - Parametros:

        - sem_t *sem (Primero);: Este es un puntero al semáforo que se va a inicializar. Debe haber sido declarado previamente, y se le pasará la dirección de la variable semáforo.

        - int pshared (Segundo): Si se establece en 0, el semaforo sera utilizado solo por los hilos del mismo proceso.
        Si se establece en 1, el semaforo puede ser compartido entre procesos difenrentes

        - unsigned int value (Tercero): Si se establece en cero significa que el semaforo estara inicialmente bloqueado, y cualquier hilo que intente realizar una operacion que dependa del semaforo debera esperar hasta que sea liberado.
        Si se establece mayor que cero indica la cantidad de recursos disponibles y permite que ese numeros de hilos acceda al recurso sin esperar.

## pthread_join(hilo1, NULL);
Se utiliza en programación multihilo para esperar a que un hilo específico termine su ejecución.

    - Parametros:

        - hilo1 (Primero): Este es el identificador del hilo que deseas esperar.

        - void **retval (Segundo): Este es un puntero a un puntero void donde se puede almacenar el valor de retorno del hilo una vez que haya terminado. Si no necesitas este valor, puedes pasar NULL.

## sem_wait(&sem);
Se utiliza para decrementar el valor de un semáforo y, potencialmente, bloquear el hilo que la llama si el valor del semáforo es cero.
El valor del semáforo sem se decrementa en uno. Si el valor del semáforo es mayor que cero antes de la llamada, la operación se completa y el hilo continúa su ejecución.
Bloqueo: Si el valor del semáforo es cero, la llamada a sem_wait hará que el hilo se bloquee y espere hasta que el semáforo sea incrementado

    - Parametros 

    - &sem: Este es un puntero al semáforo que se va a decrementar. Cuando llamas a sem_wait(&sem);, 

## sem_post(&sem);
Se utiliza para incrementar el valor de un semáforo y, potencialmente, liberar a un hilo que está esperando en sem_wait.
Incremento del Semáforo: Cuando llamas a sem_post(&sem);, el valor del semáforo sem se incrementa en uno. Esto puede permitir que un hilo que está bloqueado en sem_wait continúe su ejecución.
Liberación de Hilos: Si hay hilos que están esperando (bloqueados) en sem_wait debido a que el semáforo tenía un valor de cero, al ejecutar sem_post, uno de esos hilos se desbloqueará y podrá proceder.

    - Parametros

    - &sem: Este es un puntero al semáforo que se va a incrementar.