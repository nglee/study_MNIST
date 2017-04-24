#include <iostream> // cout, endl
#include <fstream> // ifstream, ofstream
#include <iomanip> // setw
#include <string>
#include <opencv2/opencv.hpp>

#include "local_settings.h"

int raw2img()
{
	std::ifstream in;
	unsigned char buf[784];
	cv::Mat imageWithData;

	in.open(trainImgPath.c_str(), std::ios_base::binary);
	if (!in.good()) {
		std::cout << "Error opening " << trainImgPath << std::endl;
		return 1;
	}

	in.seekg(16, std::ios_base::beg); // start of the first pixel of the first image

	for (int j = 0; j < numTrain; j++) {
		for (int i = 0; i < 784; i++) {
			buf[i] = (unsigned char)in.get();
			if (!in) {
				std::cout << "Read fail from " << trainImgPath << std::endl;
				return 1;
			}
		}
		imageWithData = cv::Mat(28, 28, CV_8U, buf).clone();
		cv::imwrite(trainImgStorePath + std::to_string(j) + ".bmp", imageWithData);
	}

	in >> buf[0]; // must be EOF
	if (in) {
		std::cout << "Something went wrong while reading from " << trainImgPath << std::endl;
		return 1;
	}

	in.close();

	in.open(testImgPath.c_str(), std::ios_base::binary);
	if (!in.good()) {
		std::cout << "Error opening " << testImgPath << std::endl;
		return 1;
	}

	in.seekg(16, std::ios_base::beg);

	for (int j = 0; j < numTest; j++) {
		for (int i = 0; i < 784; i++) {
			buf[i] = (unsigned char)in.get();
			if (!in) {
				std::cout << "Read fail from " << testImgPath << std::endl;
				return 1;
			}
		}
		imageWithData = cv::Mat(28, 28, CV_8U, buf).clone();
		cv::imwrite(testImgStorePath + std::to_string(j) + ".bmp", imageWithData);
	}
		
	in >> buf[0];
	if (in) {
		std::cout << "Something went wrong while reading from " << testImgPath << std::endl;
		return 1;
	}

	in.close();

	return 0;
}

inline bool exist(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

int main()
{
	if (!exist(trainImgStorePath + std::to_string(numTrain - 1) + ".bmp")
		|| !exist(testImgStorePath + std::to_string(numTest - 1) + ".bmp")) {
		
		std::cout << "Transforming MNIST raw data to image files..." << std::endl;
		if (raw2img())
			return 1;
	} else {
		std::cout << "MNIST raw data already transformed to image files." << std::endl;
	}

#if 0
	std::ifstream lbl(testLblPath.c_str());
	lbl.seekg(8, std::ios_base::beg);
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 6; i++) {
			int tmp;
			tmp = lbl.get();
			std::cout << std::setw(5) << tmp;
		}
		std::cout << std::endl;
	}
#endif

	/*
    const int arraySize = 5;
    const int a[arraySize] = { 1, 2, 3, 4, 5 };
    const int b[arraySize] = { 10, 20, 30, 40, 50 };
    int c[arraySize] = { 0 };

    // Add vectors in parallel.
    cudaError_t cudaStatus = addWithCuda(c, a, b, arraySize);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addWithCuda failed!");
        return 1;
    }

    printf("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}\n",
        c[0], c[1], c[2], c[3], c[4]);

    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }
	*/

    return 0;
}
