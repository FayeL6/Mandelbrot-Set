#include <iostream>
#include <cstdlib>
#include "window.h"
#include "mandelbrot.h"
#include "bitmap.h"

int main(int argc, char *argv[])
{
	if (argc < 7)
	{
		std::cerr << "Usage: " << argv[0]
				  << " filename ox oy dimension color_model N"
			          << std::endl;
		exit(-1);
	}
	
	Window win(std::atof(argv[2]), std::atof(argv[3]), std::atof(argv[4]));
	double lpp = win.get_lpp();
	double dim = win.get_dimension();
	int width = win.get_width();
	int height = win.get_height();
	double ox = win.get_ox() - dim;
	double oy = win.get_oy() - dim / width * height;
	int N = std::atof(argv[6]);
	int times = 0;
	int m = 0;

	char *cache = new char[width * height * 3];

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
		{
			double x = ox + lpp * i;
			double y = oy + lpp * j;
			int pos = width * j + i; 
			Manderbrot man(std::complex<double>{0.0, 0.0},
						   N,
						   std::complex<double>{x, y});
			while (!man.stop_criterion())
			{
				man.forward_step();
				if (man.is_disconvergence())
					break;
			}
			times = man.stopplaceis();
			m = std::atof(argv[5]);
			if (m==0)
			  times = 0;
			if (man.stop_criterion())
			{
				cache[pos * 3] = 255 - times - m;
				cache[pos * 3 + 1] = 255 - times*2 - m*10;
				cache[pos * 3 + 2] = 255 ;
			}
			else
			{
           			cache[pos * 3] = 0 ;
				cache[pos * 3 + 1] = 0 ;
				cache[pos * 3 + 2] = 255 ;
			}
		}
	build_bmp(argv[1], width, height, cache);
	delete [] cache;
	return 0;
};
