#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 100

typedef struct direktorij * Stablo;
struct direktorij{

        char ime[N];
        Stablo Brat;
        Stablo Dijete;
};

typedef struct Stog * Pozicija;
struct Stog
{
    Stablo El;
    Pozicija Next;
};

Pozicija Push(Pozicija red, Stablo P);
Stablo Pop(Pozicija red);
Pozicija PopStog(Pozicija red);
void Print(Stablo P);
void Brisi(Stablo P);
Stablo umetni(Stablo P, Stablo q);
Stablo trazi(Stablo P, char* ImeDirektorija, char* trenutni, int n, Pozicija red);

int main(void)
{
    struct direktorij C;
    struct Stog head = {.El=&C, .Next=NULL};

    char komanda[10],ImeDir[N],trenutni[100];
    Stablo q, current = &C;
    Pozicija trenutniStog = &head, h;
    int n=0,i;

    strcpy(trenutni,"");

    strcpy(C.ime, "C:");
    C.Brat=NULL;
    C.Dijete=NULL;

    while(1)
    {
        printf("%s%s\n", C.ime, trenutni);
        scanf("%s", komanda);
        if(strcmp(komanda, "md")==0)
        {
            scanf("%s", ImeDir);
            q=(Stablo)malloc(sizeof(struct direktorij));
            strcpy(q->ime, ImeDir);
            q->Brat=NULL;
            q->Dijete=NULL;
            current->Dijete=umetni(current->Dijete, q);
        }
        else if(strcmp(komanda, "cd")==0)
        {
            scanf("%s", ImeDir);
            n=strlen(trenutni);
            current=trazi(current, ImeDir, trenutni, n, trenutniStog);
            trenutniStog=Push(trenutniStog, current);
        }
        else if(strcmp(komanda, "cd..")==0)
        {
            if(current!=&C)
            {
                trenutniStog=PopStog(trenutniStog);
                current=Pop(trenutniStog);
            }
            for(i=strlen(trenutni)-2;i>=0;i--)
            {
                if(trenutni[i]==':')
                    break;
                trenutni[i]='\0';
            }
        }
        else if(strcmp(komanda, "dir")==0)
        {
            Print(current->Dijete);
        }
        else if(strcmp(komanda, "exit")==0)
        {
            Brisi(&C);
            return 0;
        }
        else
        {
            printf("Naredba nije valjana!\n");
        }

    }

    return 0;
}



Stablo umetni(Stablo P, Stablo q)
{
   if(P==NULL)
        return q;
   if(strcmp(P->ime, q->ime)<0)
        P->Brat=umetni(P->Brat,q);
   else if(strcmp(P->ime, q->ime)>0)
   {
       q->Brat=P;
       return q;
   }
   else
   {
       printf("\nNe moze!!\n");
       free(q);
   }
   return P;
}
Stablo trazi(Stablo P, char* ImeDirektorija, char* trenutni, int n, Pozicija red)
{
    int i;
    Stablo q=P;
    P=P->Dijete;
    while(P!=NULL)
    {
        if(strcmp(P->ime, ImeDirektorija)==0)
        {
            for(i=0;i<strlen(ImeDirektorija);i++)
                trenutni[n+i]=ImeDirektorija[i];
            trenutni[n+i]=':';
            trenutni[n+i+1]='\0';
            red=Push(red,P);
            return P;
        }
        P=P->Brat;
    }
    if(P==NULL)
    {
        printf("\nDirektorij nije pronaden!\n");
        return q;
    }
    return q;
}



Pozicija Push(Pozicija red, Stablo P)
{
    Pozicija q=NULL;
    q=(Pozicija)malloc(sizeof(struct Stog));
    q->El=P;
    q->Next=red;
    return q;
}
Stablo Pop(Pozicija red)
{
    Stablo q=NULL;
    q=red->El;
    return q;
}
Pozicija PopStog(Pozicija red)
{
    Pozicija q=NULL;
    q=red->Next;
    return q;
}
void Print(Stablo P)
{
    if(P==NULL)
       printf("\nDirektoriji ne postoje.\n");
    while(P!=NULL)
    {
        printf("\n %s", P->ime);
        P=P->Brat;
    }
}
void Brisi(Stablo P)
{
    if(P==NULL)
        return;
    Brisi(P->Brat);
    Brisi(P->Dijete);
    free(P);
}
