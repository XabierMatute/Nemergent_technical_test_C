#include "technical_test.h"

void rutine(int numbers, t_list_head *positives, t_list_head *negatives, unsigned int seed)
{
    while(numbers--)
    {
        // equivalent to +-1 * random positive number
        // rand_r is thread safe but is a little obsolete, could be updated 
        int num = (2 * (rand_r(&seed) % 2) - 1) * rand_r(&seed);
        if (num > 0)
            insert(positives, num);
        if (num < 0)
            insert(negatives, num);
    }
}

void	*rutine_start(void *p)
{
    t_data *data = (t_data *)p;

    rutine(data->numbers_per_thread, data->positives, data->negatives, data->seed);
    return 0;
}
