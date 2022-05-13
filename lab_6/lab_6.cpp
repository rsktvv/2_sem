#include <iostream>

struct T_List
{
	T_List* next;   
	int elements; 
};

void ADD(T_List* head, int elements)
{
	T_List* p = new T_List;
	p->elements = elements;

	p->next = head->next;
	head->next = p;
}

void PRINT(T_List* head)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		std::cout << p->elements << " ";
		p = p->next;
	}
}

void CLEAR(T_List* head)
{
	T_List* tmp;
	T_List* p = head->next;
	while (p != nullptr)
	{
		tmp = p;
		p = p->next;
		delete tmp;
	}
}

bool FIND(T_List* head,int x)
{
	T_List* p = head->next;
	while (p->next != nullptr)
	{
		if (p->elements == x)
		{
			std::cout << "nayden" << std::endl;
			return true;

		}
		else
		{
			p = p->next;
		}
	}
	return false;
}

void DELETE(T_List* head, int key)
{
	T_List* tmp = head;
	T_List* p;
	while (tmp->next != nullptr)
	{
		if (tmp->next->elements == key && tmp != nullptr)
		{
			p = tmp->next;
			tmp->next = tmp->next->next;
			delete p;
		}
		else
			tmp = tmp->next;
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");
	T_List* head = new T_List; 
	head->next = nullptr; 
	int N = 0;
	int a = 0;
	int v=0;
	std::cout << "esli sozdat spisok avtomaticheski, napishite 1, esli samomu, to 2" << std::endl;
	std::cin >> a;
	if (a > 2)
	{
		while(a>2)
		{ 
			std::cout << "esli sozdat spisok avtomaticheski, napishite 1, esli samomu, to 2" << std::endl;
			std::cin >> a;
		}

	}
	else
		if (a == 1)
		{
			std::cout << "skolko doljno bit znacheniy?" << std::endl;
			std::cin >> N;
			for (int i = 0; i < N; i++)
			{
				ADD(head, rand() % 1000);
			}
			PRINT(head);
		}
		else 
			if (a == 2)
			{
				std::cout << "napishite, skolko znacheniy doljno bit v spiske" << std::endl;
				std::cin >> N;
				for (int i = 0; i < N; i++)
				{
					int c = 0;
					std::cin >> c;
					ADD(head, c);
				}

			}

	std::cout << "elsi vi hotite dobavit znachenie - 1, esli udalit - 2, nayti - 3, viyti - 4" << std::endl;
	std::cin >> v;

	while (v != 4)
	{
		if (v > 4)
		{
			while (v > 4)
			{
				std::cout << "elsi vi hotite dobavit znachenie - 1, esli udalit - 2, nayti - 3, viyti - 4" << std::endl;
				std::cin >> v;
			}

		}
		else
			if (v == 1)
			{
				std::cout << "napishite, kakoe znachenie nado dobavit" << std::endl;
				int b = 0;
				std::cin >> b;
				ADD(head, b);
				
				std::cout << "elsi vi hotite dobavit znachenie - 1, esli udalit - 2, nayti - 3, viyti - 4" << std::endl;
				std::cin >> v;
			}
			else
				if (v == 2)
				{
					std::cout << "napishite, kakoe znachenie nado udalit" << std::endl;
					int n = 0;
					std::cin >> n;
					DELETE(head, n);
					std::cout << "elsi vi hotite dobavit znachenie - 1, esli udalit - 2, nayti - 3, viyti - 4" << std::endl;
					std::cin >> v;
				}
				else
					if (v == 3)
					{
						std::cout << "napishite, kakoe znachenie nado nayti" << std::endl;
						int m = 0;
						std::cin >> m;
						FIND(head, m);
						std::cout << "elsi vi hotite dobavit znachenie - 1, esli udalit - 2, nayti - 3, viyti - 4" << std::endl;
						std::cin >> v;
					}
	}
	PRINT(head);
	//std::cout << std::endl;
	return 0;
}