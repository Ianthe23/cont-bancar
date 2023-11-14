#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//initalizam vectorul cu tranzactii si lungimea acestuia
struct data{char data[11]; char descriere[201]; int valoare; char tip;};
struct data tranzactii[1001];
int n = 1;

int validare_data(int zi, int luna, int an) {
    /*
        Validam data introdusa ca sa o putem adauga in tranzactii
    */
    if (an < 1900 || an > 2099) 
        return false;
    
    if (luna < 1 || luna > 12) 
        return false;
    
    if (zi < 1) 
        return false;
    
    //verificam luna februarie cu an bisect
    if (luna == 2) {
        if ((an % 4 == 0 && an % 100 != 0) || (an % 400 == 0)) {
            if (zi > 29) 
                return false;
        }
        else 
            if (zi > 28) 
                return false;
            
    }
    
    //verificam lunile cu 30 de zile
    else if (luna == 4 || luna == 6 || luna == 9 || luna == 11) 
        if (zi > 30) 
            return false;
        
    //verificam lunile cu 31 de zile
    else 
        if (zi > 31) 
            return false;
        
    return true;
}


int validare_tip(char tip) {
    /*
        Validam tipul tranzactiei
    */
   if(tip != 'C' && tip != 'V')
        return false;

   return true;

}

void adaugare_valida(int n, char data[], char descriere[], int valoare, char tip) {
    /*
        Adaugam datele valide in vectorul de tranzactii
    */
    strcpy(tranzactii[n].data, data);
    strcpy(tranzactii[n].descriere, descriere);
    tranzactii[n].valoare = valoare;
    tranzactii[n].tip = tip;
}

int initializare_tranzactii() {
    /*
        Initializam tranzactiile
    */
   strcpy(tranzactii[0].data, "01/01/2000");
   strcpy(tranzactii[0].descriere, "curent");
   tranzactii[0].valoare = 50000;
   tranzactii[0].tip = 'V';

}

