/*
Завдання 2.  (додаткове, на 12)
Побудувати клас  для роботи з однозв’язним(або двозв’язним) списком (class BusList). Можна скористатися шаблоном класу CDList<>.
Елемент списку містить наступну інформацію про автобус (class або struct Bus) :
o	номер автобуса ;
o	прізвище та ініціали водія;
o	номер маршруту.

На основі класу BusList написати клас AutoPark, котрий  повинен забезпечувати
1)	Початкове формування двох списків:
o	з даними про автобуси, які знаходяться в автопарку;
o	з даними про автобуси, які знаходяться на маршрутах.

2)	При виїзді кожного автобуса з автопарку програма видаляє дані про цей автобус зі списку автобусів, які знаходяться в автопарку, та записує ці дані в список автобусів, які знаходяться на маршруті. Якщо якийсь автобус повертається в автопарк, виконується протилежна операція
3)	Виведення відомостей про автобуси, які знаходяться в автопарку
4)	Виведення відомостей про автобуси, які знаходяться на маршруті.

Клас AutoPark керується з меню.
Команди:
o	купити автобус -- новий автобус додається до автопарку
o	продати автобус -- обраний автобус видаляється з автопарку
o	на маршрут -- обраний автобус видаляється з автопарку і додається до списку на маршруті
o	на стоянку -- обраний автобус видаляється зі списку на маршруті і додається до списку Автопарку

Обирати автобус можна двома шляхами:
o	запитати його номер у списку,
o	або реалізувати вибір автобуса клавішами курсора (вгору / донизу) обраний автобус підсвічується інверсним кольором

*/


#include "stdafx.h"
#include <iostream> 
#include <string>

using namespace std;

struct Bus
{
	int numBus;
	string nameDrv;
	int routeBus;
};

template<typename T>
class BusList
{

private:

	struct Node
	{
		Bus data;
		Node * next, *prev;

		Node(Bus data, Node * next = nullptr, Node * prev = nullptr) : data(data), next(next), prev(prev)
		{
		}
	};

	Node * Head = nullptr, *Tail = nullptr;
	int size = 0;

public:


	BusList() = default;

	//ctor copy
	BusList(const BusList & other)
	{
		Node * tmp = other.Head;
		while (tmp != nullptr)
		{
			addTail(tmp->data);
			//cout << "Test add " << tmp->data;
			tmp = tmp->next;
		}
	}

	//ctor move
	BusList(BusList && other)
	{
		this->size = other.size;
		this->Head = other.Head;
		this->Tail = other.Tail;
		other.size = 0;
		other.Head = nullptr;
		other.Tail = nullptr;
		//cout << "\n\tctor move\n";
	}

	~BusList()
	{
		clear();
	}

	//додавання нового елементу на початок списку
	void addHead(Bus data)
	{
		Node * tmp = new Node(data);
		if (isEmpty())
		{
			Head = Tail = tmp;
		}
		else
		{
			tmp->next = Head;
			Head->prev = tmp;
			Head = tmp;
		}
		++size;
	}

	//додавання нового елементу у хвіст списку
	void addTail(Bus data)
	{
		Node * tmp = new Node(data);
		if (isEmpty())
		{
			Head = Tail = tmp;
		}
		else
		{
			Tail->next = tmp;
			tmp->prev = Tail;
			Tail = tmp;
		}
		++size;
	}

	//видалення всіх елементів
	void clear()
	{
		Node * tmp = Head;
		while (Head != nullptr)
		{
			tmp = Head;
			Head = Head->next;
			delete tmp;
		}
		Tail = nullptr;
		size = 0;
	}

	bool isEmpty()const
	{
		return Head == nullptr;
	}

	//перегляд елементів списку 
	void print()const
	{
		if (isEmpty())
			cout << "Empty!\n";
		else
		{
			Node * tmp = Head;
			int count = 1;
			while (tmp != nullptr)
			{
				cout << "(" << count++ << ") Number: " << tmp->data.numBus << ", name of driver: " << tmp->data.nameDrv << ", number of route: " << tmp->data.routeBus << endl;
				tmp = tmp->next;
			}
			cout << endl;
		}
	}


	//видалення елемента з голови списку
	void delHead()
	{

		if (isEmpty())
		{
			cout << "not found\n";
		}
		else
		{
			Node *current;
			current = Head;
			Head = Head->next;
			Head->prev = nullptr;
			delete current;
		}
		--size;
	}

	//видалення елемента з хвоста списку
	void delTail()
	{

		if (isEmpty())
		{
			cout << "not found\n";
		}
		else
		{
			Node *current;
			current = Tail;
			Tail = Tail->prev;
			Tail->next = nullptr;
			delete current;
		}
		--size;
	}


	//видалення елемента за номером у списку
	Bus delNode(int count)
	{
		Node * del = Head;
		for(int i = 0; i < count; ++i)
			del = del->next;
		Bus tmp = del->data;
		if (del == nullptr)
			cout << "not found\n";
		else
			if (del == Head && size == 1)
			{
				delete Head;
				Head = Tail = nullptr;
			}
			else
				if (del == Head)
				{
					delHead();
				}
				else
					if (del == Tail)
					{
						delTail();
					}
					else
					{
						del->prev->next = del->next;
						del->next->prev = del->prev;
						delete del;
					}
		--size;
		return tmp;
	}

	int getSize() const
	{
		return size;
	}
};

class AutoPark 
{
private:

	BusList <Bus> park;
	BusList <Bus> route;

public:

	//o	купити автобус -- новий автобус додається до автопарку
	void buyBus()
	{
		Bus bus;
		cout << "\n\t= Buy Bus = \nEnter number of bus: ";
		cin >> bus.numBus;
		cout << "Enter name of driver: ";
		cin >> bus.nameDrv;
		cout << "Enter route of bus: ";
		cin >> bus.routeBus;
		park.addHead(bus);
		showBus(bus, " - BUY to park");
	}

	void buyBus(int numBus, string nameDrv, int routeBus)
	{
		Bus bus;
		bus.numBus = numBus;
		bus.nameDrv = nameDrv;
		bus.routeBus = routeBus;
		park.addHead(bus);
		showBus(bus, " - BUY to park");
	}

	//o	продати автобус -- обраний автобус видаляється з автопарку
	void sellBus()
	{
		if (park.isEmpty())
		{
			cout << "Park don't have of buses";
			return;
		}
		int count = 0;
		cout << "\n\t= Sale Bus =\n";
		park.print();
		do 
		{
			cout << "Select # bus for sale:";
			cin >> count;
			--count;
		} while (count > park.getSize() - 1 || count < 0);
		Bus del = park.delNode(count);
		park.print();
		showBus(del, " - SOLD");
	}

	//o	на маршрут -- обраний автобус видаляється з автопарку і додається до списку на маршруті
	void toRoute()
	{
		if (park.isEmpty())
		{
			cout << "Park don't have of buses";
			return;
		}
		int count;
		park.print();
		do
		{
			cout << "Select # bus for sending on the route:";
			cin >> count;
			--count;
		} while (count > park.getSize() - 1 || count < 0);
		Bus tmp = park.delNode(count);
		route.addHead(tmp);
		showBus(tmp, " - sent to route");
	}

	//o	на стоянку -- обраний автобус видаляється зі списку на маршруті і додається до списку Автопарку
	void toPark()
	{
		if (route.isEmpty())
		{
			cout << "Route don't have of buses";
			return;
		}
		int count;
		route.print();
		do
		{
			cout << "Select # bus for sending to the park:";
			cin >> count;
			--count;
		} while (count > park.getSize() - 1 || count < 0);
			
		Bus tmp = route.delNode(count);
		park.addHead(tmp);
		showBus(tmp, " - sent to park");

	}

	//3)	Виведення відомостей про автобуси, які знаходяться в автопарку
	void showPark()
	{
		cout << "\n\t= List of park Bus =\n";
		park.print();
	}

	//4)	Виведення відомостей про автобуси, які знаходяться на маршруті.
	void showRoute()
	{
		cout << "\n\t= List of route Bus =\n";
		route.print();
	}

	//вивід інфо по автобусу + певне повідомлення при потребі (куплено, продано etc)
	void showBus(Bus bus, string tmp = "")
	{
		cout << "\nBus: " << bus.numBus << ", driver: " + bus.nameDrv << ", route: " << bus.routeBus << tmp;
	}

	//меню з діями
	int menu()
	{
		int choose;
		cout << "\n\t = Menu =\n";
		cout << "1. Buy bus\n";
		cout << "2. Sell bus\n";
		cout << "3. To route\n";
		cout << "4. To park\n";
		cout << "5. Show route's buses\n";
		cout << "6. Show park's buses\n";
		cout << "0. Exit\n";
		cout << "Select item of menu:\t";
		cin >> choose;
		return choose;
	}

};



int main()
{
	AutoPark a;

	a.buyBus(5678, "Ivanenko T.R.", 10);
	a.buyBus(4567, "Smith J.", 22);
	a.buyBus(3456, "Petrenenko D.S.", 67);
	a.buyBus(2345, "Pavlov R.V.", 57);
	a.buyBus(1234, "Petrov V.K.", 47);

	for (;;) {
		switch (a.menu())
		{
		case 0:
			return 0;
		case 1:
			a.buyBus();
			break;
		case 2:
			a.sellBus();
			break;
		case 3:
			a.toRoute();
			break;
		case 4:
			a.toPark();
			break;
		case 5:
			a.showRoute();
			break;
		case 6:
			a.showPark();
			break;
		default:
			cout << "Wrong select!";
			break;
		}
	}

	cout << endl;
	system("pause");
	return 0;
}

