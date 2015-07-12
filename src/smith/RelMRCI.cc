//
// BAGEL - Parallel electron correlation program.
// Filename: RelMRCI.cc
// Copyright (C) 2014 Shiozaki group
//
// Author: Shiozaki group <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// The BAGEL package is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with the BAGEL package; see COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include <bagel_config.h>
#ifdef COMPILE_SMITH


#include <src/util/math/davidson.h>
#include <src/smith/extrap.h>
#include <src/smith/RelMRCI.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;

RelMRCI::RelMRCI::RelMRCI(shared_ptr<const SMITH_Info<std::complex<double>>> ref) : SpinFreeMethod(ref) {
  auto eig = f1_->diag();
  eig_.resize(eig.size());
  for (int i = 0; i != eig.size(); ++i)
    eig_[i] = real(eig[i]);
  nstates_ = ref->ciwfn()->nstates();

  for (int i = 0; i != nstates_; ++i) {
    auto tmp = make_shared<MultiTensor>(nstates_);
    for (auto& j : *tmp)
      j = init_amplitude();
    t2all_.push_back(tmp);

    auto tmp2 = make_shared<MultiTensor>(nstates_);
    for (auto& j : *tmp2)
      j = init_residual();
    sall_.push_back(tmp2);
    nall_.push_back(tmp2->copy());
  }
}


void RelMRCI::RelMRCI::solve() {
  Timer timer;
  print_iteration();

  const double core_nuc = core_energy_ + info_->geom()->nuclear_repulsion();

  // target state
  for (int istate = 0; istate != nstates_; ++istate) {
    const double refen = info_->ciwfn()->energy(istate) - core_nuc;
    // takes care of ref coefficients
    t2all_[istate]->fac(istate) = 1.0;
    nall_[istate]->fac(istate)  = 1.0;
    sall_[istate]->fac(istate)  = refen;

    for (int jst = 0; jst != nstates_; ++jst) {
      set_rdm(jst, istate);
      s = sall_[istate]->at(jst);
      auto queue = make_sourceq(false, jst == istate);
      while (!queue->done())
        queue->next_compute();
    }
  }

  DavidsonDiag_<Amplitude<std::complex<double>>, Residual<std::complex<double>>, ZMatrix> davidson(nstates_, info_->davidson_subspace());

  // first iteration is trivial
  {
    vector<shared_ptr<const Amplitude<std::complex<double>>>> a0;
    vector<shared_ptr<const Residual<std::complex<double>>>> r0;
    for (int istate = 0; istate != nstates_; ++istate) {
      a0.push_back(make_shared<Amplitude<std::complex<double>>>(t2all_[istate]->copy(), nall_[istate]->copy(), this));
      r0.push_back(make_shared<Residual<std::complex<double>>>(sall_[istate]->copy(), this));
    }
    energy_ = davidson.compute(a0, r0);
    for (int istate = 0; istate != nstates_; ++istate)
      assert(fabs(energy_[istate]+core_nuc - info_->ciwfn()->energy(istate)) < 1.0e-8);
  }

  // set the result to t2
  {
    vector<shared_ptr<Residual<std::complex<double>>>> res = davidson.residual();
    for (int i = 0; i != nstates_; ++i) {
      t2all_[i]->zero();
      update_amplitude(t2all_[i], res[i]->tensor());
    }
  }

  shared_ptr<MultiTensor> rtmp = nall_[0]->copy();
  rtmp->zero();

  Timer mtimer;
  int iter = 0;
  vector<bool> conv(nstates_, false);
  for ( ; iter != info_->maxiter(); ++iter) {

    // loop over state of interest
    vector<shared_ptr<const Amplitude<std::complex<double>>>> a0;
    vector<shared_ptr<const Residual<std::complex<double>>>> r0;
    for (int istate = 0; istate != nstates_; ++istate) {
      if (conv[istate]) {
        a0.push_back(nullptr);
        r0.push_back(nullptr);
        continue;
      }
      // first calculate left-hand-side vectors of t2 (named n)
      nall_[istate]->zero();
      for (int ist = 0; ist != nstates_; ++ist) {
        for (int jst = 0; jst != nstates_; ++jst) {
          set_rdm(jst, ist);
          t2 = t2all_[istate]->at(ist);
          n  = nall_[istate]->at(jst);
          auto queue = make_normq(false, jst == ist);
          while (!queue->done())
            queue->next_compute();
        }
      }

      // normalize t2 and n
      const double scal = 1.0 / sqrt(detail::real(dot_product_transpose(nall_[istate], t2all_[istate])));
      nall_[istate]->scale(scal);
      t2all_[istate]->scale(scal);

      a0.push_back(make_shared<Amplitude<std::complex<double>>>(t2all_[istate]->copy(), nall_[istate]->copy(), this));

      // compute residuals (named r)
      rtmp->zero();
      for (int ist = 0; ist != nstates_; ++ist) { // ket sector
        for (int jst = 0; jst != nstates_; ++jst) { // bra sector
          set_rdm(jst, ist);
          t2 = t2all_[istate]->at(ist);
          r = rtmp->at(jst);
          auto queue = make_residualq(false, jst == ist);
          while (!queue->done())
            queue->next_compute();
        }
      }

      // <ab/ij| T |0_ist> Eref_ist.
      {
        shared_ptr<MultiTensor> m = t2all_[istate]->copy();
        for (int ist = 0; ist != nstates_; ++ist) {
          // First weighted T2 amplitude
          m->at(ist)->scale(info_->ciwfn()->energy(ist) - core_nuc);
          // then add it to residual
          for (int jst = 0; jst != nstates_; ++jst) {
            set_rdm(jst, ist);
            t2 = m->at(ist);
            n  = rtmp->at(jst);
            auto queue = make_normq(false, jst == ist);
            while (!queue->done())
              queue->next_compute();
          }
        }
      }

      {
        shared_ptr<MultiTensor> m = rtmp->copy();
        for (int ist = 0; ist != nstates_; ++ist)
          m->fac(ist) = dot_product_transpose(sall_[ist], t2all_[istate]);
        r0.push_back(make_shared<Residual<std::complex<double>>>(m, this));
      }
    }

    energy_ = davidson.compute(a0, r0);

    // find new trial vectors
    vector<shared_ptr<Residual<std::complex<double>>>> res = davidson.residual();
    for (int i = 0; i != nstates_; ++i) {
      const double err = res[i]->tensor()->rms();
      print_iteration(iter, energy_[i]+core_nuc, err, mtimer.tick(), i);

      t2all_[i]->zero();
      conv[i] = err < info_->thresh();
      if (!conv[i])
        update_amplitude(t2all_[i], res[i]->tensor());
    }
    if (nstates_ > 1) cout << endl;

    if (all_of(conv.begin(), conv.end(), [](bool i){ return i;})) break;
  }
  print_iteration(iter == info_->maxiter());
  timer.tick_print("MRCI energy evaluation");

  // Davidson corrections...
  {
    cout << endl;
    vector<double> energy_q(nstates_);
    vector<shared_ptr<Amplitude<std::complex<double>>>> ci = davidson.civec();
    for (int i = 0; i != nstates_; ++i) {
      const double c = norm(ci[i]->tensor()->fac(i));
      const double eref = info_->ciwfn()->energy(i);
      const double eq = energy_[i]+core_nuc + (energy_[i]+core_nuc-eref)*(1.0-c)/c;
      print_iteration(0, eq, 0.0, 0.0, i);
    }
    cout << endl;
  }
  timer.tick_print("MRCI+Q energy evaluation");
}


void RelMRCI::RelMRCI::solve_deriv() {
  throw std::logic_error("Nuclear gradients not implemented for RelMRCI");
}


#endif