#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOTAL 2000
typedef struct {
    char produs[256];
    int cantitate;
} Comanda;

// Imi afisez optiunile din meniu
int menu() {
    int optiune;
    printf("------- Meniu --------\n");
    printf("1.Editare produs\n");
    printf("2.Adaugare produs\n");
    printf("3.Stergere produs\n");
    printf("4.Comanda produs\n");
    printf("5.Cauta produs dupa numele produsului\n");
    printf("6.Cauta produs dupa tara fabricarii produsului\n");
    printf("7.Exit\n");
    printf("----------------------\n");
    printf("Alege optiunea dorita: ");
    scanf("%d", &optiune); // utilizatorul introduce optiunea dorita
    getchar();  //Se elimina \n character rămas in stringul tastat care este salvat temporar
    printf("\n");
    system("cls");
    return optiune;
}

//Se scriu in fisier datele produsului pe care dorim sa il adaugam
void adaugare_in_fisier(char produs[256], char tara[20], int cantitate, char descriere[200]) {
    FILE *f = fopen("stock.txt", "a");
    fprintf(f, "%s/", produs);
    fprintf(f, "%d/", cantitate);
    fprintf(f, "%s/", tara);
    fprintf(f, "%s\n", descriere);
    fclose(f);
}

//Editeaza produsul
void editare_produs() {
    char produs[256];
    printf("Introduceti \033[1;31mnumele\033[0m prousului pe care doriti sa-l editati:");
    scanf("%s", &produs);
    int raspuns;
    char new_produs[256];
    char new_cantitate[10];
    char new_tara[20];
    char new_descriere[200];
    char continut1[TOTAL];
    char continut2[TOTAL];
    char continut3[TOTAL];
    char continut4[TOTAL];
    char continut5[TOTAL];
    char continut_final[TOTAL];


    printf("Vrei sa editezi \033[1;31mnumele\033[0m produsului?\n");
    printf("1.Da\n");
    printf("2.Nu\n");
    scanf("%d", &raspuns);
    getchar(); //Se elimina \n character ramas in raspunsul introdus de utilizator

    if (raspuns==1)
    {
        printf("Introdu noul \033[1;31mnume\033[0m de produs:\n");
        fgets(new_produs, sizeof(new_produs), stdin);
        new_produs[strcspn(new_produs, "\n")] = 0; //Sterge \n character pt a fi datele scrise corect in fisier
    }
    else
    {
        strcpy(new_produs, produs);
    }
    printf("Vrei sa editezi \033[1;32mcantitatea\033[0m produsului?:\n");
    printf("1.Da\n");
    printf("2.Nu\n");
    scanf("%d", &raspuns);
    getchar(); //Se elimina \n character de la sfarsitul raspunsului introdus de utilizator
    if (raspuns==1)
    {
        printf("Introdu \033[1;32mcantitatea\033[0m dorita a produs:\n");
        fgets(new_cantitate, sizeof(new_cantitate), stdin);
        new_cantitate[strcspn(new_cantitate, "\n")] = 0; //Se elimina \n character pentru a fi datele scrise corect in fisier

    }
    else
    {
        strcpy(new_cantitate, "");
    }
    printf("Vrei sa editezi \033[1;34mtara\033[0m produsului?:\n");
    printf("1.Da\n");
    printf("2.Nu\n");
    scanf("%d", &raspuns);
    getchar(); //Se elimina \n character de la sfarsitul raspunsului introdus de utiliator
    if (raspuns==1)
    {
        printf("Introdu \033[1;34mtara\033[0m dorita pentru produs\n");
        fgets(new_tara, sizeof(new_tara), stdin);
        new_tara[strcspn(new_tara, "\n")] = 0; //Se elimina \n character pentru a fi datele scrise frumos in fisier
    }
    else
    {
        strcpy(new_tara, "");
    }
    printf("Vrei sa editeti \033[1;33mdescrierea\033[0m produsului?\n");
    printf("1.Da\n");
    printf("2.Nu\n");
    scanf("%d", &raspuns);
    getchar(); //Se elimina \n character de la raspunsul introdus
    if (raspuns==1)
    {
        printf("Introdu \033[1;33mdescrierea\033[0m dorita pentru produs\n");
        fgets(new_descriere, sizeof(new_descriere), stdin);
        new_descriere[strcspn(new_descriere, "\n")] = 0; //Se elimina \n character pentru a fi datele scrise corect in fisier
    }
    else
    {
        strcpy(new_descriere, "");
    }

    FILE *read = fopen("stock.txt", "r"); // se deschide fisierul pentru a se citi in el
    FILE *write = fopen("stock2.txt", "w"); //se deschide fisierul pentru a se scrie in el
    char linie[TOTAL];
    char linie_copy[TOTAL];

    while (fgets(linie,TOTAL,read) != NULL) { //Se citeste fiecare linie din fisier
        strcpy(linie_copy, linie);
        char *tok = strtok(linie_copy,"/");
        if (strcmp(tok,produs) != 0) //Daca produsul din linia citica nu este cel dorit de utilizator, linia este scrisa in noul fisier
        {
            fprintf(write, "%s", linie);
        }
        else
        {
            if (strcmp(new_produs, produs) == 0) //Daca produsul din linia citita este cel dorit de utilizator,are loc modificarea
            {
                strncpy(new_produs, tok, sizeof(new_produs) - 1);
                new_produs[sizeof(produs) - 1] = '\0';
            }
            tok = strtok(NULL, "/"); //
            if (strcmp(new_cantitate, "") == 0) //daca cantitatea nu a fost modificata
            {
                if (tok != NULL) {
                    strncpy(new_cantitate, tok, sizeof(new_cantitate) - 1); //se adauga in new_cantitate cantitatea produsului citita din linie
                    new_cantitate[sizeof(new_cantitate) - 1] = '\0'; //Se elimina \n character pentru a fi scrise corect atele in fisier
                }
            }

            tok = strtok(NULL, "/");
            if (strcmp(new_tara, "") == 0)//daca tara nu a fost modificata
            {
                if (tok != NULL) {
                    strncpy(new_tara, tok, sizeof(new_tara) - 1); // se scrie in new_tara tara citita din linie
                    new_tara[sizeof(new_tara) - 1] = '\0'; //Se elimina \n character pentru a fi scrise datele corect in fisier
                }
            }

            tok = strtok(NULL, "/");
            if (strcmp(new_descriere, "") == 0) //daca descrierea nu a fost modificata
            {
                if (tok != NULL) {
                    strncpy(new_descriere, tok, sizeof(new_descriere) - 1); //se scrie in new_descriere descrierea citita din linie
                    new_descriere[sizeof(new_descriere) - 1] = '\0'; //Se elimina \n character pentru ca datele sa fie scrise corect in fisier
                }
            }

            strncpy(continut1 , strcat(new_produs, "/"), sizeof(continut1) - 1);

            strncpy(continut2 , strcat(continut1, new_cantitate), sizeof(continut2) - 1);

            strncpy(continut3 , strcat(continut2, "/"), sizeof(continut3) - 1);

            strncpy(continut4, strcat(continut3, new_tara), sizeof(continut4) - 1 );

            strncpy(continut5, strcat(continut4, "/"), sizeof(continut5) - 1);

            strncpy(continut_final, strcat(continut5, new_descriere), sizeof(continut_final) - 1);



            fprintf(write, "%s\n", continut_final); //Se scrie in noul fisier linia editata
        }
    }

    fclose(read);
    fclose(write);

    remove("stock.txt");
    rename("stock2.txt", "stock.txt");
}

//Afiseaza detalile produsului cautat
int afisarea_detalii_produs(char linie[TOTAL]) {
    char produs[256];
    char cantitate[11];
    char tara[20];
    char descriere[200];

    char *tok = strtok(linie, "/");

    if (tok != NULL) {
        strncpy(produs, tok, sizeof(produs) - 1);
        produs[sizeof(produs) - 1] = '\0';
    }

    tok = strtok(NULL, "/");
    if (tok != NULL) {
        strncpy(cantitate, tok, sizeof(cantitate) - 1);
        cantitate[sizeof(cantitate) - 1] = '\0';
    }

    tok = strtok(NULL, "/");
    if (tok != NULL) {
        strncpy(tara, tok, sizeof(tara) - 1);
        tara[sizeof(tara) - 1] = '\0';
    }

    tok = strtok(NULL, "/");
    if (tok != NULL) {
        strncpy(descriere, tok, sizeof(descriere) - 1);
        descriere[sizeof(descriere) - 1] = '\0';
    }


    printf("Produsul este: \033[1;31m%s\033[0m\n", produs);
    printf("Cantitatea este: \033[1;32m%s\033[0m\n", cantitate);
    printf("Tara este: \033[1;34m%s\033[0m\n", tara);
    printf("Descriere: \033[1;33m%s\033[0m\n", descriere);


    int numar = atoi(cantitate);
    return numar;
}

//Cauta produsul dupa nume
int cautare_produs_nume(char produs[256])
{
    FILE *f = fopen("stock.txt", "r");
    char linie[TOTAL];
    char linie_copy[TOTAL];
    int cantitate = 0;



    while (fgets(linie,TOTAL,f) != NULL) {
        strcpy(linie_copy, linie);
        char *produs_fisier = strtok(linie_copy,"/");
        if (strcmp(produs_fisier,produs) == 0)
        {
            cantitate = afisarea_detalii_produs(linie);
            break;
        }
    }


    fclose(f);

    return cantitate;
}


//Cauta produsul dupa tara
void cautare_produs_tara() {
    FILE *f = fopen("stock.txt", "r");
    char linie[TOTAL];
    char linie_copy[TOTAL];
    int count =0;
    printf("Introdu \033[1;34mtara\033[0m produsului pe care doriti sa il cautati: ");

    char tara[20];
    scanf("%s", tara);

    printf("\n");

    while (fgets(linie,TOTAL,f) != NULL) {
        strcpy(linie_copy, linie);
        char *tara_fisier = strtok(linie_copy,"/");
        tara_fisier = strtok(NULL,"/");
        tara_fisier = strtok(NULL,"/");
        if (tara_fisier != NULL) {
            if (tara_fisier[sizeof(tara_fisier)-1] == '\n') {
                tara_fisier[sizeof(tara_fisier) - 1] = '\0';
            }
        }

        if (strcmp(tara_fisier,tara) == 0)
        {
            afisarea_detalii_produs(linie);
            count = 1;
        }


    }

    if (count == 0) {
        printf("Nu s-a gasit niciun produs cu tara introdusa");
    }

    getchar();
}

//Se realizeaza comanda produsului
void comanda_produs() {
    Comanda c;
    int raspuns;
    int cantitate_dorita;
    int cantitate_dupa_comanda;
    char cantitate_dupa_comanda_char[10];
    char new_produs[256];
    char new_cantitate[10];
    char new_tara[20];
    char new_descriere[200];
    char continut_final[TOTAL];



    printf("Introdu \033[1;31mnumele\033[0m produsului pe care doriti sa il cautati:");
    fgets(c.produs, sizeof(c.produs), stdin);
    c.produs[strcspn(c.produs, "\n")] = 0;

    int cantitate_produs_int = cautare_produs_nume(c.produs);

    while (cantitate_produs_int == 0) {
        printf("Produsul nu se afla in stoc. Introdu un produs existent in stoc: ");
        fgets(c.produs, sizeof(c.produs), stdin);
        c.produs[strcspn(c.produs, "\n")] = 0;
        cantitate_produs_int = cautare_produs_nume(c.produs);
    }

    printf("Introdu \033[1;32mcantitatea\033[0m dorita:\n");
    scanf("%d", &c.cantitate);
    getchar();
    while (c.cantitate <= 0 || c.cantitate> cantitate_produs_int) {

        printf("Cantitatea introdusa nu este valida(cantitatea introdusa depaseste stocul magazinului).\n");
        printf("Introdu din nou cantitatea dorita: ");
        scanf("%d", &c.cantitate);
        getchar();
    }

    printf("Doriti sa plasati comanda\n");
    printf("1.Da\n");
    printf("2.Nu\n");
    scanf("%d", &raspuns);
    getchar();

    while (raspuns != 1 && raspuns != 2) {
        printf("Introdu un raspuns valid (1 sau 2)");
        scanf("%d", &raspuns);
        getchar();
    }

    if(raspuns == 1) {
        cantitate_dupa_comanda = cantitate_produs_int - c.cantitate;
        sprintf(cantitate_dupa_comanda_char, "%d",cantitate_dupa_comanda);

        FILE *read = fopen("stock.txt", "r");
        FILE *write = fopen("stock2.txt", "w");
        char linie[TOTAL];
        char linie_copy[TOTAL];


        while (fgets(linie, TOTAL, read) != NULL) {
            strcpy(linie_copy, linie);
            char *tok = strtok(linie_copy, "/");

            if (strcmp(tok, c.produs) != 0) {
                // produs diferit -> copiem linia originala
                fprintf(write, "%s", linie);
            } else {
                // produs gasit -> inlocuim cantitatea
                strcpy(new_produs, tok);

                tok = strtok(NULL, "/"); // cantitatea veche – ignorata
                strcpy(new_cantitate, cantitate_dupa_comanda_char);

                tok = strtok(NULL, "/"); // tara
                strcpy(new_tara, tok);

                tok = strtok(NULL, "/"); // descriere
                strcpy(new_descriere, tok);
                new_descriere[strcspn(new_descriere, "\n")] = 0;

                // scriere linie actualizata
                snprintf(continut_final, TOTAL, "%s/%s/%s/%s\n", new_produs, new_cantitate, new_tara, new_descriere);
                fprintf(write, "%s", continut_final);
            }
        }
        fclose(read);
        fclose(write);


        remove("stock.txt");
        rename("stock2.txt", "stock.txt");

        // Salvare comanda în fisier
        FILE *comanda = fopen("comanda.txt", "a");
        fprintf(comanda, "%s/%d\n", c.produs, c.cantitate);
        fclose(comanda);

        printf("Comanda a fost plasata cu succes!\n");
    }

}

//Sterge produsul dorit
int stergere_produs() {
    printf("Introdu \033[1;31mnumele\033[0m produsul pe care doriti sa il stergeti: ");
    char produs[256];
    int total = 256 * sizeof(char) + 20 * sizeof(char) + 200 * sizeof(char) + sizeof(int) + 3 * sizeof(char);
    scanf("%s", produs);
    FILE *read = fopen("stock.txt", "r");
    FILE *write = fopen("stock2.txt", "w");


    char linie[total];
    char linie_copy[total];

    while (fgets(linie,total,read) != NULL) {
        strcpy(linie_copy, linie);
        char *produs_fisier = strtok(linie_copy,"/");
        if (strcmp(produs_fisier,produs) != 0)
        {
            fprintf(write, "%s", linie);
        }
    }

    fclose(read);
    fclose(write);

    remove("stock.txt");
    rename("stock2.txt", "stock.txt");

    getchar();

    return 0;

}

//Se adauga produsul dorit
int adauga_produs() {
    char produs[256], tara[20], descriere[200];
    int cantitate;

    // Citirea produsului
    printf("\nIntroduceti \033[1;31mnumele\033[0m produsului: ");

    fgets(produs, sizeof(produs), stdin);
    produs[strcspn(produs, "\n")] = 0;  // Elimină newline-ul dacă există

    // Citirea cantității
    printf("\nIntroduceti \033[1;32mcantitatea\033[0m produsului: ");

    scanf("%d", &cantitate);
    getchar();  // Consumă newline-ul lăsat de scanf

    // Citirea țării
    printf("\nIntroduceti \033[1;34mtara\033[0m produsului: ");

    fgets(tara, sizeof(tara), stdin);
    tara[strcspn(tara, "\n")] = 0;  // Elimină newline-ul dacă există

    // Citirea descrierii
    printf("\nIntroduceti \033[1;33mdescrierea\033[0m produsului: ");
    fgets(descriere, sizeof(descriere), stdin);
    descriere[strcspn(descriere, "\n")] = 0;  // Elimină newline-ul dacă există

    adaugare_in_fisier(produs, tara, cantitate, descriere);




    return 0;
}


int main(void) {
    int running=1;
    //Iesirea din program cand dorim
    while(running) {
        int obtiune= menu();
        switch(obtiune) {
            case 1:
                printf("------- Editare Produs --------\n");
                editare_produs();
                printf("-------------------------------\n");
                printf("Apasa pe ENTER pentru a continua.");
                getchar();
                system("cls");
                break;
            case 2:
                printf("------- Adaugare Produs -------\n");
                adauga_produs();
                printf("-------------------------------\n");
                printf("Apasa pe ENTER pentru a continua.");
                getchar();
                system("cls");
                break;
            case 3:
                printf("------- Stergere Produs -------\n");
                stergere_produs();
                printf("-------------------------------\n");
                printf("Apasa pe ENTER pentru a continua.");
                getchar();
                system("cls");
                break;
            case 4:
                printf("-------- Comanda Produs -------\n");
                comanda_produs();
                printf("-------------------------------\n");
                printf("Apasa pe ENTER pentru a continua.");
                getchar();
                system("cls");
                break;
            case 5:
                char produs[256];
                printf("--- Cautare Produs Dupa Nume ---\n");
                printf("Introduceti \033[1;31mnumele\033[0m produsului cautat: \n");

                scanf("%s", produs);
                getchar();
                printf("\n");
                int x = cautare_produs_nume(produs);
                if(x == 0) {
                    printf("Produsul nu se afla in stoc.\n");
                }
                printf("--------------------------------\n");
                printf("Apasa pe ENTER pentru a continua.");
                getchar();
                system("cls");
                break;
            case 6:
                printf("--- Cautare Produs Dupa Tara ---\n");
                cautare_produs_tara();
                printf("--------------------------------\n");
                printf("Apasa pe ENTER pentru a continua.");
                getchar();
                system("cls");
                break;
            case 7:
                running=0;
                break;
        }
    }

    printf("La revedere! Apasa pe ENTER pentru a iesi din program.");
    getchar();
    return 0;
}
