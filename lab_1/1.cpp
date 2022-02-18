/*5к символов без сортировки- 0.04с
	5к символов с сортировкой, перва€ гласна€ - 5.3с
	5к символов с сортировкой, последн€€ гласна€ - 5.9с
	10к символов без сортировки - 0.03с
	10к сиволов с 1 гласной - 16.7 с 
	10к символов с последней гласной - 17.4с
*/
#include <iostream>
#include <chrono>
#include <string>
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
void SWAPSORT(std::string& m)
{
	for (int i = 0; i < m.length(); i++)
	{
		for (int j = i + 1; j < m.length(); j++)
		{
			if (m[i] > m[j])
			{
				std::swap(m[i], m[j]);

			}
		}
	}
}
bool isVowels(std::string& m, std::string& n)
{
	for (int i = 0; i < m.length(); i++)
	{
		for (int j = 0; j < n.length(); j++)
		{
			if (m[i] == n[j])
			{
				return true;
			}
		}
	}
	return false;
}
int main()
{
	
	int N = 0;
	std::string vowels = "eyuioa";
	std::string stroka;
	std::cin >> stroka;
	N = stroka.length();
	Timer t;
	if (isVowels(stroka, vowels))
	{
		std::cout << "timer: " << t.elapsed() << std::endl;
		SWAPSORT(stroka);
		std::cout << stroka << std::endl;	
	}
	else
	{
		std::cout << stroka<<std::endl;
	}
	
	return 0;
}
