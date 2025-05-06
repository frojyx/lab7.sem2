#include "functions.h"

int InputNum()
{
    char str[INT_LIMIT];
    int ind = 0, num;

    while (1)
    {
        str[ind] = _getch();
        str[ind + 1] = '\0';
        num = atoi(str);
        if (str[ind] == ENTER && (ind > 0 || (str[0] == '-' && ind > 1)))
        {
            return num;
        }
        else if (str[ind] == '\b' && ind > 0)
        {
            ind--;
            printf("\b \b");
        }
        else if (myIsDigit(str[ind]) == 1 || (str[ind] == '-' && ind == 0))
        {
            if ((num == 0 && ind > 0) || num == INT_MAX || num == INT_MIN) continue;
            printf("%c", str[ind]);
            ind++;
        }
    }
}

int myIsDigit(char symbol)
{
    return (symbol >= '0' && symbol <= '9');
}
