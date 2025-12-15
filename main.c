#include "technical_test.h"

int error_argc(int argc, char **argv)
{
    fprintf(stderr, "Error: invalid number of arguments 2 expected %i found\n", argc - 1);
    if (argc != 0)
        fprintf(stderr, "usage: %s [total number of threads] [numbers per thread]\n", argv[0]);
    else
        fprintf(stderr, "usage: program [total number of threads] [numbers per thread]\n");
    return ERROR_ARGC;
}

int	is_numeric(char *s)
{
    if (!*s)
        return (0);
    while (isdigit(*s))
        s++;
    if (*s)
    {
        return (0);
    }
    return (1);
}

int is_valid_argument(char *s)
{
    if (!is_numeric(s))
    {
        fprintf(stderr, "Error: invalid of argument: %s is not an unsigned number\n", s);
        return 0;
    }
    if (strlen(s) > 9) // This ensure its an int and having more that 1000000000 numbers per thread or list is unreasonable
    {
        fprintf(stderr, "Error: invalid of argument: %s is too big(it has more than 9 digits)", s);
        return 0;
    }
    return 1;    
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return error_argc(argc, argv);
    if (!is_valid_argument(argv[1]))
        return ERROR_ARGV1;
    if (!is_valid_argument(argv[2]))
        return ERROR_ARGV2;
    return run(atoi(argv[1]), atoi(argv[2]));
}