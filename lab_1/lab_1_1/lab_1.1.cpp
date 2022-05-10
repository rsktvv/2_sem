/* 
   time N=100 - 0.0001218
   time N=1000 - 0.0006659
   time N=10000 - 0.007831
   time N=100000 - 0.384093
*/

#include <iostream>
#include <chrono>
#include <vector>

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

int main()
{
	int N = 0;
	std::cin >> N;
	std::vector <int> mass(N);
	for (int i = 0; i < mass.size(); i++)
	{
		mass[i] = rand() % 50;
		std::cout << mass[i] << " ";
	}
	std::cout << '\n';
	Timer t;

	for (int i = 0; i < mass.size(); i++)
	{
		if (mass[i] % 2 == 0)
		{
			mass.insert(mass.begin() + i + 1, mass[i]);
			i++;
		}
	}
	std::cout << "time: " << t.elapsed() << std::endl;

	for (int i = 0; i < mass.size(); i++)
	{
		std::cout << mass[i] << " ";
	}
	
	return 0;
}
