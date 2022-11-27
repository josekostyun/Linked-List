#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leak_detector_c.h"

typedef struct fail_fish_struct
{
    int serial_num;
    struct fail_fish_struct *next;
    struct fail_fish_struct *prev;

}failfish;

typedef struct pond_struct
{
    char *pondname;
    int nfailfish, eatcounter, min_fish;
    failfish *head;
    failfish *tail;
}failfish_queue;

///Prototypes
failfish *create_failfish(int sequence_number);
failfish_queue *create_failfish_queue(char *pondname, int n, int e, int th);
failfish_queue *create_fish_queue(failfish_queue *queue, int nfailish);
void enqueue(failfish_queue *q, failfish *new_fish);
int is_empty(failfish_queue *list);
void print_failfish_queue(failfish_queue *q, FILE *ofp);
void first_course(failfish_queue *que, int pond_num, FILE *ofp);
void dequeue(failfish_queue *que, failfish *fish);
void second_course(failfish_queue *que[], int nponds, FILE *ofp);
failfish *peek(failfish_queue *que);
void dequeue_pond(failfish_queue *pond, int pond_num, FILE *ofp);
void dispose_fish(failfish *fish);
void dispose_pond(failfish_queue *pond);

//These functions are from Dr. Gerber
void remove_crlf(char *s)
{
    char *t = s + strlen(s);

    t--;

    while((t >= s) && (*t == '\n' || *t == '\r'))
    {
        *t = '\0';  // ...clobber it by overwriting it with null, and...
        t--;        // decrement t *itself (i.e., change the pointed location)
    }
}

int get_next_nonblank_line(FILE *ifp, char *buf, int max_length)
{
    buf[0] = '\0';

    while(!feof(ifp) && (buf[0] == '\0'))
    {
        fgets(buf, max_length, ifp);
        remove_crlf(buf);
    }

    if(buf[0] != '\0') {
        return 1;
    } else {
        return 0;
    }
}

//This function gets the number of ponds
int getnumber_ponds(FILE *ifp)
{
    int ponds;
    char buff[256];

    get_next_nonblank_line(ifp, buff, 255);
    sscanf(buff, "%d", &ponds);

    return ponds;
}

//This creates the pond by mallocing the proper space for it
failfish_queue *create_failfish_queue(char *pondname, int n, int e, int th)
{
    failfish_queue *pond_que = malloc(sizeof(failfish_queue));

    pond_que->pondname = strdup(pondname);
    pond_que->nfailfish = n;
    pond_que->eatcounter = e;
    pond_que->min_fish = th;
    pond_que->head = NULL;
    pond_que->tail = NULL;

    return pond_que;
}

//Function that creates the pond array
void create_array(FILE *ifp, failfish_queue *que[], int nponds, FILE *ofp)
{
    char buff[256];
    char pondname[256];
    int pondnum, nfailish, eat_counter, min_failfish;

    //Sets array elements to NULL
     for(int i = 0; i < 11; ++i)
    {
        que[i] = NULL;
    }

    //Fills the pond array
    for(int i = 0; i < nponds; ++i)
    {
        get_next_nonblank_line(ifp, buff, 255);
        sscanf(buff, "%d %s %d %d %d", &pondnum, pondname, &nfailish, &eat_counter, &min_failfish);
        for(int j = 0; j < 11; ++j)
        {
            if(pondnum == j)
            {
                que[j] = create_failfish_queue(pondname, nfailish, eat_counter, min_failfish);
            }
        }
    }

    //Creates the failfish linked list
    for(int i = 0; i < 11; ++i)
    {
        if(que[i] != NULL)
        {
            for(int j = 1; j <= que[i]->nfailfish; ++j)
            {
                enqueue(que[i], create_failfish(j));
            }
        }
    }

     //Prints Initial Pond Status
    fprintf(ofp,"Initial Pond Status\n");
    for(int i = 0; i < 11; ++i)
    {
        if(que[i] != NULL)
        {
            fprintf(ofp,"%d ", i);
            print_failfish_queue(que[i], ofp);
        }
    }

    //Prints the first course, which fish was eaten
    fprintf(ofp,"\nFirst Course\n");
    for(int i = 0; i < 11; ++i)
    {
        if(que[i] != NULL)
        {
            first_course(que[i], i, ofp);
        }
    }

    //Prints end of course pond status
    fprintf(ofp,"\nEnd of Course Pond Status\n");

    for(int i = 0; i < 11; ++i)
    {
        if(que[i] != NULL)
        {
            fprintf(ofp, "%d ", i);
            print_failfish_queue(que[i], ofp);
        }
    }
    fprintf(ofp, "\n");

}

//Prints the failfish linked list
void print_failfish_queue(failfish_queue *q, FILE *ofp)
{
    fprintf(ofp,"%-10s ", q->pondname);
    do
    {
        if(q->head->next == NULL)
        {
            fprintf(ofp,"Fish %d is the only fish in the pond\n", q->head->serial_num);
        }
        else
        {
            fprintf(ofp,"%d ", q->head->serial_num);
            q->head = q->head->next;

        }
    }while(q->tail->next != q->head);

    fprintf(ofp, "\n");
}

//Checks to see if failfish queue is empty
int is_empty(failfish_queue *list)
{
    if(list->head == NULL)
        return 0;
    else
        return 1;
}

//Fills the failfish queue
void enqueue(failfish_queue *q, failfish *new_fish)
{
    int temp = is_empty(q);
    if(temp == 0)
    {
        q->head = new_fish;
        q->tail = new_fish;
        new_fish->prev = NULL;
        new_fish->next = NULL;
    }
    else
    {
        new_fish->next = q->head;
        new_fish->prev = q->tail;
        q->head->prev = new_fish;
        q->tail->next = new_fish;
        q->tail = new_fish;
    }

}

//Allocates memory for each fish
failfish *create_failfish(int sequence_number)
{
    failfish *new_fish = malloc(sizeof(failfish));
    new_fish->serial_num = sequence_number;

    return new_fish;
}

//Eats n amount of fish till threshold th is met.
void first_course(failfish_queue *que, int pond_num, FILE *ofp)
{
    failfish *current = que->head;
    fprintf(ofp, "\nPond %-2d: %s\n", pond_num, que->pondname);
    int e = que->eatcounter - 1;

    for (int i = que->nfailfish; i > que->min_fish; --i)
    {

        for(int k = 1; k <= e ; ++k)
        {
            current = current->next;
        }

        fprintf(ofp,"Failfish %-2d eaten\n", current->serial_num);

        current = current->next;
        dequeue(que, current->prev);
    }
}

//Mimic from Dr. Gerber
void dequeue(failfish_queue *que, failfish *fish)
{
    /* We now have four cases to deal with. */

    /* Case 0: Don't delete from an empty list. */

    if(que->head == NULL) {
        return;
    }

    /* Case 1: Emptying the list. */

    if((que->head == que->tail) && (que->head == fish)) {
        que->head = NULL;
        que->tail = NULL;
        fish->prev = NULL;
        fish->next = NULL;
        dispose_fish(fish);
        return;
    }

    /* Case 2: Removing the head. */

    if(fish == que->head) {
        que->head = que->head->next;
        que->head->prev = que->tail;
        que->tail->next = que->head;

        fish->prev = NULL;
        fish->next = NULL;
        dispose_fish(fish);
        return;
    }

    /* Case 3: Removing the tail. */

    if(fish == que->tail) {
        que->tail = que->tail->prev;
        que->tail->next = que->head;
        que->head->prev = que->tail;

        fish->prev = NULL;
        fish->next = NULL;
        dispose_fish(fish);
        return;
    }

    /* Case 4: Removing an interior element. */

    /* We are deleting neither the head nor the tail, so we have elements to our left
       and our right - which means we can just hook them together. */

    fish->prev->next = fish->next;
    fish->next->prev = fish->prev;
    fish->prev = NULL;
    fish->next = NULL;
    dispose_fish(fish);
}

//Checks heads of ponds returns head sequence number
int *peek(failfish_queue *que[], i)
{
    for(int j = i; j < 11; ++j)
    {
        if(q[i]->head->num < q[j]->head->num)
        return j;
    }
    return i;
}

//Function that handles dequeue of pond and freeing memory
void dequeue_pond(failfish_queue *pond, int pond_num, FILE *ofp)
{
    failfish *fish = pond->head;
    for(int i = 0; i < pond->min_fish; ++i)
    {
        fprintf(ofp, "Eaten: Failfish %-2d from pond %-2d\n", fish->serial_num, pond_num);
        fish = fish->next;

        dequeue(pond, fish->prev);
    }

    dispose_pond(pond);
}

//Second course function, returns highest head sequence and dequeues and frees
void second_course(failfish_queue *que[], int nponds, FILE *ofp)
{
    printf("Second Course\n\n");
    int pond_count = nponds;
    failfish_queue *last_pond;
    int pond_num;

    do
    {
        failfish_queue *pond;
        failfish *fish1, *fish2;
        pond_num = 0;
        for(int i = 0; i < 11;++i)
        {
            if(que[i] != NULL)
            {
                fish1 = peek(que[i]);
                pond = que[i];
                pond_num = i;
                break;
            }
        }

        for(int i = 0; i < 11; ++i)
        {
            if(que[i] != NULL && que[i] != pond)
            {
                fish2 = peek(que[i]);
                if(fish1->serial_num < fish2->serial_num)
                {
                    pond_num = i;
                    pond = que[i];
                    break;
                }
            }
        }
        dequeue_pond(pond, pond_num, ofp);
        que[pond_num] = NULL;
        --pond_count;
    }while(pond_count > 1);

    for(int i = 0; i < 11; ++i)
    {
        if(que[i] != NULL)
        {
            last_pond = que[i];
            pond_num = i;
        }
    }

    if(pond_count == 1)
    {
        failfish *fish = last_pond->head;
        for(int i = 0; i < (last_pond->min_fish - 1); ++i)
        {
            fprintf(ofp, "Eaten: Failfish %-2d from pond %-2d\n", last_pond->head->serial_num, pond_num);
            fish = fish->next;
            dequeue(last_pond, fish->prev);
        }
        fprintf(ofp, "\n");
        fprintf(ofp, "Failfish %-2d from pond %-2d remains\n", last_pond->head->serial_num, pond_num);
        free(fish);
    }
    dispose_pond(last_pond);

}

//Free fish function
void dispose_fish(failfish *fish)
{
    free(fish);
}

//Free pond function
void dispose_pond(failfish_queue *pond)
{
    free(pond->pondname);
    free(pond);
}

int main()
{
    atexit(report_mem_leak);

    FILE *ifp = fopen("cop3502-as2-input.txt" , "r");
    FILE *ofp = fopen("cop3502-as2-output-kostyun-jose.txt" , "w");

    int nponds = getnumber_ponds(ifp);

    failfish_queue *que[11];
    create_array(ifp, que, nponds, ofp);

    second_course(que, nponds, ofp);

    fclose(ifp);
    fclose(ofp);
    return 0;
}
