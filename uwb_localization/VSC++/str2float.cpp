#include <stdio.h>

char distance[9];



int char2int(char x){
    int y;
    if('0' <= x && x <= '9'){
        y = x - '0';
        return y;
    }
    else if ('a' <= x && x <= 'f')
    {
         y = x - 'a' + 10;
            return y;
    }
    return -1;
}

int str2int(char *distance){
    int i, j;
    int y = 0;
    int x = 1;
    char a;
    for(i = 7; i>=0 ;i--){
        a = distance[i];
        j = char2int(a);
        y = y + j * x;
        x = x * 16;
        
    }
    return y;
}

int main(){
    distance[0] = '0';
    distance[1] = '0';
    distance[2] = '0';
    distance[3] = '0';
    distance[4] = '0';
    distance[5] = 'e';
    distance[6] = 'f';
    distance[7] = 'c';
    int x;
    x = str2int(distance);
    printf("\n input : %d \n", x);
}