#include "Atom.h"

int    main(void)
{
    char    *input;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input || ft_strncmp(input, "exit", ft_strlen(input)) == 0)
        {
            printf("\nBye!\n");
            break ;
        }
        if (*input) // si la ligne n’est pas vide
            add_history(input);
        printf("Vous avez tapé : %s\n", input);
        free(input);
    }
    rl_clear_history();
    return (0);
}