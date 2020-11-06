#include "tiffHandler.h"
#include "krigeHandler.h"
#include "idwHandler.h"
#include "cvpHandler.h"

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

std::string fileName(const std::string & path)
{
    std::size_t found = path.find_last_of("/\\");
    std::size_t ext = path.find_last_of(".");
    return path.substr(found+1,ext);
}

int main (int argc, char* argv[]){
	if(argc != 5 && (argc != 6 || *(argv[5]+1) != 'i')){
		cout << "Refer to README for usage." << std::endl;
		return 0;
	}

	tiffHandler tH(argv[2]);
	tiffHandler og(argv[2]);
	tiffHandler mask(argv[4]);
	double NAvalue = atof(argv[3]);
	int invertMask = 0;
	bool aer = (*(argv[1]+2) == '1'); //-a1 is true, -a0 is false
	if(argc == 6) //-i1 is true, -i0 is false
	{
		char c = *(argv[5]+2);
		switch(c)
		{
			case '0':
				invertMask = 0;
				break;
			case '1':
				invertMask = 1;
		}
	}

	const Mat NAmask = (og.data() == NAvalue);
	{
		Mat temp;
		if(mask.data().type() != CV_8U) { mask.data().convertTo(temp, CV_8U); }
		else { temp = mask.data(); }
		if(invertMask == 1)
		{ temp = cv::Mat::ones(temp.size(), temp.type()) * 255 - temp; }
		dilate( temp, temp, getStructuringElement(MORPH_CROSS, Size(23,23),Point(11,11)) );

		mask = tiffHandler(temp, "./out/"+fileName(mask.name())+"__.tif");
	}
	
	double min = 0; double max = 0;
	{
		Mat temp = tH.data().clone();
		minMaxIdx(temp, &min, &max);
		temp.setTo(max, temp==NAvalue);
		minMaxIdx(temp, &min, &max);
	}
	
	tH.mask(mask, min-1);
	Mat toEdit(tH.data().clone());
	// ...
	const double scale = 1000.0;
	toEdit = toEdit*scale;
	toEdit.setTo(NAvalue,NAmask);
	
	/*========================================IDW INTERPOLATION RESULTS========================================*/
	std::cout << "IDW INTERPOLATION BEGINNING" << std::endl;
	// idw_ce::nearestNeighbour(toEdit,/* mask.data(),*/ (min-1)*scale, NAvalue);
	int numIter = idw_ce::interpolate(toEdit, mask.data(), 100, (min-1)*scale, NAvalue);
	toEdit = toEdit*(1/scale);
	minMaxIdx(toEdit, &min, &max);
	toEdit.setTo(NAvalue,NAmask);
	
	tiffHandler interpolated(toEdit,"./out/"+fileName(tH.name())+"_edited.tif");
	interpolated.copyTags(tH, aer);

	std::cout << "IDW INTERPOLATION COMPLETE" << std::endl;
	/*=============================================DIFFERENCE DEM==============================================*/
	{
		Mat temp = og.data() + (interpolated.data() * -1);
		temp.setTo(0, temp < 0);
		temp.setTo(NAvalue, NAmask);
		tiffHandler diff(temp, "./out/"+fileName(tH.name())+"_difference.tif");
		diff.copyTags(tH, aer);
	}

	/*======================================Kriging INTERPOLATION RESULTS======================================*/
		/*Mat kriged = og.data().clone();
		kriged.setTo(0,mask.data());
		krige_ce::interpolate(kriged, 0, 100, NAvalue);
		{
			tiffHandler krigedTiff(kriged.clone(), "./out/"+fileName(tH.name())+"_kriged.tif");
			krigedTiff.copyTags(tH, aer);
		}*/

	/*====================================INPAINTING INTERPOLATION RESULTS=====================================*/
		/*int r = (og.data().rows + og.data().cols) / 8;
		Mat cvp;
		inpaint(og.data(), mask.data(), cvp, r, INPAINT_NS); //INPAINT_NS vs INPAINT_TELEA
		cvp.convertTo(cvp, og.data().type());
		{
			tiffHandler INP(cvp.clone(), "./out/"+fileName(tH.name())+"_inp.tif");
			INP.copyTags(tH, aer);
		}*/

	/*=========================================CVP INTERPOLATION RESULTS======================================*/
	std::cout << "CVP INTERPOLATION BEGINNING" << std::endl;
	Mat cvpMat(tH.data().clone());
	Mat voids(mask.data());
	cvp_ce::interpolate(cvpMat, voids);
	cvpMat.setTo(NAvalue,NAmask);
	{
		tiffHandler cvp(cvpMat, "./out/"+fileName(tH.name())+"_cvp.tif");
		cvp.copyTags(tH, aer);
	}

	std::cout << "CVP INTERPOLATION COMPLETE" << std::endl;
	return 0;
}