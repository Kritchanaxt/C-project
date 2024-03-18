/*Program to print a code donut animation*/

//Header file
#include <stdio.h>
#include <string.h>

//Declare a variable trigonometry
int k;

double sin(),cos();

// Main function
int main() {
    
    // 1.float A = 0, B = 0, i, j, z[1760]; Several variables are declared and initialized here. A and B are initialized to 0, and i, j, z, and b are declared but not explicitly initialized. z is an array of 1760 floating-point numbers, and b is an array of 1760

    // 2.char b[1760]; An array named b of characters is declared, which will presumably be used to store graphical data or character

    // 3.printf("\n1b2J"); This line uses the printf function to print the string "\n1b2J". The character sequence (1b2J) is intended to send some type of control code to the terminal or console to clear the screen. \ n represents a newline character and 1b2J is some type of control sequence. This indicates that the program is interacting with the terminal to produce graphical output.

    float A = 0, B = 0, i, j, z[1760];
    char b[1760];
    printf("\n1b2J"); 

    //which indicates that the subsequent code block will keep running indefinitely
    for (;;) { 

        /*In each iteration of the loop, two memory areas b and z are being initialized.*/
        //memset is used to set consecutive bytes of memory to a specified value. 
        //b is being filled with the value 32  and z is being filled with zeros.
        //of size 1760, and 7040 will be the number of bytes starting in each memory area.
        memset(b, 32, 1760); 
        memset(z, 0, 7040);
        
        //Two nested loops iterate over j and i. These loops are responsible for generating the values ​​used in subsequent calculations. j and i increase by 0.001 and 0.08 with each iteration, respectively, until reaching 6.28.
        for (j = 0; 6.28 > j; j += 0.001) {
            for (i = 0; 6.28 > i; i += 0.08) {

                //Inside the nested loops, a series of calculations are performed involving trigonometric functions (sin and cos). The variables c, d, e, f, g, h, D, l, m, n, and t are being calculated based on the values of i, j, A, and B. The purpose and meaning of these calculations depend on the values of A and B, which are not provided in the snippet.
                float c = sin(i), d = cos (j), e = sin(A), f = sin(j), g = cos(A),
                      h = d + 2, D = 1 / (c * h * e + f * g + 5), l = cos(i),
                      m = cos(B), n = sin(B), t = c * h * g - f * e; 


                // 1.int x = 40 + 30 * D * (l * h * m - t * n); The value of x is calculated from various previously defined variables and constants. Use D, l, h, m and n in this calculation The results involve a weighted combination of these variables.

                // 2.int y = 12 + 15 * D * (l * h * n + t * m);: Similar to x, the value of y is calculated based on a combination of variables, including D, l, h, n, and t

                // 3.int o = x + 80 * y; The calculated x and y values ​​are combined to calculate o. This can be used to determine a position on a 2D grid.

                // 4.int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n); The value of N is calculated using various constants and previously calculated variables. This involves a more complex calculation, and the purpose of this value is not immediately clear without more context.
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y = 12 + 15 * D * (l * h * n + t * m), o = x + 80 * y,
                    N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

                /* 1.if (22 > y && y > 0 && 80 > x && x > 0 && D > z[o]) {: This if statement checks multiple conditions. It's essentially verifying if the calculated coordinates (x and y) are within certain ranges and if D is greater than the value currently stored in the z array at position o.
                - 22 > y && y > 0: This part checks if y is greater than 0 and less than 22.
                - 80 > x && x > 0: This part checks if x is greater than 0 and less than 80.
                - D > z[o]: This part checks if the calculated value D is greater than the value currently stored in the z array at index o.*/

                /* 2.If all of these conditions are met, the code block within the if statement is executed:
                - z[o] = D;: The value at index o in the z array is updated with the value of D.
                - b[o] = ".,-~:;=!*#$@:"[N > 0 ? N : 0];: The value at index o in the b array is updated based on the value of N.The expression ".,-~:;=!*#$@:"[N > 0 ? N : 0] retrieves a character from the string ".,-~:;=!*#$@:". The index for the character is determined by N, but if N is less than or equal to 0, it's replaced with 0 to avoid negative indices.*/    

                //characters from string ".,-~:;=!*#$@:" is used to display different levels of shading or texture in the graphics output.
                if (22 > y && y > 0 && 80 > x && x > 0 && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@:"[N > 0 ? N : 0];
                }
            }
        }

        // 1.printf("\x1b[H");: This line uses the printf function to send a terminal control code (\x1b[H) that positions the cursor at the top-left corner of the terminal or console screen. This is used to clear the screen and prepare for displaying the graphical output.

        /* 2.The loop for (k = 0; 1761 > k; k++) iterates through the graphical data arrays. It looks like there are 1761 iterations, corresponding to the size of the arrays.
        - putchar(k % 80 ? b[k] : 10);: In each iteration, this line uses the putchar function to output characters to the console. The expression k % 80 ? b[k] : 10 checks whether k is not a multiple of 80. If it is, it outputs the character from the b array at index k. If k is a multiple of 80, it outputs the ASCII value 10, which represents a newline character. This effectively prints characters in rows of 80, creating a grid-like structure.*/

        //3.A += 0.04; and B += 0.02;: After the iteration, the values ​​of A and B are incremented by 0.04 and 0.02 respectively. This suggests that these values ​​are updated with each iteration. to get the animation in the generated format
         printf("\x1b[H");
            for (k = 0; 1761 > k; k++)
              putchar(k % 80 ? b[k] : 10);
            A += 0.04;
            B += 0.02;
    }
} 
