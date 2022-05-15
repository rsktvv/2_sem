#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cmath>
const int N = 100000;
const int M = 10000;

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

void Quick_Sort(int low, int high, int* x)
{
	if (low >= high)
	{
		return;
	}
	int m = (low + high) / 2 + 1;
	int k = x[m];
	int l = low - 1;
	int r = high + 1;
	while (1)
	{
		do
		{
			l++;
		}
		while (x[l] < k);
		do
		{
			r--;
		}
		while (x[r] > k);
		if (l >= r)
		{
			break;
		}
		std::swap(x[l], x[r]);
	}
	r = l;
	l--;
	Quick_Sort(low, l, x);
	Quick_Sort(r, high, x);
}

int Binarn_Search(int low, int high, int* x, int k)
{
	if (k < x[low])
	{
		return -1;
	}
	if (k == x[low])
	{
		return 0;
	}
	if (k > x[high])
	{
		return -1;
	}
	int left = 0;
	int right = N - 1;
	while ((left + 1) < right) 
	{
		int c = floor((left + right) / 2);
		if (k > x[c])
		{
			left = c;
		}
		else
		{
			right = c;
		}
	}
	if (x[right] == k)
	{
		return right;
	}
	else
	{
		std::cout << "ne nayden " << std::endl;
	}
}

bool searching(int x[], int N, int k)
{
	for (int i = 0; i < N; i++)
	{
		if (x[i] == k)
		{
			return true;
		}
	}
	return false;
}

double f(double x)
{
	return log(x) - 1;
}

double Bisection(double left, double right)
{
	double eps = 1e-4;
	while (1)
	{
		double x = (left + right) / 2;
		if ((abs(x - left) < eps) && (abs(x - right) < eps))
			return x;
		else if (f(x) * f(left) > 0)
			left = x;
		else
			right = x;
	}
}


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	int x[N];
	int k = 0;
	double a, b = 0;

	for (int i = 0; i < N; i++)
	{
		x[i] = rand()%50;
	}

	Quick_Sort(0, N - 1, x);

	std::cout << "chto nayti " << std::endl;
	std::cin >> k;

	Timer t;
	for (int i = 0; i < M; i++)
	{
		searching(x, N, k);
	}
	std::cout << "massiv " << t.elapsed() << std::endl;

	Timer u;
	for (int i = 0; i < M; i++)
	{
		 Binarn_Search(0, N - 1, x, k);
	}
	std::cout << "BinarnSearch " << u.elapsed() << std::endl;
	
	std::cout << "levaya i pravaya granica " << std::endl;
	std::cin >> a >> b;

	std::cout << Bisection(a, b);

	return 0;
}