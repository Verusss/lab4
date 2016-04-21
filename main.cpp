/*Weronika Borek, 226327
Program pobiera z wiersza poleceń liczbę n, szuka dla niej naturalnego k>0, tak aby n*k składało się tylko/
z zer i jedynek. Jeśli wynik oraz k mieszczą się w obsługiwanym przez funkcję readInPolish zakresie <0-999999>
wyświetla je słownie.*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

//Funkcja służy do wyświetlania słownie otrzymywanej liczby.
void readInPolish(int*, unsigned long long, int, unsigned long long, int);

int main (int argc, char *argv[])
{
	//Obsługa błędów. 
	if (argc!=2)
		printf ("Nieprawidłowa liczba argumentów wiersza poleceń.\n");
	//Deklaracje potrzebnych zmiennych.
	int n=atoi(argv[1]);
	int how_many_digits;
	int *digits;
	int how_many_zero_one;
	unsigned long long k=1;
	unsigned long long result;
	digits=(int*)malloc(how_many_digits*sizeof(int));

	//Szukanie takiej liczby n*k, która będzie złożona tylko z zer i jedynek.
	do
	{
		how_many_digits=1;
		how_many_zero_one=0;
		result=k*n;

		//Ile cyfr ma dana liczba?
		for (int d=10; result/d!=0; d=10*d)
			how_many_digits++;
		digits=(int*)realloc(digits, how_many_digits*sizeof(int));

		//Pakowanie poszczególnych cyfr do tablicy.
		int d=1;
		for(int i=0; i<how_many_digits; i++)
		{
			digits[i]=(result/d)%10;
			d=10*d;
		}

		//Ile jest zer i jedynek w result?
		for (int i=0; i<how_many_digits; i++)
		{
			if (digits[i]==1 || digits[i]==0)
			{
				how_many_zero_one++;		
			}
		}
		k++;
	}
	//Wyświetlanie komunikatów.
	while (how_many_zero_one!=how_many_digits);
	printf ("Liczbą złożoną z samych zer i jedynek dla n=%d jest %llu. \nOtrzymamy ją poprzez pomnożenie n przez k=%llu.\n", n, result, --k);
	if (result<999999)
	{
		printf ("\nWynik ten słownie brzmi: ");
		readInPolish(digits, result, n, k, how_many_digits);
	}
	else 
		printf("\nWynik jest zbyt długi, aby program wyświetlił go słownie.\n");
	
	if (k<999999)
	{
		printf ("\nZ kolei wartość k słownie brzmi: ");
		how_many_digits=1;
		result=k;
		for (int d=10; k/d!=0; d=10*d)
			how_many_digits++;
		digits=(int*)malloc(how_many_digits*sizeof(int));
		int d=1;
		for(int i=0; i<how_many_digits; i++)
		{
			digits[i]=(k/d)%10;
			d=10*d;
		}
		readInPolish(digits, result, n, k, how_many_digits);
	}
	else 
		printf("\nK jest zbyt długie, aby wyświetlić słownie jego wartość.\n");

	return 0;
}

void readInPolish (int *digits, unsigned long long result, int n, unsigned long long k, int how_many_digits)
{
	//Tablice zawierające wymowę poszczególnych liczb.
	const string units[]={"zero", "jeden", "dwa", "trzy", "cztery", "pięć", "sześć", "siedem", "osiem", "dziewięć"};
	const string teens[]={"jedenaście", "dwanaście", "trzynaście", "czternaście", "piętnaście", "szesnaście", "siedemnaście", "osiemnaście", "dziewiętnaście"};
	const string tens[]={"dziesięć", "dwadzieścia", "trzydzieści", "czterdzieści", "pięćdziesiąt", "sześćdziesiąt", "siedemdziesiąt", "osiemdziesiąt", "dziewięćdziesiąt"};
	const string hundreds[]={"sto", "dwieście", "trzysta", "czterysta", "pięćset", "sześćset", "siedemset", "osiemset", "dziewięćset"};
	const string tousends[]={"tysiąc", "tysiące", "tysięcy"};


	switch (how_many_digits)
	{
		//Liczby sześciocyfrowe.
		case 6:
		if (digits[4]!=0)
			cout << hundreds[digits[5]-1] << " ";
		else if (digits[4]==0 && digits[3]==0)
			cout << hundreds[digits[5]-1] << " " << tousends[2] << " ";
		else if (digits[4]==0 && digits[3]>1 && digits[3]<5)
			cout << hundreds[digits[5]-1] << " " << units[digits[3]] << " " << tousends[1] << " ";
		else if (digits[4]==0 && digits[3]<2 || digits[4]==0 && digits[3]>4)
			cout << hundreds[digits[5]-1] << " " << units[digits[3]] << " " << tousends[2] << " ";

		//Liczby pięciocyfrowe. 
		case 5:
		if (digits[4]>1 && digits[3]<2 && digits[3]!=0 || digits[4]>1 && digits[3]>4 && digits[3]!=0)
			cout << tens[digits[4]-1] << " " << units[digits[3]] << " " << tousends[2] << " ";
		else if (digits[4]>1 && digits[3]>1 && digits[3]<5)
			cout << tens[digits[4]-1] << " " << units[digits[3]] << " " << tousends[1] << " ";
		else if (digits[4]>1 && digits[3]==0)
			cout << tens[digits[4]-1] << " " << tousends[2] << " ";
		if (digits[4]==1 && digits[3]!=0)
			cout << teens[digits[3]-1] << " " << tousends[2] << " ";
		else if (digits[4]==1 && digits[3]==0)
			cout << tens[0] << " " << tousends[2] << " ";
		if (result%1000==0)
		{
			cout << endl;
			break;
		}

		//Liczby czterocyfrowe.
		case 4:
		if (how_many_digits<5)
		{
			if (digits[3]==1)
				cout << tousends[0] << " ";
			else if (digits[3]>1 && digits[3]<5)
				cout << units[digits[3]] << " " << tousends[1] << " ";
			else 
				cout << units[digits[3]] << " " << tousends[2] << " ";
			if (result%1000==0)
			{
				cout << endl;
				break;
			}
		}

		//Liczby trzycyfrowe.
		case 3:
		if (digits[2]>0)
		{
			if (result%100!=0)
				cout << hundreds[digits[2]-1] << " ";
			else if (result%100==0)
			{
				cout << hundreds[digits[2]-1] << endl;
				break;
			}
		}

		//Liczby dwucyfrowe.
		case 2:
		if (digits[1]>0)
		{
			if (result%10!=0 && digits[1]>1)
				cout << tens[digits[1]-1] << " " << units[digits[0]];
			else if (digits[1]==1 && digits[0]!=0)
				cout << teens[(result%10)-1];
			else if (digits[1]==1 && digits[0]==0)
				cout << tens[0];
			else if (result%10==0 && result<100)
				cout << tens[digits[1]-1];
			else if (result%10==0)
				cout << tens[digits[1]-1];
			cout << endl;
			break;
		}
		else;

		//Liczby jednocyfrowe.
		case 1:
		cout << units[digits[0]] << endl;
		break;
	}
}
