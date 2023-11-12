
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cont_bancar.c"

FILE *fp;

void afisare_lista_tranzactii(int n) {
    /*
        Afisam lista totala de tranzactii
    */
   printf("\n");
   if(n) {
      for(int i = 0; i < n; ++i) {
        printf("  Tranzactia %d: \n", i + 1);
          printf("      - din data: %s\n", tranzactii[i].data);
          printf("      - cu descrierea: %s\n", tranzactii[i].descriere);
          printf("      - valoare: %d\n", tranzactii[i].valoare);
          printf("      - de tipul: ");
          if (tranzactii[i].tip == 'V')
              printf("venit\n");
          else
              printf("cheltuiala\n");
          printf("\n");
      }
   }
   else
     printf(" Nu exista tranzactii de niciun tip.\n");
   printf("\n");

}

void afisare_date_din_fisier() {
    /*
        Afisam datele din tranzactii din fisier pe consola
    */
    int nr_ordin, valoare;
    char data[12], descriere[201], tip;

    fp = fopen("financial_data.txt", "r");
    if (fp) {
        
        while(fscanf(fp, "tranzactia %d\n data %s\n descriere %[^\n]\n valoare %d\n tip %c\n", &nr_ordin, data, descriere, &valoare, &tip) != EOF) {
            printf("Tranzactia: %d\n", nr_ordin);
            printf(" - din data: %s\n", data);
            printf(" - cu descrierea: %s\n", descriere);
            printf(" - valoare: %d\n", valoare);
            if(tip == 'C')
                printf(" - tip: cheltuiala\n\n");
            else
                printf(" - tip: venit\n\n");
        }
        fclose(fp);
    }
    else 
        printf("\nEroare: Nu putem deschide fisierul pentru a citi.");
    
    
 
}

void adaugare_tranzactie(int n) {
    /*
        Adaugam o noua tranzactie
    */
   char data[11], descriere[201], tip;
   int valoare, zi, luna, an;
   bool ok = 1;
   printf(" - introduceti data: ");
   scanf("%s", data); // citim data
   getc(stdin);

   printf(" - introduceti descrierea: ");
   fgets(descriere, 201, stdin); // citim descrierea cu spatii, inclusiv enter-ul de la final
   descriere[strlen(descriere) - 1] = '\0'; // stergem caracterul new line care se afla inainte de NULL

   printf(" - introduceti valoarea: ");
   scanf("%d", &valoare); // citim valoarea
   
   printf(" - introduceti tipul: ");
   scanf(" %c", &tip); // citim tipul
   getchar();

   if (sscanf(data, "%d/%d/%d", &zi, &luna, &an) == 3) {
        if(!validare_data(zi, luna, an))
            printf("Data introdusa gresit!\n"), ok = 0;
   }//validam data

   if (!validare_tip(tip))
        printf("Tipul tranzactiei este introdus gresit!\n"), ok = 0;//validam tipul tranzactiei

   if (ok) {
    adaugare_valida(n, data, descriere, valoare, tip);//adaugam datele valide in vector
    /*
        Adaugam tranzactia in fisier
    */
    fp = fopen("financial_data.txt", "a");
    if (fp) {
        fprintf(fp, "tranzactia %d\n data %s\n descriere %s\n valoare %d\n tip %c\n", n + 1, data, descriere, valoare, tip);
        fclose(fp);
    }
    else {
        printf("\nEroare: Nu putem deschide fisierul pentru a scrie.");
    }
   }
   
}

void vizualizare_sold(int n) {
    /*
        Calculam soldul contului     
    */
   long long int sold = tranzactii[0].valoare;
   for (int i = 1; i < n; ++i) {
        if(tranzactii[i].tip == 'V')
            sold += tranzactii[i].valoare;
        else
            sold -= tranzactii[i].valoare;

   }

   printf("    Soldul contului dumneavoastra in acest moment este: %lld\n", sold);

}

void vizualizare_raport(int n, int luna_dorita) {
    /*
        Creeam raportul cu veniturile si cheltuielile contului
    */
   int cheltuieli = 0, venituri = 0, luna, zi, an;

   printf("    Raport privind istoricul dumneavoastra de tranzactii\n\n");

   printf("    Veniturile dumneavoastra sunt urmatoarele: \n\n");

   
   for(int i = 0; i < n; ++i) {
        sscanf(tranzactii[i].data, "%d/%d/%d", &zi, &luna, &an);
        if(tranzactii[i].tip == 'V' && luna == luna_dorita) {
            venituri ++;
            printf("         %d) %s in valoare de %d\n", venituri, tranzactii[i].descriere, tranzactii[i].valoare);
        }
   }
   
   printf("\n");
   printf("    Cheltuielile dumneavoastra sunt urmatoarele: \n\n");
   for(int i = 0; i < n; ++i) {
        sscanf(tranzactii[i].data, "%d/%d/%d", &zi, &luna, &an);
        if(tranzactii[i].tip == 'C' && luna == luna_dorita) {
            cheltuieli ++;
            printf("         %d) %s in valoare de %d\n", cheltuieli, tranzactii[i].descriere, tranzactii[i].valoare);
        }
   }
   printf("\n");


}

void print_meniu() {
    /*
        Printam meniul pentru banca
    */

   printf("  Va rugam sa alegeti o optiune dintre urmatoarele: \n");
   printf("       1) Vizualizati lista dumneavoastra de tranzactii; \n");
   printf("       2) Adaugati o tranzactie; \n");
   printf("       3) Vizualizati soldul contului dumneavoastra; \n");
   printf("       4) Vizualizati un raport cu istoricul dumneavoastra de venituri si cheltuieli pe o luna data; \n");
   printf("       5) Iesiti din meniu. \n");
}

void run() {
    /*
        Implementam consola interefata-utilizator
    */
   initializare_tranzactii();

    fp = fopen("financial_data.txt", "w+");
    fprintf(fp, "tranzactia %d\n data %s\n descriere %s\n valoare %d\n tip %c\n", 1, tranzactii[0].data, tranzactii[0].descriere, tranzactii[0].valoare, tranzactii[0].tip);
    fclose(fp);
    
   int exit = 0;
   int optiune;
   bool valid = 1;

   printf("             Bun venit la Banca X!    \n\n");

   while(!exit) {

        printf("\n");
        print_meniu();
        printf("\n");
        optiune = 0;
        valid = 1;
        printf("Optiunea aleasa de dumneavoastra este: ");
        scanf("%d", &optiune);
        if (!optiune){
            printf("Introduceti o optiune valida!\n");
            valid = 0;
        }
        printf("\n");

        if(valid)
            switch (optiune) {
                case 1:
                    int mod = 0;
                    printf("Modul de afisare al tranzactiilor este: \n");
                    printf("     1) din fisierul de date;\n");
                    printf("     2) direct pe consola;\n\n");
                    printf("Introduceti modul ales de dumneavoastra: ");
                    scanf("%d", &mod);
                    if(mod == 1)
                        afisare_date_din_fisier();
                    else if(mod == 2)
                        afisare_lista_tranzactii(n);
                    else
                        printf("Nu a fost introdus modul corect din cele de mai sus!\n\n");
                    break;
                case 2:
                    adaugare_tranzactie(n);
                    n++;
                    break;
                case 3:
                    vizualizare_sold(n);
                    break;
                case 4:
                    int luna;
                    printf("Introduceti luna: ");
                    scanf("%d", &luna);
                    printf("\n");

                    if(luna < 1 || luna > 12)
                        printf("Nu a fost introdusa o luna valida!\n\n");
                    else
                        vizualizare_raport(n, luna);
                    break;
                case 5:
                    exit = 1;
                    break;
            }

   }
   printf("\n       Va multumim ca ati ales Banca X! La revedere!\n\n");

}

