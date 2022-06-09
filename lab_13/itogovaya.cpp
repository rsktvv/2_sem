#include <iostream>
#include "matrix.hpp"



int main()
{
	int N,M;
	//std::cout << "Gauss" <<std::endl;
	std::cin >> N>>M;
	Matrix A(N, M);
	//Matrix B(N, 1);
	//std::cout << "vedite koeficenti pri x" << std::endl;
	std::cin >> A;
	//std::cin >> B;
	//std::cout << 1<<std::endl;
	//A.linear_dependence();
	//A % B;
	std::cout << A.Rang();
}
