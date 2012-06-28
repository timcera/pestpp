/*  
    � Copyright 2012, David Welter
    
    This file is part of PEST++.
   
    PEST++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PEST++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PEST++.  If not, see<http://www.gnu.org/licenses/>.
*/
#ifndef QSQRT_MATRIX_H_
#define QSQRT_MATRIX_H_

#include <vector>


class ObservationInfo;
class Observations;
class LaGenMatDouble;
class PriorInformation;
class Parameters;

using namespace std;

class QSqrtMatrix
{
public:
	friend LaGenMatDouble operator*(const LaGenMatDouble &lhs, const QSqrtMatrix &rhs);
	QSqrtMatrix(const ObservationInfo &obs_info, const vector<string> &obs, const PriorInformation *prior_info_ptr, 
	double tikhonov_weight);
	LaGenMatDouble operator*(const LaGenMatDouble &rhs) const;
	LaGenMatDouble tran_q_mat_mult(const LaGenMatDouble &lhs) const;
	~QSqrtMatrix(void);

private:
	vector<double> weights;
};

LaGenMatDouble operator*(const LaGenMatDouble &lhs, const QSqrtMatrix &rhs);

#endif /* QSQRT_MATRIX_H_ */