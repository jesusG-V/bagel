//
// BAGEL - Parallel electron correlation program.
// Filename: MRCI_tasks10.cc
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

#include <src/smith/MRCI_tasks10.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::MRCI;

void Task450::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c2, x1, x0, a1") += (*ta1_)("x7, x0, x1, x6") * (*ta2_)("x7, a1, c2, x6") * (-0.5);
  madness::World::get_default().gop.fence();
}

void Task451::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c2, x1, x0, a1") += (*ta1_)("x7, x6, x1, x0") * (*ta2_)("c2, a1, x7, x6") * 0.5;
  madness::World::get_default().gop.fence();
}

void Task452::compute_() {
  madness::World::get_default().gop.fence();
  (*ta0_)("x0, x1, c1, a2") += (*ta1_)("c1, x1, x0, a2");
  madness::World::get_default().gop.fence();
}

void Task453::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x1, x0, a2") += (*ta1_)("x2, a2") * (*ta2_)("c1, x2, x1, x0");
  madness::World::get_default().gop.fence();
}

void Task454::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x2, x1, x0") += (*ta1_)("x5, x4, x2, x3, x1, x0") * (*ta2_)("x5, x4, c1, x3");
  madness::World::get_default().gop.fence();
}

void Task455::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x1, x0, a2") += (*ta1_)("x2, x3, x1, x0") * (*ta2_)("x2, a2, c1, x3");
  madness::World::get_default().gop.fence();
}

void Task456::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x2, a2, c1, x3") += (*ta1_)("c3, a2, c1, x3") * (*ta2_)("x2, c3") * (-1);
  madness::World::get_default().gop.fence();
}

void Task457::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x2, a2, c1, x3") += (*ta1_)("c1, a2, c3, x3") * (*ta2_)("x2, c3") * 2;
  madness::World::get_default().gop.fence();
}

void Task458::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x2, a2, c1, x3") += (*ta1_)("c4, a2, c3, x3") * (*ta2_)("x2, c4, c1, c3");
  madness::World::get_default().gop.fence();
}

void Task459::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x2, a2, c1, x3") += (*ta1_)("c3, a2, c4, x3") * (*ta2_)("x2, c4, c1, c3") * (-2);
  madness::World::get_default().gop.fence();
}

void Task460::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x2, a2, c1, x3") += (*ta1_)("c4, a3, c1, x3") * (*ta2_)("x2, c4, a3, a2") * (-1);
  madness::World::get_default().gop.fence();
}

void Task461::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x2, a2, c1, x3") += (*ta1_)("c3, a4, c1, x3") * (*ta2_)("x2, a2, a4, c3") * 2;
  madness::World::get_default().gop.fence();
}

void Task462::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x2, a2, c1, x3") += (*ta1_)("c1, a3, c4, x3") * (*ta2_)("x2, c4, a3, a2") * 2;
  madness::World::get_default().gop.fence();
}

void Task463::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x2, a2, c1, x3") += (*ta1_)("c1, a4, c3, x3") * (*ta2_)("x2, a2, a4, c3") * (-1);
  madness::World::get_default().gop.fence();
}

void Task464::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x2, a2, c1, x3") += (*ta1_)("c1, a4, c3, a2") * (*ta2_)("a4, x3, x2, c3") * (-1);
  madness::World::get_default().gop.fence();
}

void Task465::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x2, a2, c1, x3") += (*ta1_)("c1, a2, c3, a4") * (*ta2_)("a4, x3, x2, c3") * 2;
  madness::World::get_default().gop.fence();
}

void Task466::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x1, x0, a2") += (*ta1_)("x3, x2, x1, x0") * (*ta2_)("c1, x3, a2, x2");
  madness::World::get_default().gop.fence();
}

void Task467::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("x3, a2, c3, x2") * (*ta2_)("c1, c3");
  madness::World::get_default().gop.fence();
}

void Task468::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("x3, a3, c1, x2") * (*ta2_)("a3, a2") * (-1);
  madness::World::get_default().gop.fence();
}

void Task469::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("c3, a2, x3, x2") * (*ta2_)("c1, c3") * (-2);
  madness::World::get_default().gop.fence();
}

void Task470::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("c1, a3, x3, x2") * (*ta2_)("a3, a2") * 2;
  madness::World::get_default().gop.fence();
}

void Task471::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("x3, a3, c1, a2") * (*ta2_)("a3, x2") * 2;
  madness::World::get_default().gop.fence();
}

void Task472::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("x3, a2, c1, a3") * (*ta2_)("a3, x2") * (-1);
  madness::World::get_default().gop.fence();
}

void Task473::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("x3, a3, c4, x2") * (*ta2_)("c1, c4, a3, a2");
  madness::World::get_default().gop.fence();
}

void Task474::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("x3, a4, c3, x2") * (*ta2_)("c1, a2, a4, c3") * (-2);
  madness::World::get_default().gop.fence();
}

void Task475::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("c4, a3, x3, x2") * (*ta2_)("c1, c4, a3, a2") * (-2);
  madness::World::get_default().gop.fence();
}

void Task476::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("c3, a4, x3, x2") * (*ta2_)("c1, a2, a4, c3") * 4;
  madness::World::get_default().gop.fence();
}

void Task477::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("c1, a4, c3, a2") * (*ta2_)("a4, c3, x3, x2");
  madness::World::get_default().gop.fence();
}

void Task478::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a4, c3, x3, x2") += (*ta1_)("a4, c3, x3, x2") * (-2)
     + (*ta1_)("x3, x2, a4, c3") * (-2);
  madness::World::get_default().gop.fence();
}

void Task479::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("c1, a2, c3, a4") * (*ta2_)("a4, c3, x3, x2");
  madness::World::get_default().gop.fence();
}

void Task480::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a4, c3, x3, x2") += (*ta1_)("a4, c3, x3, x2") * 4
     + (*ta1_)("x3, x2, a4, c3") * 4;
  madness::World::get_default().gop.fence();
}

void Task481::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("c1, a3, c4, a2") * (*ta2_)("x3, c4, a3, x2");
  madness::World::get_default().gop.fence();
}

void Task482::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("c1, a2, c4, a3") * (*ta2_)("x3, c4, a3, x2") * (-2);
  madness::World::get_default().gop.fence();
}

void Task483::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("x3, a4, c3, a2") * (*ta2_)("a4, x2, c1, c3");
  madness::World::get_default().gop.fence();
}

void Task484::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a4, x2, c1, c3") += (*ta1_)("a4, x2, c1, c3") * (-2)
     + (*ta1_)("c1, x2, a4, c3");
  madness::World::get_default().gop.fence();
}

void Task485::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("x3, a2, c3, a4") * (*ta2_)("a4, x2, c1, c3");
  madness::World::get_default().gop.fence();
}

void Task486::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a4, x2, c1, c3") += (*ta1_)("a4, x2, c1, c3")
     + (*ta1_)("c1, x2, a4, c3") * (-2);
  madness::World::get_default().gop.fence();
}

void Task487::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("x3, a4, c1, a3") * (*ta2_)("a4, x2, a3, a2") * 2;
  madness::World::get_default().gop.fence();
}

void Task488::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x3, a2, x2") += (*ta1_)("x3, a3, c1, a4") * (*ta2_)("a4, x2, a3, a2") * (-1);
  madness::World::get_default().gop.fence();
}

void Task489::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x1, x0, a2") += (*ta1_)("c1, x2") * (*ta2_)("a2, x2, x1, x0");
  madness::World::get_default().gop.fence();
}

void Task490::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, x2, x1, x0") += (*ta1_)("x5, x2, x4, x3, x1, x0") * (*ta2_)("x5, a2, x4, x3") * (-1);
  madness::World::get_default().gop.fence();
}

void Task491::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x1, x0, a2") += (*ta1_)("x1, x0") * (*ta2_)("c1, a2");
  madness::World::get_default().gop.fence();
}

void Task492::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2") += (*ta1_)("c1, a4, c3, a2") * (*ta2_)("a4, c3") * (-4);
  madness::World::get_default().gop.fence();
}

void Task493::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2") += (*ta1_)("c1, a2, c3, a4") * (*ta2_)("a4, c3") * 8;
  madness::World::get_default().gop.fence();
}

void Task494::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2") += (*ta1_)("c3, a4, c5, a2") * (*ta2_)("c1, c5, a4, c3") * (-8);
  madness::World::get_default().gop.fence();
}

void Task495::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2") += (*ta1_)("c3, a2, c5, a4") * (*ta2_)("c1, c5, a4, c3") * 4;
  madness::World::get_default().gop.fence();
}

void Task496::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2") += (*ta1_)("c1, a5, c3, a4") * (*ta2_)("a5, a2, a4, c3") * 8;
  madness::World::get_default().gop.fence();
}

void Task497::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2") += (*ta1_)("c1, a4, c3, a5") * (*ta2_)("a5, a2, a4, c3") * (-4);
  madness::World::get_default().gop.fence();
}

void Task498::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x1, x0, a2") += (*ta1_)("x3, a2, x2, c3") * (*ta2_)("c1, c3, x3, x2, x1, x0");
  madness::World::get_default().gop.fence();
}

void Task499::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, x3, x2, x1, x0") += (*ta1_)("x3, x5, x2, x4, x1, x0") * (*ta2_)("c1, x5, c3, x4") * (-2);
  madness::World::get_default().gop.fence();
}

#endif
