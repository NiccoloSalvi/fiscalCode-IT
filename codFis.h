#define ROW 8102
#define MAX 100
#define COL_COD 5

int lun_str(char[]);
char str_maiuscola(char[],int);
void caricamento_dati(char[][MAX],char[][COL_COD]);
void maiusc(char[],char[]);
void inserimento_nominativi(char[],char[]);
void inserimento_luogo(char[],char[][MAX]);
void inserimento_nascita(char[],char[],char[],char[]);
void calcolo_giorno(char[],char[]);
void calcolo_mese(char[],char[]);
void calcolo_anno(char[],char[]);
void calcolo_date(char[],char[],char[],char[]);
int dati_ok(int,int);
char input_sesso();
void consonanti_nominativo(char[],char[]);
void vocali_nominativo(char[],char[]);
void nominativo(char[],char[],char[],char[],char[],char[]);
void cognome_fis(char[],char[],char[],char[]);
void nome_fis(char[],char[],char[],char[]);
void anno_fis(char[],char[]);
void mese_fis(char[],char[],char[]);
void giorno_fis(char,char[],char[]);
int ricerca(char[][MAX],int,char[]);
void luogo_fis(char[][COL_COD],char[],int);
void posizioni(char[],char[],char[]);
int corr_pari(char[],int[]);
int corr_dispari(char[],int[]);
int calcolo_resto(int,int);
void control_fis(int,char[]);

int lun_str (char str[]) {
  int i;
  for (i=0;str[i]!=0;i++);
  return i;
}

char str_maiuscola (char str[],int i) {
  if (str[i]>91) str[i]-=32;
  return str[i];
}

void caricamento_dati (char comuni[][MAX],char codici[][COL_COD]) {
  FILE *fd;
  char buf[MAX];
  int a=0,i,j;
  fd=fopen("comuni.txt","r");
  while (fgets(buf,MAX+COL_COD,fd)!=NULL) {
    for (i=0;i<5;i++) codici[a][i]=buf[i];
    codici[a][i]='\0';
    j=0;
    for (i=5;buf[i]!='\n';i++) {
      comuni[a][j]=buf[i];
      j++;
    }
    comuni[a][j]='\0';
    a++;
  }
  fclose(fd);
}

void maiusc (char cognome[],char nome[]) {
  //Ritorna la stringa maiuscola, se al momento dell'inserimento è
  //stata inserita minuscola
  int i;
  for (i=0;i<lun_str(cognome);i++) str_maiuscola(cognome,i);
  for (i=0;i<lun_str(nome);i++) str_maiuscola(nome,i);
}

void inserimento_nominativi (char cognome[],char nome[]) {
  //Inserimento del cognome
  printf("Inserisci cognome: ");
  gets(cognome);
  //Inserimento del nome
  printf("Inserisci nome: ");
  gets(nome);
  //Ritorna le stringhe maiuscole
  maiusc(cognome,nome);
}

void inserimento_luogo (char luogo[],char comuni[][MAX]) {
	int trovato,i;
	do {
		if (trovato==-1) printf("Luogo non trovato nel database! Reinscilo: ");
		else printf("Inserisci il luogo di nascita: ");
		gets(luogo);
		for (i=0;i<lun_str(luogo);i++) str_maiuscola(luogo,i);
		trovato=ricerca(comuni,ROW,luogo);
	} while (trovato==-1);
}

void inserimento_nascita (char gg[],char mese[],char anno[],char data[]) {
  int i;
  do {
    //Azzeramento della stringa, utile nel caso di reinserimento dati,
    //dovuto ad un errore
    for (i=0;i<11;i++) data[i]=0;
    //Inserimento della data di nascita
    printf("Inserisci data di nascita (GG/MM/AAAA): ");
    gets(data);
    calcolo_date(gg,mese,anno,data);
    //Viene fatto un controllo tra i dati inseriti
  } while (dati_ok(atoi(gg),atoi(mese))==1);
}

void calcolo_giorno (char nascita[],char giorno[]) {
  giorno[0]=nascita[0];
  giorno[1]=nascita[1];
  giorno[2]='\0';
}

void calcolo_mese (char nascita[],char mese[]) {
  mese[0]=nascita[3];
  mese[1]=nascita[4];
  mese[2]='\0';
}

void calcolo_anno (char nascita[],char anno[]) {
  anno[0]=nascita[8];
  anno[1]=nascita[9];
  anno[2]='\0';
}

void calcolo_date (char gg[],char mese[],char anno[],char data[]) {
  //Ritorna la stringa contenente il giorno della data di nascita
  calcolo_giorno(data,gg);
  //Ritorna la stringa contenente il mese della data di nascita
  calcolo_mese(data,mese);
  //Ritorna la stringa contenente solo le ultime 2 cifre dell'anno di nascita
  calcolo_anno(data,anno);
}

int dati_ok (int g,int m) {
  if (m==2) {
    if (g>28) return 1;
  } else if (m==4 || m==6 || m==9 || m==11) {
    if (g>30) return 1;
  } else {
    if (g>31) return 1;
  }
  if (g<1) return 1;
  if (m<1 || m>12) return 1;
  return 0;
}

char input_sesso () {
  char s;
  do {
    printf("Sesso (M/F): ");
    scanf(" %c",&s);
  } while (s!='M' && s!='F');
  return s;
}

void consonanti_nominativo (char nominativo[],char consonanti[]) {
  int i=0,j=0;
  while (i<lun_str(nominativo)) {
    if (nominativo[i]!='A' && nominativo[i]!='E' && nominativo[i]!='I' && nominativo[i]!='O' && nominativo[i]!='U') {
      consonanti[j]=nominativo[i];
      j++;
    }
    i++;
  }
  consonanti[j]='\0';
}

void vocali_nominativo (char cognome[],char voc_cognome[]) {
  int i=0,j=0;
  while (i<lun_str(cognome)) {
    if (cognome[i]=='A' || cognome[i]=='E' || cognome[i]=='I' || cognome[i]=='O' || cognome[i]=='U') {
      voc_cognome[j]=cognome[i];
      j++;
    }
    i++;
  }
  voc_cognome[j]='\0';
}

void nominativo (char cognome[],char cons_cognome[],char voc_cognome[],char nome[],char cons_nome[],char voc_nome[]) {
  //Ritorna la stringa contenente le consonanti del cognome
  consonanti_nominativo(cognome,cons_cognome);
  //Ritorna la stringa contenente le vocali del cognome
  vocali_nominativo(cognome,voc_cognome);
  //Ritorna la stringa contenente le consonanti del nome
  consonanti_nominativo(nome,cons_nome);
  //Ritorna la stringa contenente le vocali del nome
  vocali_nominativo(nome,voc_nome);
}

void cognome_fis (char cognome[],char consonanti[],char vocali[],char codFis[]) {
  int i,j=0,a=0;
  if (lun_str(cognome)<3 && a<3) {
    for (i=0;i<lun_str(cognome);i++) {
      codFis[i]=cognome[i];
      a++;
    }
    codFis[a]='X';
    a++;
  }
  else if (lun_str(consonanti)<3) {
    for (i=0;i<lun_str(consonanti);i++) codFis[i]=consonanti[i];
    a=3-lun_str(consonanti);
    while (a>0) {
      codFis[i]=vocali[j];
      j++,i++,a--;
    }
  } else for (i=0;i<3;i++) codFis[i]=consonanti[i];
}

void nome_fis (char nome[],char consonanti[],char vocali[],char codFis[]) {
  int i,j=0,a=0;
  if (lun_str(nome)<3 && a<3) {
    for (i=0;i<lun_str(nome);i++) {
      codFis[i+3]=nome[i];
      a++;
    }
    codFis[a+3]='X';
    a++;
  }
  else if (lun_str(consonanti)<=3) {
    for (i=0;i<lun_str(consonanti);i++) codFis[i+3]=consonanti[i];
    a=3-lun_str(consonanti);
    while (a>0) {
      codFis[i+3]=vocali[j];
      j++,i++,a--;
    }
  } else {
    codFis[3]=consonanti[0];
    codFis[4]=consonanti[2];
    codFis[5]=consonanti[3];
  }
}

void anno_fis (char anno[],char codFis[]) {
  codFis[6]=anno[0];
  codFis[7]=anno[1];
}

void mese_fis (char mese[],char corr[],char codFis[]) {
  codFis[8]=corr[atoi(mese)-1];
}

void giorno_fis (char sesso,char giorno[],char codFis[]) {
  if (sesso=='F') giorno[0]+=4;
  codFis[9]=giorno[0];
  codFis[10]=giorno[1];
}

int ricerca (char lista[][MAX],int n,char paese[]) {
  int start=0,end=n-1,medium;
  while (start<=end) {
      medium=(start+end)/2;
      if (strcmp(lista[medium],paese)==0) return medium;
      else if (strcmp(lista[medium],paese)==-1) start=medium+1;
      else end=medium-1;
  }
  return -1;
}

void luogo_fis (char codici[][COL_COD],char codFis[],int i) {
  int a;
  for (a=0;a<4;a++) codFis[a+11]=codici[i][a];
}

void posizioni (char codFis[],char pari[],char dis[]) {
  int i,a=0,b=0;
  for (i=0;i<16;i++) {
    if (i%2==0) {
      dis[a]=codFis[i];
      a++;
    } else {
      pari[b]=codFis[i];
      b++;
    }
  }
  pari[a]='\0';
  dis[b]='\0';
}

int corr_pari (char pos[],int corr[]) {
  int sum=0,i;
  for (i=0;i<7;i++) {
    if (pos[i]>64) sum=sum+corr[pos[i]-55];
    else sum=sum+corr[pos[i]-48];
  }
  return sum;
}

int corr_dispari (char pos[],int corr[]) {
  int sum=0,i;
  for (i=0;i<8;i++) {
    if (pos[i]>64) sum=sum+corr[pos[i]-55];
    else sum=sum+corr[pos[i]-48];
  }
  return sum;
}

int calcolo_resto (int pari,int dis) {
  return (pari+dis)%26;
}

void control_fis (int resto, char codFis[]) {
  codFis[15]=65+resto;
  codFis[16]='\0';
}
