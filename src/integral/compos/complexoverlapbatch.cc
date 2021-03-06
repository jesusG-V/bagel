//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: complexoverlapbatch.cc
// Copyright (C) 2014 Toru Shiozaki
//
// Author: Ryan D. Reynolds <RyanDReynolds@u.northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//


#include <src/integral/hrrlist.h>
#include <src/integral/carsphlist.h>
#include <src/integral/compos/complexoverlapbatch.h>
#include <complex>

using namespace std;
using namespace bagel;

const static CHRRList hrr;
const static CCarSphList carsphlist;

void ComplexOverlapBatch::compute() {

  const CSortList sort_(spherical_);

  complex<double>* const intermediate_p = stack_->get<complex<double>>(prim0_ * prim1_ * asize_);
  perform_VRR(intermediate_p);

  complex<double>* const intermediate_c = stack_->get<complex<double>>(cont0_ * cont1_ * asize_);
  perform_contraction(asize_, intermediate_p, prim0_, prim1_, intermediate_c,
                      basisinfo_[0]->contractions(), basisinfo_[0]->contraction_ranges(), cont0_,
                      basisinfo_[1]->contractions(), basisinfo_[1]->contraction_ranges(), cont1_);

  complex<double>* const intermediate_fi = stack_->get<complex<double>>(cont0_ * cont1_ * asize_intermediate_);

  if (basisinfo_[1]->angular_number() != 0) {
    const int hrr_index = basisinfo_[0]->angular_number() * ANG_HRR_END + basisinfo_[1]->angular_number();
    hrr.hrrfunc_call(hrr_index, cont0_ * cont1_, intermediate_c, AB_, intermediate_fi);
  } else {
    const unsigned int array_size = cont0_ * cont1_ * asize_intermediate_;
    copy_n(intermediate_c, array_size, intermediate_fi);
  }

  if (spherical_) {
    complex<double>* const intermediate_i = stack_->get<complex<double>>(cont0_ * cont1_ * asize_final_);
    const unsigned int carsph_index = basisinfo_[0]->angular_number() * ANG_HRR_END + basisinfo_[1]->angular_number();
    const int nloops = cont0_ * cont1_;
    carsphlist.carsphfunc_call(carsph_index, nloops, intermediate_fi, intermediate_i);

    const unsigned int sort_index = basisinfo_[1]->angular_number() * ANG_HRR_END + basisinfo_[0]->angular_number();
    sort_.sortfunc_call(sort_index, data_, intermediate_i, cont1_, cont0_, 1, swap01_);
    stack_->release(cont0_ * cont1_ * asize_final_, intermediate_i);
  } else {
    const unsigned int sort_index = basisinfo_[1]->angular_number() * ANG_HRR_END + basisinfo_[0]->angular_number();
    sort_.sortfunc_call(sort_index, data_, intermediate_fi, cont1_, cont0_, 1, swap01_);
  }

  stack_->release(cont0_*cont1_*asize_intermediate_, intermediate_fi);
  stack_->release(cont0_*cont1_*asize_, intermediate_c);
  stack_->release(prim0_*prim1_*asize_, intermediate_p);

}

complex<double> ComplexOverlapBatch::get_P(const double coord1, const double coord2, const double exp1, const double exp2, const double one12,
                                                const int dim, const bool swap) {
  const double Areal = coord1*exp1;
  const double Breal = coord2*exp2;
  const double Aimag = basisinfo_[0]->vector_potential(dim);
  const double Bimag = basisinfo_[1]->vector_potential(dim);
  const double imag = 0.5 * (swap ? Bimag - Aimag : Aimag - Bimag );
  const complex<double> num (Areal + Breal, imag);
  return num * one12;
}


