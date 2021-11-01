#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
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
int UnesiIza(char* prezime1, char* ime2, char* prezime2, int godinaRodenja2, Pozicija P);
int UnesiIspred(char* prezime1, char* ime2, char* prezime2, int godinaRodenja2, Pozicija P);

void SortirajListu(Pozicija P);
void UnesiUDat(FILE *f, Pozicija P);
void ProcitajIzDatoteke(FILE *f, Pozicija P);
int main(void)
{
    Pozicija T;
    struct osoba Head;
    Head.Next=NULL;
    FILE *f=NULL;
    UnosNaPocetak("Ante", "Antic", 2001, &Head);
    UnosNaPocetak("Sime", "Simic", 2002, &Head);
    UnosNaPocetak("Jure", "Juric", 2002, &Head);
    UnosNaPocetak("Frane", "Franic", 2002, &Head);
    UnesiUDat(f, Head.Next);
    ProcitajIzDatoteke(f, &Head);
    UnesiIza("Antic", "Vlaho", "Petkovic", 2002, Head.Next);
    UnesiIspred("Petkovic", "Mate", "Matic", 2003, &Head);
  //  BrisiElement("Antic", &Head);
   // UnosNaKraj("Duje", "Dujic", 1999, &Head);
   // T=Pronadi("Franic", Head.Next);


    SortirajListu(&Head);
    Ispis(Head.Next);
  /*  if(T!=NULL)
        printf("\nPronaden");
    else
        printf("\nNije pronaden");
*/
    return 0;
}
void UnesiUDat(FILE *f, Pozicija P)
{
    f=fopen("Osobe.txt", "w");
    if(!f)
        {
            printf("Greska");
            return NULL;
        }
    Pozicija q;

    fprintf(f,"IME\tPREZIME\tGODINA RODENJA\n");
    while(P!=NULL)
    {
        fprintf(f,"%s\t%s\t%d\n", P->ime, P->prezime, P->godinaRodenja);
        P=P->Next;
    }
    fclose(f);
}
void ProcitajIzDatoteke(FILE *f, Pozicija P)
{
    f=fopen("Proba.txt", "w");
    char ime[100]={0}, prezime[100]={0};
    int godRod;
    if(!f)
    {
        printf("Greska.");
        return NULL;
    }
    while(!feof(f))
    {
        fscanf(f,"%s\t%s\t%d\n", ime, prezime, &godRod);
        UnosNaPocetak(ime,prezime,godRod,P);

    }
    fclose(f);
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
    strcpy(q->prezime, prezime);
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
int UnesiIza(char* prezime1, char* ime2, char* prezime2, int godinaRodenja2, Pozicija P)
{
    Pozicija q=NULL;
    while(P!=NULL && strcmp(P->prezime, prezime1)!=0)
        P=P->Next;
    if(P!=NULL)
    {
        q=(Pozicija)malloc(sizeof(struct osoba));
        strcpy(q->ime, ime2);
        strcpy(q->prezime, prezime2);
        q->godinaRodenja=godinaRodenja2;
        q->Next=P->Next;
        P->Next=q;
    }
    else
        printf("\nGreska.");
    return 0;
}
int UnesiIspred(char* prezime1, char* ime2, char* prezime2, int godinaRodenja2, Pozicija P)
{
    Pozicija q;
    while(P!=NULL && strcmp(P->Next->prezime, prezime1)!=0)
        P=P->Next;
    if(P!=NULL)
    {
        q=(Pozicija)malloc(sizeof(struct osoba));
        strcpy(q->ime, ime2);
        strcpy(q->prezime, prezime2);
        q->godinaRodenja=godinaRodenja2;
        q->Next=P->Next;
        P->Next=q;
    }
    else
        printf("\nGreska.");
    return 0;

}
void SortirajListu(Pozicija P)
{
    Pozicija q=NULL;
    Pozicija prevq=NULL;
    Pozicija tmp=NULL;
    Pozicija kraj=NULL;

    while(P->Next!=kraj)
    {
        prevq=P;
        q=P->Next;
        while(q->Next!=kraj)
        {

            if(strcmp(q->prezime, q->Next->prezime)>0)
        {
            tmp=q->Next;
            prevq->Next=tmp;
            q->Next=tmp->Next;
            tmp->Next=q;

            q=tmp;
        }
        prevq=q;
        q=q->Next;

        }
    kraj=q;
    }
}
