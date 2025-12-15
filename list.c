#include "technical_test.h"

t_list *create_node(int n)
{
    t_list *node = malloc(sizeof(t_list));

    node->content = n;
    node->next = 0;
    return node;
}

t_list_head create_list()
{
    t_list_head head = {};

    if (pthread_mutex_init(&(head.mutex), NULL))
        perror("ups");
    head.list = NULL;
    return head;
}

void destroy_list(t_list_head head)
{
    t_list *list = head.list;
    t_list *n;

    while (list)
    {
        n = list->next;
        free(list);
        list = n;
    }
    pthread_mutex_unlock(&head.mutex);
    pthread_mutex_destroy(&head.mutex);
}

// this function could be cleaner
void insert(t_list_head *head, int n)
{
    pthread_mutex_lock(&(head->mutex));
    t_list *list = head->list;

    while (list)
    {
        if (!list->next)
        {
            list->next = create_node(n);
            break;
        }
        if (list->next->content < n)
        {
            list = list->next;
            continue;
        }
        t_list *node = list->next;    
        list->next = create_node(n);
        list->next->next = node;
        break;
    }
    if (!list)
    {
        head->list = create_node(n);
    }
    
    pthread_mutex_unlock(&(head->mutex));
}

void print_list(t_list_head head)
{
    pthread_mutex_lock(&(head.mutex));
    t_list *list = head.list;    

    while (list)
    {
        printf("%i\n", list->content);
        list = list->next;
    }
    pthread_mutex_unlock(&(head.mutex));
}