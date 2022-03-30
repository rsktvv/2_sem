ì#include <iostream>
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
void QuickSort(int a, int b, int* x)
{
	if (a >= b)
	{
		return;
	}
	int m = ((a + b) / 2) + 1;
	int k = x[m];
	int l = a - 1;
	int r = b + 1;
	while (1)
	{
		do
		{
			l++;
		} while (x[l] < k);
		do
		{
			r--;
		} while (x[r] > k);
		if (l >= r)
		{
			break;
		}
		std::swap(x[l], x[r]);
	}
	r = l;
	l = l - 1;
	QuickSort(a, l, x);
	QuickSort(r, b, x);
}
int BinarySearch(int* mass, int left, int right, int key)
{
	if (key < mass[left])
	{
		return -1;
	}
		
	if (key == mass[left])
	{
		return 1;
	}
	if (key > mass[right])
	{
		return -1;
	}

//	int a = left;
//	int b = right;

	while (left + 1 < right)
	{
		int centre = (left + right) / 2;
		if (key > mass[centre])
		{
			left = centre;
		}
		else
		{
			right = centre;
		}
	}
	if (mass[right] == key)
	{
		return right+1;
	}
	else
	{
		return -1;
	}
}
int main()
{
	srand(time(NULL));
	int M = 10000;
	int N = 11;
	int* mass = new int [N];
	for (int i = 0; i < N; i++)
	{
		mass[i] = rand()%10;
	}
	for (int i = 0; i < N; i++)
	{
		std::cout << mass[i] << " ";
	}
	std::cout << std::endl;
	QuickSort(0, N - 1, mass);
	int k = 0;
	std::cin >> k;
	for (int i = 0; i < N; i++)
	{
		std::cout << mass[i] << " ";
	}
	std::cout << std::endl;
	Timer A;
	for (int i = 0; i < M; i++)
	{
		BinarySearch(mass, 0, N - 1, k);
	}
	std::cout << BinarySearch(mass, 0, N - 1, k) <<std::endl;
	std::cout << "BinarySearch = " << A.elapsed() << std::endl;
	Timer B;
	for (int i = 0; i < M; i++)
	{
		{for (int j = 0; j < N; j++)
			if (mass[j] == k)
			{
				break;
			}
		}
	}
	std::cout << "Search= " << B.elapsed() << std::endl;
	return 0;
}
