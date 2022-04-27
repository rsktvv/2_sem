#include <iostream>
#include <chrono>

class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};
struct T_List
{
	T_List* next;   
	int elements; 
};

void add(T_List* head, int elements)
{
	T_List* p = new T_List;
	p->elements = elements;

	p->next = head->next;
	head->next = p;
}
void print(T_List* head)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		std::cout << p->elements << std::endl;
		p = p->next;
	}
}

void clear(T_List* head)
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

bool find(T_List* head,int x)
{
	T_List* p = head->next;
	while (p->next->next != nullptr)
	{
		if (p->elements == x)
		{
			return true;
		}
		else
		{
			p = p->next;
		}
	}
	return false;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	T_List* head = new T_List; 
	head->next = nullptr; 
	int N = 10000;
	int M = 1000;
	
	int* x = new int[M];
	for (int i = 0; i < N; i++)
	{
		add(head, rand() % 10);
	}
	
	for (int i = 0; i < M; i++)
	{
		x[i] = rand() % 10;
	}

	Timer a;
	for (int i = 0; i < M; i++)
	{
		if (find(head, x[i]) == true)
		{
			//std::cout << x[i] << std::endl;
		}
		else
		{
			//std::cout << x[i] << std::endl;
			
		}
    }
	std::cout <<"spisok " << a.elapsed() << std::endl;
	clear(head);
	delete head;
	std::cout << std::endl;
	int* mass = new int[N];
	for (int i = 0; i < N; i++)
	{
		mass[i] = rand() % 10;
	}
	/*for (int i = 0; i < N; i++)
	{
		std::cout << mass[i];
	}*/
	Timer b;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (mass[i] == x[j])
			{
				std::cout << 1 << std::endl;
			}
			else
			{
				std::cout << 2 << std::endl;
			}
		}
	}
	std::cout <<"massiv " << b.elapsed() << std::endl;
	delete[] mass;
	delete[] x;
	return 0;
}