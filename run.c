#include "technical_test.h"

int run(int threads_n, int numbers_per_thread)
{
    printf("Running...\n");
    printf("Number of threads:\t%i\n", threads_n);
    printf("Numbers per thread:\t%i\n", numbers_per_thread);
    
    t_list_head positives = create_list();
    t_list_head negatives = create_list();
    pthread_t   *threads = calloc(threads_n, sizeof(pthread_t));

    srand(time(NULL));

    t_data *data = calloc(1, sizeof(t_data));
    data->numbers_per_thread = numbers_per_thread;
    data->negatives = &negatives;
    data->positives = &positives;
    data->seed = time(NULL);
    int n = threads_n;
    
    while (threads_n--)
    {
        printf("%i\n", threads_n);
        data->seed = 42 + threads_n * 69;
        
        pthread_create(&threads[threads_n], NULL, rutine_start, data);
    }
    
    
    while (n--)
    {
        pthread_join(threads[n], NULL);
    }
    print_list(negatives);
    print_list(positives);

    
    free(data);
    
    free(threads);
    destroy_list(positives);
    destroy_list(negatives);
    return 0;
}