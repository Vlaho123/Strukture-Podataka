#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stog* Pozicija;
struct stog{

    double Element;
    Pozicija Next;
};

int Push(double Element, Pozicija P);
double Pop(Pozicija P);
int racunanje(char* nazivdatoteke, Pozicija P);

int main(void)
{
    double rjesenje=0;
    struct stog Head;
    Head.Next=NULL;

    rjesenje=racunanje("postfix.txt", &Head);
    printf("Rjesenje je: %.5lf", rjesenje);

    return 0;
}
int Push(double El, Pozicija P)
{
    Pozicija q;
    q=(Pozicija)malloc(sizeof(struct stog));

    q->Element=El;
    q->Next=P->Next;
    P->Next=q;

    return 0;

}
double Pop(Pozicija P)
{
    Pozicija temp=NULL;
    double br;

    temp=P->Next;
    br=temp->Element;

    if(temp==NULL)
    {
        printf("U stogu ne postoji niti jedan element.\n");
        return 0;
    }
    else
    {
        P->Next=temp->Next;
        free(temp);
    }
    return br;
}
int racunanje(char* nazivdatoteke, Pozicija P)
{
    FILE* f;
    char buffer[1024]={0};
    char* current_buffer;
    double broj=0;
    int br=0;
    int status=0;
    char znak;
    double rezultat=0;
    f=fopen(nazivdatoteke, "rb");
    if(!f)
    {
        printf("Greska pri otvaranju datoteke.\n");
        return -1;
    }
    fgets(buffer, 1024, f);
    fclose(f);
    current_buffer=buffer;

    while(strlen(current_buffer)>0)
    {
        status=sscanf(current_buffer, "%lf %n", &broj, &br);
        if(status==1)
        {
            Push(broj, P);
        }

        if(status!=1)
        {
            sscanf(current_buffer, " %c %n", &znak, &br);

            if(znak=='+')
                rezultat=Pop(P)+Pop(P);
            else if(znak=='*')
                rezultat=Pop(P)*Pop(P);
            else if(znak=='-')
                rezultat=Pop(P)-Pop(P);
            else if(znak=='/')
                rezultat=Pop(P)/Pop(P);
            else
            {
                printf("Pogresan znak.\n");
                return 0;
            }
            Push(rezultat, P);
        }
        current_buffer+=br;
    }
    rezultat=Pop(P);
    return rezultat;

}
