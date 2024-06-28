#include <stdio.h>

int arrayElements[1000000];
int temporaryArray[1000000];

int main(){
    int numberOfElements, numberOfOperations;
    scanf("%d %d", &numberOfElements, &numberOfOperations);
    
    for(int index = 0; index < numberOfElements; index++) {
        scanf("%d", &arrayElements[index]);
    }
    
    for(int currentOperation = 1; currentOperation <= numberOfOperations; currentOperation *= 2){
        if(currentOperation & numberOfOperations){
            for(int index = 0; index < numberOfElements; index++) {
                temporaryArray[index] = arrayElements[index] ^ arrayElements[(currentOperation + index) % numberOfElements];
            }
            for(int index = 0; index < numberOfElements; index++) {
                arrayElements[index] = temporaryArray[index];
            }
        }
    }
    
    for(int index = 0; index < numberOfElements; index++) {
        printf("%d\n", arrayElements[index]);
    }
}
