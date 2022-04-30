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
		std::cout << p->elements << std::endl;
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
			return true;
		}
		else
		{
			p = p->next;
		}
	}
	return false;
}

bool FIND2(int mass[], int N, int M, int x[])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			mass[i] == x[j];
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
		ADD(head, rand() % 10000);
	}
	
	for (int i = 0; i < M; i++)
	{
		x[i] = rand() % 10000;
	}

	Timer a;
	for (int i = 0; i < M; i++)
	{
		FIND(head, x[i]) == true;
    }
	std::cout <<"������: " << a.elapsed() << std::endl;
	CLEAR(head);
	delete head;

	int* mass = new int[N];
	for (int i = 0; i < N; i++)
	{
		mass[i] = rand() % 10000;
	}
	
	Timer b;
	FIND2(mass, N, M, x);

	std::cout <<"������: " << b.elapsed() << std::endl;
	delete[] mass;
	delete[] x;
	return 0;
}