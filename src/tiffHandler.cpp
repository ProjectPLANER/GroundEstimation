
/*
 * @author emrchi001@myuct.ac.za
 * @date July 2020
 * tiff file handler
*/

#include "tiffHandler.h"

using namespace cv;

/**
 * <!--
 * NAME OF FUNCTION: tiffHandler-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Constructor for the tiffHandler class.
 * 
 * <!--
 * PARAMETERS:
 * 			name 		type 		value/reference 		description
 * 			----------------------------------------------------------------------------------------->
 * @param	grid 		cv::Mat		r-value reference	--- Matrix of values.
 * @param 	fileName 	std::string const value 		--- Name of tiff image file.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 		value/reference 		description
 * 			----------------------------------------------------------------------------------------->
 * @return	new instance of type tiffHandler
 *
 * @see #tiffHandler(cv::Mat & grid, const std::string fileName), std::move
*/
tiffHandler::tiffHandler(cv::Mat && grid, const std::string fileName)
	:fileName(fileName), TIFFgrid(std::move(grid)){}

/**
 * <!--
 * NAME OF FUNCTION: tiffHandler-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Constructor for the tiffHandler class.
 * 
 * <!--
 * PARAMETERS:
 * 			name 		type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	grid 		cv::Mat		reference		--- Matrix of values.
 * @param 	fileName 	std::string const value 	--- Name of tiff image file.
 * 
 * <!--
 * RETURN VALUE:
 * 			description
 * 			----------------------------------------------------------------------------------------->
 * @return	new instance of type tiffHandler
 * 
 * @see #tiffHandler(cv::Mat && grid, const std::string fileName)
*/
tiffHandler::tiffHandler(cv::Mat & grid, const std::string fileName)
	:fileName(fileName), TIFFgrid(grid){}

/**
 * <!--
 * NAME OF FUNCTION: -->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Constructor for the tiffHandler class.
 * 
 * <!--
 * PARAMETERS:
 * 			name 		type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param 	fileName 	std::string const value 	--- Name of tiff image file.
 * 
 * <!--
 * RETURN VALUE:
 * 			description
 * 			----------------------------------------------------------------------------------------->
 * @return	new instance of type tiffHandler
*/
tiffHandler::tiffHandler(const std::string fileName):fileName(fileName){
	TIFF* TIFFfile = TIFFOpen(fileName.c_str(), "r");

	uint32 W,H;
	uint16 Bands,bps,sf;
	TIFFGetField(TIFFfile, TIFFTAG_IMAGEWIDTH, &W);	
	TIFFGetField(TIFFfile, TIFFTAG_IMAGELENGTH, &H);
	TIFFGetField(TIFFfile, TIFFTAG_SAMPLESPERPIXEL, &Bands);
	TIFFGetField(TIFFfile, TIFFTAG_BITSPERSAMPLE, &bps);
	TIFFGetField(TIFFfile, TIFFTAG_SAMPLEFORMAT, &sf);					//sf=1:unsigned; sf=2:signed;sf=3:floating point

	int type;
	switch(sf){
		case 1:
			switch(bps){
				case 8:		type = CV_8U;	std::cout << "type: CV_8U" << std::endl; break;
				case 16:	type = CV_16U;	std::cout << "type: CV_16U" << std::endl; break;
			}
			break;
		case 2:
			switch(bps){
				case 8:		type = CV_8S;	std::cout << "type: CV_8S" << std::endl; break;
				case 16:	type = CV_16S;	std::cout << "type: CV_16S" << std::endl; break;
				case 32:	type = CV_32S;	std::cout << "type: CV_32S" << std::endl; break;
			}
			break;
		case 3:
			switch(bps){
				case 32:	type = CV_32F;	std::cout << "type: CV_32F" << std::endl; break;
				case 64:	type = CV_64F;	std::cout << "type: CV_64F" << std::endl; break;
			}
			break;
		default:
			type = CV_32F;
	}
	long sls = TIFFScanlineSize(TIFFfile);	std::cout << "sls: " << sls << std::endl;
	TIFFgrid = Mat(H, W, type);	//Dealing with single-band tiff images
	
	for(uint32 i = 0; i < H; i++){
	    TIFFReadScanline(TIFFfile, TIFFgrid.ptr(i), i);
	}

	TIFFClose(TIFFfile);
}

/**
 * <!--
 * NAME OF FUNCTION: -->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Move constructor for the tiffHandler class.
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 		value/reference 		description
 * 			----------------------------------------------------------------------------------------->
 * @param	rhs 	tiffHandler r-value reference	--- tiffHandler object whose values are to be 
 *														moved to the new tiffHandler object.
 * 
 * <!--
 * RETURN VALUE:
 * 			description
 * 			----------------------------------------------------------------------------------------->
 * @return	new instance of type tiffHandler
 * 
 * @see std::move, #tiffHandler(const tiffHandler & rhs)
*/
tiffHandler::tiffHandler(tiffHandler && rhs)
	:fileName(std::move(rhs.fileName)), TIFFgrid(std::move(rhs.TIFFgrid)){}

/**
 * <!--
 * NAME OF FUNCTION: -->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Copy constructor for the tiffHandler class.
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	rhs 	tiffHandler reference		--- tiffHandler object whose values are to be copied 
 *													to the new tiffHandler object. Creates deep copy.
 * 
 * <!--
 * RETURN VALUE:
 * 			description
 * 			----------------------------------------------------------------------------------------->
 * @return	new instance of type tiffHandler
 * 
 * @see #tiffHandler(tiffHandler && rhs)
*/
tiffHandler::tiffHandler(const tiffHandler & rhs)
	:fileName(rhs.fileName), TIFFgrid(rhs.TIFFgrid.clone()){}

/**
 * <!--
 * NAME OF FUNCTION: operator= -->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Copy assignment operator for the tiffHandler class.
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	rhs 	tiffHandler reference		--- tiffHandler object whose values are to be copied 
 *													to the calling tiffHandler object. Creates deep copy.
 * 
 * <!--
 * RETURN VALUE:
 * 			description
 * 			----------------------------------------------------------------------------------------->
 * @return	reference to the calling tiffHandler instance.
 * 
 * @see operator=(tiffHandler && rhs)
*/
tiffHandler & tiffHandler::operator=(const tiffHandler & rhs){//deepcopy [x]
	if (!this->TIFFgrid.empty()) { TIFFgrid.release(); }
	this->TIFFgrid = rhs.TIFFgrid.clone();
	this->fileName = rhs.fileName;
	return *this;
}

/**
 * <!--
 * NAME OF FUNCTION: operator= -->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Move assignment operator for the tiffHandler class.
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 		value/reference 		description
 * 			----------------------------------------------------------------------------------------->
 * @param	rhs 	tiffHandler r-value reference	--- tiffHandler object whose values are to be 
 *														moved to the calling tiffHandler object.
 * 
 * <!--
 * RETURN VALUE:
 * 			description
 * 			----------------------------------------------------------------------------------------->
 * @return	reference to the calling tiffHandler instance.
 * 
 * @see operator=(const tiffHandler & rhs)
*/
tiffHandler & tiffHandler::operator=(tiffHandler && rhs){
	if (!this->TIFFgrid.empty()) { TIFFgrid.release(); }
	this->TIFFgrid = std::move(rhs.TIFFgrid);
	this->fileName = std::move(rhs.fileName);
	return *this;
}

/**
 * <!--
 * NAME OF FUNCTION: ~tiffHandler-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Destructor for tiffHandler class.
 * 
 * CALLS TO: cv::Mat.release
 * 
 * CALLED FROM: main
*/
tiffHandler::~tiffHandler(){
	TIFFgrid.release();
}

/**
 * <!--
 * NAME OF FUNCTION: copyTags-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *  This function saves the calling tiffHandler's data in a tiff image file using the tag values from 
 *	tH.
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param 	tH 		tiffHandler const reference --- tiffHandler to copy tag values from.
 * @param	aer 	bool		value			---	Boolean specifying whether to include Aerobotics 
 *													special tags. Default value is false.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 	value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	void
 * 
 * @see	#saveTiff
 * 
 * METHOD: The following is pseudocode describing how the function works.
 * 1. open both tiff image files: tH for reading, this for writing.
 * 2. read tag values from tH and write them to this image file.
 * 3. close tH tiff image file.
 * 4. write image data to this image file.
 * 5. close this image tiff file.
*/
void tiffHandler::copyTags(const tiffHandler & tH, bool aer){
		
	TIFF* rhs = TIFFOpen(tH.name().c_str(), "r");
	TIFF* lhs = TIFFOpen(fileName.c_str(), "w");

	if(aer){
		int error = TIFFMergeFieldInfo( lhs, xtiffFieldInfo, NxtiffFieldInfo );
	}
	
	// write tag values to image file [x]
	/*  
	void* var;
	TIFFGetField(rhs, --TAG--, &var);
	TIFFSetField(lhs, --TAG--, var);	
	*/
	uint16	bps, sf, spp;
	uint32	cmp, phm, plc;
	uint32	imgl = TIFFgrid.size().height;
	uint32	imgw = TIFFgrid.size().width;
	double	d1, d2, d4; short d3; uchar *d5, *d6;
	uint16	c1, c2, c3, c4, c5, c6;
	
	TIFFSetField(lhs, TIFFTAG_IMAGEWIDTH, imgw);
	TIFFSetField(lhs, TIFFTAG_IMAGELENGTH, imgl);

	TIFFGetField(rhs, TIFFTAG_BITSPERSAMPLE, &bps);
	TIFFSetField(lhs, TIFFTAG_BITSPERSAMPLE, bps);
	TIFFGetField(rhs, TIFFTAG_COMPRESSION, &cmp);
	TIFFSetField(lhs, TIFFTAG_COMPRESSION, cmp);
	TIFFGetField(rhs, TIFFTAG_PHOTOMETRIC, &phm);
	TIFFSetField(lhs, TIFFTAG_PHOTOMETRIC, phm);
	TIFFGetField(rhs, TIFFTAG_SAMPLESPERPIXEL, &spp);
	TIFFSetField(lhs, TIFFTAG_SAMPLESPERPIXEL, spp);
	TIFFGetField(rhs, TIFFTAG_PLANARCONFIG, &plc);
	TIFFSetField(lhs, TIFFTAG_PLANARCONFIG, plc);
	TIFFGetField(rhs, TIFFTAG_SAMPLEFORMAT, &sf);
	TIFFSetField(lhs, TIFFTAG_SAMPLEFORMAT, sf);
	if(aer){
		TIFFGetField(rhs, TIFFTAG_33550, &c1, &d1);
		TIFFSetField(lhs, TIFFTAG_33550, d1);
		TIFFGetField(rhs, TIFFTAG_33922, &c2, &d2);
		TIFFSetField(lhs, TIFFTAG_33922, d2);
		TIFFGetField(rhs, TIFFTAG_34735, &c3, &d3);
		TIFFSetField(lhs, TIFFTAG_34735, d3);
		TIFFGetField(rhs, TIFFTAG_34736, &c4, &d4);
		TIFFSetField(lhs, TIFFTAG_34736, d4);
		TIFFGetField(rhs, TIFFTAG_34737, &c5, &d5);
		TIFFSetField(lhs, TIFFTAG_34737, d5);
		TIFFGetField(rhs, TIFFTAG_42113, &c6, &d6);
		TIFFSetField(lhs, TIFFTAG_42113, d6);
	}

	// write image data	[x]
	saveTiff(lhs, *this);

	TIFFWriteDirectory(lhs);
	TIFFClose(lhs);
	TIFFClose(rhs);
}

/**
 * <!--
 * NAME OF FUNCTION: mask-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *	This function replaces all values in the calling instance's TIFFgrid with v using tH as a mask.
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param 	tH 		tiffHandler const reference --- tiffHandler object containing mask.
 * @param	v 		double		const value		---	Value to apply with mask.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 	value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	void
 * 
 * @see cv::Mat::setTo
*/
void tiffHandler::mask(const tiffHandler & tH, const double v){
	TIFFgrid.setTo(v , tH.data());
}

/**
 * <!--
 * NAME OF FUNCTION: data-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Read-only accessor method for grid data.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 	value/reference		description
 * 			----------------------------------------------------------------------------------------->
 * @return	cv::Mat const reference --- Matrix containing tiff image data.
*/
const Mat & tiffHandler::data(void) const{
	return TIFFgrid;
}

/**
 * <!--
 * NAME OF FUNCTION: -->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Read-only accessor method for tiff image width.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 	value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	int 	const value 	--- Width of tiff image.
*/
const int tiffHandler::getWidth(void) const{
	return TIFFgrid.size().width;
}

/**
 * <!--
 * NAME OF FUNCTION: -->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Read-only accessor method for tiff image height.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 	value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	int 	const value 	--- Height of tiff image.
*/
const int tiffHandler::getHeight(void) const{
	return TIFFgrid.size().height;
}

/**
 * <!--
 * NAME OF FUNCTION: -->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *    Read-only accessor method for tiff image path.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	std::string	const value 	--- Path of tiff image file.
*/
const std::string & tiffHandler::name(void) const{
	return fileName;
}