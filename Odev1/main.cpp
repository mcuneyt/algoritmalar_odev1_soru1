#include <stdio.h>
#include <stdlib.h> // tip dönüþümleri için...
#include <ctype.h> // girilen deðerlerin tip kontrolü için...
#include <conio.h>

#define KAYITLI_MUSTERI_AD "Cuneyt Manavoglu"
#define KAYITLI_MUSTERI_NO 12457836 // Banka müþteri numaralarý genel olarak 8 karakter ve sayýsal olduðundan tercih ettim.
#define KAYITLI_MUSTERI_SIFRE 1234 // Rastgele þifre.

bool musteriNoKontrol (char musteriNoStr[]); // Girilen müþteri numarasý sadece harf ve sayýlardan mý oluþuyor kontrol fonksiyonu.
bool musteriSifreKontrol (char musteriSifreStr[]); // Girilen þifre sadece harf ve sayýlardan mý oluþuyor kontrol fonksiyonu.
bool dogrulama(int musteriNo, int sifre); // Müþteri no ve þifre doðrulama fonksiyonu.

void main()
{
	char musteriNoStr[BUFSIZ];
	char girilenSifreStr[BUFSIZ];
	int musteriNo, girilenSifre;
	int girisDenemesi = 0;
	float bakiye = 2750.50;

	printf("\t%9 T.C.\n\tPAU BANK\n\t\tDENIZLI\n");
	printf("%3 Tum bankacilik islemlerinize ulasmak icin sistemimize giris yapmalisiniz...\n\n\n");

	do
	{
		printf("%3 Musteri No: ");
		scanf("%s", &musteriNoStr);
		printf("%3 Sifre: ");
		scanf("%s", &girilenSifreStr);

		if (musteriNoKontrol(musteriNoStr) && musteriSifreKontrol(girilenSifreStr))
		{
			musteriNo = atoi(musteriNoStr);
			girilenSifre = atoi(girilenSifreStr);

			if (dogrulama(musteriNo, girilenSifre))
			{
				printf("\n%3 Hos geldiniz, %s\n\n", KAYITLI_MUSTERI_AD);
				girisDenemesi = 3;

				float islemMiktari;
				char menuSecim;
				char hesapNo[BUFSIZ];
				yeniIslem: // Menü seçip iþlem tamamlandýktan sonra buradan devam et...
				printf("%3 MENU: \n\n");
				printf("%3 (S) - Bakiye Sorgulama\n (P) - Para Yatirma Islemleri\n (M) - Para Cekme Islemleri\n (H) - Para Transfer Islemleri\n (X) - Oturumu Sonlandir\n\n");
				tekrarSecim: // Olmayan bir menü seçildiðinde buradan devam et...
				menuSecim = getch();
				switch (menuSecim)
				{
					case 'S':
					case 's':
						printf("%3 Bakiye Sorgulama Ekrani #===============>\n\n");
						printf("%3 Son bakiyeniz: %10.2f TL.\n\n", bakiye);
						printf("<==========================================>\n\n");
						goto yeniIslem;

					case 'P':
					case 'p':
						printf("Para Yatirma Islemleri #===============>\n\n");
						do
						{
							printf("%3Hesabiniza yatirmak istediginiz miktari giriniz:\n");
							scanf("%f", &islemMiktari);
							if (islemMiktari < 0)
							{
								printf("%3Lutfen gecerli olan para miktari giriniz!\n\n");
							}
							else
							{
								bakiye = bakiye + islemMiktari;
								printf("\n%3Yeni bakiyeniz: %10.2f\n", bakiye);
							}
						}
						while (islemMiktari < 0);
						printf("<==========================================>\n\n");
						goto yeniIslem;

					case 'M':
					case 'm':
						printf("Para Cekme Islemleri #=====================>\n\n");
						do
						{
							printf("%3Hesabinizdan cekmek istediginiz miktari giriniz:\n");
							scanf("%f", &islemMiktari);
							if (islemMiktari > bakiye)
							{
								printf("%3Hesabinizde bulunan miktardan fazlasini cekemezsiniz!\n\n");
							}
							else if (islemMiktari < 0)
							{
								printf("%3Lutfen gecerli olan para miktari giriniz!\n\n");
							}
							else
							{
								bakiye = bakiye - islemMiktari;
								printf("\n%3Yeni bakiyeniz: %10.2f\n", bakiye);
							}
						}
						while (islemMiktari > bakiye || islemMiktari < 0);			
						printf("<==========================================>\n\n");
						goto yeniIslem;

					case 'H':
					case 'h':
						printf("Para Transfer Islemleri #=======================>\n\n");
						printf("%3Para transferi yapilacak Hesap No:\n");
						scanf("%s", &hesapNo);
						do
						{
							printf("%3Transfer miktari giriniz:\n");
							scanf("%f", &islemMiktari);
							if (islemMiktari > bakiye)
							{
								printf("%3Hesabinizde bulunan miktardan fazlasini gonderemezsiniz!\n\n");
							}
							else if (islemMiktari < 0)
							{
								printf("%3Lutfen gecerli olan para miktari giriniz!\n\n");
							}
							else
							{
								bakiye = bakiye - islemMiktari;
								printf("\n%s hesap numarasina...\n %10.2f TL transfer yaptiniz.\n\n", hesapNo, islemMiktari);
								printf("%3Yeni bakiyeniz: %10.2f\n\n", bakiye);
							}
						} 
						while (islemMiktari > bakiye || islemMiktari < 0);
						printf("<==========================================>\n\n");
						goto yeniIslem;

					case 'X':
					case 'x':
						goto oturumuKapat;
						break;

					default:
						printf("%3Hatali secim yaptiniz! Lutfen gecerli menulerden seciminizi yapiniz.\n\n");
						goto tekrarSecim;
				}
			}
			else
			{
				girisDenemesi++;
				printf("%5 Musteri Numarasi yada Sifreyi hatali girdiniz!\n\n\a");
			}
		}
		else
		{
			girisDenemesi++;
			printf("%5 Musteri Numarasi yada Sifreyi hatali girdiniz!\n\a");
		}
	}
	while (girisDenemesi < 3);
	
	oturumuKapat: printf("%5 Bol kazancli gunler diler, yine bekleriz!\n\n");
}

bool musteriNoKontrol(char musteriNoStr[])
{
	int i = 0;
	while (musteriNoStr[i])
	{
		if (isalnum(musteriNoStr[i]))
		{
			return true;
		}
	    else
		{
			return false;
		}
	    i++;
	}
	return false;
}

bool musteriSifreKontrol(char musteriSifreStr[])
{
	int i = 0;
	while (musteriSifreStr[i])
	{
	    if (isalnum(musteriSifreStr[i]))
		{
			return true;
		}
	    else
		{
			return false;
		}
	    i++;
	}
	return false;
}

bool dogrulama(int musteriNo, int sifre)
{
	if (musteriNo == KAYITLI_MUSTERI_NO && sifre == KAYITLI_MUSTERI_SIFRE)
	{
		return true;
	}
	return false;
}