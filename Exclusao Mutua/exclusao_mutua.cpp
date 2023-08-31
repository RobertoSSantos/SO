// Team: Alexandre Del Raso, Pedro Martins, Roberto Santos
# include <stdio.h>
# include <windows.h>

int global_var = 0;

void subtraction();

int main(){
    //subtraction();
    printf("%d\n", global_var);

    return 0;
}

void subtraction(){
    int local_var = global_var;
    local_var--;
    Sleep(100);
    global_var = local_var;
}

void addition(){
    int local_var = global_var;
    local_var++;
    Sleep(100);
    global_var = local_var;
}