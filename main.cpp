#include <iostream>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <locale>
#include <iomanip>

using namespace std;

char FILENAME[] = "currencies.dat";
fstream fp;
int n;

const unsigned short MAX_CURRENCIES = 70;
const unsigned short MAX_CURRENCY_NAME = 30;
const unsigned short MAX_CURRENCY_ISO = 3;

#define COLUMN_SEPARATOR 1;
#define COLUMN_NAME_WIDTH ;
#define COLUMN_ISO_WIDTH 5;
#define COLUMN_BUY_WIDTH 10;
#define COLUMN_SELL_WIDTH 10;
#define COLUMN_AVALIBALITY_WIDTH 10;
#define COLUMN_TRADE_WIDTH 5;

struct currency {
	char currencyName[MAX_CURRENCY_NAME];
	char currencyISOcode[MAX_CURRENCY_ISO];
	double buyingRate;
	double sellingRate;
	double avalibality;
	double maxAmountForChange;
	bool isItTraded;
};

void menu();
void createFile(struct currency currencyList[]);
void printAllCurrency(struct currency currencyList[]);
void addCurrency();


void main()
{
	setlocale(LC_ALL, "Bulgarian");
	menu();
;}

void menu()
{
	currency currencyList[MAX_CURRENCIES];
	int menuOption;

	do
	{
		do
		{
			cout << "********Меню********" << endl;
			cout << "1) Добави валута " << endl;
			cout << "2) Принтирай всички валути" << endl;
			cout << "3) Допълване на валута" << endl;
			cout << "4) Изход" << endl;
			cout << "Въведете своя избор от 1 до 4!" << endl;
			cin >> menuOption;
		} while (menuOption < 1 || menuOption > 4);
		switch (menuOption)
		{
		case 1:
			createFile(currencyList);
			break;
		case 2:
			printAllCurrency(currencyList);
			cin.get();
			system("pause");
			system("CLS");
			break;
		case 3:
			addCurrency();
			break;
		default: cout << "Край" << endl;
			break;
		}
	} while (menuOption != 4);
}


void createFile(struct currency currencyList[])
{
	cout << "How many currencies would you like to add?" << endl;
	cin >> n;

	fp.open(FILENAME,ios::binary | ios::out);

	if (!fp)
	{
		cout << "Грешка при отварянето на файла" << endl;
		system("pasue");
		return;
	}

	for (int i = 0; i < n; i++)
	{
		fflush(stdin); // Clear the input buffer
		cout << "Enter the data for currency number" << i + 1 << endl; 
		cout << "What is the currency name?" << endl;
		cin >> currencyList[i].currencyName;
		cout << "What is the currency's iso code?" << endl;
		cin >> currencyList[i].currencyISOcode;
		cout << "What is the currency's buying rate?" << endl;
		cin >> currencyList[i].buyingRate;
		cout << "What is the currency's selling rate?" << endl;
		cin >> currencyList[i].sellingRate;
		cout << "What is the currency's avalibality?" << endl;
		cin >> currencyList[i].avalibality;
		cout << "What is the currency's max amount per change?" << endl;
		cin >> currencyList[i].maxAmountForChange;
		cout << "Is it tradable? (type 1 for no and 0 for yes)" << endl;
		cin >> currencyList[i].isItTraded;
	}
	fp.write((char*)currencyList, n * sizeof(currency));
	fp.close();
}

void printAllCurrency(struct currency currencyList[])
{
	int i = 0;
	long pos;
	currency c;

	cout << setw(15) << left << "Currency name";
	cout << setw(1) << left << " | ";
	cout << setw(5) << left << "ISO code";
	cout << setw(1) << left << " | ";
	cout << setw(12) << left << "Buying rate";
	cout << setw(1) << left << " | ";
	cout << setw(15) << left << "Selling rate";
	cout << setw(1) << left << " | ";
	cout << setw(15) << left << "Avalability";
	cout << setw(1) << left << " | ";
	cout << setw(20) << left << "Max amount per change";
	cout << setw(1) << left << " | ";
	cout << setw(15) << left << "Is it tradable?" << endl;

	fp.open(FILENAME, ios::in | ios::binary); // file opens for reading

	if (!fp) {
		cout << "Грешка при създаване на файла." << endl;
	}

	fp.seekg(0, ios::end);
	pos = fp.tellg();
	fp.close();

	fp.open(FILENAME, ios::in | ios::binary);

	for (int i = 0; i < pos / (sizeof(currency)); i++) {
		fp.read((char*)&c, sizeof(currency)); // From the file it reads data for one currency
		currencyList[i] = c;

		cout << setw(15) << left << currencyList[i].currencyName;
		cout << setw(1) << left << " | ";
		cout << setw(5) << left << currencyList[i].currencyISOcode;
		cout << setw(1) << left << " | ";
		cout << setw(12) << left << currencyList[i].buyingRate;
		cout << setw(1) << left << " | ";
		cout << setw(15) << left << currencyList[i].sellingRate;
		cout << setw(1) << left << " | ";
		cout << setw(15) << left << fixed << setprecision(0) << currencyList[i].avalibality;
		cout << setw(1) << left << " | ";
		cout << setw(20) << left << fixed << setprecision(0) << currencyList[i].maxAmountForChange;
		cout << setw(1) << left << " | ";
		cout << setw(15) << left << (currencyList[i].isItTraded ? "No" : "Yes") << endl;
	}

	fp.close();
}

void addCurrency() 
{
	currency cc;
	long pos;
	fp.open(FILENAME, ios::binary | ios::in);
	if (!fp)
	{
		cout << "Грешка при прочитане на файла. " << endl;
	}
	fp.seekg(01, ios::end);
	pos = fp.tellg();
	fp.close();
	fp.open(FILENAME, ios::binary | ios::app);

	if (!fp)
	{
		cout << "Грешка при отваряне на файла." << endl;
	}
	fflush(stdin);
	cout << "Enter the data for currency number" << pos / sizeof(currency) + 1 << endl;
	cout << "What is the currency name?" << endl;
	cin >> cc.currencyName;
	cout << "What is the currency's iso code?" << endl;
	cin >> cc.currencyISOcode;
	cout << "What is the currency's buying rate?" << endl;
	cin >> cc.buyingRate;
	cout << "What is the currency's selling rate?" << endl;
	cin >> cc.sellingRate;
	cout << "What is the currency's avalibality?" << endl;
	cin >> cc.avalibality;
	cout << "What is the currency's max amount per change?" << endl;
	cin >> cc.maxAmountForChange;
	cout << "Is it tradable? (type 1 for no and 0 for yes)" << endl;
	cin >> cc.isItTraded;

	
	fp.write((char*)&cc, sizeof(currency));
	fp.close();


}