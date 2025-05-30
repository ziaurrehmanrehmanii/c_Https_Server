#include <stdio.h>

int main()
{
    printf("Enter the number for the Table you want");
    int num;
    scanf("%d", &num);
    int even_or_odoo = num % 2;
    int sum_of_n;
    for (int i = 1; i <= num; i++)
    {
        sum_of_n += i;
    }
    printf("The sum of n is %d\n", sum_of_n);

    (!even_or_odoo)
        ? printf("The number %d is even.\n", num)
        : printf("The number %d is odd.\n", num);

    for (int i = 1; i <= 10; i++)
    {
        int result = i * num;
        printf("%d * %d ==  %d  \n", num, i, result);
    }

    // Print a message to indicate successful execution
    printf("Example function executed successfully.\n");

    return 0;
}
