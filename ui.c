
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cont_bancar.c"

/*
        Creați o aplicație care permite utilizatorului să înregistreze și 
    să gestioneze date financiare simple, cum ar fi tranzacțiile: veniturile și cheltuielile.

    Structura tranzactiilor este definita printr-un vector, unde:
        - data este un string, ziua, luna si anul fiind despartite de '/'
              EX: tranzactii[0].data = "01/01/2000"
        - descrierea este tot un string care include si spatii
              EX: tranzactii[0].descriere = "Carte sf"
        - valoarea este o valoarea intreaga de tip integer
        - tipul este un singur caracter ('C' = cheltuiala, 'V' = venit)
    
*/

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
          if (tranzactii[i].tip == 'V') //daca tipul tranzactiei este 'V', atunci printam "venit"
              printf("venit\n");
          else
              printf("cheltuiala\n");   //daca tipul tranzactiei este 'C', atunci printam "cheltuiala"
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

    fp = fopen("financial_data.txt", "r"); //deschidem fisierul unde am stocat tranzactiile, prin modul "read only"
    if (fp) {
        /*
            Citim intrarile formatate dintr-un flux, pana cand ajungem la capatul fisierului
        */
        while(fscanf(fp, "tranzactia %d\n data %s\n descriere %[^\n]\n valoare %d\n tip %c\n", &nr_ordin, data, descriere, &valoare, &tip) != EOF) {
            printf("Tranzactia: %d\n", nr_ordin);
            printf(" - din data: %s\n", data);
            printf(" - cu descrierea: %s\n", descriere);
            printf(" - valoare: %d\n", valoare);
            if(tip == 'C')
                printf(" - tip: cheltuiala\n\n"); //daca tipul tranzactiei este 'C', atunci printam "cheltuiala"
            else
                printf(" - tip: venit\n\n");      //daca tipul tranzactiei este 'V', atunci printam "venit"
        }
        fclose(fp); //inchidem fisierul
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
        Adaugam tranzactia in fisier, dand append in acesta
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
        if(tranzactii[i].tip == 'V')       //daca tranzactia este de tip venit, o adaugam in sold
            sold += tranzactii[i].valoare;
        else                               //daca nu este de tip venit, o scadem din sold
            sold -= tranzactii[i].valoare;

   }

   printf("    Soldul contului dumneavoastra in acest moment este: %lld\n", sold);

}

void vizualizare_raport(int n, int luna_dorita) {
    /*
        Creeam raportul cu veniturile si cheltuielile contului, perioada fiind LUNA in care s-au efectuat tranzactiile
    */
   int cheltuieli = 0, venituri = 0, luna, zi, an;

   printf("    Raport privind istoricul dumneavoastra de tranzactii\n\n");

   printf("    Veniturile dumneavoastra sunt urmatoarele: \n\n");

   /*
        Afisam prima data veniturile din luna respectiva
   */
   for(int i = 0; i < n; ++i) {
        sscanf(tranzactii[i].data, "%d/%d/%d", &zi, &luna, &an);
        if(tranzactii[i].tip == 'V' && luna == luna_dorita) {
            venituri ++;
            printf("         %d) %s in valoare de %d\n", venituri, tranzactii[i].descriere, tranzactii[i].valoare);
        }
   }
   
   printf("\n");
   printf("    Cheltuielile dumneavoastra sunt urmatoarele: \n\n");

   /*
        Afisam dupa aceea cheltuielile din luna respectiva
   */
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
   run_teste();
   initializare_tranzactii();

    fp = fopen("financial_data.txt", "w+"); //creeam fisierul in care vom pune tranzactia initiala
    fprintf(fp, "tranzactia %d\n data %s\n descriere %s\n valoare %d\n tip %c\n", 1, tranzactii[0].data, tranzactii[0].descriere, tranzactii[0].valoare, tranzactii[0].tip);
    fclose(fp);
    
   int exit = 0;
   char optiune[21];
   int optiune_int;
   bool valid = 1;
   printf("             Bun venit la Banca X!    \n\n");

   while(!exit) {

        printf("\n");
        print_meniu();
        printf("\n");
        valid = 1;
        printf("Optiunea aleasa de dumneavoastra este: ");
        scanf("%s", optiune); 
        getc(stdin); 
        
        if ((optiune[0] - '0') >= 1 && (optiune[0] - '0') <= 5 && strlen(optiune) == 1);
        else {
            printf("Introduceti o optiune valida!\n");
            valid = 0;
        }  
        //verificam daca optiunea introdusa se afla in meniu
        printf("\n");

        if(valid)
            
            switch ((int)(optiune[0] - '0')) {
                case 1:
                    int mod = 0; //printam modurile prin care se poate printa vectorul de tranzactii
                    printf("Modul de afisare al tranzactiilor este: \n");
                    printf("     1) din fisierul de date;\n"); //primul mod de afisare este sa preia datele din fisier si sa le scrie in consola
                    printf("     2) direct pe consola;\n\n");  //al doilea mod este de a le afisa direct in consola
                    printf("Introduceti modul ales de dumneavoastra: ");
                    scanf("%d", &mod);
                    if(mod == 1)
                        afisare_date_din_fisier();
                    else if(mod == 2)
                        afisare_lista_tranzactii(n);
                    else{
                        char linie[201];
                        fgets(linie, 201, stdin); //daca nu este introdus modul corect, citim linia gresita de comanda
                        printf("Nu a fost introdus modul corect din cele de mai sus!\n\n");//verificam daca a fost introduc un mod corect
                    }
                    break;
                case 2:
                    adaugare_tranzactie(n);
                    n++;
                    break;
                case 3:
                    vizualizare_sold(n);
                    break;
                case 4:
                    int luna;//preluam perioada pe care sa se scrie raportul
                    printf("Introduceti luna: ");
                    scanf("%d", &luna); //luna este de tip integer, de la 1 la 12
                    printf("\n");

                    if(luna < 1 || luna > 12) //verificam daca a fost introdusa o luna valida
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

