/*
* @author emrchi001@myuct.ac.za
* @date August 2020
* CVP interpolation handler
*/

#include "cvpHandler.h"
//-------------<TRACE>---------------
// #include <iostream> //~temp
//-------------</TRACE>--------------


/**
 * <!--
 * NAME OF FUNCTION: interpolate-->
 * CREDIT: emrchi001@myuct.ac.za; Wecker et al. (2007), Contextual Void Patching for Digital Elevation Model.
 * <!--
 * PURPOSE:-->@brief 
 * 	This function will use the binary mask "mask" to determine which values in "grid" to estimate.\ 
 *	These values will be estimated using Wecker at al.'s contextual void patching algorithm and the
 *	estimates will be stored in "grid".
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	grid 	cv::Mat 	reference 		---	Matrix containing known points.
 * @param	mask    cv::Mat 	const reference ---	Binary mask showing points to be interpolated. 
 *													Must have the same dimensions as grid.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 		value/reference 		description
 * 			----------------------------------------------------------------------------------------->
 * @return	void   
 * 
 * CALLS TO: findVoids, {@link #hermiteSmooth}
 * 
 * CALLED FROM: main
 * 
 * METHOD: The following is pseudocode describing how the function works.
 * 1. Find start and end points of voids along all curves in the 4 {@link DIRECTIONS directions}
 * 2. Store the void coordinate pairs
 * 3. At each void coordinate pair, build a hermite curve interpolated patch between the beginning 
 *	  and end points
 * 4. Calculate the minimum distance to a known point for every missing point in "grid" in each 
 *	  {@link DIRECTIONS direction}
 * 5. For every missing point M:
 * 5.1. calculate the sum of inverse distances @arg \c invTotal in all 4 {@link DIRECTIONS directions}
 * 5.2. weight the hermite solution in each direction with the inverse minimum distance
 * 5.3. add the 4 weighted hermite solutions
 * 5.4. divide the weighted sum by @arg \c invTotal and store the answer at M
 * 6 end loop
 * 7 return
*/
void cvp_ce::interpolate(cv::Mat & grid, const cv::Mat & mask){
	CV_Assert(grid.size() == mask.size());
	double grid_min, grid_max;
	minMaxIdx(grid, &grid_min, &grid_max);
	double noValue = grid_min-1;
	grid.setTo(noValue, mask);

	// curves
	curvePatch u_curve;
	curvePatch v_curve;
	curvePatch w_curve;
	curvePatch t_curve;
	// [x] first step - identify voids
	cvp_ce::findVoids(grid, noValue, u_curve, v_curve, w_curve, t_curve);
	// [x] next step - at each void build a smooth patch
	cv::Mat uPatched = grid.clone();
	cv::Mat vPatched = grid.clone();
	cv::Mat wPatched = grid.clone();
	cv::Mat tPatched = grid.clone();
	for(int i_ = 0; i_ < u_curve.size(); i_++) {
		cvp_ce::hermiteSmooth(uPatched, noValue, u_curve.at(i_).first, u_curve.at(i_).second, cvp_ce::u);
	}
	for(int i_ = 0; i_ < v_curve.size(); i_++) {
		cvp_ce::hermiteSmooth(vPatched, noValue, v_curve.at(i_).first, v_curve.at(i_).second, cvp_ce::v);
	}
	for(int i_ = 0; i_ < w_curve.size(); i_++) {
		cvp_ce::hermiteSmooth(wPatched, noValue, w_curve.at(i_).first, w_curve.at(i_).second, cvp_ce::w);
	}
	for(int i_ = 0; i_ < t_curve.size(); i_++) {
		cvp_ce::hermiteSmooth(tPatched, noValue, t_curve.at(i_).first, t_curve.at(i_).second, cvp_ce::t);
	}
	//...
	// [x] next step - combine curve solutions
	cv::Mat u_dist = cv::Mat::zeros(grid.size(),CV_32F);
	cv::Mat v_dist = cv::Mat::zeros(grid.size(),CV_32F);
	cv::Mat w_dist = cv::Mat::zeros(grid.size(),CV_32F);
	cv::Mat t_dist = cv::Mat::zeros(grid.size(),CV_32F);
	// for each curve find dist...
	cv::Mat index (u_curve.size(), 1, CV_8U);
	index.forEach<uchar>([&](uchar & val, const int pos[]) -> void{
		//go through patch
		int patchWidth = 1 + norm(u_curve[pos[0]].second - u_curve[pos[0]].first) / cv::norm(cvp_ce::u);
		int patchPoint = 1;
		cv::Point2i p (u_curve[pos[0]].first);
		while(patchPoint <= patchWidth){
			//add min dist fom beg/end to dist matrix
			int ldist = patchPoint;
			int rdist = patchWidth - patchPoint + 1;
			u_dist.at<float>(p.x, p.y) = std::min(ldist, rdist);
			CV_Assert( u_dist.at<float>(p.x, p.y) > 0 );
			p += cvp_ce::u;
			patchPoint++;
		}
		u_dist.at<float>(u_curve[pos[0]].second.x, u_curve[pos[0]].second.y) = 1;
		return;
	});
	index = cv::Mat(v_curve.size(), 1, CV_8U);
	index.forEach<uchar>([&](uchar & val, const int pos[]) -> void{
		//go through patch
		int patchWidth = 1 + norm(v_curve[pos[0]].second - v_curve[pos[0]].first) / cv::norm(cvp_ce::v);
		int patchPoint = 1;
		cv::Point2i p (v_curve[pos[0]].first);
		while(patchPoint <= patchWidth){
			//add min dist fom beg/end to dist matrix
			int ldist = patchPoint;
			int rdist = patchWidth - patchPoint + 1;
			v_dist.at<float>(p.x, p.y) = std::min(ldist, rdist);
			CV_Assert( v_dist.at<float>(p.x, p.y) > 0 );
			p += cvp_ce::v;
			patchPoint++;
		}
		v_dist.at<float>(v_curve[pos[0]].second.x, v_curve[pos[0]].second.y) = 1;
		return;
	});
	index = cv::Mat(w_curve.size(), 1, CV_8U);
	index.forEach<uchar>([&](uchar & val, const int pos[]) -> void{
		//go through patch
		int patchWidth = 1 + norm(w_curve[pos[0]].second - w_curve[pos[0]].first) / cv::norm(cvp_ce::w);
		int patchPoint = 1;
		cv::Point2i p (w_curve[pos[0]].first);
		while(patchPoint <= patchWidth){
			//add min dist fom beg/end to dist matrix
			int ldist = patchPoint;
			int rdist = patchWidth - patchPoint + 1;
			w_dist.at<float>(p.x, p.y) = std::min(ldist, rdist);
			CV_Assert( w_dist.at<float>(p.x, p.y) > 0 );
			p += cvp_ce::w;
			patchPoint++;
		}
		w_dist.at<float>(w_curve[pos[0]].second.x, w_curve[pos[0]].second.y) = 1;
		return;
	});
	index = cv::Mat(t_curve.size(), 1, CV_8U);
	index.forEach<uchar>([&](uchar & val, const int pos[]) -> void{
		//go through patch
		const int patchWidth = 1 + ( norm(t_curve[pos[0]].second - t_curve[pos[0]].first) / cv::norm(cvp_ce::t) );
		int patchPoint = 1;
		cv::Point2i p (t_curve[pos[0]].first);
		while(patchPoint <= patchWidth){
			//add min dist fom beg/end to dist matrix
			int ldist = patchPoint;
			int rdist = patchWidth - patchPoint + 1;
			t_dist.at<float>(p.x, p.y) = std::min(ldist, rdist);
			CV_Assert( t_dist.at<float>(p.x, p.y) > 0 );
			p += cvp_ce::t;
			patchPoint++;
		}
		t_dist.at<float>(t_curve[pos[0]].second.x, t_curve[pos[0]].second.y) = 1;
		return;
	});
	// weighted sum using inverse ratio...
	grid.forEach<float>([&](float & val, const int pos[])->void{
		if(val == noValue) {
			double invtotal = (1 / u_dist.at<float>(pos[0], pos[1]))
							+ (1 / v_dist.at<float>(pos[0], pos[1]))
							+ (1 / w_dist.at<float>(pos[0], pos[1]))
							+ (1 / t_dist.at<float>(pos[0], pos[1]));
			val = uPatched.at<float>(pos[0], pos[1]) * (1 / ( u_dist.at<float>(pos[0], pos[1]) * invtotal ))
				+ vPatched.at<float>(pos[0], pos[1]) * (1 / ( v_dist.at<float>(pos[0], pos[1]) * invtotal ))
				+ wPatched.at<float>(pos[0], pos[1]) * (1 / ( w_dist.at<float>(pos[0], pos[1]) * invtotal ))
				+ tPatched.at<float>(pos[0], pos[1]) * (1 / ( t_dist.at<float>(pos[0], pos[1]) * invtotal ));
		}
		return;
	});
	return;
}

/**
 * <!--
 * NAME OF FUNCTION: findVoids-->
 * CREDIT: emrchi001@myuct.ac.za
 * <!--
 * PURPOSE:-->@brief
 * 	This function finds the begin and end vertices of every void in "grid", along every curve in each 
 *	of 4 directions ({@link DIRECTIONS u}, {@link DIRECTIONS v}, {@link DIRECTIONS w}, 
 *	{@link DIRECTIONS t}).\ Each vertex pair is stored in the corresponding direction_curvePatch.
 * 
 * <!--
 * PARAMETERS:
 * 			name 	type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	grid 	cv::Mat 	const reference ---	Matrix of values.
 * @param 	noValue double 		const value 	---	Missing points in "grid" have this value.
 * @param 	u_curve curvePatch 	reference 		---	A vector where start and end vertices will be 
 * 													stored along {@link DIRECTIONS u} direction.
 * @param 	v_curve curvePatch 	reference 		---	A vector where start and end vertices will be 
 * 													stored along {@link DIRECTIONS v} direction.
 * @param 	w_curve curvePatch 	reference 		---	A vector where start and end vertices will be 
 * 													stored along {@link DIRECTIONS w} direction.
 * @param 	t_curve curvePatch 	reference 		---	A vector where start and end vertices will be 
 * 													stored along {@link DIRECTIONS t} direction.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 		value/reference 		description
 * 			----------------------------------------------------------------------------------------->
 * @return	void
 * 
 * CALLS TO: none
 * 
 * CALLED FROM: {@link #interpolate}
 * 
 * METHOD: The following is pseudocode describing how the function works.
 * 1. Empty u_curve, v_curve, w_curve and t_curve vectors.
 * 2. ...
*/
void cvp_ce::findVoids(const cv::Mat & grid, const double noValue,\
curvePatch & u_curve, curvePatch & v_curve, curvePatch & w_curve, curvePatch & t_curve){
	cv::Mat r_index (grid.rows, 1, CV_8U);
	cv::Mat c_index (grid.cols, 1, CV_8U);
	//u direction
	u_curve.clear();
	//each column is a u curve, find patches on each
	c_index.forEach<uchar>(
	[&](const uchar & val, const int pos[]) -> void {
		//go down the col (i.e. add u until bottom)
		cv::Point2i coords(pos[0],0);
		cv::Mat ext(1,grid.cols,CV_32F);
		while(coords.y < grid.rows){
			std::pair<cv::Point2i, cv::Point2i> patch;
			//	find next patch along curve
			while(grid.at<float>(coords.x, coords.y) != noValue){
				coords = coords + cvp_ce::u;
				if(coords.y >= grid.rows) {return;}
			}
			patch.first = cv::Point2i(coords);
			//	find end of patch
			while(grid.at<float>(coords.x, coords.y) == noValue){
				coords = coords + cvp_ce::u;
				if(coords.y == grid.rows){break;}
			}
			patch.second = coords + (-1)*cvp_ce::u;
			
			u_mtx.lock();
			try{ u_curve.push_back(patch); }
			catch(...) { u_mtx.unlock(); }
			u_mtx.unlock();
		}
		return;
	});
	//-------------------------<TRACE>-----------------------------
	//std::cout << "U CURVE PATCHES (" << u_curve.size() << ")" << std::endl;
	//-------------------------</TRACE>----------------------------
	//v direction
	v_curve.clear();
	//each row is a v curve, find patches on each
	r_index.forEach<uchar>(
	[&](const uchar & val, const int pos[]) -> void {
		//go down the row (i.e. add v until end)
		cv::Point2i coords(0,pos[0]);
		while(coords.x < grid.cols){
			std::pair<cv::Point2i, cv::Point2i> patch;
			//	find next patch along curve
			while(grid.at<float>(coords.x, coords.y) != noValue){
				coords += cvp_ce::v;
				if(coords.x >= grid.cols) {return;}
			}
			patch.first = cv::Point2i(coords);
			//	find end of patch
			while(grid.at<float>(coords.x, coords.y) == noValue){
				coords += cvp_ce::v;
				if(coords.x == grid.cols){break;}
			}
			patch.second = coords + (-1)* cvp_ce::v;
			
			v_mtx.lock();
			try{ v_curve.push_back(patch); }
			catch(...) { v_mtx.unlock(); }
			v_mtx.unlock();
		}
		return;
	});
	//-------------------------<TRACE>-----------------------------
	//std::cout << "V CURVE PATCHES (" << v_curve.size() << ")" << std::endl;
	//-------------------------</TRACE>----------------------------
	//w direction
	w_curve.clear();
	//first column and bottom row cover all w curves
	r_index.forEach<uchar>(
	[&](const uchar & val, const int pos[]) -> void {
		//go up the diag (i.e. add w until top)
		cv::Point2i coords(pos[0],0);
		while(coords.x >= 0 && coords.y < grid.cols){
			std::pair<cv::Point2i, cv::Point2i> patch;
			//	find next patch along curve
			while(grid.at<float>(coords.x, coords.y) != noValue){
				coords += cvp_ce::w;
				if(coords.x < 0 || coords.y >= grid.cols) 
				{ return; }
			}
			patch.first = cv::Point2i(coords);
			//	find end of patch
			while(grid.at<float>(coords.x, coords.y) == noValue){
				coords += cvp_ce::w;
				if(coords.x < 0 || coords.y == grid.cols)
				{ break; }
			}
			patch.second = coords + (-1)* cvp_ce::w;
			
			w_mtx.lock();
			try{ w_curve.push_back(patch); }
			catch(...) { w_mtx.unlock(); }
			w_mtx.unlock();
		}
		return;
	});
	c_index.forEach<uchar>(
	[&](const uchar & val, const int pos[]) -> void {
		if(pos[0] == 0) { return; }
		//go up the diag (i.e. add w until edge)
		cv::Point2i coords(grid.rows-1,pos[0]);
		while(coords.x >= 0 && coords.y < grid.cols){
			std::pair<cv::Point2i, cv::Point2i> patch;
			//	find next patch along curve
			while(grid.at<float>(coords.x, coords.y) != noValue){
				coords += cvp_ce::w;
				if(coords.x < 0 || coords.y >= grid.cols)
				{ return; }
			}
			patch.first = cv::Point2i(coords);
			//	find end of patch
			while(grid.at<float>(coords.x, coords.y) == noValue){
				coords += cvp_ce::w;
				if(coords.x < 0 || coords.y == grid.cols)
				{ break; }
			}
			patch.second = coords + (-1)*cvp_ce::w;
			
			w_mtx.lock();
			try{ w_curve.push_back(patch); }
			catch(...) { w_mtx.unlock(); }
			w_mtx.unlock();
		}
		return;
	});
	//-------------------------<TRACE>-----------------------------
	//std::cout << "W CURVE PATCHES (" << w_curve.size() << ")" << std::endl;
	//-------------------------</TRACE>----------------------------
	//t direction
	t_curve.clear();
	//first column and top row cover all t curves
	r_index.forEach<uchar>(
	[&](const uchar & val, const int pos[]) -> void {
		//go down the diag (i.e. add t until bottom)
		cv::Point2i coords(pos[0],0);
		while(coords.x < grid.rows && coords.y < grid.cols){
			std::pair<cv::Point2i, cv::Point2i> patch;
			//	find next patch along curve
			while(grid.at<float>(coords.x, coords.y) != noValue){
				coords += cvp_ce::t;
				if(coords.x >= grid.rows || coords.y >= grid.cols) 
				{ return; }
			}
			patch.first = cv::Point2i(coords);
			//	find end of patch
			while(grid.at<float>(coords.x, coords.y) == noValue){
				coords += cvp_ce::t;
				if(coords.x == grid.rows || coords.y == grid.cols)
				{ break; }
			}
			patch.second = coords + (-1)*cvp_ce::t;
			
			t_mtx.lock();
			try{ t_curve.push_back(patch); }
			catch(...) { t_mtx.unlock(); }
			t_mtx.unlock();
		}
		return;
	});
	c_index.forEach<uchar>(
	[&](const uchar & val, const int pos[]) -> void {
		if(pos[0] == 0) { return; }
		//go down the diag (i.e. add t until edge)
		cv::Point2i coords(0,pos[0]);
		while(coords.x < grid.rows && coords.y < grid.cols){
			std::pair<cv::Point2i, cv::Point2i> patch;
			//	find next patch along curve
			while(grid.at<float>(coords.x, coords.y) != noValue){
				coords += cvp_ce::t;
				if(coords.x >= grid.rows || coords.y >= grid.cols)
				{ return; }
			}
			patch.first = cv::Point2i(coords);
			//	find end of patch
			while(grid.at<float>(coords.x, coords.y) == noValue){
				coords += cvp_ce::t;
				if(coords.x == grid.rows || coords.y == grid.cols)
				{ break; }
			}
			patch.second = coords + (-1)*cvp_ce::t;
			
			t_mtx.lock();
			try{ t_curve.push_back(patch); }
			catch(...) { t_mtx.unlock(); }
			t_mtx.unlock();
		}
		return;
	});
	//-------------------------<TRACE>-----------------------------
	//std::cout << "T CURVE PATCHES (" << t_curve.size() << ")" << std::endl;
	//-------------------------</TRACE>----------------------------
	return;
}

/**
 * <!--
 * NAME OF FUNCTION: hermiteSmooth-->
 * CREDIT: emrchi001@myuct.ac.za; Nils Pipenbrinck (1998), Hermite Curve Interpolation.
 * <!--
 * PURPOSE:-->@brief
 *	This function takes user input "beg" and "end", which specify the start and end points of a line 
 * 	in the direction "direction". Cubic Hermite curves are used to estimate the values of collinear 
 *	points between beg and end. These estimates are stored at the corresponding coordinate positions 
 *	in "grid".
 * 
 * <!--
 * PARAMETERS:
 * 			name 		type 		value/reference 	description
 * 			----------------------------------------------------------------------------------------->
 * @param	grid 		cv::Mat 	 reference		--- Matrix of values.
 * @param 	noValue 	double 		 const value 	--- Missing points in "grid" have this value.
 * @param 	beg 		cv::Point2i  const value    --- Point coordinates indicating position in 
 * 														"grid" to begin hermite curve interpolation.
 * @param 	end 		cv::Point2i  const value    --- Point coordinates indicating position in 
 * 														"grid" to end hermite curve interpolation.
 * 														Must be collinear with "beg" in the positive 
 * 														direction of vector "direction".
 * @param 	direction 	cv::Point2i  const value    --- Vector coordinates of the direction of the 
 * 														curve. Treated as a unit vector i.e. all 
 * 														distances are scaled with its norm.
 * 
 * <!--
 * RETURN VALUE:
 * 			type 		value/reference 		description
 * 			----------------------------------------------------------------------------------------->
 * @return	void
 * 
 * CALLS TO: none
 * 
 * CALLED FROM: {@link #interpolate}
 * 
 * METHOD: The following is pseudocode describing how the function works.
 * 1. ...
*/
void cvp_ce::hermiteSmooth(cv::Mat & grid, const double noValue,\
	const cv::Point2i beg, const cv::Point2i end, const cv::Point2i direction){
	//      | s^3 |            | P1 |             |  2  -2   1   1 |
	// S =  | s^2 |       C =  | P2 |        h =  | -3   3  -2  -1 |
	//      | s^1 |            | T1 |             |  0   0   1   0 |
	//      | 1   |            | T2 |             |  1   0   0   0 |
    // P = S * h * C
    //...
    // find tangent of surface on either side of patch
	// rise = diference in height values
	// run  = width of patch (ideally)
	double tangent1 = 1.0;
	double tangent2 = -1.0;
    const double dirNorm = cv::norm(direction);
	const int patchWidth = cv::norm(end - beg)/dirNorm + 1;
    cv::Point2i found = beg - std::max(2,patchWidth)*direction;
    cv::Point2i edge  = beg - direction;
    // if coordinates "found"/"edge" fall outside the grid:
    // reduce distance from the edge of the void and adjust 
    // coordinates
    if( edge.x >= 0 && edge.y >= 0 && 
    	edge.x < grid.rows && edge.y < grid.cols) {
    	int i = 0;
    	while( found.x < 0 || found.y < 0 || 
	    	found.x >= grid.rows || found.y >= grid.cols) {
	    	found += direction;
	    	i++;
	    }
    	while( grid.at<float>(found.x, found.y) == noValue\
    		&& found!=(edge-direction) ){
    		found += direction;
    		i++;
    	}

    	if(patchWidth > i){
    		tangent1 = (grid.at<float>(found.x, found.y) 
    				 - grid.at<float>(edge.x, edge.y)) / (patchWidth-i); }
    }
    found = end + std::max(2,patchWidth)*direction;
    edge  = end + direction;
    // if coordinates "found"/"edge" fall outside the grid:
    // reduce distance from the edge of the void and adjust 
    // coordinates
    if( edge.x >= 0 && edge.y >= 0 && 
    	edge.x < grid.rows && edge.y < grid.cols) {
    	int i = 0;
    	while( found.x < 0 || found.y < 0 || 
	    	found.x >= grid.rows || found.y >= grid.cols) {
	    	found -= direction;
	    	i++;
	    }
    	while( grid.at<float>(found.x, found.y) == noValue\
    		&& found!=(edge+direction) ){
    		found -= direction;
    		i++;
    	}

    	if(patchWidth > i){
    		tangent2 = (grid.at<float>(edge.x, edge.y) 
    				 - grid.at<float>(found.x, found.y)) / (patchWidth-i); }
    }
	
	cv::Point2i p1(beg - direction);
    if(p1.x < 0 || p1.y < 0 || p1.x >= grid.rows || p1.y >= grid.cols) {p1 = beg;}
    cv::Point2i p2(end + direction);
    if(p2.x < 0 || p2.y < 0 || p2.x >= grid.rows || p2.y >= grid.cols) {p2 = end;}

	cv::Mat C ({4,1}, {
		(double)grid.at<float>(p1.x, p1.y),
		(double)grid.at<float>(p2.x, p2.y),
		tangent1, tangent2});
	const cv::Mat h ({4,4}, {
		 2.0, -2.0,  1.0,  1.0,
		-3.0,  3.0, -2.0, -1.0,
		 0.0,  0.0,  1.0,  0.0,
		 1.0,  0.0,  0.0,  0.0
	});
	// recalculated with every s in the curve patch
	cv::Mat S ({1,4}, {0.0, 0.0, 0.0, 1.0});
	cv::Point2i curr = beg;
	for(int p = 0; p < patchWidth; p++, curr+=direction){
		// s from 0 to 1
		double s = p / std::max(1, patchWidth-1);
		S.at<double>(0,0) = s*s*s;
		S.at<double>(0,1) = s*s;
		S.at<double>(0,2) = s;
		double P = sum((S * h) * C)(0);
		grid.at<float>(curr.x, curr.y) = P;
	}
	return;
}