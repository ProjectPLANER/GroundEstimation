
/* @author emrchi001@myuct.ac.za
 * @date August 2020
 * idw interpolation handler
*/

#include "idwHandler.h"

double epsilon = 5e2;
std::atomic<long> changes(0);

/**
 * <!--
 * NAME OF FUNCTION: nearestNeighbour-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *	This function estimates missing values in "dataset" by setting the value to the value of its 
 *	nearest known neighbour.\ If there are multiple nearest neighbours, the average is taken and it 
 *	stores the estimates in "dataset.
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	dataset cv::Mat 	reference		--- Matrix of values.
 * @param 	noValue double 		const value 	--- Missing points in "dataset" have this value.
 * @param 	ignore 	double 		const value 	---	Points with this value are not taken into account.
 * 
 * <!--
 * RETURN VALUE:
 * 			type	value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	void
 * 
 * CALLS TO: none
 * 
 * CALLED FROM: main
 * 
 * METHOD: The following is pseudocode describing how the function works. 
 * 1. For each missing point in "dataset":
 * 1.1. radius := 1
 * 1.2. begin loop until radius covers all of "dataset":
 * 1.2.1. search for known points within radius in "dataset"
 * 1.2.2. if numberOfKnownPoints == 0: radius++
 * 1.2.3. else: exit loop
 * 1.3 Set value at missing point = averageOfFoundPointValues
 * 2 return
*/
void idw_ce::nearestNeighbour(cv::Mat & dataset, const double& noValue, const double& ignore){
	const int dimy = dataset.rows;
	const int dimx = dataset.cols;
	// count the number of missing values
	std::size_t missing = cv::countNonZero(dataset == noValue);
	std::size_t p;
	int loops = 16;
	int radLim = (dimx+dimy)/loops;
	while(loops > 0){
		loops--;
		dataset.forEach<float>([&](float & value, const int pos[])->void{
			if(value != noValue){ return; }
			// at a missing value, find the nearest known points within radius limit radLim
			int rad = 1;
			int tot = 0;
			float val = 0;
			while(rad <= radLim){
				cv::Range xRange, yRange;
				xRange = cv::Range(std::max(0, pos[0]-rad+1), std::min(pos[0]+rad, dimy));
				yRange = cv::Range(std::max(0, pos[1]-rad+1), std::min(pos[1]+rad, dimx));
	    		const cv::Mat & subMatrix = dataset(xRange,yRange);
	    		// check if there are known points at block radius rad
				cv::Mat sub = cv::Mat::ones(subMatrix.size(), subMatrix.type());
				sub.setTo(0, subMatrix == ignore);
				sub.setTo(0, subMatrix == noValue);

				tot = sum(sub.rowRange(0,1))[0]	// tot: number of known points
					+ sum(sub.colRange(0,1))[0]
					+ sum(sub.rowRange(sub.rows-1,sub.rows))[0]
					+ sum(sub.colRange(sub.cols-1,sub.cols))[0];

				if(tot > 0){
					// if there are known points at radius rad, take average of those points as the estimate for val
					val = sum( (subMatrix.rowRange(0,1)).mul(sub.rowRange(0,1)) )[0]
						+ sum( (subMatrix.colRange(0,1)).mul(sub.colRange(0,1)) )[0]
						+ sum( (subMatrix.rowRange(sub.rows-1,sub.rows)).mul(sub.rowRange(sub.rows-1,sub.rows)) )[0]
						+ sum( (subMatrix.colRange(sub.cols-1,sub.cols)).mul(sub.colRange(sub.cols-1,sub.cols)) )[0];
					val /= tot;
					value = val;
					break;
				}
				rad++;
				// if the radius covered the full grid, exit loop
				if(xRange == cv::Range(0,dimx) && yRange == cv::Range(0,dimy)){ break; }
			}
			return;
		});
		p = missing;
		missing = cv::countNonZero(dataset == noValue);
		if(missing == 0 || missing == p) { break; }
	}
	return;
}

/**
 * <!--
 * NAME OF FUNCTION: interpolate-->
 * CREDIT: emrchi001@myuct.ac.za; Local Modified Shephard algorithm
 * <!--
 * PURPOSE:-->@brief
 *  This function estimates the values of "dataset" indicated by "mask" using an iterative version of 
 *	local modified Shephard algorithm with the neighbourhood radius set to blockRadius.
 * 
 * <!--
 * PARAMETERS:
 * 			name 		type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	dataset 	cv::Mat 	reference		--- Matrix of values.
 * @param	mask 		cv::Mat 	const reference	--- Binary mask showing values to be estimated. 
 *														Must have the same dimensions as "dataset". 
 *														Every corresponding point in "dataset" to be 
 *														estimated must have value "noValue".
 * @param	blockRadius int			const value		--- Radius of grid points to use in estimation.
 * @param 	noValue 	double 		const value 	--- Missing points in "dataset" have this value.
 * @param 	ignore 		double 		const value 	---	Points with this value are not taken into 
 *														account.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 	value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	int 	value 			--- returns the number of iterations.
 * 
 * CALLS TO: {@link #iterate}
 * 
 * CALLED FROM: main
 * 
 * METHOD: The following is pseudocode describing how the function works.
 * 1. while NumberOfMissingValues > 0: call iterate
 * 2. return NumberOfIterations
*/
int idw_ce::interpolate(cv::Mat & dataset, const cv::Mat & mask, const int blockRadius, const double& noValue, const double& ignore){
	CV_Assert(dataset.size() == mask.size());
	if(blockRadius == 0) {return 0;}
	int i = 0;
	std::size_t missing = cv::countNonZero(dataset == noValue);
	std::size_t p;
	std::size_t iLim = (dataset.rows + dataset.cols) *3;
	epsilon = 900;

	while(missing > 0 || changes > 0){
		p = missing;
		changes = 0;
		idw_ce::iterate(dataset, mask, blockRadius, noValue, ignore);
		i++;
		missing = cv::countNonZero(dataset == noValue);
		if((missing-p) == 0) { break; }
	}
	for(;iLim > 0; iLim--){
		if(changes == 0) { break; }
		changes = 0;
		idw_ce::iterate(dataset, mask, blockRadius+10, noValue, ignore);
	}
			
	return i;
}

/**
 * <!--
 * NAME OF FUNCTION: iterate-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 *	This function performs a single iteration over the Matrix "dataset" and estimates values for 
 *	missing points---indicated by "mask"---using the local modified Shephard algorithm.\ <b>See</b>
 *	{@link interpolate}.
 * 
 * <!--
 * PARAMETERS:
 * 			name 		type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	dataset 	cv::Mat 	reference		--- Matrix of values.
 * @param	mask 		cv::Mat 	const reference	--- Binary mask showing values to be estimated. 
 *														Must have the same dimensions as "dataset". 
 *														Every corresponding point in "dataset" to be 
 *														estimated must have value "noValue".
 * @param	blockRadius int			const value		--- Radius of grid points to use in estimation.
 * @param 	noValue 	double 		const value 	--- Missing points in "dataset" have this value.
 * @param 	ignore 		double 		const value 	---	Points with this value are not taken into 
 *														account.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 	value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @return	void
 * 
 * CALLS TO: none
 * 
 * CALLED FROM: {@link #interpolate}
 * 
 * METHOD: The following is pseudocode describing how the function works.
 * 1. calculate filter Matrix of weights
 * 2. For each missing value M:
 * 2.1 extract subMatrix of size (2*blockRadius-1) by (2*blockRadius-1) centered at M from "dataset"
 * 2.2 apply weights to subMatrix
 * 2.3 sum values in the weighted Matrix
 * 2.4 store sum at M
 * 3 return
*/
void idw_ce::iterate(cv::Mat & dataset, const cv::Mat & mask, const int blockRadius, const double& noValue, const double& ignore){
	const int dimx = dataset.cols;
	const int dimy = dataset.rows;
	 //@TODO: create filter Matrix [x]
	int s = 2*blockRadius-1;
	int type = dataset.type();
	cv::Mat weights(s, s, type);
	float sumOfWeights = 0.0;
	
	for (int v = 1; v <= s; ++v){
		long dv_sq = (blockRadius-v)*(blockRadius-v);
		for (int u = 1; u <= v; ++u)
		{
			long dist_sq = dv_sq + (blockRadius-u)*(blockRadius-u);
			float dist = sqrt( dist_sq );
			float val = (blockRadius<=dist || dist==0)? 0 : pow(((blockRadius-dist) / (blockRadius*dist)) , 2);	//max(0,blockRadius-dist) = blockRadius-dist
			weights.at<float>(v-1,u-1) = val;
			sumOfWeights += val;

			if(v == u) { continue; }
			weights.at<float>(s-v,s-u) = val;
			sumOfWeights += val;
		}
	}
	
 	if(sumOfWeights == 0) return;
	
	cv::Mat prevMat( dataset.clone() );
	
	dataset.forEach<float>([&](float& value, const int pos[]) -> void {
	    if(mask.at<uchar>(pos[0],pos[1]) != (uchar)0) {
    		//@TODO: find noValue points and extract subMatrix [x]
    		cv::Range xRange, yRange;
    		// check: (blockRadius < pos[0] && blockRadius < pos[1] &&
    		// pos[0]+blockRadius < dimx && pos[1]+blockRadius < dimy)	[x]
			xRange = cv::Range(std::max(0, pos[0]-blockRadius+1), std::min(pos[0]+blockRadius, dimy));
			yRange = cv::Range(std::max(0, pos[1]-blockRadius+1), std::min(pos[1]+blockRadius, dimx));

    		const cv::Mat & subMatrix = prevMat(xRange,yRange);
    		//@TODO: apply filter i.e. calculate the weighted sum [x]
			//WeightedSum = Trace ( subMatrix * t(weights) ) = Trace ( subMatrix * weights )[x]
			//if(noValue!=0) => subMatrix.mask(noValue,ignore) =>* weightedSum				[x]
			cv::Mat subMask = cv::Mat::ones(subMatrix.size(), subMatrix.type());
			subMask.setTo(0, subMatrix == ignore);
			subMask.setTo(0, subMatrix == noValue);

			if(sum(subMask)[0] / subMask.total() < idw_ce::SURROUND_THRESHOLD){ return;	}

			cv::Mat adjWeights = weights.clone();
	    	float adjSumOfWeights = sumOfWeights;
	    	bool recalc = false;
	    	
	    	if(blockRadius > pos[0]) 
	    		{ adjWeights = adjWeights.rowRange(blockRadius-pos[0]-1,adjWeights.rows); recalc=true; }
    		if(blockRadius > pos[1]) 
    			{ adjWeights = adjWeights.colRange(blockRadius-pos[1]-1,adjWeights.cols); recalc=true; }
    		if(pos[0]+blockRadius > dimy) 
    			{ adjWeights = adjWeights.rowRange(0,adjWeights.rows+dimy-pos[0]-blockRadius); recalc=true; }
    		if(pos[1]+blockRadius > dimx) 
    			{ adjWeights = adjWeights.colRange(0,adjWeights.cols+dimx-pos[1]-blockRadius); recalc=true; }
    		
    		CV_Assert(adjWeights.size() == subMatrix.size());
			if(recalc) {
    			adjSumOfWeights = sum( adjWeights.mul(subMask) )[0];
    			if (adjSumOfWeights / sumOfWeights < 0.2) { return; }
	    	}
			//WeightedSum = Trace ( subMatrix * t(weights) ) [x]
	    	double weightedSum = sum( subMatrix.mul(adjWeights.mul(subMask)) )[0]; //sum(arg)[0] converts cv::Scalar to primitive as required
			double newValue = weightedSum / (adjSumOfWeights);

			if(abs(newValue - noValue) < epsilon) { return; }
			if(abs(newValue - value) != 0) {changes++;}
			value = newValue;
			
			return;
    	}
	});

 	prevMat.release();
	return;
}
