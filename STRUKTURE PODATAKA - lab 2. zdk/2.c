#include<stdio.h>
#include<string.h>

typedef struct osoba *Pozicija;
struct osoba
{
    char ime[50];
    char prezime[50];
    int godinaRodenja;
    Pozicija Next;
};
void UnosNaPocetak(char* ime, char* prezime, int godinaRodenja, Pozicija P);
void Ispis(Pozicija P);
void UnosNaKraj(char* ime, char* prezime, int godinaRodenja, Pozicija P);
Pozicija Pronadi(char* prezime, Pozicija P);
Pozicija TraziPrev(char* prezime, Pozicija P);
void BrisiElement(char* ime, Pozicija P);
int main(void)
{
    Pozicija T;
    struct osoba Head;
    Head.Next=NULL;
    UnosNaPocetak("Ante", "Antic", 2001, &Head);
    UnosNaPocetak("Sime", "Simic", 2002, &Head);
    UnosNaPocetak("Jure", "Juric", 2002, &Head);
    UnosNaPocetak("Frane", "Franic", 2002, &Head);

    BrisiElement("Antic", &Head);
    UnosNaKraj("Jure", "Juric", 1999, &Head);
    T=Pronadi("Franic", Head.Next);

    Ispis(Head.Next);
    if(T!=NULL)
        printf("\nPronaden");
    else
        printf("\nNije pronaden");

    return 0;
}
void UnosNaPocetak(char* ime, char* prezime, int godinaRodenja, Pozicija P)
{
    Pozicija q=NULL;
    q=(Pozicija)malloc(sizeof(struct osoba));
    strcpy(q->ime, ime);
    strcpy(q->prezime, prezime);
    q->godinaRodenja = godinaRodenja;

    q->Next = P->Next;
    P->Next = q;
}
void Ispis(Pozicija P)
{
    while(P!=NULL)
        {
            printf("%s\t%s\t%d\n", P->ime, P->prezime, P->godinaRodenja);
            P=P->Next;
        }
}
void UnosNaKraj(char* ime, char* prezime, int godinaRodenja, Pozicija P)
{
    Pozicija q=NULL;
    q =(Pozicija)malloc(sizeof(struct osoba));
    strcpy(q->ime, ime);
    srtcpy(q->prezime, prezime);
    q->godinaRodenja = godinaRodenja;
    while(P->Next!=NULL)
    {
        P=P->Next;
    }
    q->Next=P->Next;
    P->Next=q;

}
Pozicija Pronadi(char* prezime, Pozicija P)
{
    /*Pozicija tmp=NULL;
    tmp=P;
    while(P!=NULL)
    {
        if(strcmp(tmp->prezime, prezime)==0)
            return tmp;
        tmp=P->Next;
    }
    return NULL;*/

    while(P!=NULL && strcmp(P->prezime, prezime)!=0)
        P=P->Next;
    if(P==NULL)
        return 0;
    else
        return P;
}
Pozicija TraziPrev(char* prezime, Pozicija P)
{
    Pozicija prev;
    prev=P;
    P=P->Next;
    while(P!=NULL && strcmp(P->prezime, prezime)!=0)
    {
        prev=P;
        P=P->Next;
    }
    if(P==NULL)
        return NULL;
    else
        return prev;
}
void BrisiElement(char* prezime, Pozicija P)
{
    Pozicija tmp=NULL;
    P=TraziPrev(prezime, P);
    if(P==NULL)
        printf("Greska");
    else
    {

        tmp=P->Next;
        P->Next=tmp->Next;
        free(tmp);
    }
}
