// Money_Storage.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
//using namespace std;
struct Date  // структура Дата
{
	unsigned day;
	unsigned month;
	unsigned year;

	void Output() const  // ф-ия для вывода на экран даты
	{
		std::cout << std::setw(2) << std::setfill('0') << day << '/'
			<< std::setw(2) << std::setfill('0') << std::setfill('0')
			<< month << '/' << std::setw(2) << std::setfill('0')
			<< year;
	}
	void Input()  // ф-ия для ввода даты пользователем
	{
		std::cout << "Enter day of spending: ";
		std::cin >> day;
		std::cout << "Enter month of spending: ";
		std::cin >> month;
		std::cout << "Enter year of spending: ";
		std::cin >> year;
	}
};



struct Time  // структура Время
{
	unsigned hour;
	unsigned min;
	unsigned sec;

	void Output() const  // ф-ия для вывода на экран времени
	{
		std::cout << hour << ':' << min << ':' << sec
			<< std::endl;
	}

	void Input()  // ф-ия для ввода времени пользователем
	{
		std::cout << "Enter hour of spending: ";
		std::cin >> hour;
		std::cout << "Enter minute  of spending: ";
		std::cin >> min;
		std::cout << "Enter second of spending: ";
		std::cin >> sec;
	}
};

bool isLeap(int year)    // функция для определения, високосным ли является год
{
	if (year % 400 == 0) return true;    // если год кратен 400, то он високосный
	if (year % 4 == 0 && year % 100 != 0) return true;   // если год кратен 4, но в то же время не кратен 100, то он тоже високосный
	return false;
}

int diff_between_dates(Date begin_date, Date end_date) // функция, определяющая количество дней между 2-мя датами
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
	int leap_summ_4 = (year_end - 1) / 4 - (year_begin / 4 + 1) + 1;   // количество лет, кратных 4, между данными годами
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

/*
	Создайте систему управления персональными финансами. 
	Система должна иметь следующие возможности:
	■ Наличие разных кошельков и карт (дебетовых/кредитных);
	■ Пополнение кошельков и карт;
	■ Внесение затрат. Каждая затрата относится к определенной категории;
	■ Формирование отчетов по затратам и категориям:
	  • день; • неделя;• месяц.
	■ Формирование рейтингов по максимальным суммам:
	  • ТОП-3 затрат: - неделя; - месяц.
	  • ТОП-3 категорий: - неделя; - месяц.
	■ Сохранение отчетов и рейтингов в файл.
*/



class Spending  // класс Затрата
{
protected:
	float money;  // сумма конкретной затраты
	int category;  // категория затраты (1-продукты, 2-автотовары, 3-зоотовары,4-спорттовары, 5-спорт, 6-строительный мат)
	Date date;  // дата затраты
	Time time;  // время затраты
public:
	Spending() = default;
	
	Spending(float moneyP, int categoryP, Date dateP, Time timeP)
	{
		money = moneyP;
		category = categoryP;
		date = dateP;
		time = timeP;
	}
	
	void SetSpending()
	{
		std::cout << "Enter spending: 'n";
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
	
	//void Input() // для ввода полей с клавиатуры
	//{
	//	int choice;
	//	do {
	//		
	//		int sum;
	//		std::cout << "Choose category of spending: \n"
	//			<< "1. Food shops.\n"
	//			<< "2. Pet shops.\n"
	//			<< "3. Other shops.\n"				
	//			<< "4. Exit\n";
	//		std::cin >> choice;
	//		switch (choice)
	//		{
	//			case 1: 
	//				std::cout << "Enter spending for food shops: ";
	//				std::cin >> sum;
	//				category = 1;
	//				money += sum;
	//				break;
	//			case 2:
	//				std::cout << "Enter spending for pet shops: ";
	//				std::cin >> sum;
	//				category = 2;
	//				money += sum;
	//				break;
	//			case 3:
	//				std::cout << "Enter spending for other shops: ";
	//				std::cin >> sum;
	//				category = 3;
	//				money += sum;
	//				break;
	//		}
	//	} while (choice != 4);
	//
	//	date.Input();
	//	time.Input();
	//}

	void Output() const
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
		return money;  // возвращает значение поля money
	}
	
	float GetCategory() const  // гэттер
	{
		return category;  // возвращает значение поля category
	}

	// оператор< необходим для сортировки затрат в отчетах
	// оператор< необходим, чтобы расположить затраты в контейнере multiset
	bool operator<(const Spending obj) const  // перегрузка оператора <
	{
		return money > obj.money;
	}
	
	const Date GetDate() const { return date; }
	
	const Time GetTime() const { return time; }


};


class MoneyStorage  // базовый класс Хранилище денег, абстрактный
	                // потомки хранилища - кошелек и карта
					// главный элемент Хранилища - массив затрат
{
protected:
	std::string pass;
	long long number;  // номер кошелька или карты
	float total_money;  // общее кол-во денег на карте или клшельке (баланс??)
	std::vector<Spending> spendings;  // динамический массив звтрат с пом.STL
	                               // как динамический массив объектов типа Spending
	float credit_limit;  // если кредитный лимит > 0, то кредитная, иначе дебетовая
	bool CardOrWallet;  // card==0, wallet==1
public:
	MoneyStorage()  // конструктор без параметров
	{
		pass = "";
		number = 0;
		total_money = 0;
		credit_limit = 0;
	}
		
	
	MoneyStorage(long long numberP, float total_moneyP, 
		float credit_limitP)
	{
		number = numberP;
		total_money = total_moneyP;
		credit_limit = credit_limitP;
	}

	MoneyStorage(std::vector<Spending>& spendingsP, long long numberP,
		float total_moneyP, float credit_limitP)
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

	void TopUp()  // пополнение хранилища денег, с клавиатуры 
		// будем вводить, на какую сумму хотим пополнить
	{
		double replenishment;  // сумма пополнения
		std::cout << "Enter an amount of replenishment: ";  // введите сумму пополнения
		std::cin >> replenishment;  // ввод суммы пополнения
		total_money += replenishment;  // общее кол-во денег + пополнение
	}

	void AddSpending()  // добавить затрату - внести затра
	{
		float spend;
		std::cout << "Enter spend: ";
		std::cin >> spend;
		total_money -= spend;  // общее кол-во денег - затрата
	}

	long long GetNumber() const { return number; }

	std::vector<Spending> GetSpendings() const  // вернуть весь набор
		                                         // затрат
	{
		return spendings;
	}
};


class Card : public MoneyStorage // класс Карта
{
	std::string bank_name;  // строка "название банка"
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

	Card(std::vector<Spending>& spend, std::string bank_nameP,
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
		std::cout << "**********Make_Card**********\n";
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
		std::cout << "**********Your_Card**********\n";
		std::cout << "Bank name: " << bank_name;
		std::cout << "Card number: " << number;
		std::cout << "Balance: " << total_money;
		std::cout << "Credit limit: " << credit_limit;
	}

	
};

class Wallet : public MoneyStorage // класс Кошелек
{
	std::string bank_name;  // строка "название банка"
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

	Wallet(std::vector<Spending>& spend, std::string bank_nameP,
		long long numberP, float total_moneyP)

	{
		spendings = spend;
		bank_name = bank_nameP;
		number = numberP;
		total_money = total_moneyP;
	}

	void Input()
	{
		std::cout << "**********Make_Wallet**********\n";
		std::cout << "Enter name of the bank: ";
		std::cin >> bank_name;
		std::cout << "Enter wallet number: ";
		std::cin >> number;
		std::cout << "Enter carrent amount of money: ";
		std::cin >> total_money;
	}

	void Output()
	{
		std::cout << "**********Your_Wallet**********\n";
		std::cout << "Bank name: " << bank_name;
		std::cout << "Wallet number: " << number;
		std::cout << "Balance: " << total_money;
	}

};


// ?? класс система управления финансами???
// это набор хранилищ денег
// система управления финансами внутри себя инкапсулирует массив указателей
// на базовый класс MoneyStorage

class FinManagement : public Card, public Wallet
{
	std::string phone_num;
	std::string name;
	std::string second_name;
	std::vector <MoneyStorage*> pers;  // указатели на базовый класс MoneyStorage
	// на этапе выпонения уже будет определяться, на какой конкретно объект 
	// смотреть этот указатель - на карту или на кошелек
	// или динамич массив указателей типа MoneyStorage* на хранилищА денег - 
	// либо карта, либо кошелек
public:
	FinManagement()
		: phone_num(), name(), second_name(), pers()
	{
		SetName();
		SetPhone();
	}
	void SetName()
	{
		std::cout << "Enter 1st name: ";
		std::cin >> name;
		std::cout << "Enter 2nd name: ";
		std::cin >> second_name;
	}
	void SetPhone()
	{
		std::cout << "Enter phone :";
		std::cin >> phone_num;
	}

	void AddNewCard()
	{
		Card::Input();

	}
	void AddNewWallet()
	{
		Wallet::Input();
	}
	//void DeleteCard();
	//void DeleteWallet();
	void OutputInfo()
	{
		Card::Output();
		Wallet::Output();
	}
	



	void AddStorage(MoneyStorage* ptr)  // добавить хранилище - у нас
		// есть набор хранилищ денег - кошельков и карт. И мы хотим добавить\
		// еще одну карту или кошелек - это метод AddStorage. Это метод
		// принимает указатель на существующее хранилище денег, в мейн
		// выделим память на конкретное хранилище денег и добавим его в 
		// нашу систему.
	{
		

	}
	
	void DeleteStorage(int number);  // удалить карту или кошелек
	// в параметре - номер кошелька или карты, перед удалением 
	// будет происходить поиск по номеру хранилища денег (кошелька или карты)

	

	void TopUpStorage()  // пополнить конкретное хранилище - карту или кошелек
		// в теле метода должен вводится номер конкретного кош.или карты,
		// внутри это метода будет вызываться метод TopUp из класса MoneyStorage
		// для конкретного кош.или карты
	{
		MoneyStorage::TopUp();
	}

	void AddSpendingStorage()  // добавить затрату к хранилищу - так же
		// как в TopUpStorage - выбираем конкретный кошелек, с которого хотим
		// потратить деньги, и елаем затрату . Для этого (для осуществления щатраты),
		// мы вызываем метод AddSpending() из класса MoneyStorage

		//void DayReport();  // пройтись по всем кош.и картам (по массиву MoneyStorage* ptr)
		// заходим внуть каждого объекта затрата, анализируем - подходит ли она нам по 
		// дате - если подходит выводим на экран
	{
		MoneyStorage::AddSpending();
	}

	//void WeekReport();

	//void MonthReport();
	
	void RatingMonth()
	{
		std::multiset<Spending> rating;
		std::cout << "\nMonth rating - TOP 3 spendings\n";
		unsigned month;
		std::cout << "Enter month number for the rating: ";
		std::cin >> month;
		unsigned year;
		std::cout << "Enter year for rating: ";
		std::cin >> year;
		for (auto elemSt : pers)
		{
			for (auto elemSp : elemSt->GetSpendings())
			{
				if (elemSp.GetDate().month == month && elemSp.GetDate().year == year)
				{
					rating.insert(elemSp);
				}
			}
		}
		std::multiset<Spending>::iterator it;
		it = rating.begin();
		unsigned size = 3;
		if (rating.size() < 3)
		{
			size = rating.size();
		}
		for (int i = 0; i < size; i++)
		{
			(*it).Output();
			it++;
		}

		std::cout << "Do you want to save rating in the file?"
			<< " (yes - 1, no 0)";
		bool yes;
		std::cin >> yes;
		if (!yes) { return;  }
		std::ofstream out;
		out.open("Month reting.txt");
		it = rating.begin();
		if (out.is_open())
		{
			out << "Top 3 spendings for month " << month
				<< " of the year: " << year << "\n";
			for (int i = 0; i < size; i++)
			{
				out << "Amount of money spending: " << it->GetMoney()
					<< " Category of spending: " << it->GetCategory()
					<< std::endl;
				out << "Date of transaction: " << it->GetDate().day
					<< it->GetDate().month << it->GetDate().year
					<< std::endl;
				out << "Time of transaction: " << it->GetTime().hour
					<< it->GetTime().min << it->GetTime().sec
					<< std::endl;
			}
		}

	}

	//void RatingWeak();

	//void RatingMonthCategory();

	//void RatingWeakCategory();

};





/*
	нужен отдельны класс затрата (поля: дата, время, размер затраты,
	категория затраты)
	будет массив объектов MoneyStorage, класс MoneyStorage будет
	абстрактным.
	от класса MoneyStorage будут наследоваться 
	в MoneyStorage будут virtual методы
	
	один динамич.массив кошелько и карт
*/


int main()
{
	MoneyStorage* stor_ptr1;  // указатель на базовый абстрактный класс
	MoneyStorage* stor_ptr2;

	stor_ptr1 = new Card("Privat", 111111111111, 2000, 300);  // создаем карту
	stor_ptr2 = new Wallet("PayPal", 2323232323223, 4000);  // создаем кошелек

	FinManagement system;  // создаем систему управл.финансами
	system.AddStorage(stor_ptr1);  // добавляем систему "хранилиша денег"
	system.AddStorage(stor_ptr2);
	system.OutputInfo();

	unsigned operation;
	do
	{
		std::cout << "\nChoose op: \n";
		std::cout << "1. Top up storage\n";  // пополнить кош.иил карту
		std::cout << "2. Add spend to storage\n";  // провести оплату с карты или кош
		std::cout << "3. Show storages\n";  // посмтореть состояние всех карт или кош
		                                    // включая затраты которые осуществлялись 
		std::cout << "4. Show day report \n";
		std::cout << "5. Show weak report \n";
		std::cout << "6. Show month report \n";
		std::cout << "7. Show weak rating \n";
		std::cout << "8. Show month rating \n";
		std::cout << "9. Show weak rating for categories\n";
		std::cout << "10. Show month rating for categories\n";
		std::cout << "Exit - . \n";
		std::cin >> operation;
		switch (operation)
		{
			case 1:
				system.TopUpStorage();
				break;
			case 2:
				system.AddSpendingStorage();
				break;
			case 3:
				system.OutputInfo();
				break;
			//case 4:
			//	system.DayReport();
			//	break;
			//case 5:
			//	system.WeekReport();
			//	break;
			//case 6:
			//	system.MonthReport();
			//	break;
			//case 7:
			//	system.RatingWeak();
			//	break;
			//case 8:
			//	system.RatingMonth();
			//case 9:
			//	system.RatingWeakCategory();
			//	break;
			//case 10:
			//	system.RatingMonthCategory();
			//	break;
			case 4:
				std::cout << "Bye\n";
				break;
			default:
				std::cout << "operation doesn't exist!";
		} 
	} while (operation != 4);

}