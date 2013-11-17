//
// BAGEL - Parallel electron correlation program.
// Filename: sonaibatch_base.h
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Hai-Anh Le <anh@u.northwestern.edu>
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


#ifndef __SRC_RYSINT_SONAIBATCH_BASE_H
#define __SRC_RYSINT_SONAIBATCH_BASE_H

#include <src/integral/rys/rysintegral.h>
#include <src/molecule/molecule.h>

namespace bagel {

class SONAIBatch_base : public RysInt {
  protected:
    std::shared_ptr<const Molecule> mol_;
    int natom_;
    double zeta_;

    /// for periodic calculations (UNCHECKED!!)
    const int L_;
    const double A_;

    void root_weight(const int ps) override;
    void compute_ssss(const double) override;
    void allocate_data(const int asize_final, const int csize_final, const int asize_final_sph, const int csize_final_sph) override;

  public:
    SONAIBatch_base(const std::array<std::shared_ptr<const Shell>,2>& _info, const std::shared_ptr<const Molecule> mol, const int deriv,
                  std::shared_ptr<StackMem> stack = std::shared_ptr<StackMem>(),
                  const int L = 0, const double A = 0.0);
    ~SONAIBatch_base() {};

    std::shared_ptr<const Molecule> mol() const { return mol_; }

};

}

#endif
