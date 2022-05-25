#include <iostream>
#include "BMP.hpp"

using namespace std;
using namespace image;

int main()
{
    try
    {
		BMP OutBMP(664, 610);
		OutBMP.Read("in.bmp");
		OutBMP.Filter(0, 50, 100);
		OutBMP.Save("out.bmp");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
	return 0;
}
