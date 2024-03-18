#include <stdio.h>

int main() {

    char sentence[] = "HE45L32LO458T6H359ISIS1BO589RNT34ODEVN80AJA";

    int sum = 0, i;

    for (i = 0; sentence[i] != '\0'; ++i) {
        if (sentence[i] >= '0' && sentence[i] <= '9'){
            sum += sentence[i] - '0';
        }
    }

    if (sum < 1000) {
      printf("You can use the code %04d to press the ATM card code\n", sum);
      
    } else {
        printf("sum equal to %d\n", sum);
    }

    return 0;
}