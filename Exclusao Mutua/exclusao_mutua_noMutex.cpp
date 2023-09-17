// Team: Alexandre Del Raso, Pedro Martins, Roberto Santos
# include <stdio.h>
# include <windows.h>

//Define o numero maximo de threads
#define THREADCOUNT 100

// Funcao global de Referencia
int global_var = 0;

void subtraction();
void addition();

int main() {

    // Criando as threads
    for(int i = 0; i < THREADCOUNT; i++){
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)addition, NULL, 0, NULL);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)subtraction, NULL, 0, NULL);

    }

    Sleep(5000);

    printf("Final var: %d\n", global_var);

    return 0;
}

void subtraction(){
    int local_var;
    local_var = global_var;
    local_var--;
    Sleep(100);
    global_var = local_var;
    printf("Global var: %d\n", global_var);
}

void addition(){
    int local_var;
    local_var = global_var;
    local_var++;
    Sleep(100);
    global_var = local_var;
   printf("Global var: %d\n", global_var);
}