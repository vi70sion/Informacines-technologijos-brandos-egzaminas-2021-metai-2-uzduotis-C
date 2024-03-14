#include <stdio.h>
#include <string.h>

const int max = 50; //max number of student

struct MOKINYS {
    char vardas[20];
    char dalykas[20];
    double vidurkis;    
};

struct DALYKAS {
    char pavadinimas[20];
    char vardai[50][20];
    int mokKiekis;
};

void sortByLessons( struct DALYKAS *D, int d);

int main(){
    
    FILE *dataFile = fopen("U2.txt", "r");
    FILE *resultFile = fopen("U2rez.txt", "w");

    struct MOKINYS M[max]; 
    int mok, sum, p, pazym, newmok;

    // read data from file
    int p1 = fscanf(dataFile,"%d", &mok); //number of students
    for (int i = 0; i < mok; i++)
    {
        int p1 = fscanf(dataFile, "%s %s %d", M[i].vardas, M[i].dalykas, &p);
        //p- number of grades
        sum = 0;
        for (int j = 0; j < p; j++)
        {
            int p1 = fscanf(dataFile,"%d",&pazym);
            sum += pazym;
        };
        M[i].vidurkis = (double)sum/p;
    }
    
    //removing lines with a grade below 9
    newmok = mok; //number of students after removing
    for (int i = 0; i < newmok; i++)
    {
        if (M[i].vidurkis < 9)
        {
            for (int j = i+1; j < newmok; j++)
            {
                M[j-1] = M[j];
            };
            i--; //need to be checked- is it ok when first line must be removed
            newmok--;
        }
    }

    // D[] data same as M[]
    struct DALYKAS D[newmok];
    for (int i = 0; i < newmok; i++)
    {
        strcpy(D[i].pavadinimas, M[i].dalykas);
        strcpy(D[i].vardai[0], M[i].vardas);
        D[i].mokKiekis = 1;
    }

    //looking for the same lessons names
    //adding name to the firs and removing same lesson line from D[] 
    int lessonsAll = newmok; //favorit lessons count
    int n;
    for (int i = 0; i < lessonsAll; i++)
    {
        for (int j = i+1; j < lessonsAll; j++)
        {
            if (strcmp(D[i].pavadinimas, D[j].pavadinimas) == 0)
            {   
                n = D[i].mokKiekis++;
                strcpy(D[i].vardai[n], D[j].vardai[0]);
                for (int k = j; k < lessonsAll; k++)
                {
                    strcpy(D[k].pavadinimas, D[k+1].pavadinimas);
                    strcpy(D[k].vardai[0], D[k+1].vardai[0]);
                    D[k].mokKiekis = 1;
                };
                j--;
                lessonsAll--;
            } 
        }
        i++;
    }

    sortByLessons(D, lessonsAll);

    //printing to resultFile D[]
    for (int i = 0; i < lessonsAll; i++)
    {
        fprintf(resultFile, "%s %d\n", D[i].pavadinimas, D[i].mokKiekis);
        for (int j = 0; j < D[i].mokKiekis; j++)
        {
            fprintf(resultFile, "%s\n", D[i].vardai[j]);
        }
    };

    fclose(dataFile);
    fclose(resultFile);
return 0;
}

void sortByLessons( struct DALYKAS *D, int d){
    struct DALYKAS T[d];
    for (int i = 0; i < d; i++)
    {
        if ((D[i].mokKiekis < D[i+1].mokKiekis) || ((D[i].mokKiekis == D[i+1].mokKiekis) && (strcmp(D[i].pavadinimas, D[i+1].pavadinimas) == 1)))
        {
            T[i] = D[i];
            D[i] = D[i+1];
            D[i+1] = T[i];
            i = -1; //from the begining
        }
    }
}

