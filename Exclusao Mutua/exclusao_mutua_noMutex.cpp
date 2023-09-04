// Team: Alexandre Del Raso, Pedro Martins, Roberto Santos
# include <stdio.h>
# include <windows.h>

//Define o numero maximo de threads
#define THREADCOUNT 50

// Funcao global de Referencia
int global_var = 0;

void subtraction();
void addition();

int main() {
    HANDLE aThread[THREADCOUNT];
    HANDLE sThread[THREADCOUNT];

    // Criando as threads
    for(int i = 0; i < THREADCOUNT; i++){
        aThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)addition, NULL, 0, NULL);
        sThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)subtraction, NULL, 0, NULL);

        if( aThread[i] == NULL || sThread[i] == NULL ) {
            printf("CreateThread error");
            return 1;
        }
    }

    // Espera todas as threads terminarem
    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);
    WaitForMultipleObjects(THREADCOUNT, sThread, TRUE, INFINITE);

    printf("Global var: %d\n", global_var);

    // Fechando as threads e mutex
    for(int i = 0; i < THREADCOUNT; i++){
        CloseHandle(aThread[i]);
        CloseHandle(sThread[i]);
    }

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