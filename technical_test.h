#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

#define ERROR_ARGC  0x10
#define ERROR_ARGV1 0x11
#define ERROR_ARGV2 0x12

typedef struct s_list
{
    int            content;
    struct s_list   *next;
}               t_list;

typedef struct s_list_head
{
	pthread_mutex_t	mutex;
    struct s_list   *list;
}				t_list_head;

typedef struct s_data
{
    t_list_head     *positives;
    t_list_head     *negatives;
    int             numbers_per_thread;
    unsigned int    seed;
}				t_data;

t_list_head create_list();
void destroy_list(t_list_head head);
void insert(t_list_head *head, int n);
void print_list(t_list_head head);

void	*rutine_start(void *p);

int run(int threads_n, int numbers_per_thread);