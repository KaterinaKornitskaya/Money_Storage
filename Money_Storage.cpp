// Money_Storage.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <set>
#include <map>
#include <iomanip>
#include <algorithm>

struct Date              // структура Дата
{
	unsigned day;
	unsigned month;
	unsigned year;

	void Output() const  // метод для вывода на экран даты
	{
		std::cout << std::setw(2) << std::setfill('0') << day << '/'
			<< std::setw(2) << std::setfill('0') << std::setfill('0')
			<< month << '/' << std::setw(2) << std::setfill('0')
			<< year;
	}
	void Input()        // метод для ввода даты пользователем
	{
		std::cout << "Enter day, month and year of spending: "
			<< " (in format dd mm yyyy with spaces):\n";
		std::cin >> day  >> month >> year;		
	}
};

struct Time              // структура Время
{
	unsigned hour;
	unsigned min;
	unsigned sec;

	void Output() const  // ф-ия для вывода на экран времени
	{
		std::cout << hour << ':' << min << ':' << sec
			<< std::endl;
	}
	void Input()         // ф-ия для ввода времени пользователем
	{
		std::cout << "Enter hour, minute and secund of spending: "
			<< " (in format hh mm ss with spaces):\n";
		std::cin >> hour >> min >> sec;
	}
};

bool isLeap(int year);
int diff_between_dates(Date begin_date, Date end_date);


class Spending     // класс Затрата
{
protected:
	float money;   // сумма конкретной затраты
	int category;  // категория затраты (1-продукты, 2-автотовары, 3-зоотовары,4-спорттовары, 5-спорт, 6-строительный мат)
	Date date;     // дата затраты
	Time time;     // время затраты
public:
	Spending() = default;
	
	Spending(float moneyP, int categoryP, Date dateP, Time timeP)
	{
		money = moneyP;
		category = categoryP;
		date = dateP;
		time = timeP;
	}
	
	void SetSpending()  // метод Добавить затрату
	{
		std::cout << "Enter spending: ";
		std::cin >> money;
		std::cout << "Choose category of spending: \n";
		std::cout << "1. Food shops.\n"
			      << "2. Pet shops.\n"
			      << "3. Other shops.\n"
			      << "4. Exit\n";
		std::cin >> category;
		date.Input();
		time.Input();
	}
	
	void Output() const  // вывод затраты
	{
		std::cout << "**********Spending**********\n"
			<< "Summa: " << money << std::endl
			<< "Category: " << category << std::endl;
		std::cout << "Date: ";
		date.Output();
		std::cout << "Time: ";
		time.Output();
	}
	
	float GetMoney() const  // гэттер
	{
		return money;       // возвращает значение поля money
	}

	float GetCategory() const  // гэттер
	{
		return category;       // возвращает значение поля category
	}

	bool operator<(const Spending obj) const  // перегрузка оператора <
	{
		return money > obj.money;
	}
	
	const Date GetDate() const { return date; }	
	const Time GetTime() const { return time; }
};


class MoneyStorage  // базовый класс Хранилище денег, абстрактный	                
{
protected:
	long long number;                   // номер кошелька или карты
	float total_money;                  // общее кол-во денег на карте или клшельке
	std::multiset<Spending> spendings;  // динамический массив объектов типа Spending
	float credit_limit;                 // если кредитный лимит > 0, то кредитная, иначе дебетовая
public:
	MoneyStorage()  // конструктор без параметров
	{
		number = 0;
		total_money = 0;
		credit_limit = 0;
	}
			
	MoneyStorage(long long numberP, float total_moneyP, float credit_limitP)  // конструктор с параметрами
	{
		number = numberP;
		total_money = total_moneyP;
		credit_limit = credit_limitP;
	}

	MoneyStorage(std::multiset<Spending>& spendingsP, long long numberP,
		float total_moneyP, float credit_limitP)  // конструктор с параметрами
	{
		spendings = spendingsP;
		number = numberP;
		total_money = total_moneyP;
		credit_limit = credit_limitP;
	}

	long long GetNumber()
	{
		return number;
	}
	float GetTotalMoney()
	{
		return total_money;
	}
	float GetCreditLimit()
	{
		return credit_limit;
	}
	virtual void Output() = 0;
	virtual void Input() = 0;

	void TopUp()  // пополнение хранилища денег		
	{
		double replenishment;                               // сумма пополнения
		std::cout << "Enter an amount of replenishment: ";  // введите сумму пополнения
		std::cin >> replenishment;                          // ввод суммы пополнения
		total_money += replenishment;                       // общее кол-во денег + пополнение
	}

	void AddSpending()  // добавить затрату
	{
		float spend;
		std::cout << "Enter spend: ";
		std::cin >> spend;
		total_money -= spend;  // общее кол-во денег - затрата
	}
	void Spend_money(double temp_money)  // метод Затрата
	{
		total_money -= temp_money;       // отнимаем от "всего денег" потраченные
	}
	long long GetNumber() const { return number; }
	std::multiset<Spending> GetSpendings() const  // вернуть весь набор затрат
	{
		return spendings;
	}
};


class Card : public MoneyStorage // класс Карта
{
	std::string bank_name;       // строка "название банка"
public:
	Card() : MoneyStorage() 
	{
		bank_name = "";
		number = 0;
		total_money = 0;
		credit_limit = 0;
	}

	Card(std::string bank_nameP, long long numberP, 
		float total_moneyP, float credit_limitP )
	{
		bank_name = bank_nameP;
		number = numberP;
		total_money = total_moneyP;
		credit_limit = credit_limitP;
	}

	Card(std::multiset<Spending>& spend, std::string bank_nameP,
		long long numberP, float total_moneyP, float credit_limitP)
		
	{
		spendings = spend;
		bank_name = bank_nameP;
		number = numberP;
		total_money = total_moneyP;
		credit_limit = credit_limitP;
	}

	void Input()
	{
		std::cout << "**********Make_Card*********\n";
		std::cout << "Enter name of the bank: ";
		std::cin >> bank_name;
		std::cout << "Enter card number: ";
		std::cin >> number;
		std::cout << "Enter carrent amount of money: ";
		std::cin >> total_money;
		std::cout << "Enter credit limit: ";
		std::cin >> credit_limit;
	}

	void Output()
	{
		//std::cout << "**********Your_Card*********\n";
		std::cout << "\nBank name: " << '\t' << bank_name;
		std::cout << "\nCard number: " << '\t' << number;
		std::cout << "\nBalance: " << '\t' << total_money;
		std::cout << "\nCredit limit: " << '\t' << credit_limit << '\n';
	}	
};

class Wallet : public MoneyStorage // класс Кошелек
{
	std::string bank_name;         // строка "название банка"
public:
	Wallet() : MoneyStorage()
	{
		bank_name = "";
		number = 0;
		total_money = 0;
	}

	Wallet(std::string bank_nameP, long long numberP,
		float total_moneyP)
	{
		bank_name = bank_nameP;
		number = numberP;
		total_money = total_moneyP;
	}

	Wallet(std::multiset<Spending>& spend, std::string bank_nameP,
		long long numberP, float total_moneyP)

	{
		spendings = spend;
		bank_name = bank_nameP;
		number = numberP;
		total_money = total_moneyP;
	}

	void Input()
	{
		std::cout << "*********Make_Wallet********\n";
		std::cout << "Enter name of the wallet: ";
		std::cin >> bank_name;
		std::cout << "Enter wallet number: ";
		std::cin >> number;
		std::cout << "Enter carrent amount of money: ";
		std::cin >> total_money;
	}

	void Output()
	{
		//std::cout << "\n*********Your_Wallet********\n";
		std::cout << "\nBank name: " << '\t' << bank_name;
		std::cout << "\nWallet number: " << '\t' << number;
		std::cout << "\nBalance: " << '\t' << total_money << '\n';
	}
};

void RatingMonth(std::multiset <Spending> report_spend_wallet, std::multiset <Spending> report_spend_card);
void RatingWeek(std::multiset <Spending> report_spend_wallet, std::multiset <Spending> report_spend_card);

void ShowDayReport(std::multiset <Spending> report_spend_card,
	std::multiset <Spending> report_spend_wallet);
void ShowMonthReport(std::multiset <Spending> report_spend_card,
	std::multiset <Spending> report_spend_wallet);

int main()
{
	Spending* spend_card[10];      // объявление указателя на массив затрата_карты типа Spending
	Spending* spend_wallet[10];    // объявление указателя на массив затрата_кошелька типа Spending
	std::multiset<Spending> report_spend_card;    // объект затраты для отчета по карте
	std::multiset<Spending> report_spend_wallet;  // объект затраты для отчета по кошельку
	MoneyStorage* obj_card[10];    // объявление указателя на массив карта типа MoneyStorage
	MoneyStorage* obj_wallet[10];  // объявление указателя на массив кошелек типа MoneyStorage

	short num_spend_card = 0;      // начальная переменная для затраты по карте
	short num_spend_wallet = 0;    // начальная переменная для затраты по кошельку
	int count_card = 0;            // счетчик для колличества карт
	int count_wallet = 0;          // счетчик для колличества кошельков	
	int num_in_order = 0;          // переменная для номера по/порядку

	unsigned operation_main_menu;  // переменная для выбора пункта главного меню
	do
	{
		system("cls");
		std::cout << "Please, choose the operation: \n";
		std::cout << "1. Card Menu"                     // Меню карта
				  << "\n   (here you can add new card, top up card, view your cards.)\n"
				  << "2. Wall Menu"                     // Меню кошелек
				  << "\n   (here you can add new wallet, top up wallet, view your wallets.)\n"
		          << "3. Add spend to storage\n"        // Добавить затрату
			      << "4. Reports Menu\n"                // меню Отчеты
			<< "5. \n"
		          << "5. Exit\n";  // выход
		std::cout << "Enter your choice: ";
		std::cin >> operation_main_menu;
		//while (true)
		unsigned operation_card_menu = 0;  // переменная для выбора пунктов в подменю карта/кошелек
		switch (operation_main_menu)
		{
		case 1:   // Menu карты
			while (operation_card_menu != 4)
			{
				system("cls");
				std::cout << "Card Menu\n";           // меню Карта (подменю основного меню)
				std::cout << "1. Add new card\n";     // добавить карту
				std::cout << "2. Top up the card\n";  // Пополнить карту
				std::cout << "3. Show all cards\n";   // Показать все карты
				std::cout << "4. Exit\n";             // выход
				std::cout << "Enter your choice: ";
				std::cin >> operation_card_menu;
				if (operation_card_menu == 4) break;
				switch (operation_card_menu)
				{
				case 1:  // добавить карту
					count_card += 1;                  // плюсуем счетчик карт
					obj_card[count_card] = new Card;  // создаем объект Карта
					obj_card[count_card]->Input();    // вызов метода Input
					break;
				case 2:  // Пополнить карту
					for (int i = 1; i < count_card + 1; i++)  // для вывода существующих карт с номером п/п
					{										  //
						std::cout << "\n***********Card# " 	  //
							<< i << "***********";			  //
						obj_card[i]->Output();				  //  
					}										  //
					std::cout << "Enter card number: ";
					std::cin >> num_in_order;         // ввод номера по/порядку
					obj_card[num_in_order]->TopUp();  // вызов метода TopUp для соответствующей карты
					break;
				case 3:  // Показать все карты
					for (int i = 1; i < count_card + 1; i++)  //  для вывода существующих карт с номером п/п
					{										  //
						std::cout << "\n***********Card# " 	  //
							<< i << "***********";			  //
						obj_card[i]->Output();				  //
					}										  //
					break;
				default: std::cout << "Invalid choice\n";
					break;
				}
				std::cout << "Press any button...";
				_getch();
			}
			break;
		case 2:   // Menu Кошелек
			while (operation_card_menu != 4)
			{
				system("cls");
				std::cout << "Wallet Menu\n";           // меню Кошелек (подменю основного меню)
				std::cout << "1. Add new wallet\n";     // добавить кошелек
				std::cout << "2. Top up the wallet\n";  // Пополнить кошелек
				std::cout << "3. Show all wallets\n";   // Показать все кошельки
				std::cout << "4. Exit\n";               // выход
				std::cout << "Enter your choice: ";
				std::cin >> operation_card_menu;
				if (operation_card_menu == 4) break;
				switch (operation_card_menu)
				{
				case 1:  // добавить кошелек
					count_wallet += 1;                          // плюсуем счетчик кошельков
					obj_wallet[count_wallet] = new Wallet;      // создаем объект Кошелек
					obj_wallet[count_wallet]->Input();          // вызов метода Input
					break;
				case 2:  // Пополнить кошелек
					for (int i = 1; i < count_wallet + 1; i++)  // для вывода существующих кошельков с номером п/п
					{										    //
						std::cout << "\n***********Wallet# " 	//
							<< i << "***********";			    //
						obj_wallet[i]->Output();				//  
					}										    //
					std::cout << "Enter wallet number: ";
					std::cin >> num_in_order;                   // ввод номера по/порядку
					obj_card[num_in_order]->TopUp();            // вызов метода TopUp для соответствующего кошелька
					break;
				case 3:  // Показать все кошельки
					for (int i = 1; i < count_wallet + 1; i++)  //  для вывода существующих кошельков с номером п/п
					{										    //
						std::cout << "\n***********Wallet# " 	//
							<< i << "***********";			    //
						obj_wallet[i]->Output();				//
					}										    //
					break;
				default:
					std::cout << "Invalid choice\n";
					break;
				}
				std::cout << "Press any button...";
				_getch();
			}
			break;
		case 3:  // добавить затрату
			do
			{
				system("cls");
				unsigned operation_spend_menu = 0;            // переменная для выбора пункта в подменю Затрата
				double money_spend = 0;                       // переменная для потраченных денег
				std::multiset<Spending>::iterator it_card;    // объявляем итератор для прохода по картам
				std::multiset<Spending>::iterator it_wallet;  // объявляем итератор для прохода по кошелькам

				std::cout
					<< "\n1. Add spend to card.\n"            // внести затрату с карты
					<< "2. Add spend to wallet.\n"            // внести затрату с кошелька
					<< "3. Show all spendings.\n"             // посмотреть все затраты
					<< "4. Exit.\n";                          // выход
				std::cout << "Enter your choice: ";

				std::cin >> operation_spend_menu;
				if (operation_spend_menu == 4) break;
				switch (operation_spend_menu)
				{
				case 1:  // внести затрату с карты
					for (int i = 1; i < count_card + 1; i++)  // для вывода существующих карт с номером п/п
					{										  // 
						std::cout << "\n***********Card# " 	  // 
							<< i << "***********";			  // 
						obj_card[i]->Output();				  // 
					}
					std::cout << "\nEnter card number: ";
					std::cin >> num_in_order;                 // ввод номера п/п карты
					obj_card[num_in_order]->Output();

					spend_card[num_in_order] = new Spending;              // создание объекта затрата_карты
					spend_card[num_in_order]->SetSpending();              // вызов метода SetSpending для соотв. карты
					money_spend += spend_card[num_in_order]->GetMoney();  // к потраченным деньгам плюсуем затрату
					obj_card[num_in_order]->Spend_money(money_spend);     // вызов метода Трата для карты

					spend_card[num_in_order]->Output();

					report_spend_card.insert(*spend_card[num_in_order]);
					num_spend_card += num_in_order;
					break;
				case 2:  // внести затрату с кошелька
					for (int i = 1; i < count_wallet + 1; i++)  // для вывода существующих кошельков с номером п/п
					{										    // 
						std::cout << "\n***********Wallet# " 	// 
							<< i << "***********";			    // 
						obj_wallet[i]->Output();				// 
					}
					std::cout << "\nEnter wallet number: ";
					std::cin >> num_in_order;                   // ввод номера п/п кошелька
					obj_card[num_in_order]->Output();

					spend_wallet[num_in_order] = new Spending;              // создание объекта затрата_кошелька
					spend_wallet[num_in_order]->SetSpending();              // вызов метода SetSpending для соотв. кошелька
					money_spend += spend_wallet[num_in_order]->GetMoney();  // к потраченным деньгам плюсуем затрату
					obj_wallet[num_in_order]->Spend_money(money_spend);     // вызов метода Трата для кошелька

					spend_wallet[num_in_order]->Output();

					report_spend_wallet.insert(*spend_wallet[num_in_order]);
					num_spend_wallet += num_in_order;
					break;
					break;
				case 3:  // посмотреть все затраты
					it_card = report_spend_card.begin();
					for (; it_card != report_spend_card.end(); it_card++)
					{
						it_card->Output();    // все затраты карты
					}
					it_wallet = report_spend_wallet.begin();
					for (; it_wallet != report_spend_wallet.end(); it_wallet++)
					{
						it_wallet->Output();  // все затраты кошелька
					}
					break;
				default:
					std::cout << "Invalid choice!\n";
				}
				std::cout << "Press any button...";
				_getch();
			} while (true);
			break;

		case 4:
			unsigned operation_report_menu = 0;  // переменная для выбора пункта меню Рейтинг
			while (operation_report_menu != 5)
			{
				system("cls");
				std::cout << "Report Menu\n";          // меню Очет (подменю основного меню)
				std::cout << "1. Day report\n";        // отчет за день
				std::cout << "2. Month report\n";      // отчет за месяц
				std::cout << "3. Rating for month\n";  // рейтинг за месяц
				std::cout << "4. Rating for week\n";   // рейтинг за неделю
				std::cout << "5. Exit\n";              // выход
				std::cout << "Enter your choice: ";
				std::cin >> operation_report_menu;
				if (operation_report_menu == 5) break;
				switch (operation_report_menu)
				{
				case 1:  // добавить карту
					ShowDayReport(report_spend_card, report_spend_wallet);
					break;
				case 2:  // Пополнить карту
					ShowMonthReport(report_spend_card, report_spend_wallet);
					break;
				case 3:  // Показать все карты
					RatingMonth(report_spend_card, report_spend_wallet);
					break;
				case 4:  // Показать все карты
					RatingWeek(report_spend_card, report_spend_wallet);
					break;
				default: std::cout << "Invalid choice\n";
					break;
				}
				std::cout << "Press any button...";
				_getch();
			}
			break;
		}
		std::cout << "Press any button...";
		_getch();
	}while (operation_main_menu !=5);
	return 0;
}



// метод Топ-3 траты за выбранный месяц
void RatingMonth(std::multiset <Spending> report_spend_wallet, std::multiset <Spending> report_spend_card)
{
	std::multiset <Spending> rating;  // создаем объект типа multiset
	std::cout << "\nMonth rating - Top 3 spendings!\n";
	unsigned month;                   // переменная для требуемого месяца
	std::cout << "Enter month number for the rating: ";
	std::cin >> month;                // ввод искомого месяца
	unsigned year;                    // переменная для требуемого года
	std::cout << "Enter year for rating: ";
	std::cin >> year;                 // ввод искомого года
	for (auto elem1 : report_spend_card)  
	{		
		// ищем элементы, с соответствующим месяцем и годом для карты
		if (elem1.GetDate().month == month && elem1.GetDate().year == year)
		{
			rating.insert(elem1);  // вставялем нужные элементы
		}	
	}
	for (auto elem2 : report_spend_wallet)
	{
		// ищем элементы, с соответствующим месяцем и годом для кошелька
		if (elem2.GetDate().month == month && elem2.GetDate().year == year)
		{
			rating.insert(elem2);  // вставялем нужные элементы
		}
	}
	
	std::multiset<Spending>::iterator it;  // объявляем итератор
	it = rating.begin();                   // присваиваем итератору начальный элемент 
	unsigned size = 3;                     // размер рейтинга (топ-3)
	if (rating.size() < 3) size = rating.size();
	for (int i = 0; i < size; i++)
	{
		(*it).Output();  // выводим соответствующие значения
		it++;
	}

	std::cout << "Do you want to save the rating in the file? (yes - 1, no - 0)\n";
	bool yes;  // булевая перемнная для выбора пользователем
	std::cin >> yes;
	if (!yes)
		return;
	std::ofstream out;             // поток для записи
	out.open("Month rating.txt");  // окрываем файл для записи
	it = rating.begin();
	if (out.is_open())             // если файл открылся верно - записываем в него результаты
	{
		out << "Top 3 spendings for the month " << month << " of the year: " << year << "!\n";
		for (int i = 0; i < size; i++)
		{
			// записываем сумму затраты
			out << "Amount of money spending: " << it->GetMoney() << "  Category of spending: " 
				<< it->GetCategory() << std::endl;
			// записываем дату затраты
			out << "Date of transaction: " << std::setw(2) << std::setfill('0') 
				<< it->GetDate().day << '/' << std::setw(2) << std::setfill('0') 
				<< it->GetDate().month << '/' << std::setw(2) << std::setfill('0') 
				<< it->GetDate().year << "\n";
			// записываем время затраты
			out << "Time of transaction: " << std::setw(2) << std::setfill('0') 
				<< it->GetTime().hour << ':' << std::setw(2) << std::setfill('0') 
				<< it->GetTime().min << ':' << std::setw(2) << std::setfill('0') 
				<< it->GetTime().sec << "\n";
			it++;
		}
	}
}

// метод Топ-3 траты за выбранную неделю
void RatingWeek(std::multiset <Spending> report_spend_wallet, std::multiset <Spending> report_spend_card)
{
	std::multiset <Spending> rating;  // создаем объект типа multiset
	std::cout << "\nWeek rating - Top 3 spendings!\n";
	Date start_day;  // переменная для начала отсчета недели
	start_day.Input();
	Date end_day;    // переменная для конца отсчета недели
	end_day.Input();
	
	for (auto elem1 : report_spend_card)
	{
		// ищем элементы, с соответствующими датами для карты
		if (elem1.GetDate().year >= start_day.year && elem1.GetDate().year <= end_day.year &&
			elem1.GetDate().month >= start_day.month && elem1.GetDate().month <= end_day.month &&
			elem1.GetDate().day >= start_day.day && elem1.GetDate().day <= end_day.day)
		{
			rating.insert(elem1);  // вставялем нужные элементы
		}
	}
	for (auto elem2 : report_spend_wallet)
	{
		// ищем элементы, с соответствующими датами для кошелька
		if (elem2.GetDate().year >= start_day.year && elem2.GetDate().year <= end_day.year &&
			elem2.GetDate().month >= start_day.month && elem2.GetDate().month <= end_day.month &&
			elem2.GetDate().day >= start_day.day && elem2.GetDate().day <= end_day.day)
		{
			rating.insert(elem2);  // вставялем нужные элементы
		}
	}

	std::multiset<Spending>::iterator it;  // объявляем итератор
	it = rating.begin();                   // присваиваем итератору начальный элемент 
	unsigned size = 3;                     // размер рейтинга (топ-3)
	if (rating.size() < 3) size = rating.size();
	for (int i = 0; i < size; i++)
	{
		(*it).Output();  // выводим соответствующие значения
		it++;
	}

	std::cout << "Do you want to save the rating in the file? (yes - 1, no - 0)\n";
	bool yes;  // булевая перемнная для выбора пользователем
	std::cin >> yes;
	if (!yes)
		return;
	std::ofstream out;            // поток для записи
	out.open("Week rating.txt");  // окрываем файл для записи
	it = rating.begin();
	if (out.is_open())            // если файл открылся верно - записываем в него результаты
	{
		out << "Top 3 spendings for the week "  << "!\n";
		for (int i = 0; i < size; i++)
		{
			// записываем сумму затраты
			out << "Amount of money spending: " << it->GetMoney() << "  Category of spending: "
				<< it->GetCategory() << std::endl;
			// записываем дату затраты
			out << "Date of transaction: " << std::setw(2) << std::setfill('0')
				<< it->GetDate().day << '/' << std::setw(2) << std::setfill('0')
				<< it->GetDate().month << '/' << std::setw(2) << std::setfill('0')
				<< it->GetDate().year << "\n";
			// записываем время затраты
			out << "Time of transaction: " << std::setw(2) << std::setfill('0')
				<< it->GetTime().hour << ':' << std::setw(2) << std::setfill('0')
				<< it->GetTime().min << ':' << std::setw(2) << std::setfill('0')
				<< it->GetTime().sec << "\n";
			it++;
		}
	}
}

// дневной отчет
void ShowDayReport(std::multiset <Spending> report_spend_card,
	std::multiset <Spending> report_spend_wallet)
{
	std::multiset <Spending> rating;  // создаем объект типа multiset
	std::cout << "\ndaily rating - Top 3 spendings!\n";
	unsigned day;                     // переменная для требуемого дня
	std::cout << "Enter day number for the rating: ";
	std::cin >> day;                  // ввод искомого дня
	unsigned month;                   // переменная для требуемого месяца
	std::cout << "Enter month number for the rating: ";
	std::cin >> month;                // ввод искомого месяца
	unsigned year;                    // переменная для требуемого года
	std::cout << "Enter year for rating: ";
	std::cin >> year;                 // ввод искомого года

	for (const auto& elem1 : report_spend_card)
	{
		if (elem1.GetDate().day == day &&
			elem1.GetDate().month == month &&
			elem1.GetDate().year == year)
		{
			rating.insert(elem1);
		}
	}

	for (const auto& elem2 : report_spend_wallet)
	{
		if (elem2.GetDate().day == day &&
			elem2.GetDate().month == month &&
			elem2.GetDate().year == year)
		{
			rating.insert(elem2);
		}
	}

	std::multiset<Spending>::iterator it;
	it = rating.begin();
	for (; it != rating.end(); ++it)
	{
		it->Output();
	}

	std::cout << "To save daily raport to the file?\n"
		<< "if 'yes' - press 1, if 'no' - press 0. ";
	bool user_choice;
	std::cin >> user_choice;
	if (!user_choice)
		return;

	for (it = rating.begin(); it != rating.end(); ++it)
	{
		std::cout << "Amount of money spending: " << it->GetMoney() << std::endl
			<< "Date of transaction: " << std::setw(2) << std::setfill('0')
			<< it->GetDate().day << '/' << std::setw(2) << std::setfill('0')
			<< it->GetDate().month << '/' << std::setw(2) << std::setfill('0')
			<< it->GetDate().year << "\n";
		std::cout << "Time of transaction: " << std::setw(2) << std::setfill('0')
			<< it->GetTime().hour << ':' << std::setw(2) << std::setfill('0')
			<< it->GetTime().min << ':' << std::setw(2) << std::setfill('0')
			<< it->GetTime().sec << "\n\n";
		it++;
	}

	std::ofstream file_d_rep;
	file_d_rep.open("Daily report.txt");
	if (file_d_rep.is_open())
	{
		file_d_rep << "Daily report for :" << std::endl;
		//day_for_report.Output();

		for (it = rating.begin(); it != rating.end(); ++it)
		{
			file_d_rep << "Amount of money spending: " << it->GetMoney() << std::endl
			    << "Date of transaction: " << std::setw(2) << std::setfill('0')
				<< it->GetDate().day << '/' << std::setw(2) << std::setfill('0')
				<< it->GetDate().month << '/' << std::setw(2) << std::setfill('0')
				<< it->GetDate().year << "\n";
			file_d_rep << "Time of transaction: " << std::setw(2) << std::setfill('0')
				<< it->GetTime().hour << ':' << std::setw(2) << std::setfill('0')
				<< it->GetTime().min << ':' << std::setw(2) << std::setfill('0')
				<< it->GetTime().sec << "\n\n";
			it++;
		}
	}
}

// отчет за месяц
void ShowMonthReport(std::multiset <Spending> report_spend_card,
	std::multiset <Spending> report_spend_wallet)
{
	std::multiset <Spending> rating;  // создаем объект типа multiset
	std::cout << "\nMonth rating - Top 3 spendings!\n";
	unsigned month;                   // переменная для требуемого месяца
	std::cout << "Enter month number for the rating: ";
	std::cin >> month;                // ввод искомого месяца
	unsigned year;                    // переменная для требуемого года
	std::cout << "Enter year for rating: ";
	std::cin >> year;                 // ввод искомого года

	for (const auto& elem1 : report_spend_card)
	{
		if (elem1.GetDate().month == month &&
			elem1.GetDate().year == year)
		{
			rating.insert(elem1);
		}
	}

	for (const auto& elem2 : report_spend_wallet)
	{
		if (elem2.GetDate().month == month &&
			elem2.GetDate().year == year)
		{
			rating.insert(elem2);
		}
	}

	std::multiset<Spending>::iterator it;
	it = rating.begin();
	for (; it != rating.end(); ++it)
	{
		it->Output();
	}

	std::cout << "To save monthly raport to the file?\n"
		<< "if 'yes' - press 1, if 'no' - press 0. ";
	bool user_choice;
	std::cin >> user_choice;
	if (!user_choice)
		return;

	for (it = rating.begin(); it != rating.end(); ++it)
	{
		std::cout << "Amount of money spending: " << it->GetMoney() << std::endl
			<< "Date of transaction: " << std::setw(2) << std::setfill('0')
			<< it->GetDate().day << '/' << std::setw(2) << std::setfill('0')
			<< it->GetDate().month << '/' << std::setw(2) << std::setfill('0')
			<< it->GetDate().year << "\n";
		std::cout << "Time of transaction: " << std::setw(2) << std::setfill('0')
			<< it->GetTime().hour << ':' << std::setw(2) << std::setfill('0')
			<< it->GetTime().min << ':' << std::setw(2) << std::setfill('0')
			<< it->GetTime().sec << "\n\n";
		it++;
	}

	std::ofstream file_d_rep;
	file_d_rep.open("Daily report.txt");
	if (file_d_rep.is_open())
	{
		file_d_rep << "Daily report for :" << std::endl;
		//month_for_report.Output();

		for (it = rating.begin(); it != rating.end(); ++it)
		{
			file_d_rep << "Amount of money spending: " << it->GetMoney() << std::endl
				<< "Date of transaction: " << std::setw(2) << std::setfill('0')
				<< it->GetDate().day << '/' << std::setw(2) << std::setfill('0')
				<< it->GetDate().month << '/' << std::setw(2) << std::setfill('0')
				<< it->GetDate().year << "\n";
			file_d_rep << "Time of transaction: " << std::setw(2) << std::setfill('0')
				<< it->GetTime().hour << ':' << std::setw(2) << std::setfill('0')
				<< it->GetTime().min << ':' << std::setw(2) << std::setfill('0')
				<< it->GetTime().sec << "\n\n";
			it++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////// Методы для даты
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isLeap(int year)  // функция для определения, високосным ли является год
{
	if (year % 400 == 0) return true;                   // если год кратен 400, то он високосный
	if (year % 4 == 0 && year % 100 != 0) return true;  // если год кратен 4, но в то же время не кратен 100, то он тоже високосный
	return false;
}

int diff_between_dates(Date begin_date, Date end_date)  // функция, определяющая количество дней между 2-мя датами
{                                                       // эта функция нужна для отображения дел за неделю
	int day_begin = begin_date.day;
	int month_begin = begin_date.month;
	int year_begin = begin_date.year;
	int day_end = end_date.day;
	int month_end = end_date.month;
	int year_end = end_date.year;
	enum months { jan = 31, feb = 28, march = 31, apr = 30, may = 31, jun = 30, jul = 31, aug = 31, sept = 30, oct = 31, nov = 30, dec = 31 };
	int alldays_begin = 0, alldays_end = 0;
	switch (month_begin) {
	case 1: alldays_begin = day_begin; break;
	case 2: alldays_begin = day_begin + jan; break;
	case 3: alldays_begin = day_begin + feb + jan; break;
	case 4: alldays_begin = day_begin + march + feb + jan; break;
	case 5: alldays_begin = day_begin + apr + march + feb + jan; break;
	case 6: alldays_begin = day_begin + may + apr + march + feb + jan; break;
	case 7: alldays_begin = day_begin + jun + may + apr + march + feb + jan; break;
	case 8: alldays_begin = day_begin + jul + jun + may + apr + march + feb + jan; break;
	case 9: alldays_begin = day_begin + aug + jul + jun + may + apr + march + feb + jan; break;
	case 10: alldays_begin = day_begin + sept + aug + jul + jun + may + apr + march + feb + jan; break;
	case 11: alldays_begin = day_begin + oct + sept + aug + jul + jun + may + apr + march + feb + jan; break;
	case 12: alldays_begin = day_begin + nov + oct + sept + aug + jul + jun + may + apr + march + feb + jan; break;
	}
	switch (month_end) {
	case 1: alldays_end = day_end; break;
	case 2: alldays_end = day_end + jan; break;
	case 3: alldays_end = day_end + feb + jan; break;
	case 4: alldays_end = day_end + march + feb + jan; break;
	case 5: alldays_end = day_end + apr + march + feb + jan; break;
	case 6: alldays_end = day_end + may + apr + march + feb + jan; break;
	case 7: alldays_end = day_end + jun + may + apr + march + feb + jan; break;
	case 8: alldays_end = day_end + jul + jun + may + apr + march + feb + jan; break;
	case 9: alldays_end = day_end + aug + jul + jun + may + apr + march + feb + jan; break;
	case 10: alldays_end = day_end + sept + aug + jul + jun + may + apr + march + feb + jan; break;
	case 11: alldays_end = day_end + oct + sept + aug + jul + jun + may + apr + march + feb + jan; break;
	case 12: alldays_end = day_end + nov + oct + sept + aug + jul + jun + may + apr + march + feb + jan; break;
	}

	// определим количество високосных годов между двумя датами, но без цикла
	// сначала найдем високосных лет между начальным и конечным годом (не включительно)
	int leap_summ = 0;
	int leap_summ_4 = (year_end - 1) / 4 - (year_begin / 4 + 1) + 1;         // количество лет, кратных 4, между данными годами
	int leap_summ_100 = (year_end - 1) / 100 - (year_begin / 100 + 1) + 1;   // количество лет, кратных 100, между данными годами
	int leap_summ_400 = (year_end - 1) / 400 - (year_begin / 400 + 1) + 1;   // количество лет, кратных 400, между данными годами
	leap_summ = leap_summ_4 - leap_summ_100 + leap_summ_400;

	// если начальный год високосный и дата раньше 1 марта, то учитываем, что он високосный
	if (isLeap(year_begin) && month_begin < 3)
		leap_summ++;
	// если конечный год високосный и дата не раньше 1 марта, то учитываем, что он високосный
	if (isLeap(year_end) && month_end >= 3)
		leap_summ++;

	int difference = alldays_end - alldays_begin + 365 * (year_end - year_begin) + leap_summ;
	return difference;
}


