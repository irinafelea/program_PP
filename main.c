#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define CANALE 100
#define USER 50

int numar_canale;

struct canal{
    char id_canal[CANALE][CANALE];
    char nume_canal[CANALE][CANALE];
    double rating_canale[CANALE];
    int numar_rating[CANALE];
}c;

struct persoana{
    char nume[USER];
    char prenume[USER];
    char email[USER];
    char parola[USER];
    char data_nasterii[USER];
    char gen[USER];
}p;

void inregistrare()
{
    FILE *fp = fopen("date-utilizatori.txt", "a+");

    int i;

    printf("NUME: "); scanf("%s", p.nume);
    printf("PRENUME: "); scanf("%s", p.prenume);

    char line[USER*6];
    int ok = 0;
    while (ok == 0){
        int aux = 1;
        printf("ADRESA DE EMAIL: "); scanf("%s", p.email);
        while (eof() != 1 && fgets(line, USER*6, fp)!= NULL){
            char *eml = strtok(line, " ");
            char *oth = strtok(NULL, "\n");

            if (strcmp(p.email, eml) == 0)
                aux = 0;
        }
        if (aux == 0)
            printf("Adresa de email introdusa exista deja!\n");
        else
            ok = 1;
    }

    while (strlen(p.parola)<8){
        printf("PAROLA (cel putin 8 caractere): "); scanf("%s", p.parola);
    }

    printf("DATA NASTERII (zz/ll/aaaa): "); scanf("%s", p.data_nasterii);
    printf("GEN (feminin/masculin): "); scanf("%s", p.gen);

    fprintf(fp, "%s %s %s;%s;%s;%s;\n", p.email,
                                        p.parola,
                                        p.nume,
                                        p.prenume,
                                        p.data_nasterii,
                                        p.gen);

    fclose(fp);

    FILE *fp2 = fopen("abonat-canale.txt", "a");
    fprintf(fp2, "%s ;\n", p.email);

    fclose(fp2);
}


int logat = 0;

char date[6*USER];
void logare()
{
    FILE *fp = fopen("date-utilizatori.txt", "r");
    char line[USER*6];

    printf("----- Logare ----- \n\n");
    printf("ADRESA DE EMAIL: ");
    scanf("%s", p.email);
    printf("PAROLA: ");
    scanf("%s", p.parola);

    int oke = 0, okp = 0;
    while (logat == 0 && eof() != 1 && fgets(line, USER*6, fp)!= NULL){
        char *em = strtok(line, " ");
        char *pass = strtok(NULL, " ");
        strcpy(date, strtok(NULL, "\n"));

        if(strcmp(p.email, em) == 0 && strcmp(p.parola, pass) == 0)
            logat = 1;
    }
    if (logat == 0){
        printf("\nAdresa de email sau parola invalida(e)!");
        sleep(2);
    }
    else{
        printf("\nTe-ai logat cu succes!");
        sleep(2);
    }
    system("cls");
}


double top_rating[CANALE];

char top_canale[CANALE][CANALE];

void citire_canale()
{
    FILE *fp = fopen("canale.txt", "r");

    fscanf(fp, "%d", &numar_canale);

    int i;
    char rat_can[CANALE];
    for (i=0; i<numar_canale; i++){
        fscanf(fp, "%s%s%lf%d", c.id_canal[i],
                                c.nume_canal[i],
                                &c.rating_canale[i],
                                &c.numar_rating[i]);
    }
    fclose(fp);
}

char alegere_canal[CANALE];

char abonat_canale[CANALE][CANALE*CANALE];
char email_abonat[USER][USER];

char w[CANALE][CANALE];
void abonare()
{
    FILE *fp = fopen("abonat-canale.txt", "r");
    char line[USER*6];
    int n=0;
    while (eof() != 1 && fgets(line, USER*6, fp)!= NULL){
        strcpy(email_abonat[n], strtok(line, " "));
        strcpy(abonat_canale[n], strtok(NULL, "\n"));
        n++;
    }
    fclose(fp);

    int i=0;
    int ok = 0;
    while(i<n && ok == 0){
        if (strcmp(email_abonat[i], p.email) == 0)
            ok = 1;
        i++;
    }

    int y = 0;
    int ok2=1;

    if (strcmp(abonat_canale[i-1], ";")==0){
        strcpy(abonat_canale[i-1], "");
    }
    else{
        char vector[CANALE*CANALE];
        strcpy(vector, abonat_canale[i-1]);
        strcat(vector, " ");
        while (strcmp(vector, " ")==1){
            char *can = strtok(vector, ";");
            char *oth = strtok(NULL, "\n");

            strcat(w[y], can);
            y++;
            strcpy(vector, oth);
        }

        for (int j=0; j<y; j++)
            if (strcmp(alegere_canal, w[j])==0)
                ok2 = 0;
    }

    if (ok2==1){
            strcat(abonat_canale[i-1], alegere_canal);
            strcat(abonat_canale[i-1], ";");
            printf("Te-ai abonat la canalul %s!", alegere_canal);
        }
        else
            printf("Esti deja abonat(a) la acest canal!");

    fp = fopen("abonat-canale.txt", "w");

    for (i=0; i<n; i++)
        fprintf(fp, "%s %s\n", email_abonat[i],
                               abonat_canale[i]);
    fclose(fp);
}

void dezabonare()
{
    FILE *fp = fopen("abonat-canale.txt", "r");
    char line[USER*6];
    int n=0;
    while (eof() != 1 && fgets(line, USER*6, fp)!= NULL){
        strcpy(email_abonat[n], strtok(line, " "));
        strcpy(abonat_canale[n], strtok(NULL, "\n"));
        n++;
    }
    fclose(fp);

    int i=0;
    int ok = 0;
    while(i<n && ok == 0){
        if (strcmp(email_abonat[i], p.email) == 0)
            ok = 1;
        i++;
    }

    int y = 0;
    int j;

    if (strcmp(abonat_canale[i-1], ";")==0){
        strcpy(abonat_canale[i-1], "");
    }
    else{
        char vector[CANALE*CANALE];
        strcpy(vector, abonat_canale[i-1]);
        strcat(vector, " ");
        while (strcmp(vector, " ")==1){
            char *can = strtok(vector, ";");
            char *oth = strtok(NULL, "\n");

            strcat(w[y], can);
            y++;
            strcpy(vector, oth);
        }
        ok=-1;
        for (j=0; j<y; j++)
            if (strcmp(alegere_canal, w[j])==0)
                ok = j;
    }

    strcpy(abonat_canale[i-1], "");

    if (ok!=-1){
        for (j=ok; j<y; j++)
            strcpy(w[j], w[j+1]);
        y--;
    }

    for (j=0; j<y; j++){
        strcat(abonat_canale[i-1], w[j]);
        strcat(abonat_canale[i-1], ";");
    }

    if(ok==-1)
        printf("Nu esti abonat(a) la acest canal!");
    else
        printf("Te-ai dezabonat de la canalul %s!", alegere_canal);

    if (y==0)
        strcpy(abonat_canale[i-1], ";");

    fp = fopen("abonat-canale.txt", "w");

    for (i=0; i<n; i++)
        fprintf(fp, "%s %s\n", email_abonat[i],
                               abonat_canale[i]);
    fclose(fp);
}

char ca[CANALE][CANALE];
void abonat()
{
    FILE *fp = fopen("abonat-canale.txt", "r");
    char line[USER*6];
    int n=0;
    while (eof() != 1 && fgets(line, USER*6, fp)!= NULL){
        strcpy(email_abonat[n], strtok(line, " "));
        strcpy(abonat_canale[n], strtok(NULL, "\n"));
        n++;
    }
    fclose(fp);

    int y=0;;

    int i=0;
    int ok = 0;
    while(i<n && ok == 0){
        if (strcmp(email_abonat[i], p.email) == 0){
            ok=1;
            if (strcmp(abonat_canale[i], ";")==0){
                printf("Nu esti abonat(a) la niciun canal!");
                sleep(2);
            }
            else{
                char vector[CANALE*CANALE];
                strcpy(vector, abonat_canale[i]);
                strcat(vector, " ");
                while (strcmp(vector, " ")==1){
                    strcpy(ca[y], "");
                    char *can = strtok(vector, ";");
                    char *oth = strtok(NULL, "\n");

                    strcat(ca[y], can);
                    y++;
                    strcpy(vector, oth);
                }
            }

        }
        else
            i++;
    }

    if (strcmp(abonat_canale[i], ";")==1){
        for (int j=0; j<y; j++)
            printf("%s\n", ca[j]);
        sleep(2);
    }
}

void rating_can()
{
    FILE *fp = fopen("canale.txt", "w");

    double rating = 0;
    while(rating<1 || rating>5){
        printf("Introduceti un numar (1-5): ");
        scanf("%lf", &rating);
    }

    int i;
    for (i=0; i<numar_canale; i++)
        if (strcmp(alegere_canal, c.nume_canal[i])==0){
        c.rating_canale[i] = (double)((c.rating_canale[i]*c.numar_rating[i] + rating)/(c.numar_rating[i]+1));
        c.numar_rating[i]++;
        printf("\nAi oferit %.2lf rating canalului %s!!", rating, alegere_canal);
        sleep(2);
    }

    fprintf(fp,"%d\n", numar_canale);

    for (i=0; i<numar_canale; i++)
        fprintf(fp, "%s %s %.2lf %d\n", c.id_canal[i],
                                        c.nume_canal[i],
                                        c.rating_canale[i],
                                        c.numar_rating[i]);

    fclose(fp);
}

void sortare(char tc[CANALE][CANALE], double tr[CANALE], double rc[CANALE])
{
    int i, j;
    for (i=0; i<numar_canale; i++){
        tr[i] = rc[i];
    }

    double aux;
    char can[CANALE];
    for (i=1; i<numar_canale; i++){
        aux = tr[i];
        strcpy(can, tc[i]);
        j=i-1;
        while (j>=0 && aux>tr[j]){
            tr[j+1] = tr[j];
            strcpy(tc[j+1], tc[j]);
            j--;
        }
        tr[j+1] = aux;
        strcpy(tc[j+1], can);
    }
}

int main()
{
    citire_canale();

    int i;
    for (i=0; i<numar_canale; i++){
        strcpy(top_canale[i], c.nume_canal[i]);
        top_rating[i] = c.rating_canale[i];
    }



    int end_program=1;

    while (end_program){
        int alegere_meniu_principal = 0;
        printf("----- MENIU PRINCIPAL ----- \n\n");
        printf("1. Inregistrare\n2. Logare\n3. Top canale\n4. Iesire\n\n");
        while (alegere_meniu_principal < 1 || alegere_meniu_principal > 4){
            printf("Selectati optiunea dorita: ");
            scanf("%d", &alegere_meniu_principal);
        }

        system("cls");

        if (alegere_meniu_principal == 1){  //----------------------------------------------- INREGISTRARE --------------------------------------
            printf("----- Inregistrare ----- \n\n");
            inregistrare();
        }
        if (alegere_meniu_principal == 2){  //----------------------------------------------- LOGARE --------------------------------------------
            logare();


            while (logat){
                int alegere_logare = 0;
                printf("----- OPTIUNI ----- \n\n");
                printf("1. Date utilizator \n2. Canale\n3. Delogare\n\n");
                while (alegere_logare < 1 || alegere_logare > 3){
                    printf("Selectati optiunea dorita: ");
                    scanf("%d", &alegere_logare);
                }

                system("cls");

                if (alegere_logare == 1){               //----------------------------------- DATE UTILIZATOR ------------------------------------
                    char *nume;
                    char *prenume;
                    char *data_nasterii;
                    char *gen;

                    nume =  strtok(date, ";");
                    prenume = strtok(NULL, ";");
                    data_nasterii = strtok(NULL, ";");
                    gen = strtok(NULL, ";");

                    printf("----- Date utilizator ----- \n\n");

                    printf("Nume: %s\n", nume);
                    printf("Prenume: %s\n", prenume);
                    printf("Adresa de email: %s\n", p.email);
                    printf("Data nasterii: %s\n", data_nasterii);
                    printf("Gen: %s\n", gen);

                    printf("\n");
                    system("pause");
                }

                if (alegere_logare == 2){               //----------------------------------- MENIUL CANALELOR -----------------------------------

                    int canale = 1;
                    while(canale){
                        printf("----- CANALE ----- \n\n");
                        int alegere_meniu_canale = 0;
                        printf("1. Canale disponibile\n2. Canale la care esti abonat\n3. Cautare\n4. Top canale\n5. Iesire\n\n");
                        while (alegere_meniu_canale < 1 || alegere_meniu_canale > 5){
                            printf("Selectati optiunea dorita: ");
                            scanf("%d", &alegere_meniu_canale);
                        }

                        system("cls");

                        if (alegere_meniu_canale == 1){     //-------------------------- CANALE DISPONIBILE -------------------------------------
                            printf("----- CANALE DISPONIBILE -----\n\n");
                            int i;
                            for (i=0; i<numar_canale; ++i){
                                printf("id:%s - %s \n", c.id_canal[i],
                                                        c.nume_canal[i]);
                            }

                            printf("\n");
                            printf("Doriti sa accesati un canal? (da=1/ nu=0): ");
                            int raspuns;
                            scanf("%d", &raspuns);


                            printf("\n");

                            if (raspuns == 1){
                                printf("Introduceti numele canalului: "); scanf("%s", &alegere_canal);

                                int i=0, ok=0;
                                while (i<numar_canale && ok == 0){
                                    if(strcmp(alegere_canal, c.nume_canal[i]) == 0){
                                        ok = 1;
                                    }
                                    i++;
                                }

                                system("cls");

                                if (ok == 1){
                                    int abonare_rating = 1;
                                    while(abonare_rating){
                                        int alegere_optiune = 0;
                                        printf("1. Abonare\n2. Dezabonare\n3. Rating\n4. Iesire\n\n");
                                        while (alegere_optiune < 1 || alegere_optiune > 4){
                                            printf("Selectati optiunea dorita: ");
                                            scanf("%d", &alegere_optiune);
                                        }

                                        system("cls");

                                        if (alegere_optiune == 1){  //--------------------------- ABONARE --------------------------------------------
                                            abonare();
                                            sleep(2);
                                        }

                                        if(alegere_optiune == 2){   //--------------------------- DEZABONARE ------------------------------------------
                                            dezabonare();
                                            sleep(2);
                                        }

                                        if(alegere_optiune == 3){   //--------------------------- RATING ---------------------------------------------
                                            rating_can();
                                        }

                                        if (alegere_optiune == 4)
                                            abonare_rating = 0;
                                        system("cls");
                                    }
                                }
                                else{
                                    printf("Acest canal nu exista!");
                                    sleep(2);
                                }

                                system("cls");
                            }
                        }

                        if (alegere_meniu_canale == 2){     //-------------------------- CANALE LA CARE ESTI ABONAT -----------------------------
                            printf("----- CANALE LA CARE ESTI ABONAT -----\n\n");
                            abonat();
                        }

                        if (alegere_meniu_canale == 3){     //-------------------------- CAUTARE ------------------------------------------------
                            printf("Introduceti numele canalului: "); scanf("%s", &alegere_canal);

                            int i=0, ok=0;
                            while (i<numar_canale && ok == 0){
                                if(strcmp(alegere_canal, c.nume_canal[i]) == 0){
                                    ok = 1;
                                }
                                i++;
                            }

                            system("cls");

                            if (ok == 1){
                                int abonare_rating = 1;
                                while(abonare_rating){
                                    int alegere_optiune = 0;
                                    printf("1. Abonare\n2. Dezabonare\n3. Rating\n4. Iesire\n\n");
                                    while (alegere_optiune < 1 || alegere_optiune > 4){
                                        printf("Selectati optiunea dorita: ");
                                        scanf("%d", &alegere_optiune);
                                    }

                                    system("cls");

                                    if (alegere_optiune == 1){  //--------------------------- ABONARE --------------------------------------------
                                        abonare();
                                        sleep(2);
                                    }

                                    if(alegere_optiune == 2){   //--------------------------- DEZABONARE ------------------------------------------
                                        dezabonare();
                                        sleep(2);
                                    }

                                    if(alegere_optiune == 3){   //--------------------------- RATING ---------------------------------------------
                                        rating_can();
                                    }

                                    if (alegere_optiune == 4)
                                        abonare_rating = 0;
                                    system("cls");
                                }
                            }

                            else{
                                printf("Acest canal nu exista!");
                                sleep(2);
                            }
                        }

                        if (alegere_meniu_canale == 4){ //------------------------------ TOP CANALE -------------------------------------------
                            sortare(top_canale, top_rating, c.rating_canale);

                            printf("----- TOP CANALE -----\n\n");

                            int i=0;
                            for (i=0; i<25; i++)
                                printf("%s - %.2lf\n", top_canale[i], top_rating[i]);

                            printf("\n");
                            system("pause");
                        }


                        if (alegere_meniu_canale == 5){
                            canale = 0;
                        }
                        system("cls");
                    }
                }
                if (alegere_logare == 3){
                    logat = 0;
                }
                system("cls");
            }
        }

        if (alegere_meniu_principal == 3){  //----------------------------------------------- TOP CANALE --------------------------------------
            sortare(top_canale, top_rating, c.rating_canale);

            printf("----- TOP CANALE -----\n\n");

            int i=0;
            for (i=0; i<25; i++)
                printf("%s - %.2lf\n", top_canale[i], top_rating[i]);

            printf("\n");
            system("pause");
        }

        system("cls");

        if(alegere_meniu_principal == 4){   //----------------------------------------------- IESIRE --------------------------------------------
            printf("La revedere!!!");
            end_program = 0;
        }
    }
}
