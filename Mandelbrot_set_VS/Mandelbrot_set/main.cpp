#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>
#include <fstream>
#include <windows.h>

/*#define SIZE 0.00000000374
#define CENTER_X -1.7433419053321
#define CENTER_Y 0.0000907687489
#define RESOLUTION 8000
#define DEPTH 3000
#define THRESHOLD_VALUE 10
#define FILE_NAME "test.bmp"
*/
using namespace std;
int main(int argc, char **argv)
{
	if (argc != 7 && argc != 8)
	{
		cout << "ENTER: Mandelbrot_set.exe FILE_NAME CENTER_X CENTER_Y SIZE RESOLUTION DEPTH (THRESHOLD_VALUE)" << endl;
		cout << "\tFILE_NAME - saving location e.c. filename.bmp" << endl;
		cout << "\tCENTER_X - real coordinate e.c. 0" << endl;
		cout << "\tCENTER_Y - imaginary coordinate e.c. 0" << endl;
		cout << "\tSIZE - desirable dimentions e.c. 3" << endl;
		cout << "\tRESOLUTION - final square resolution e.c. 1000" << endl;
		cout << "\tDEPTH - how much iterations will be done e.c. 100" << endl;
		cout << "\tTHRESHOLD_VALUE - (not required) penalty (max value before kick) for distance default=10" << endl;
		return 1;
	}
	double CENTER_X = stod(argv[2]), CENTER_Y = stod(argv[3]), SIZE = stod(argv[4]), DEPTH = stod(argv[6]);
	char* FILE_NAME = argv[1];
	int RESOLUTION = stoi(argv[5]);
	double THRESHOLD_VALUE = 10;
	if (argc == 8)
		THRESHOLD_VALUE = stod(argv[7]);
		

	cout << "Starting"<< endl;

	HANDLE file;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER fileInfo;
	RGBTRIPLE *image;
	DWORD write = 0;
	image = new RGBTRIPLE[RESOLUTION * RESOLUTION];

	file = CreateFile(FILE_NAME, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  //Sets up the new bmp to be written to

	fileHeader.bfType = 19778;                                                                    //Sets our type to BM or bmp
	fileHeader.bfSize = sizeof(fileHeader.bfOffBits) + sizeof(RGBTRIPLE);                                                //Sets the size equal to the size of the header struct
	fileHeader.bfReserved1 = 0;                                                                    //sets the reserves to 0
	fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);                    //Sets offbits equal to the size of file and info header

	fileInfo.biSize = sizeof(BITMAPINFOHEADER);
	fileInfo.biWidth = RESOLUTION;
	fileInfo.biHeight = RESOLUTION;
	fileInfo.biPlanes = 1;
	fileInfo.biBitCount = 24;
	fileInfo.biCompression = BI_RGB;
	fileInfo.biSizeImage = RESOLUTION * RESOLUTION * (24 / 8);
	fileInfo.biXPelsPerMeter = 2400;
	fileInfo.biYPelsPerMeter = 2400;
	fileInfo.biClrImportant = 0;
	fileInfo.biClrUsed = 0;

	WriteFile(file, &fileHeader, sizeof(fileHeader), &write, NULL);
	WriteFile(file, &fileInfo, sizeof(fileInfo), &write, NULL);



	long long it = 0;
	for (int i = RESOLUTION / 2; i > -RESOLUTION / 2; i--)
	{
		for (int j = -RESOLUTION / 2; j < RESOLUTION / 2; j++)
		{
			double x = j*SIZE / (double)RESOLUTION + CENTER_X,
				y = (i*SIZE / (double)RESOLUTION + CENTER_Y);
			complex<double> z = 0, c = x + y * 1i;

			// Hack from Wikipedia
			double p, theta, pc;
			p = sqrt((x - 0.25)*(x - 0.25) + y*y);
			theta = atan2(y, x - 0.25);
			pc = 0.5 - 0.5*cos(theta);

			int k;
			if (p <= pc)
			{
				k = DEPTH;
			}
			else
			{
				for (k = 0; k < DEPTH; k++)
				{
					z = z*z + c;
					if (z.imag()*z.imag() + z.real()*z.real() > THRESHOLD_VALUE)
						break;
				}
			}

			int value = 255*k/DEPTH;
			image[it].rgbtBlue = value;
			image[it].rgbtGreen = value;
			image[it].rgbtRed = value;
			
			if ((it+1) % (RESOLUTION*RESOLUTION / 10) == 0)			
				cout << int(1+ (it) / (float)((RESOLUTION*RESOLUTION)) * 100)<< "%" << endl;
			
			it++;
		}
	}

	cout << "Saving "<< FILE_NAME << endl;

	WriteFile(file, image, fileInfo.biSizeImage, &write, NULL);
	CloseHandle(file);

	cout << "finish" << endl;
	//system("pause");
	return 0;
}


/*

std::cout << std::fixed << std::setprecision(20);

std::complex<double> z1 = 1i * 1i;     // imaginary unit squared
std::cout << "i * i = " << z1 << '\n';

std::complex<double> z2 = std::pow(1i, 2); // imaginary unit squared
std::cout << "pow(i, 2) = " << z2 << '\n';

double PI = std::acos(-1);
std::complex<double> z3 = complex<double>(1)/ complex<double>(7); // Euler's formula
std::cout << "exp(i * pi) = " << z3 << '\n';

std::complex<double> z4 = 1. + 2i, z5 = 1. - 2i; // conjugates
std::cout << "(1+2i)*(1-2i) = " << z4*z5 << '\n';
*/