#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//initalizam vectorul cu tranzactii si lungimea acestuia
struct data{char data[11]; char descriere[201]; int valoare; char tip;};
struct data tranzactii[1001], copie_tranzactii[1001];
int n = 1;


int validare_data(int zi, int luna, int an) {
    /*
        Validam data introdusa ca sa o putem adauga in tranzactii
    */
    if (an < 1900 || an > 2099) 
        return false;
    
    if (luna < 1 || luna > 12) 
        return false;
    
    if (zi < 1 || zi > 31) 
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

bool test_validare_data(){
    /*
        Testam functia de validare a datei
    */
    bool verifica_toate = true;
    if(validare_data(1, 1, 2000) == false)
        verifica_toate = false;
    if(validare_data(31, 12, 2099) == false)
        verifica_toate = false;
    if(validare_data(29, 2, 2000) == false)
        verifica_toate = false;
    if(validare_data(28, 2, 2001) == false)
        verifica_toate = false;
    if(validare_data(30, 4, 2000) == false)
        verifica_toate = false;
    if(validare_data(31, 5, 2000) == false)
        verifica_toate = false;
    if(validare_data(30, 6, 2000) == false)
        verifica_toate = false;
    if(validare_data(31, 7, 2000) == false)
        verifica_toate = false;
    if(validare_data(31, 8, 2000) == false)
        verifica_toate = false;
    if(validare_data(30, 9, 2000) == false)
        verifica_toate = false;
    if(validare_data(31, 10, 2000) == false)
        verifica_toate = false;
    if(validare_data(30, 11, 2000) == false)
        verifica_toate = false;
    if(validare_data(31, 12, 2000) == false)
        verifica_toate = false;
    if(validare_data(0, 1, 2000) == true)
        verifica_toate = false;
    if(validare_data(32, 1, 2000) == true)
        verifica_toate = false;
    if(validare_data(1, 0, 2000) == true)
        verifica_toate = false;
    if(validare_data(1, 13, 2000) == true)
        verifica_toate = false;
    if(validare_data(1, 1, 1899) == true)
        verifica_toate = false;
    if(validare_data(1, 1, 2100) == true)
        verifica_toate = false;
    if(validare_data(30, 2, 2000) == true)
        verifica_toate = false;
    if(validare_data(29, 2, 2001) == true)
        verifica_toate = false;
    if(validare_data(31, 4, 2000) == true)
        verifica_toate = false;
    if(validare_data(31, 6, 2000) == true)
        verifica_toate = false;
    if(validare_data(31, 9, 2000) == true)
        verifica_toate = false;
    if(validare_data(31, 11, 2000) == true)
        verifica_toate = false;
    if(validare_data(1, 1, 2000) == false)
        verifica_toate = false;
    if(validare_data(31, 1, 2000) == false)
        verifica_toate = false;
    return verifica_toate;
}
bool test_validare_tip(){
    /*
        Testam functia de validare a tipului
    */
    bool verifica_toate = true;
    if(validare_tip('C') == false)
        verifica_toate = false;
    if(validare_tip('V') == false)
        verifica_toate = false;
    if(validare_tip('c') == true)
        verifica_toate = false;
    if(validare_tip('v') == true)
        verifica_toate = false;
    if(validare_tip('A') == true)
        verifica_toate = false;
    if(validare_tip('a') == true)
        verifica_toate = false;
    return verifica_toate;
}
bool test_adaugare_valida(){
    /*
        Testam functia de adaugare valida
    */
    bool verifica_toate = true;
    adaugare_valida(1, "01/01/2000", "curent", 50000, 'V');
    if(strcmp(tranzactii[1].data, "01/01/2000") != 0)
        verifica_toate = false;
    if(strcmp(tranzactii[1].descriere, "curent") != 0)
        verifica_toate = false;
    if(tranzactii[1].valoare != 50000)
        verifica_toate = false;
    if(tranzactii[1].tip != 'V')
        verifica_toate = false;
    return verifica_toate;
}
bool test_initializare_tranzactii(){
    /*
        Testam functia de initializare a tranzactiilor
    */
    bool verifica_toate = true;
    initializare_tranzactii();
    if(strcmp(tranzactii[0].data, "01/01/2000") != 0)
        verifica_toate = false;
    if(strcmp(tranzactii[0].descriere, "curent") != 0)
        verifica_toate = false;
    if(tranzactii[0].valoare != 50000)
        verifica_toate = false;
    if(tranzactii[0].tip != 'V')
        verifica_toate = false;
    return verifica_toate;
}
void run_teste(){
    if(test_adaugare_valida())
        printf("Testul 1 a trecut cu succes!\n");
    else
        printf("Testul 1 NU a trecut cu succes!\n");
    if(test_initializare_tranzactii())
        printf("Testul 2 a trecut cu succes!\n");
    else
        printf("Testul 2 NU a trecut cu succes!\n");
    if(test_validare_data())
        printf("Testul 3 a trecut cu succes!\n");
    else
        printf("Testul 3 NU a trecut cu succes!\n");    
    if(test_validare_tip())
        printf("Testul 4 a trecut cu succes!\n");
    else
        printf("Testul 4 NU a trecut cu succes!\n");
    
}
