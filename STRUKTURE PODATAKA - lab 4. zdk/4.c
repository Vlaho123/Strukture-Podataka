#include<stdio.h>
#include<stdlib.h>
#define MAX_LINE 1024
typedef struct Polinom *Pozicija;
struct Polinom
{
    int koeficijent;
    int eksponent;
    Pozicija Next;
};
void Unos(int k, int p, Pozicija P);
void Ispis(Pozicija P);
void Mnozenje(Pozicija Produkt, Pozicija P1, Pozicija P2);
void Zbrajanje(Pozicija Zbroj, Pozicija P1, Pozicija P2);

int main(void)
{
    struct Polinom Head1={.Next =NULL, .koeficijent=0, .eksponent=0};
    struct Polinom Head2={.Next =NULL, .koeficijent=0, .eksponent=0};
    struct Polinom Zbroj={.Next =NULL, .koeficijent=0, .eksponent=0};
    struct Polinom Umnozak={.Next =NULL, .koeficijent=0, .eksponent=0};


    FILE *f=NULL;
    char buffer1[MAX_LINE]={0};
    char buffer2[MAX_LINE]={0};
    int koef, eksp, brojbajtova;
    f=fopen("Polinom.txt", "r");
    if(!f)
    {
        printf("Neispravno otvorena datoteka.");
        return NULL;
    }
        fgets(buffer1, MAX_LINE, f);
        sscanf(buffer1, "%d, %d, %n", koef, eks, brojbajtova);*/
        Unos(koef, eks, &Head1);

        fgets(buffer2, MAX_LINE, f);
        sscanf(buffer2, "%d %d %n", koef, eks, brojbajtova);
        Unos(koef, eks, &Head2);

        Zbrajanje(&Zbroj, &Head1, &Head2);
        printf("Zbroj ova dva polinoma iznosi: \n");
        Ispis(Zbroj.Next);
        printf("\n\n");
        Mnozenje(&Umnozak, &Head1, &Head2);
        printf("Produkt ova dva polinoma iznosi: \n");
        Ispis(Umnozak.Next);

        return 0;

}
void Unos(int k, int p, Pozicija P)
{
    Pozicija q;
    Pozicija Prev;
    Prev=P;
    P=P->Next;

    while(P!=NULL && P->eksponent>p)
    {
        Prev=P;
        P=P->Next;
    }

    if(P!=NULL && P->eksponent==p)
    {
       P->koeficijent+=k;
    }
    else
    {
        q=(Pozicija)malloc(sizeof(struct Polinom));
        q->eksponent=p;
        q->koeficijent=k;
        q->Next=P;
        Prev->Next=q;
    }

}
void Ispis(Pozicija P)
{
    int i=0;
    while(P!=NULL)
    {

        printf("Koeficijent %d.: %d  Eksponent %d. : %d\n", i+1, P->koeficijent, i+1, P->eksponent);
        i++;
        P=P->Next;
    }
}

void Mnozenje(Pozicija Produkt, Pozicija P1, Pozicija P2)
{
    Pozicija VracanjeNaPocetak=P2;;
    while(P1!=NULL)
    {
        P2=VracanjeNaPocetak;
        while(P2!=NULL)
        {
            Unos(P1->koeficijent * P2->koeficijent, P1->eksponent + P2->eksponent, Produkt);
            P2=P2->Next;
        }
        P1=P1->Next;
    }
}
void Zbrajanje(Pozicija Zbroj, Pozicija P1, Pozicija P2)
{
    Pozicija temp=NULL;
    while(P1!=NULL && P2!=NULL)
    {
        if((P1->eksponent)==(P2->eksponent))
        {
            Unos(P1->koeficijent+P2->koeficijent, P1->eksponent, Zbroj);
            P1=P1->Next;
            P2=P2->Next;
        }
        else if((P1->eksponent)>(P2->eksponent))
        {
            Unos(P1->koeficijent, P1->eksponent, Zbroj);
            P1=P1->Next;
        }
        else
        {
            Unos(P2->koeficijent, P2->eksponent, Zbroj);
            P2=P2->Next;
        }
    }
    if(P1!=NULL)
        temp=P1;
    else
        temp=P2;
    while(temp!=NULL)
    {
        Unos(temp->koeficijent, temp->eksponent, Zbroj);
        temp=temp->Next;
    }
}
