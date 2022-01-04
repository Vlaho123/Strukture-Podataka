#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct gradovi* Pozicija;
struct gradovi{
    char imegrada[50];
    Pozicija Next;
    int brojstanovnika;


};


typedef struct drzave* Stablo;
struct drzave{
    char imedrzave[50];
    Stablo D;
    Stablo L;
    Pozicija Grad;

};

int printDrzave(Stablo S);
int printGradove(Pozicija P);
Stablo trazidrzavu(Stablo S, char* imedrz);
int dodajgradove(Pozicija P, char* datoteka);
int trazi(Stablo S, char* imedrzav, int brojstan);
Stablo dodajdrzavu(Stablo S, char* imedr, char* imedat);

int main(void)
{
    Stablo root=NULL;
    FILE *f=NULL;
    char imedrzave[50];
    char imedatoteke[50];
    int stanovnici=0;

    f=fopen("drzave.txt", "r");
    if(f==NULL)
    {
        printf("Neuspjesno otvaranje.\n");
        return -1;
    }
    while(!feof(f))
    {
        fscanf(f,"%s %s", imedrzave, imedatoteke);
        root=dodajdrzavu(root, imedrzave, imedatoteke);
    }
    fclose(f);
    printDrzave(root);
    char name[50];
    printf("\nUnesite ime drzave koju zelite istraziti: ");
    scanf("%s", &name);

    printf("Unesite minimalan broj stanovnika: ");
    scanf("%d", &stanovnici);

    trazi(root,name,stanovnici);

    return 0;
}
Stablo dodajdrzavu(Stablo S, char* imedr, char* imedat)
{
    Stablo q=NULL;
    Pozicija z=NULL;
    if(S==NULL)
    {
        q=(Stablo)malloc(sizeof(struct drzave));
        if(q==NULL)
        {
            printf("Neuspjesna alokcaija.\n");
            return NULL;
        }
        strcpy(q->imedrzave, imedr);

        z=(Pozicija)malloc(sizeof(struct gradovi));
        if(z==NULL)
        {
            printf("Neuspjesna alokacija.\n");
            return NULL;
        }
        strcpy(z->imegrada, "");
        z->brojstanovnika=0;
        z->Next=NULL;

        q->Grad=z;

        dodajgradove(q->Grad, imedat);
        q->L=NULL;
        q->D=NULL;

        return q;
    }
    else if(strcmp(S->imedrzave, imedr)<0)
        S->D=dodajdrzavu(S->D, imedr, imedat);
    else if(strcmp(S->imedrzave, imedr)>0)
        S->L=dodajdrzavu(S->L, imedr, imedat);
    return S;

}


int printGradove(Pozicija P)
{
    while(P!=NULL)
    {
        printf("\t\t%s %d\n", P->imegrada, P->brojstanovnika);
        P=P->Next;
    }
    return 0;
}

int printDrzave(Stablo S)
{
    if(S==NULL)
        return 0;
    printDrzave(S->L);
    printf("\t%s\n", S->imedrzave);
    printGradove(S->Grad->Next);
    printDrzave(S->D);
    return 0;
}
int dodajgradove(Pozicija P, char* datoteka)
{
    char ime[50];
    int stan=0;
    Pozicija q=NULL;
    FILE *f=NULL;
    f=fopen(datoteka, "r");
    Pozicija Pocetak=P;
    Pozicija prev=P;
    if(f==NULL)
    {
        printf("Neispravno otvaranje datoteke.\n");
        return -1;
    }
    while(!feof(f))
    {
        P=Pocetak;
        prev=Pocetak;
        fscanf(f,"%s %d", ime, &stan);
        q=(Pozicija)malloc(sizeof(struct gradovi));
        if(q==NULL)
        {
            printf("Neispravna alokacija.\n");
            return NULL;
        }
        strcpy(q->imegrada,ime);
        q->brojstanovnika=stan;
        while(P!=NULL)
        {
            if(P->Next==NULL)
            {
                q->Next=P->Next;
                P->Next=q;
                break;
            }

            if(q->brojstanovnika<P->brojstanovnika)
            {
                q->Next=prev->Next;
                prev->Next=q;
                break;
            }

            if(strcmp(q->imegrada, P->imegrada)<0)
            {
                q->Next=prev->Next;
                prev->Next=q;
                break;
            }
        prev=P;
        P=P->Next;

        }
    }
    fclose(f);
    return 0;

}
Stablo trazidrzavu(Stablo S, char* imedrz)
{
    if(S==NULL)
        return NULL;
    if(strcmp(S->imedrzave, imedrz)==0)
        return S;
    if(strcmp(S->imedrzave, imedrz)>0)
        return trazidrzavu(S->L, imedrz);
    if(strcmp(S->imedrzave, imedrz)<0)
        return trazidrzavu(S->D, imedrz);
}
int trazi(Stablo S, char* imedrzav, int brojstan)
{
    Pozicija q=NULL;
    Stablo R=NULL;

    R=trazidrzavu(S,imedrzav);
    if(R==NULL)
    {
        printf("Nema te drzave.\n");
        return 0;
    }
    q=R->Grad;
    if(q==NULL)
    {
        printf("Drzava nema gradova.\n");
        return 0;
    }
    q=q->Next;
    while(q!=NULL)
    {
        if(q->brojstanovnika>=brojstan)
            printf("\t%s %d\n", q->imegrada, q->brojstanovnika);
        q=q->Next;
    }
    return 0;
}
