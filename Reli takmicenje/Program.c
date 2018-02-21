//NIKOLA MIOCEVIC NRT-15/14 
//Program za pracenje rezultata reli takmicenja
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 30

typedef enum Greska {GRESKA_DODELE, GRESKA_DAT}Greska;

char *poruke_o_greskama[] = {
	"\nGreska pri dinamickoj dodeli memorije!\n"
	"\nGreska pri otvaranju datoteke za upis ili citanje!\n" };



struct vozac{                       /*Kreiranje strukture tipa vozac*/
	char ime[MAX + 1];
	char automobil[MAX + 1];
	int vreme_sat;
	int vreme_min;
	int vreme_sek;
	int broj_poena;
};

//deklaracija funkcija
void cita_spisak(struct vozac niz[], int broj_takmicara);     /*Ucitavanje podataka u strukturu*/
void stampa_spisak(struct vozac niz[], int broj_takmicara);    /*Stampanje podataka iz strukture*/
void rezultati_trke(struct vozac niz[], int broj_takmicara);   /*Obradjivanje rezultata trke*/
void datoteke(struct vozac niz[], int broj_takmicara);         /*Citanje i upisivanje rezultata u datoteku rezultati*/
void sortiraj(struct vozac niz[], int broj_takmicara);         /*Sortiranje rezultata rang liste*/
void nacin_bodovanja();                                         /*Nacin na koji se boduju rezultati trke*/
int opcija1();                                                   /*Biranje izbora kod pocetnog ekrana*/
int opcija2();
void greska(Greska status);

//glavna funkcija programa
int main()
{
	int i, j, broj_takmicara, broj_trka, tmp, izbor1, izbor2;
	struct vozac *spisak;

	do{
		system("cls");
		puts("    ______________________________________________________________ ");
		puts("   |                                                              |");
		puts("   |   ****   *****   *     *        *****  ****   *   *  *****   |");
		puts("   |   *   *  *       *     *          *    *   *  *  *   *       |");
		puts("   |   ****   *****   *     *  -----   *    ****   ***    *****   |");
		puts("   |   * *    *       *     *          *    * *    *  *   *       |");
		puts("   |   *  *   *****   ****  *          *    *  *   *   *  *****   |");
		puts("   |______________________________________________________________|");

		puts("");
		puts("   1. Uneti rezultate takmicenja");
		puts("   2. Nacin bodovanja");
		puts("");
		puts("   Uneti 1 za pocetak unosa rezultata ili 2 za informacije o nacinu bodovanja!");

		izbor1 = opcija1();

		if (izbor1 == 2){
			system("cls");
			nacin_bodovanja();                                    /*Poziva se funkcija nacin_bodovanja koja cita iz datoteke Bodovanje*/
			puts("   0. Vratiti se nazad");
			izbor2 = opcija2();
		}

		if (izbor1 == 1)
		{
			fflush(stdin);
			system("cls");

			do{
				printf("\nUnesite broj vozaca:\n");
				scanf("%d", &broj_takmicara);
			} while (broj_takmicara < 2);

			if ((spisak = malloc(broj_takmicara*sizeof(struct vozac))) == NULL)      /*Dinamicka dodela memorije za vozace*/
				greska(GRESKA_DODELE);                                              /* Provera da li je memorija dodeljena*/

			system("cls");

			cita_spisak(spisak, broj_takmicara);                         /*Pozivanje fukncije za unosenje rezultata*/

			system("cls");

			printf("\nUnesite broj trka koje se voze:\n");               
			scanf("%d", &broj_trka);

			for (i = 0; i < broj_trka; i++)
			{
				printf("\nRezultati %d. trke:", i + 1);
 				rezultati_trke(spisak, broj_takmicara);                 /* Pozivanje funkcije za obradjivanje rezultata trke*/
   			}

			system("cls");

			sortiraj(spisak, broj_takmicara);
			stampa_spisak(spisak, broj_takmicara);
			datoteke(spisak, broj_takmicara);                           /*Pozivanje funkcije za upis i citanje Rezultata trke*/
			izbor2 = 1;
			free(spisak);                                               /* Oslobadjanje memorije koriscene za smestanje podataka o vozacima*/
		}

	} while (izbor1 == 2 || izbor2 == 0);
}

void sortiraj(struct vozac niz[], int broj_takmicara)                     /*Funkcija za Sortiranje rezultata*/
{ 
	
	struct vozac pom;
	int i, j;
	int min;


	for (i = 0; i <broj_takmicara - 1; i++)
	{
		min = i;
		for (j = i + 1; j <broj_takmicara; j++)
		if (niz[i].broj_poena <niz[j].broj_poena)
		{
			pom = niz[i];
			niz[i] = niz[j];
			niz[j] = pom;
		}
	}
}



void datoteke(struct vozac niz[], int broj_takmicara)              /*Funkcija za smestanje i citanje rezultata trka sa datotekama*/
{ 
	FILE *fptr;
	int i;
	char bafer[81];
	if ((fptr = fopen("Rezultati.txt", "w")) == NULL)          /*  informacije da se radi o gresci*/
		greska(GRESKA_DAT);

	fprintf(fptr, "\nREZULTATI TAKMICENJA:\n");
	fprintf(fptr, "\nIME TAKMICARA        AUTOMOBIL                   UKUPNO VREME               BROJ POENA\n\n");
	for (i = 0; i < broj_takmicara; i++)
		fprintf(fptr, "%s              %s     %dh : %dm : %ds       %d \n", niz[i].ime, niz[i].automobil, niz[i].vreme_sat, niz[i].vreme_min, niz[i].vreme_sek, niz[i].broj_poena);


	rewind(fptr);
	fclose(fptr);

	/*Drugi nacin ispisivanja rezultata, preko datoteke */

	//if((fptr = fopen("Rezultati.txt", "r"))==NULL)
	//	greska(GRESKA_DAT);                     /* informacije da se radi o gresci*/

	//while (!feof(fptr))

	//{
	//	fgets(bafer, 81, fptr);
	//	puts(bafer);
	//}


	//fclose(fptr);

}

void cita_spisak(struct vozac niz[], int broj_takmicara)      /*Funkcija za unos podataka o takmicarima*/
{ 
	int i,tmp;
	tmp = getchar();
	for (i = 0; i < broj_takmicara; i++)
	{
		printf("\nIme i prezime %d. vozaca: ", i + 1);
		gets(niz[i].ime);

	
		printf("\nUnesite marku automobila koji vozi: ");
		gets(niz[i].automobil);
		

		niz[i].broj_poena = 0;
		niz[i].vreme_sat = 0;
		niz[i].vreme_min = 0;
		niz[i].vreme_sek = 0;
	}
}

void stampa_spisak(struct vozac niz[], int broj_takmicara)        /*Stampanje rezultata trka na klasican nacin*/
{
	int i;
	printf("\                        KONACNA RANG LIST TAKMICARA                     \n");
	printf("\n_______________________________________________________________________\n");
	printf("\nTAKMICAR      VOZILO      UKUPNO VREME SVIH TRKA           UKUPNO POENA\n");
	for (i = 0; i < broj_takmicara; i++)
	{
		printf("\n%s    ", niz[i].ime);
		printf("%s               ", niz[i].automobil);
		printf("%dh : ", niz[i].vreme_sat);
		printf("%dm : ", niz[i].vreme_min);
		printf("%ds   ", niz[i].vreme_sek);
		printf("                   %d", niz[i].broj_poena);
	}

	printf("\n\n");

}

void rezultati_trke(struct vozac niz[], int broj_takmicara)             /*Obrada rezultata trka*/
{
	int i, tmp, n;
	int a1, b1, c1, d1, e1, f1, g1, h1, k1, l1, a2, b2, c2, d2, e2, f2, g2, h2, k2, l2,a3,b3,c3,d3,e3,f3,g3,h3,k3,l3;
	char a[MAX + 1], b[MAX + 1], c[MAX + 1], d[MAX + 1], e[MAX + 1], f[MAX + 1], g[MAX + 1], h[MAX + 1], k[MAX + 1], l[MAX + 1];


			printf("\nPobednik trke je vozac: ");
			tmp = getchar();
			gets(a);
				
			do                                             /*Ne dozvoljava unos vrednosti za sekunde i minute veci od 59*/
				{
					printf("\nVreme za koje je zavrsio trku(uneti sate, minute, a zatim i sekunde): ");
					scanf("%d %d %d", &a1, &a2, &a3);
				} while (a1 < 0 || a2 < 0 || a3<0 || a2>59 || a3>59);
		

			printf("\nDrugi na cilj je stigao vozac: ");
			tmp = getchar();
			gets(b);

			do{
				printf("\nVreme za koje je zavrsio trku(uneti sate, minute, a zatim i sekunde): ");
				scanf("%d %d %d", &b1, &b2, &b3);
			} while (b1<0 || b2 < 0 || b3<0 || b2>59 || b3>59);
			if (broj_takmicara > 2)                                   /* U zavisnosti od broja takmicara izbacuje sledece redove za unos*/
			{
				printf("\nTreci na cilj je stigao vozac: ");
				tmp = getchar();
				gets(c);

				do{
					printf("\nVreme za koje je zavrsio trku(uneti sate, minute, a zatim i sekunde): ");
					scanf("%d %d %d", &c1, &c2, &c3);
				} while (c1<0 || c2 < 0 || c3<0 || c2>59 || c3>59);
				if (broj_takmicara > 3)
				{
					printf("\nCetvrti na cilj je stigao vozac: ");
					tmp = getchar();
					gets(d);

					do{
						printf("\nVreme za koje je zavrsio trku(uneti sate, minute, a zatim i sekunde): ");
						scanf("%d %d %d", &d1, &d2, &d3);
					} while (d1<0 || d2 < 0 || d3<0 || d2>59 || d3>59);
					if (broj_takmicara > 4)
					{
						printf("\nPeti na cilj je stigao vozac: ");
						tmp = getchar();
						gets(e);

						do{
							printf("\nVreme za koje je zavrsio trku(uneti sate, minute, a zatim i sekunde): ");
							scanf("%d %d %d", &e1, &e2, &e3);
						} while (e1<0 || e2 < 0 || e3<0 || e2>59 || e3>59);

						if (broj_takmicara > 5)
						{
							printf("\nSesti cilj je stigao vozac: ");
							tmp = getchar();
							gets(f);

							do{
								printf("\nVreme za koje je zavrsio trku(uneti sate, minute, a zatim i sekunde): ");
								scanf("%d %d %d", &f1, &f2, &f3);
							} while (f1<0 || f2 < 0 || f3<0 || f2>59 || f3>59);

							if (broj_takmicara > 6)
							{
								printf("\nSedmi na cilj je stigao vozac: ");
								tmp = getchar();
								gets(g);

								do{
									printf("\nVreme za koje je zavrsio trku(uneti sate, minute, a zatim i sekunde): ");
									scanf("%d %d %d", &g1, &g2, &g3);
								} while (g1<0 || g2 < 0 || g3<0 || g2>59 || g3>59);

								if (broj_takmicara > 7)
								{
									printf("\nOsmi na cilj je stigao vozac: ");
									tmp = getchar();
									gets(h);

									do{
										printf("\nVreme za koje je zavrsio trku(uneti sate, minute, a zatim i sekunde): ");
										scanf("%d %d %d", &h1, &h2, &h3);
									} while (h1<0 || h2 < 0 || h3<0 || h2>59 || h3>59);

									if (broj_takmicara > 8)
									{
										printf("\nDeveti na cilj je stigao vozac: ");
										tmp = getchar();
										gets(k);

										do{
											printf("\nVreme za koje je zavrsio trku(uneti sate, minute, a zatim i sekunde): ");
											scanf("%d %d %d", &k1, &k2, &k3);
										} while (k1<0 || k2 < 0 || k3<0 || k2>59 || k3>59);

										if (broj_takmicara > 9)
										{
											printf("\nDeseti na cilj je stigao vozac: ");
											tmp = getchar();
											gets(l);

											do{
												printf("\nVreme za koje je zavrsio trku(uneti sate, minute, a zatim i sekunde): ");
												scanf("%d %d %d", &l1, &l2, &l3);
											} while (l1<0 || l2 < 0 || l3<0 || l2>59 || l3>59);

										}
									}
								}
							}
						}
					}
				}
			}


			for (i = 0; i < broj_takmicara; i++)    
			{
				if (strcmp(a, niz[i].ime) == 0)                      /*Dodeljivanje broja poena na osnovu pozicije na kojoj je zavrsio trku*/
				{
					niz[i].broj_poena += 25;
					niz[i].vreme_sat += a1;
					niz[i].vreme_min += a2;
					niz[i].vreme_sek += a3;
					
					if (niz[i].vreme_sek>59)                        /*Konvertovanje sekundi i minuta ako ih ima vise od 60 u minute i satove*/
					{
						niz[i].vreme_min += niz[i].vreme_sek / 60;
						niz[i].vreme_sek = niz[i].vreme_sek % 60;
						
					}
					
					if (niz[i].vreme_min > 59)
					{
						niz[i].vreme_sat += niz[i].vreme_min / 60;
						niz[i].vreme_min = niz[i].vreme_min % 60;
					}
				}
				else if (strcmp(b, niz[i].ime) == 0)
				{
					niz[i].broj_poena += 18;
					niz[i].vreme_sat += b1;
					niz[i].vreme_min += b2;
					niz[i].vreme_sek += b3;

					if (niz[i].vreme_sek>59)
					{
						niz[i].vreme_min += niz[i].vreme_sek / 60;
						niz[i].vreme_sek = niz[i].vreme_sek % 60;
						
					}

					if (niz[i].vreme_min > 59)
					{
						niz[i].vreme_sat += niz[i].vreme_min / 60;
						niz[i].vreme_min = niz[i].vreme_min % 60;

					}
				}
				else if (strcmp(c, niz[i].ime) == 0)
				{
					niz[i].broj_poena += 15;
					niz[i].vreme_sat += c1;
					niz[i].vreme_min += c2;
					niz[i].vreme_sek += c3;

					if (niz[i].vreme_sek>59)
					{
						niz[i].vreme_min += niz[i].vreme_sek / 60;
						niz[i].vreme_sek = niz[i].vreme_sek % 60;
					}

					if (niz[i].vreme_min > 59)
					{
						niz[i].vreme_sat += niz[i].vreme_min / 60;
						niz[i].vreme_min = niz[i].vreme_min % 60;
					}
				}
				else if (strcmp(d, niz[i].ime) == 0)
				{
					niz[i].broj_poena += 12;
					niz[i].vreme_sat += d1;
					niz[i].vreme_min += d2;
					niz[i].vreme_sek += d3;

					if (niz[i].vreme_sek>59)
					{
						niz[i].vreme_min += niz[i].vreme_sek / 60;
						niz[i].vreme_sek = niz[i].vreme_sek % 60;
					}

					if (niz[i].vreme_min > 59)
					{
						niz[i].vreme_sat += niz[i].vreme_min / 60;
						niz[i].vreme_min = niz[i].vreme_min % 60;
						
					}
				}
				else if (strcmp(e, niz[i].ime) == 0)
				{
					niz[i].broj_poena += 10;
					niz[i].vreme_sat += e1;
					niz[i].vreme_min += e2;
					niz[i].vreme_sek += e3;

					if (niz[i].vreme_sek>59)
					{
						niz[i].vreme_min += niz[i].vreme_sek / 60;
						niz[i].vreme_sek = niz[i].vreme_sek % 60;
						
					}

					if (niz[i].vreme_min > 59)
					{
						niz[i].vreme_sat += niz[i].vreme_min / 60;
						niz[i].vreme_min = niz[i].vreme_min % 60;
					}
				}
				else if (strcmp(f, niz[i].ime) == 0)
				{
					niz[i].broj_poena += 8;
					niz[i].vreme_sat += f1;
					niz[i].vreme_min += f2;
					niz[i].vreme_sek += f3;

					if (niz[i].vreme_sek>59)
					{
						niz[i].vreme_min += niz[i].vreme_sek / 60;
						niz[i].vreme_sek = niz[i].vreme_sek % 60;
					}

					if (niz[i].vreme_min > 59)
					{
						niz[i].vreme_sat += niz[i].vreme_min / 60;
						niz[i].vreme_min = niz[i].vreme_min % 60;
					}
				}
				else if (strcmp(g, niz[i].ime) == 0)
				{
					niz[i].broj_poena += 6;
					niz[i].vreme_sat += g1;
					niz[i].vreme_min += g2;
					niz[i].vreme_sek += g3;

					if (niz[i].vreme_sek>59)
					{
						niz[i].vreme_min += niz[i].vreme_sek / 60; 
						niz[i].vreme_sek = niz[i].vreme_sek % 60;	
					}

					if (niz[i].vreme_min > 59)
					{
						niz[i].vreme_sat += niz[i].vreme_min / 60;
						niz[i].vreme_min = niz[i].vreme_min % 60;
					}
				}
				else if (strcmp(h, niz[i].ime) == 0)
				{
					niz[i].broj_poena += 4;
					niz[i].vreme_sat += h1;
					niz[i].vreme_min += h2;
					niz[i].vreme_sek += h3;

					if (niz[i].vreme_sek>59)
					{
						niz[i].vreme_min += niz[i].vreme_sek / 60;
						niz[i].vreme_sek = niz[i].vreme_sek % 60;
					}

					if (niz[i].vreme_min > 59)
					{
						niz[i].vreme_sat += niz[i].vreme_min / 60;
						niz[i].vreme_min = niz[i].vreme_min % 60;
					}
				}
				else if (strcmp(k, niz[i].ime) == 0)
				{
					niz[i].broj_poena += 2;
					niz[i].vreme_sat += k1;
					niz[i].vreme_min += k2;
					niz[i].vreme_sek += k3;

					if (niz[i].vreme_sek>59)
					{
						niz[i].vreme_min += niz[i].vreme_sek / 60;
						niz[i].vreme_sek = niz[i].vreme_sek % 60;
					}

					if (niz[i].vreme_min > 59)
					{
						niz[i].vreme_sat += niz[i].vreme_min / 60;
						niz[i].vreme_min = niz[i].vreme_min % 60;
					}
				}
				else if (strcmp(l, niz[i].ime) == 0)
				{
					niz[i].broj_poena += 1;
					niz[i].vreme_sat += l1;
					niz[i].vreme_min += l2;
					niz[i].vreme_sek += l3;

					if (niz[i].vreme_sek > 59)
					{
						niz[i].vreme_min += niz[i].vreme_sek / 60;
						niz[i].vreme_sek = niz[i].vreme_sek % 60;
					}

					if (niz[i].vreme_min > 59)
					{
						niz[i].vreme_sat += niz[i].vreme_min / 60;
						niz[i].vreme_min = niz[i].vreme_min % 60;
					}
				}
				
			}

		}


void nacin_bodovanja()                             /*Ucitavanje datoteke Bodovanje*/
{
	int i;
	char bafer[81];
	FILE *fptr;

	fptr = fopen("Bodovanje.txt", "r");
	for (i = 0; i < 13; i++)
	{
		fgets(bafer, 81, fptr);
		puts(bafer);
	}
	fclose(fptr);
}


int opcija1()                                       /*Pocetni ekran izbor*/
{
	int opcija1;

	scanf("%i", &opcija1);
	while ((opcija1 < 1) || (opcija1 >2)){
		puts("Uneta pogresna vrednost, uneti 1 ili 2");
		scanf("%i", &opcija1);
	};
	return opcija1;
}

int opcija2(){
	int opcija2;

	scanf("%i", &opcija2);
	while ((opcija2 < 0) || (opcija2 >0))
	{
		puts("Uneta pogresna vrednost!");
		scanf("%i", &opcija2);
	}
	return opcija2;
}

void greska(Greska status)
{
	fprintf(stderr, poruke_o_greskama[status]);
	exit(1);
}