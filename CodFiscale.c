#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "codFis.h"

int main () {
  char cognome[MAX]="",nome[MAX]="",luogo_nascita[MAX]="",data_nascita[11]="",cod_fiscale[17]="";
  char cons_cognome[MAX]="",voc_cognome[MAX]="",cons_nome[MAX]="",voc_nome[MAX]="",gg[3]="";
  char mese[3]="",anno[3]="",corr_mese[13]="ABCDEHLMPRST",comuni[ROW][MAX],codici[ROW][COL_COD];
  char pos_pari[8]="",pos_dispari[9]="",sesso;
  int val_dispari[38]={1,0,5,7,9,13,15,17,19,21,1,0,5,7,9,13,15,17,19,21,2,4,18,20,11,3,6,8,12,14,16,10,22,25,24,23};
  int val_pari[38]={0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
  int i;
  //Inserimento dei comuni e codici, da file esterno, nelle rispettive matrici
  caricamento_dati(comuni,codici);
  //Inserimento dei dati personali
  inserimento_nominativi(cognome,nome);
  //Inserimento del luogo di nascita, con controllo ed eventuale reinserimento del comune,
  //nel caso non venga trovato all'interno della matrice dei comuni
  inserimento_luogo(luogo_nascita,comuni);
  //Inserimento della data di nascita, con controllo ed eventuale reinserimento della data,
  //nel caso vengano inseriti dati non accettabili
  inserimento_nascita(gg,mese,anno,data_nascita);
  //Inserimento del sesso
  sesso=input_sesso();
  //Individuazione delle consonanti e vocali del nome e cognome
  nominativo(cognome,cons_cognome,voc_cognome,nome,cons_nome,voc_nome);
  //Inserimento, nella stringa del codice fiscale, delle consonanti
  //del cognome ed eventuali vocali del cognome
  cognome_fis(cognome,cons_cognome,voc_cognome,cod_fiscale);
  //Inserimento, nella stringa del codice fiscale, delle consonanti
  //del nome ed eventuali vocali del nome
  nome_fis(nome,cons_nome,voc_nome,cod_fiscale);
  //Inserimento, nella stringa del codice fiscale, dell'anno di nascita
  anno_fis(anno,cod_fiscale);
  //Inserimento, nella stringa del codice fiscale, della rispettiva
  //lettera del mese di nascita
  mese_fis(mese,corr_mese,cod_fiscale);
  ////Inserimento, nella stringa del codice fiscale, del giorno di nascita
  giorno_fis(sesso,gg,cod_fiscale);
  //Inserimento, nella stringa del codice fiscale, del codice relativo al
  //luogo di nascita
  luogo_fis(codici,cod_fiscale,ricerca(comuni,ROW,luogo_nascita));
  //Ritorna stringhe contenenti i caratteri nelle posizioni pari e dispari
  //della stringa del codice fiscale
  posizioni(cod_fiscale,pos_pari,pos_dispari);
  //Inserimento, nella stringa del codice fiscale, del carattere di controllo
  control_fis(calcolo_resto(corr_pari(pos_pari,val_pari),corr_dispari(pos_dispari,val_dispari)),cod_fiscale);
  printf("\nCodice fiscale calcolato: %s\n\n",cod_fiscale);
  
  system("pause");
  return 0;
}
