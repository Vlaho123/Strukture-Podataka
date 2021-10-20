#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 100
#define MAX_SIZE (128)
#define MAX_LINE (1024)
typedef struct _student{
        char ime[MAX_SIZE];
        char prezime[MAX_SIZE];
        double bodovi;

}student;

int procitajBrojRedakaIzDatoteke(char* nazivDatoteke);
student* AlocirajProcitajIzDatoteke(int brojStudenata, char* nazivDatoteke);

int main(void)
{
    char datoteka[M];
    int brojac, i;
    student* st;

    printf("Ime datoteke: ");
    scanf("%s", datoteka);

    brojac=procitajBrojRedakaIzDatoteke(datoteka);

    printf("Ime\tPrezime\t\tApsolutni Bodovi\tRelativni bodovi\n");
    st=AlocirajProcitajIzDatoteke(brojac,datoteka);

    for(i=0;i<brojac;i++)
        printf("%s\t%s\t%lf\t%.3lf\n", st[i].ime, st[i].prezime, st[i].bodovi, st[i].bodovi/80*100);

    return 0;
}
int procitajBrojRedakaIzDatoteke(char* nazivDatoteke)
{
    int brojac=0;
    FILE* datoteka=NULL;
    char buffer[MAX_LINE]={0};

    datoteka=fopen(nazivDatoteke, "r");
    if(!datoteka)
    {
        printf("Neuspjesno otvaranje datoteke!\n");
        return -1;
    }
    while(!feof(datoteka))
    {
        fgets(buffer, MAX_LINE, datoteka);
        brojac++;
    }

    fclose(datoteka);
    return brojac;
}
student* AlocirajProcitajIzDatoteke(int brojStudenata, char* nazivDatoteke)
{
    int brojac=0;
    FILE* datoteka=NULL;
    student* studenti = NULL;

    studenti=(student*)malloc(brojStudenata * sizeof(student));
    datoteka=fopen(nazivDatoteke, "r");
    if(!datoteka)
    {
        printf("Greska");
        return NULL;
    }
    while(!feof(datoteka))
    {
        fscanf(datoteka, " %s, %s, %lf", studenti[brojac].ime, studenti[brojac].prezime, studenti[brojac].bodovi);
        brojac++;
    }
    fclose(datoteka);
    return studenti;


}
