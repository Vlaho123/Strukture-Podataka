#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct CvorStabla * Stablo;
struct CvorStabla{

        int El;
        Stablo L;
        Stablo D;
};
int ispisInorder(Stablo P);
int ispisPreorder(Stablo P);
int ispisPostorder(Stablo P);
Stablo umetni(Stablo P, int Element);
Stablo pronadiElement(int Element, Stablo P);
Stablo Brisi(int Element, Stablo P);
Stablo pronadiMinElement(Stablo P);

int main(void)
{
    Stablo root=NULL;
    Stablo T=NULL;
    root=umetni(root, 4);
    root=umetni(root, 3);
    root=umetni(root, 2);
    root=umetni(root, 1);
    root=umetni(root, 6);
    root=umetni(root, 7);

    ispisInorder(root);
    T=pronadiElement(2, root);
    printf("\n\n %d ", T->El);

    Brisi(4, root);

    printf("\n\n");

    ispisPostorder(root);
    printf("\n\n");
    ispisPreorder(root);
    return 0;
}


int ispisInorder(Stablo P)
{
    if(P==NULL)
        return 0;
    ispisInorder(P->L);
    printf(" %d ", P->El);
    ispisInorder(P->D);

    return 0;
}
int ispisPreorder(Stablo P)
{
    if(P==NULL)
        return 0;
    printf(" %d ", P->El);
    ispisPreorder(P->L);
    ispisPreorder(P->D);

    return 0;
}
int ispisPostorder(Stablo P)
{
    if(P==NULL)
        return 0;
    ispisPostorder(P->L);
    ispisPostorder(P->D);
    printf(" %d ", P->El);

    return 0;
}
Stablo umetni(Stablo P, int Element)
{
    Stablo q;
    if(P==NULL)
        {
            q=(Stablo)malloc(sizeof(struct CvorStabla));
            q->El=Element;
            q->D=NULL;
            q->L=NULL;
            return q;
        }
    if(P->El<Element)
        P->D=umetni(P->D,Element);
    else if(P->El>Element)
        P->L=umetni(P->L,Element);
    else
        return P;
}
Stablo pronadiElement(int Element, Stablo P)
{
    if(P==NULL)
        return P;
    else if(P->El<Element)
        pronadiElement(Element, P->D);
    else if(P->El>Element)
        pronadiElement(Element, P->L);
    else
        return P;
}
Stablo pronadiMinElement(Stablo P)
{
    if(P==NULL)
        return NULL;
    else if(P->L==NULL)
        return P;
    else
        return pronadiMinElement(P->L);
}
Stablo Brisi(int Element, Stablo P)
{
    Stablo temp=NULL;

    if(P==NULL)
        return P;
    else if(Element<P->El)
        P->L=Brisi(Element, P->L);
    else if(Element>P->El)
        P->D=Brisi(Element, P->D);
    else if((P->L && P->D)!=NULL)
                    {
                        temp=pronadiMinElement(P->D);
                        P->El=temp->El;
                        P->D=Brisi(P->El, P->D);

                    }
    else
            {
                temp=P;
                if(P->L==NULL)
                    P=P->D;
                else
                    P=P->L;
                free(temp);
            }

 

        return P;
}

