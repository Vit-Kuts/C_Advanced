#include <stdio.h>

int main()
{
    int N;
    char ch;

    scanf("%d", &N);

    while (1)
    {
        scanf("%c", &ch);

        if (ch == '.')
        {
            printf(".");
            break;
        }

        if (ch >= 'a' && ch <= 'z')
        {
            ch = 'a' + (ch - 'a' + N) % 26;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = 'A' + (ch - 'A' + N) % 26;
        }

        printf("%c", ch);
    }

    return 0;
}