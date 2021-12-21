#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct CvorStabla * Stablo;
struct CvorStabla{

        int El;
        Stablo L;
        Stablo D;
};
Stablo umetni(Stablo P, int Element);
int ispisInorder(Stablo P);
int random(int min, int max);
int InorderUFile(Stablo P, FILE *f);
int zamjena(Stablo P);
int main(void)
{
    Stablo root=NULL;
    srand(time(NULL));
    FILE *f=fopen("inorder.txt", "w");
    root=umetni(root, random(10,90));
    root=umetni(root, random(10,90));
    root=umetni(root, random(10,90));
    root=umetni(root, random(10,90));
   /* root=umetni(root, 3);
    root=umetni(root, 4);
    root=umetni(root,2);
    root=umetni(root,1);
    root=umetni(root,6);
    root=umetni(root,2);
*/
    ispisInorder(root);

    InorderUFile(root,f);

    root->El=zamjena(root->L)+zamjena(root->D);

    InorderUFile(root,f);

    fclose(f);
    return 0;
}
int ispisInorder(Stablo P)
{
    if(P==NULL)
        return 0;
    ispisInorder(P->L);
    printf("%d ", P->El);
    ispisInorder(P->D);

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
    if(P->El>Element)
        P->D=umetni(P->D,Element);
    else if(P->El<Element)
        P->L=umetni(P->L,Element);
    else
        return P;
}
int random(int min, int max)
{
    int brmogucih=max-min+1;
    int gornjagranica=RAND_MAX-(RAND_MAX%brmogucih);
    int slucajni=rand();
    while(slucajni>gornjagranica)
        slucajni=rand();
    return slucajni%brmogucih+min;
}
int InorderUFile(Stablo P, FILE *f)
{
     if(P==NULL)
        return 0;
    InorderUFile(P->L, f);
    fprintf(f,"%d ", P->El);
    InorderUFile(P->D, f);

    return 0;
}
int zamjena(Stablo P)
{
    int t;
    if(P==NULL)
        return 0;
    t=P->El;
    P->El=zamjena(P->L)+zamjena(P->D);
    return t + P->El;
}
