#include <stdio.h>

int main() {

    // Declare and configure sentences
    char sentence[] = "HE45L32LO458T6H359ISIS1BO589RNT34ODEVN80AJA";

    // Declare a variable to hold the total.
    int sum = 0;

    // loop to add numbers together
    for (int i = 0; sentence[i] != '\0'; ++i) {
        if (sentence[i] >= '0' && sentence[i] <= '9'){
            sum += sentence[i] - '0';
        }
    }

    // check the digits of the sum
    if (sum < 1000) {

      // add 0 in front  
      printf("You can use the code %04d to press the ATM card code\n", sum);
      
    } else {

        // Display the resulting code.
        printf("sum equal to %d\n", sum);
    }

    return 0;
}