#include <stdio.h>

#define showcase_size 10//Number of TB's which can be accommodated in the showcase.

typedef enum
{PINK=5,BROWN,WHITE} color; // Three colors of TB's

typedef struct
{
int bear_id;
float bear_cost;
color bear_color;
} teddy_bear; //Information about a TB

typedef struct node
{
    teddy_bear tb;
    struct node*next;
} NODE;
typedef struct node* link;
typedef struct
{
    NODE *first;
    int size;
} LIST; //head of the linked list

//prototypes
LIST* create_list();
teddy_bear* in();
LIST* add_beg(LIST*,teddy_bear);
void print(LIST*);
LIST* del_last(LIST*);
LIST* insert_new(LIST*,teddy_bear); //inserting a newly launched teddy bear
int count_color(LIST*,color); //number of TBs with a specific color
LIST* insert_sort(LIST*,teddy_bear);
LIST* del_teddy(LIST*,teddy_bear);

int main()
{
    LIST* l;
    l=create_list();
    //printf("%d\n",l->size);
    //if (l->first==NULL) printf( "%s\n","YES");
    teddy_bear* teddy=in();
    //printf("%d\n",teddy->bear_id);
    l=add_beg(l,*teddy);
    //printf("%d\n",(l->first->tb).bear_id);
    print(l);
    return 0;
}

LIST* create_list()
{
    LIST *ls;
    ls=(LIST*)malloc(sizeof(LIST));
    ls->size=0;
    ls->first=NULL;
    return ls;
}

teddy_bear* in()
{
    teddy_bear*ted=(teddy_bear*)malloc(sizeof(teddy_bear));
    printf("enter bear id\n");
    scanf("%d",&(ted->bear_id));
    printf("enter price\n");
    scanf("%f",&(ted->bear_cost));
    printf("enter color code=> 5=pink,6=brown,7=white\n");
    scanf("%d",&(ted->bear_color));
    return ted;
}

LIST* add_beg(LIST* ls,teddy_bear b)
{
    link n=(link)malloc(sizeof(NODE));
    n->tb=b;
    n->next=ls->first;
    ls->first=n;
    ls->size++;
    return ls;
}

void print(LIST* ls)
{
    int i=1;
    link temp=ls->first;
    if (temp==NULL)
    {
        printf("list is empty\n");
    }
    else
    {
        while (temp!=NULL)
        {
            printf("DETAILS==>teddy#%d\n",i);
            printf("id=%d\n",(temp->tb).bear_id);
            printf("cost=%f\n",(temp->tb).bear_cost);
            if ((temp->tb).bear_color==5) printf("color=%s\n","pink");
            else if ((temp->tb).bear_color==6) printf("color=%s\n","brown");
            else if ((temp->tb).bear_color==7) printf("color=%s\n","white");
            temp=temp->next;
        }

    }
}

LIST* del_last(LIST* ls)
{
    link temp=ls->first;
    if (temp==NULL)
    {
        printf("list empty!!!\n");
        ls->size++; //since deppreciated at the end
    }
    else
    {
        link prev=ls->first;
        temp=temp->next;
        while (temp->next!=NULL)
        {
            prev=temp;
            temp=temp->next;
        }
        prev->next=NULL;
    }
    ls->size--;
    return ls;
}

LIST* insert_new(LIST* ls,teddy_bear ted)
{
    if (ls->size<showcase_size)
    {
        ls=add_beg(ls,ted);
    }
    else
    {
        ls=del_last(ls);
        ls=add_beg(ls,ted);
    }

    return ls;
}

int count_color(LIST* ls,color c)
{
    link temp=ls->first;
    int count=0;
    while (temp!=NULL)
    {
        if ((temp->tb).bear_color==c)
        {
            count++;
        }
    }
    return count;
}

LIST* insert_sort(LIST* ls,teddy_bear b)
{
    link temp=ls->first;
    if (ls->first==NULL || b.bear_color< temp->tb.bear_color)
    {
        ls=add_beg(ls,b);
    }
    else
    {
        link prev=temp;
        temp=temp->next;
        link n=(link)malloc(sizeof(NODE));
        n->tb=b;
        while (temp!=NULL)
        {
            if (b.bear_color <= (temp->tb.bear_color) && b.bear_color>=(prev->tb.bear_color))
            {
                prev->next=n;
                n->next=temp;
                ls->size++;
                break;
            }
        }
        if (temp==NULL)
        {
            prev->next=n;
            n->next=NULL;
            ls->size++;
        }
    }
    return ls;
}

LIST* del_teddy(LIST* ls,teddy_bear b)
{
    link temp=ls->first;
    if (temp!=NULL) //processing only if the list is not empty
    {
        link prev=temp;
        temp=temp->next;
        if (temp==NULL) //==> list has only one member <that too, matches>
        {
            if (prev->tb.bear_id==b.bear_id && prev->tb.bear_cost==b.bear_cost && prev->tb.bear_color==b.bear_color)
            {
                ls->first=NULL;
                ls->size--;
            }
        }

        else
        {
            while (temp->next!=NULL)
            {
                if (temp->tb.bear_id==b.bear_id && temp->tb.bear_cost==b.bear_cost && temp->tb.bear_color==b.bear_color)
                {
                    prev->next=temp->next;
                    ls->size--;
                    break;
                }
                prev=temp;
                temp=temp->next;
            }
            if (temp->next==NULL)
            {
                if (temp->tb.bear_id==b.bear_id && temp->tb.bear_cost==b.bear_cost && temp->tb.bear_color==b.bear_color)
                {
                    prev->next==NULL;
                    ls->size--;
                }
            }
        }
    }
    return ls;
}

