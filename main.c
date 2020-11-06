#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct queue_node
{
    int data;
    struct queue_node *next, *prev;
};

struct queue_pointers
{
    struct queue_node *head, *tail;
};

struct queue_with_guard
{
    struct queue_node *head, *tail, *guard;
};

bool enqueue(struct queue_pointers *queue, int data)
{
    struct queue_node *new_node = (struct queue_node*)malloc(sizeof(struct queue_node));
    if(new_node)
    {
        new_node->data = data;
        new_node->next = NULL;

        if(NULL == queue->head)
        {
            queue->head = queue->tail = new_node;
            new_node->prev = NULL;
        }
        else
        {
            queue->tail->next = new_node;
            new_node->prev = queue->tail;
            queue->tail = new_node;
        }
        return true;
    }
    return false;
}

bool dequeue(struct queue_pointers *queue, int *data)
{
    if (NULL != queue->head)
    {
        struct queue_node *tmp = queue->head->next;
        *data = queue->head->data;
        free(queue->head);
        queue->head = tmp;
        if(tmp)
            queue->head->prev = NULL;
        if (NULL == tmp)
            queue->tail = NULL;
        return true;
    }
    return false;
}

bool dequeue_r(struct queue_pointers *queue, int *data)
{
    if (NULL != queue->tail)
    {
        struct queue_node *tmp = queue->tail->prev;
        *data = queue->tail->data;
        free(queue->tail);
        queue->tail = tmp;
        if(tmp)
            queue->tail->next = NULL;
        if (NULL == tmp)
            queue->head = NULL;
        return true;
    }
    return false;
}
int stan(struct queue_pointers queue)
{
    int s = 0;
    for(; NULL != queue.head; queue.head = queue.head->next)s=s+1;
    return s;
}

void print_queue(struct queue_pointers queue)
{
    if(queue.head)
    {
        for (; NULL != queue.head; queue.head = queue.head->next)
            printf("%d ", queue.head->data);
    }
    else printf("| Kolejka pusta.");
}

void print_queue_r(struct queue_pointers queue)
{
    if(queue.tail)
    {
        for (; NULL != queue.tail; queue.tail = queue.tail->prev)
            printf("%d ", queue.tail->data);
    }
    else printf("| Kolejka pusta.");
}
void info()
{
    printf("   Menu kolejki:\n"
           " [1] - Dodaj do kolejki\n"
           " [2] - Pierwszy wychodzi z kolejki\n"
           " [3] - Ostatni wychodzi z kolejki\n"
           " [0] - Wyjdz z programu\n"
           " [9] - Info danych\n"
           ": ");
}

int main()
{
    int menu,dana,i;
    //struct queue_node guard;    guard.next = &guard;
    //struct queue_with_guard queue_g = {&guard, &guard, &guard};

    struct queue_pointers queue = {NULL, NULL};

        enqueue(&queue, 5);
        enqueue(&queue, 2);


    while(menu)
    {
        printf(" Struktura kolejki"
               " \nOd prawej do lewej"
               "\n<-----------------<<<\n ");
        print_queue(queue);
        printf("\n<-----------------<<<\n");
        printf("\n Od lewej do prawej"
                "\n>>>----------------->\n ");
        print_queue_r(queue);
        printf("\n>>>----------------->\n");

        printf("\nInfo o kolejce \n  Stan kolejki: %d",stan(queue));
        printf("\nWartosc 'Head': %d\n",queue.head);
        printf("Wartosc 'Tail': %d\n",queue.tail);
        if(stan(queue)>0)
                {
                    printf("Wartosc head->data: %d\n",queue.head->data);
                    printf("Wartosc head->next: %d\n",queue.head->next);
                    printf("Wartosc head->prev: %d\n",queue.head->prev);

                    printf("Wartosc tail->data: %d\n",queue.tail->data);
                    printf("Wartosc tail->next: %d\n",queue.tail->next);
                    printf("Wartosc tail->prev: %d\n",queue.tail->prev);
                }
        else printf("Brak danych struktury kolejki");

        puts("\n");
        info();
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            {
                printf("Dodaj: ");
                scanf("%d",&dana);
                enqueue(&queue, dana);
                system("CLS");
                break;
            }
        case 2:
            {
                printf("Usuwam pierwszy element.\n\n");
                dequeue(&queue, &i);
                system("PAUSE");
                system("CLS");
                break;
            }
        case 3:
            {
                printf("Usuwam pierwszy element.\n\n");
                dequeue_r(&queue, &i);
                system("PAUSE");
                system("CLS");
                break;
            }
        case 9:
            {
                if(stan(queue)>0)
                {
                    printf("Wartosc head->data: %d\n",queue.head->data);
                    printf("Wartosc head->next: %d\n",queue.head->next);
                    printf("Wartosc head->prev: %d\n",queue.head->prev);

                    printf("Wartosc tail->data: %d\n",queue.tail->data);
                    printf("Wartosc tail->next: %d\n",queue.tail->next);
                    printf("Wartosc tail->prev: %d\n",queue.tail->prev);
                }
                else printf("Aktualnie brak danych");
                puts("\n");
                system("PAUSE");
                system("CLS");
                break;
            }
        case 0:
            exit(0);
        }
    }

    srand(time(NULL));
    int elements = 5+rand()%6;
    for (i=0; i<elements; i++)
        enqueue(&queue, i);

    printf("Queue elements: ");
    print_queue(queue);

    printf("Removing queue: ");
    while (dequeue(&queue, &i))
        printf("%d ", i);
    puts(" ");
    printf("\nQueue elements: ");
    print_queue(queue);
    puts(" ");
    return 0;
}
