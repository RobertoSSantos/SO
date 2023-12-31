// Team: Alexandre Del Raso, Pedro Martins, Roberto Santos 
# include <stdio.h>
# include <windows.h>
//Define o numero maximo de threads
#define THREADCOUNT 100

// Funcao global de Referencia
int global_var = 0;

// Handle do mutex
HANDLE mutex;

void subtraction();
void addition();

int main(){

    HANDLE aThread[THREADCOUNT];
    HANDLE sThread[THREADCOUNT];
    
    // Criando o Mutex
    mutex = CreateMutex(NULL, FALSE, NULL);

    if (mutex == NULL) {
        printf("CreateMutex error");
        return 1;
    }

    // Criando as threads
    for(int i = 0; i < THREADCOUNT; i++){
        aThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)subtraction, NULL, 0, NULL);
        sThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)addition, NULL, 0, NULL);

        if( aThread[i] == NULL || sThread[i] == NULL ) {
            printf("CreateThread error");
            return 1;
        }
    }

    Sleep(5000);
    CloseHandle(mutex);

    printf("Final var: %d\n", global_var);

    return 0;
}

void subtraction(){
    DWORD waitResult;

    waitResult = WaitForSingleObject(mutex, INFINITE);

    switch (waitResult) {
        // Thread fez o lock e executa o codigo
        case WAIT_OBJECT_0:{
            int local_var;
            local_var = global_var;
            local_var--;
            Sleep(1);
            global_var = local_var;
            printf("Global var: %d\n", global_var);
            
            // Unlock do mutex
            if (! ReleaseMutex(mutex)) {
                printf("ReleaseMutex error on subtraction");
            }
            break;
        }
        
        case WAIT_ABANDONED:{
            printf("WaitForSingleObject error on subtraction");
            break;
        }
    }
}

void addition(){
    DWORD  waitResult;
    
// Pede o controle do mutex
    waitResult = WaitForSingleObject(mutex, INFINITE);

    switch (waitResult) {
        // Thread fez o lock e executa o codigo
        case WAIT_OBJECT_0:{
            int local_var;
            local_var = global_var;
            local_var++;
            Sleep(1);
            global_var = local_var;
            printf("Global var: %d\n", global_var);

            // Unlock do mutex
            if (! ReleaseMutex(mutex)) {
                printf("ReleaseMutex error on addition");
            }
            break;
        }
        
        case WAIT_ABANDONED:{
            printf("WaitForSingleObject error on addition");
            break;
        }
    }
}