/*
https://www.programiz.com/c-programming/examples/concatenate-string
As you know, the best way to concatenate two strings in C programming is by using the strcat() function. However, in this example, we will concatenate two strings manually.
*/
#include <stdio.h>

/*
generate filename
filename = generate_filename(index);
*/

int main() 
{
    // Create uniqueid array


    char filename[100] = "rec-", extension[] = ".jpeg";
    int i, j;

    // length of filename is stored in i
    for (i = 0; filename[i] != '\0'; ++i) 
    {
        printf("i = %d\n", i);
    }

    // concatenating each character of extension to filename
    for (j = 0; extension[j] != '\0'; ++j, ++i) 
    {
        filename[i] = extension[j];
    }

    // Add null character filename string
    filename[i] = '\0';

    printf("After concatenation: ");
    puts(filename);

    return 0;
    // return filename
}