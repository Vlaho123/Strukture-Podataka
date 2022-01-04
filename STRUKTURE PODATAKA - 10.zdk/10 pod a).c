#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
typedef struct gradovi* Stablo;
struct gradovi{
    char ime[50];
    Stablo D;
    Stablo L;
    int BrojStanovnika;

};

typedef struct drzave* Pozicija;
struct drzave
{
    char ime[50];
    Stablo Grad;
    Pozicija Next;
};
int DodavanjeDrzave(char* imedrzave, char* datoteka, Pozicija P);
int DodavanjeGrada(char* datoteka, Stablo S);
Stablo UnosenjeGrada(char *ime, int brojstan, Stablo S);
int printDrzave(Pozicija P);
int printGradove(Stablo S);
Pozicija traziDrzavu(Pozicija P, char* ime);
int traziGrad(Stablo S, int brojst);
int main(void)
{
    struct drzave Head={.ime="", .Grad=NULL, .Next=NULL};
    char imedrzave[50];
    char imedatoteke[50];
    Pozicija P=NULL;
    int brojstan=0;
    FILE *f=NULL;

    f=fopen("drzave.txt", "r");
    if(f==NULL)
    {
        printf("Neuspjesno otvaranje.\n");
        return -1;
    }
    while(!feof(f))
    {
        fscanf(f, "%s %s", imedrzave, imedatoteke);
        DodavanjeDrzave(imedrzave,imedatoteke,&Head);
    }
    fclose(f);
    printDrzave(Head.Next);

    printf("\nUnesite ime drzave koju zelite pregledati: ");
    scanf("%s", imedrzave);
    P=traziDrzavu(Head.Next, imedrzave);
    if(P==NULL)
    {
        printf("Ne postoji ta drzava.\n");
        return 0;
    }
    printf("Minimalan broj stanovnika: ");
    scanf("%d", &brojstan);
    printf("\nGradovi te drzave (%s) sa vise od %d stanovnika:\n", P->ime, brojstan);
    traziGrad(P->Grad, brojstan);

    return 0;


}


int DodavanjeDrzave(char* imedrzave, char* datoteka, Pozicija P)
{
    Pozicija q=NULL;
    Pozicija prev=NULL;
    Stablo z=NULL;

    q=(Pozicija)malloc(sizeof(struct drzave));
    if(q==NULL)
    {
        printf("Neispravno alociranje.\n");
        return -1;
    }
    strcpy(q->ime, imedrzave);
    q->Grad=z;

    z=(Stablo)malloc(sizeof(struct gradovi));
    if(z==NULL)
        {
            printf("Neispravno alociranje.\n");
            return -1;
        }
    strcpy(z->ime, "");
    z->BrojStanovnika=0;
    z->D=NULL;
    z->L=NULL;

    q->Grad=z;

    DodavanjeGrada(datoteka, q->Grad);
    prev=P;
    while(P!=NULL)
    {
        if(P->Next==NULL)
        {
            P->Next=q;
            q->Next=NULL;
            break;
        }
        if(strcmp(q->ime, prev->Next->ime)<0)
        {
            q->Next=prev->Next;
            prev->Next=q;
            break;
        }
        P=P->Next;
    }
    return 0;

}
int DodavanjeGrada(char* datoteka, Stablo S)
{
    FILE* f=NULL;
    char name[50];
    int brojstan=0;

    f=fopen(datoteka, "r");
    if(f==NULL)
        {printf("Greska pri otvaranju datoteke.\n"); return -1;}
    while(!feof(f))
    {
        fscanf(f,"%s %d", name, &brojstan);
        S=UnosenjeGrada(name, brojstan, S);
    }
    fclose(f);
    return 0;
}
Stablo UnosenjeGrada(char *ime, int brojstan, Stablo S)
{
    Stablo q=NULL;
    if(S==NULL)
        {
            q=(Stablo)malloc(sizeof(struct gradovi));
            if(q==NULL)
            {
                printf("Neuspjesno alocrianje.\n");
                return NULL;
            }
            strcpy(q->ime, ime);
            q->BrojStanovnika=brojstan;
            q->D=NULL;
            q->L=NULL;
            return q;
        }
    if(S->BrojStanovnika<brojstan)
        S->D=UnosenjeGrada(ime,brojstan,S->D);
    else if(S->BrojStanovnika>brojstan)
        S->L=UnosenjeGrada(ime,brojstan,S->L);
    else if(brojstan==S->BrojStanovnika)
    {
        if(strcmp(ime,S->ime)>=0)
            S->D=UnosenjeGrada(ime,brojstan,S->D);
        else
            S->L=UnosenjeGrada(ime,brojstan,S->L);

    }
    return S;
}
int printGradove(Stablo S)
{
    if(S==NULL)
        return 0;
    printGradove(S->L);
    printf("\t%s\n", S->ime);
    printGradove(S->D);
    return 0;
}
Pozicija traziDrzavu(Pozicija P, char* ime)
{
    while(P!=NULL)
    {
        if(strcmp(P->ime, ime)==0)
            return P;
        P=P->Next;
    }
    return P;
}
int traziGrad(Stablo S, int brojst)
{
    if(S==NULL)
        return 0;
    traziGrad(S->L, brojst);
    if(S->BrojStanovnika>=brojst)
        printf("\t%s %d\n", S->ime, S->BrojStanovnika);
    traziGrad(S->D, brojst);
    return 0;
}
int printDrzave(Pozicija P)
{
    printf("Drzave:\n");
    while(P!=NULL)
    {
        printf("%s\n", P->ime);
        printGradove(P->Grad->D);
        P=P->Next;
    }
    return 0;
}


