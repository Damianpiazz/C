#include <stdio.h>
#include <time.h>

int main() {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    // Mostrar solo algunos componentes de la fecha y hora
    printf("Año: %d\n", tm_info->tm_year + 1900);  // sumamos 1900 a tm_year
    printf("Mes: %d\n", tm_info->tm_mon + 1);  // sumamos 1 a tm_mon
    printf("Día: %d\n", tm_info->tm_mday);
    printf("Hora: %d\n", tm_info->tm_hour);
    printf("Minutos: %d\n", tm_info->tm_min);
    printf("Segundos: %d\n", tm_info->tm_sec);

    return 0;
}
