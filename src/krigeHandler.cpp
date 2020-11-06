#include "krigeHandler.h"

using namespace krige_ce;

/**
 * <!--
 * NAME OF FUNCTION: convertForKrige-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *  This function reads the known points---points with values not equal to "naValue"---in "data" and 
 *	stores them as Node objects in the neighbourhhod "N".
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	data 	cv::Mat 	const reference	--- Matrix of values.
 * @param 	naValue double 		const value 	--- Missing points in "data" have this value.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 			value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	neighbourhood 	value 			---	Neighbourhood of all known coordinate points from "data"
 * 
 * CALLS TO: std::find, {@link #neighbourhood::neighbourhood}
 * 
 * CALLED FROM: {@link iterate}
*/
neighbourhood krige_ce::convertForKrige(const cv::Mat & data, const double naValue){
	// create empty neighbourhood of largest possible size
	neighbourhood N(data.rows*data.cols);
	// assign non-naValue nodes (index is calculated to be unique-avoids shared address problems between threads)
	data.forEach<float>([&,cols=data.cols](float & val, const int pos[]) -> void{
		if(val == naValue){ return; }
		size_t index = (pos[0]*cols) + pos[1];
		N[index] = Node(pos[0], pos[1], val);
	});
	CV_Assert(!N.is_empty());
	// remove blank elements
	auto beg = N.begin();
	auto end = N.end();
	std::sort(beg, end, 
		[](krige_ce::Node a, krige_ce::Node b) -> bool {
		       	return 	(a.location().x > b.location().x) || 
		        		((a.location().x == b.location().x) && (a.location().y > b.location().y));   
		});
	Node mt(0,0,0);
	auto fin = std::find(beg, end, mt);
	N.vec.erase(fin, end);
	// return populated neighbourhood
	return N;
}

/**
 * <!--
 * NAME OF FUNCTION: interpolate-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *  This function calculates the values for all points in "data" with a value of "naValue" using the 
 * 	ordinary Kriging.\ The value of a point is calculated using all known points in "data" within a 
 * 	distance of "blockradius" around the point.\ Points with value "ignore" are not used in the 
 *	estimation.
 * 
 * <!--
 * PARAMETERS:
 * 			name 		type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	data 		cv::Mat 	reference		--- Matrix of values.
 * @param 	naValue 	double 		const value 	--- Missing points in "data" have this value.
 * @param 	blockRadius int 		const value 	--- Radius for neighbourhood search. Must be a 
 * 														postive integer.
 * @param 	ignore 		double 		const value 	--- Value not be used in estimation.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	int 		value 			--- @parblock Status of algorithm on exit: <br>
 * 											@arg \c 0 	no errors <br>
 * 											@arg \c -1 	could not find solutions @endparblock
 * 
 * CALLS TO: {@link iterate}
 * 
 * CALLED FROM: main
 * 
 * METHOD: The following is pseudocode describing how the function works.
 * 1. while NumberOfMissingValues > 0: 
 * 1.1. call iterate
 * 1.2. if error occurs: return -1
 * 2. return 0
*/
int krige_ce::interpolate(cv::Mat & data, const double naValue, const int blockRadius, const double ignore){
	CV_Assert(blockRadius > 0);
	size_t missing = cv::countNonZero(data == naValue);
	size_t prev = data.rows * data.cols;
	int iterations = 0;
	while(missing > 0 && prev > missing){
		// repeat until all missing values have been estimated.
		iterations++;
		prev = missing;
		if(iterate(data, naValue, blockRadius, ignore) != 0)
		{
			// if iterate meets an error return error status.
			return -1;
		}
		missing = cv::countNonZero(data == naValue);
	}
	return 0;
}

/**
 * <!--
 * NAME OF FUNCTION: Neighbourhood2Vector-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *	This function converts a neighbourhood "N" of points into a column Matrix and returns the matrix.
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 			value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	N 		neighbourhood	const reference	--- Neighbourhood of points.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 	value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	cv::Mat value 			--- Vector of values from the points in "N".
 * 
 * CALLS TO: none
 * 
 * CALLED FROM: {@link iterate}
*/
cv::Mat Neighbourhood2Vector(const neighbourhood & N){
	cv::Mat nbhd(N.size(), 1, CV_32F);
	nbhd.forEach<double>([&](double & point, const int pos[]) -> void {
		point = N[ pos[0] ].property_value();
		return;
	});
	return nbhd;
}

/**
 * <!--
 * NAME OF FUNCTION: iterate-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *  This function estimates points in "data" with value "naValue" using a neighbourhood of radius 
 *	"blockradius" around each point and ignoring points with value "ignore".\ May return "data" with 
 *	some values still missing.\ <b>See</b> {@link interpolate}.
 * 
 * <!--
 * PARAMETERS:
 * 			name 		type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	data 		cv::Mat 	reference		--- Matrix of values.
 * @param 	naValue 	double 		const value 	--- Missing points in "data" have this value.
 * @param 	blockRadius int 		const value 	--- Radius for neighbourhood search. Must be a 
 * 														postive integer.
 * @param 	ignore 		double 		const value 	--- Value not be used in estimation.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	int 		value 				--- @parblock Status of algorithm on exit: 
 * 												@arg \c 0 	no errors @endparblock
 * 
 * CALLS TO: {@link #convertForKrige}, std::max, std::min, {@link #krige} 
 *			 <!--{@link #Neighbourhood2Vector}-->
 * 
 * CALLED FROM: {@link interpolate}
 * 
 * METHOD: The following is pseudocode describing how the function works.
 * 1. At each missing point M in "data":
 * 1.1. build a neighbourhood of points within blockRadius blocks around M
 * 1.2. if there are not enough neighbourhood points around M: continue
 * 1.3. else:
 * 1.3.1. calculate kriging weights for each point in the neighbourhood
 * 1.3.2. calculate weighted sum of neighbourhood points
 * 1.3.3. store weighted sum at M
 * 2. return
*/
int krige_ce::iterate(cv::Mat & data, const double naValue, const int blockRadius, const double ignore){
	CV_Assert(blockRadius > 0);
	int H = data.rows;
	int W = data.cols;
	
	cv::Mat out( cv::Mat::zeros(H,W,data.type()) );
	data.forEach<float>([&](float & val, const int pos[])->void{
		out.at<float>(pos[0],pos[1]) = val;
		if(val == naValue){
			// build neighbourhood of points within blockRadius
			int xbeg = std::max(0,pos[0]-blockRadius+1);
			int xend = std::min(H,pos[0]+blockRadius);
			int ybeg = std::max(0,pos[1]-blockRadius+1);
			int yend = std::min(W,pos[1]+blockRadius);
			if(xend - xbeg > yend - ybeg)
				{ xend = xbeg + yend - ybeg; }
			else if(xend - xbeg < yend - ybeg)
				{ yend = ybeg + xend - xbeg; }

			const cv::Mat & neighbours = data(cv::Range(xbeg, xend),
											  cv::Range(ybeg, yend));
			neighbourhood N = convertForKrige(neighbours, ignore);
			
			if(N.is_empty()) {return;}
			if(N.size() < 2*blockRadius) {return;}
			
			cv::Point2i loc(pos[0], pos[1]);
			std::vector<float> weights;

			// calculate kriging weights
			krige(loc, N, weights);
			
			if(weights.size() != 0) {
				// calculate weighted sum of neighbourhood points
				cv::Mat w = cv::Mat(weights).rowRange(1,weights.size());
				cv::Mat nbhd = Neighbourhood2Vector(N);
				CV_Assert(nbhd.size() == w.size());
				double fill = weights[0] + w.dot(nbhd);
				out.at<float>(pos[0],pos[1]) = fill;
			}
		}
		return;
	});

	data.release();
	data = out;
	return 0;
}

/**
 * <!--
 * NAME OF FUNCTION: krige-->
 * CREDIT: emrchi001@myuct.ac.za; GsTL-1.2.1 (Nicolas Remy. Stanford University).
 * <!--
 * PURPOSE:-->@brief
 *  This function calculates the ordinary kriging weights for each point in neighbourhood "N".\ These 
 *	weights are stored in "weights" and should be used to estimate "missing".
 * 
 * <!--
 * PARAMETERS:
 * 			name 		type 				value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	missing 	cv::Point2i 		reference 		--- Point coordinates to be estimated.
 * @param 	N 			neighbourhood 		const reference --- Vector of known coordinates and values.
 * @param 	weights 	std::vector<float> 	reference 		--- Empty vector where calculated weights
 * 																are stored.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	int 		value 			--- Status of the krige system at return. <b>see</b> 
 * 										<a href="../../include/GsTL-1.2.1/doc/latex/gtl.tex">gtl.tex</a>
 * 
 * CALLS TO: gstl::kriging_weights
 * 
 * CALLED FROM: {@link iterate}
*/
int krige_ce::krige(cv::Point2i & missing, const neighbourhood & N, std::vector<float> & weights){
	double OK_variance;
	covariance cov;
	OK_constraints OK_constr;
	int status = kriging_weights<GSTL_TNT_lib>(weights, OK_variance, missing, N, cov, OK_constr);
	return status;
}