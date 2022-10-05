#include <stdio.h>

#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"

int main(void)
{
    for (int i = 1; i <= 5; i++)
    {
        printf(COLOR_BOLD "Md.Mehedi hasan\n" COLOR_OFF);
    }
    printf("\033[1;36m Md.Mehedi hasan\n");

    return 0;
}