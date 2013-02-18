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
#include "RunManagerAbstract.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>
#include <cstring>
#include "Transformable.h"
#include "utilities.h"

RunManagerAbstract::RunManagerAbstract(const vector<string> _comline_vec,
	const vector<string> _tplfile_vec, const vector<string> _inpfile_vec,
	const vector<string> _insfile_vec, const vector<string> _outfile_vec,
	const string &stor_filename)
	: total_runs(0), comline_vec(_comline_vec), tplfile_vec(_tplfile_vec),
	inpfile_vec(_inpfile_vec), insfile_vec(_insfile_vec), outfile_vec(_outfile_vec),
	file_stor(stor_filename)
{
	cout << endl;
	cout << "             Generalized Run Manager Interface" << endl;
	cout << "                       developed by:" << endl << endl;
	cout << "                        Dave Welter" << endl;
	cout << "          Computational Water Resource Engineering" << endl;
	cout << endl << endl;
}

void RunManagerAbstract::initialize(const Parameters &model_pars, const Observations &obs)
{
	file_stor.reset(model_pars.get_keys(), obs.get_keys());
}

void RunManagerAbstract::initialize(const std::vector<std::string> &par_names, std::vector<std::string> &obs_names)
{
	file_stor.reset(par_names, obs_names);
}

void RunManagerAbstract::reinitialize()
{
	vector<string> par_names = get_par_name_vec();
	vector<string> obs_names = get_obs_name_vec();
	file_stor.reset(par_names, obs_names);
}

int RunManagerAbstract::add_run(const vector<double> &model_pars)
{
    int run_id = file_stor.add_run(model_pars);
    return run_id;
}

int RunManagerAbstract::add_run(const Parameters &model_pars)
{
	int run_id = file_stor.add_run(model_pars);
	return run_id;
}

 const vector<string>& RunManagerAbstract::get_par_name_vec() const
 {
    return file_stor.get_par_name_vec();
 }

 const vector<string>& RunManagerAbstract::get_obs_name_vec() const
{
    return file_stor.get_obs_name_vec();
}

bool RunManagerAbstract::get_run(int run_id, Parameters &pars, Observations &obs)
{
	bool success = false;
	int status = file_stor.get_run(run_id, &pars, &obs);
	if (status > 0) success = true; 
    return success;
}

bool  RunManagerAbstract::get_run(int run_id, double *pars, size_t npars, double *obs, size_t nobs)
{
	bool success = false;
	int status = file_stor.get_run(run_id, pars, npars, obs, nobs);
    if (status > 0) success = true; 
    return success;
}


void  RunManagerAbstract::free_memory()
{
	file_stor.free_memory();
}


const std::set<int>& RunManagerAbstract::get_failed_run_ids() const
{
	return failed_runs;
}
Parameters RunManagerAbstract::get_model_parameters(int run_id)
 {
	 return file_stor.get_parameters(run_id); 
 }

 Observations RunManagerAbstract::get_obs_template(double value) const
 {
	Observations ret_obs;
    const vector<string> &obs_name_vec = file_stor.get_obs_name_vec();
	int nobs = obs_name_vec.size();
	for(int i=0; i<nobs; ++i)
	{
		ret_obs[obs_name_vec[i]] = value;
	}
	return ret_obs;
 }