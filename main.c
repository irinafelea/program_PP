#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANALE 100

int numar_canale;
int id_canal[CANALE];
char nume_canal[CANALE][CANALE];

int abonat_canale[CANALE];

double rating_canale[CANALE];
double top_rating[CANALE];

int top_canale[CANALE];



void citire_canale()
{
    FILE *fp = fopen("canale.txt", "r");

    fscanf(fp, "%d", &numar_canale);

    int i;
    for (i=0; i<numar_canale; ++i){
        fscanf(fp, "%d %s", &id_canal[i],
                            &nume_canal[i]);
    }
    fclose(fp);
}

void sortare(int tc[], double tr[], double rc[])
{
    int i, j, aux;
    for (i=0; i<numar_canale; i++)
        tr[i] = rc[i];

    for (i=0; i<numar_canale-1; i++)
        for (j=i+1; j<numar_canale; j++)
            if (tr[i] < tr[j]){
                aux = tr[i];
                tr[i] = tr[j];
                tr[j] = aux;

                aux = tc[i];
                tc[i] = tc[j];
                tc[j] = aux;
            }
            else
            if (tr[i] == tr[j] && tc[i] > tc[j]){
                aux = tc[i];
                tc[i] = tc[j];
                tc[j] = aux;
            }

}

int main()
{
    citire_canale();

    char nume, prenume, email, parola, data_nasterii, sex;

    int i;
    for (i=0; i<numar_canale; i++){
        abonat_canale[id_canal[i]-1] = 0;

        rating_canale[id_canal[i]-1] = 0;
        top_rating[id_canal[i]-1] = 0;

        top_canale[id_canal[i]-1] = id_canal[i];
    }



    int end_program=1;

    while (end_program){
        int alegere_meniu_principal = 0;
        printf("----- MENIU PRINCIPAL ----- \n");
        printf("1. Inregistrare\n2. Logare\n3. Top canale\n4. Iesire\n");
        while (alegere_meniu_principal < 1 || alegere_meniu_principal > 4){
            printf("Selectati optiunea dorita: ");
            scanf("%d", &alegere_meniu_principal);
        }

        system("cls");

        if (alegere_meniu_principal == 1){  //----------------------------------------------- INREGISTRARE --------------------------------------
            printf("----- Inregistrare ----- \n");
            printf("NUME: ");
            scanf("%s", &nume);
            printf("PRENUME: ");
            scanf("%s", &prenume);
            printf("ADRESA DE EMAIL: ");
            scanf("%s", &email);
            printf("PAROLA: ");
            scanf("%s", &parola);
            printf("DATA NASTERII (zz/ll/aaaa): ");
            scanf("%s", &data_nasterii);
            printf("SEX (feminin/masculin): ");
            scanf("%s", &sex);
        }
        if (alegere_meniu_principal == 2){  //----------------------------------------------- LOGARE --------------------------------------------
            printf("----- Logare ----- \n");
            printf("ADRESA DE EMAIL: ");
            scanf("%s", &email);
            printf("PAROLA: ");
            scanf("%s", &parola);

            system("cls");

            int logat = 1;
            while (logat){
                int alegere_logare = 0;
                printf("----- OPTIUNI ----- \n");
                printf("1. Canale\n2. Delogare\n");
                while (alegere_logare < 1 || alegere_logare > 2){
                    printf("Selectati optiunea dorita: ");
                    scanf("%d", &alegere_logare);
                }

                system("cls");

                if (alegere_logare == 1){               //----------------------------------- MENIUL CANALELOR -----------------------------------

                    int canale = 1;
                    while(canale){
                        printf("----- CANALE ----- \n");
                        int alegere_meniu_canale = 0;
                        printf("1. Canale disponibile\n2. Canale la care esti abonat\n3. Cautare\n4. Top canale\n5. Iesire\n");
                        while (alegere_meniu_canale < 1 || alegere_meniu_canale > 5){
                            printf("Selectati optiunea dorita: ");
                            scanf("%d", &alegere_meniu_canale);
                        }

                        system("cls");

                        if (alegere_meniu_canale == 1){     //-------------------------- CANALE DISPONIBILE -------------------------------------
                            printf("----- CANALE DISPONIBILE -----\n\n");
                            int i;
                            for (i=0; i<numar_canale; ++i){
                                printf("%d. %s \n", id_canal[i],
                                                    nume_canal[i]);
                            }

                            printf("Doriti sa accesati un canal? (da=1/ nu=0): ");
                            int raspuns;
                            scanf("%d", &raspuns);

                            system("cls");

                            if (raspuns == 1){
                                int alegere_canal = 0;
                                while (alegere_canal < 1 || alegere_canal> numar_canale){
                                        printf("Alegeti canalul (introduceti un numar intre 1 si %d): ", numar_canale);
                                        scanf("%d", &alegere_canal);
                                }

                                system("cls");

                                int abonare_rating = 1;
                                while(abonare_rating){
                                    int alegere_optiune = 0;
                                    printf("1. Abonare\n2. Dezabonare\n3. Rating\n4. Iesire\n");
                                    while (alegere_optiune < 1 || alegere_optiune > 4){
                                        printf("Selectati optiunea dorita: ");
                                        scanf("%d", &alegere_optiune);
                                    }

                                    system("cls");

                                    if (alegere_optiune == 1){  //--------------------------- ABONARE --------------------------------------------
                                        abonat_canale[alegere_canal-1] = 1;
                                        printf("Te-ai abonat la %s!!\n", nume_canal[alegere_canal-1]);
                                        system("pause");
                                    }

                                    if(alegere_optiune == 2){   //--------------------------- DEZABONARE -----------------------------------------
                                        abonat_canale[alegere_canal-1] = 0;
                                        printf("Te-ai dezabonat de la %s!!\n", nume_canal[alegere_canal-1]);
                                        system("pause");
                                    }

                                    if(alegere_optiune == 3){   //--------------------------- RATING ---------------------------------------------
                                        double rating = 0;
                                        while(rating<1 || rating>5){
                                            printf("Introduceti un numar (1-5): ");
                                            scanf("%lf", &rating);
                                        }
                                        rating_canale[alegere_canal-1] = rating;
                                        printf("\nAi oferit %.2lf rating pentru %s!!\n", rating, nume_canal[alegere_canal-1]);
                                        system("pause");
                                    }
                                    if (alegere_optiune == 4)
                                        abonare_rating = 0;
                                    system("cls");
                                }

                                system("cls");
                            }
                        }
                        if (alegere_meniu_canale == 2){     //-------------------------- CANALE LA CARE ESTI ABONAT -----------------------------
                            printf("----- CANALE LA CARE ESTI ABONAT -----\n");
                            int nr_canal;
                            for (nr_canal=0; nr_canal<=numar_canale; nr_canal++)
                                if (abonat_canale[nr_canal] == 1)
                                    printf("%s (id canal: %d)\n", nume_canal[nr_canal], id_canal[nr_canal]);
                            system("pause");
                        }
                        if (alegere_meniu_canale == 3){     //-------------------------- CAUTARE ------------------------------------------------
                            int alegere_canal = 0;
                            while (alegere_canal < 1 || alegere_canal > numar_canale){
                                printf("Introduceti numarul canalului pe care doriti sa il cautati (intre 1 si %d): ", numar_canale);
                                scanf("%d", &alegere_canal);
                            }

                            system("cls");

                            int abonare_rating = 1;
                            while(abonare_rating){
                                int alegere_optiune = 0;
                                printf("1. Abonare\n2. Dezabonare\n3. Rating\n4. Iesire\n");
                                while (alegere_optiune < 1 || alegere_optiune > 4){
                                    printf("Selectati optiunea dorita: ");
                                    scanf("%d", &alegere_optiune);
                                }

                                system("cls");

                                if (alegere_optiune == 1){  //--------------------------- ABONARE --------------------------------------------
                                    abonat_canale[alegere_canal-1] = 1;
                                    printf("Te-ai abonat la %s!!\n", nume_canal[alegere_canal-1]);
                                    system("pause");
                                }

                                if(alegere_optiune == 2){   //--------------------------- DEZABONARE -----------------------------------------
                                    abonat_canale[alegere_canal-1] = 0;
                                    printf("Te-ai dezabonat de la %s!!\n", nume_canal[alegere_canal-1]);
                                    system("pause");
                                }

                                if(alegere_optiune == 3){   //--------------------------- RATING ---------------------------------------------
                                    double rating = 0;
                                    while(rating<1 || rating>5){
                                        printf("Introduceti un numar (1-5): ");
                                        scanf("%lf", &rating);
                                    }
                                    rating_canale[alegere_canal-1] = rating;
                                    printf("\nAi oferit %.2lf rating pentru %s!!\n", rating, nume_canal[alegere_canal-1]);
                                    system("pause");
                                }
                                if(alegere_optiune == 4)
                                    abonare_rating = 0;

                                system("cls");

                            }
                        }
                        if (alegere_meniu_canale == 4){ //------------------------------ TOP CANALE -------------------------------------------
                            sortare(top_canale, top_rating, rating_canale);
                            printf("----- TOP CANALE -----\n");

                            int i=0;
                            int id=0;
                            int j = 0;
                            while(i<25 && id < numar_canale){
                                if (top_canale[j] == id_canal[id]  && j<numar_canale){
                                    printf("%s - %.2lf\n", nume_canal[id], top_rating[i]);
                                    i++;
                                    j++;
                                    id = 0;
                                }
                                else
                                    while (id_canal[id] != top_canale[j] && id < numar_canale)
                                        id++;
                            }

                            system("pause");
                        }


                        if (alegere_meniu_canale == 5){
                            canale = 0;
                        }
                        system("cls");
                    }
                }
                if (alegere_logare == 2){
                    logat = 0;
                }
                system("cls");
            }
        }
        if (alegere_meniu_principal == 3){  //----------------------------------------------- TOP CANALE --------------------------------------
            sortare(top_canale, top_rating, rating_canale);
            printf("----- TOP CANALE -----\n");

            int i=0;
            int id=0;
            int j = 0;
            while(i<25 && id < numar_canale){
                if (top_canale[j] == id_canal[id]  && j<numar_canale){
                    printf("%s - %.2lf\n", nume_canal[id], top_rating[i]);
                    i++;
                    j++;
                    id = 0;
                }
                else
                    while (id_canal[id] != top_canale[j] && id < numar_canale)
                        id++;
            }

            system("pause");
        }

        system("cls");

        if(alegere_meniu_principal == 4){   //----------------------------------------------- IESIRE --------------------------------------------
            printf("La revedere!!!");
            end_program = 0;
        }
    }
}
