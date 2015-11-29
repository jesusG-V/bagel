//
// BAGEL - Parallel electron correlation program.
// Filename: MRCI_tasks15.cc
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

#include <src/smith/MRCI_tasks15.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::MRCI;

void Task700::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("c1, a5, c6, a2") * (*ta2_)("c3, c6, a5, a4") * 4;
  madness::World::get_default().gop.fence();
}

void Task701::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("c1, a2, c6, a5") * (*ta2_)("c3, c6, a5, a4") * (-8);
  madness::World::get_default().gop.fence();
}

void Task702::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("c1, a6, c5, a4") * (*ta2_)("c3, a2, a6, c5") * 4;
  madness::World::get_default().gop.fence();
}

void Task703::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("c1, a4, c5, a6") * (*ta2_)("c3, a2, a6, c5") * (-8);
  madness::World::get_default().gop.fence();
}

void Task704::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("c1, a6, c5, a2") * (*ta2_)("c3, a4, a6, c5") * (-8);
  madness::World::get_default().gop.fence();
}

void Task705::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("c1, a2, c5, a6") * (*ta2_)("c3, a4, a6, c5") * 16;
  madness::World::get_default().gop.fence();
}

void Task706::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("x3, a4, c1, a2") * (*ta2_)("c3, x3");
  madness::World::get_default().gop.fence();
}

void Task707::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c3, x3") += (*ta1_)("x3, x2, x1, x0") * (*ta2_)("c3, x2, x1, x0") * (-1);
  madness::World::get_default().gop.fence();
}

void Task708::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c3, x3") += (*ta1_)("x3, x0, x2, x1") * (*ta2_)("x2, x1, c3, x0") * (-1);
  madness::World::get_default().gop.fence();
}

void Task709::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("x3, a2, c1, a4") * (*ta2_)("c3, x3");
  madness::World::get_default().gop.fence();
}

void Task710::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c3, x3") += (*ta1_)("x3, x2, x1, x0") * (*ta2_)("c3, x2, x1, x0") * 0.5;
  madness::World::get_default().gop.fence();
}

void Task711::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c3, x3") += (*ta1_)("x3, x0, x2, x1") * (*ta2_)("x2, x1, c3, x0") * 0.5;
  madness::World::get_default().gop.fence();
}

void Task712::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("x1, a4, c5, a2") * (*ta2_)("c1, c3, c5, x1");
  madness::World::get_default().gop.fence();
}

void Task713::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, c5, x1") += (*ta1_)("x1, x0") * (*ta2_)("c1, x0, c3, c5") * (-1);
  madness::World::get_default().gop.fence();
}

void Task714::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("x1, a2, c5, a4") * (*ta2_)("c1, c3, c5, x1");
  madness::World::get_default().gop.fence();
}

void Task715::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, c5, x1") += (*ta1_)("x1, x0") * (*ta2_)("c1, x0, c3, c5") * 2;
  madness::World::get_default().gop.fence();
}

void Task716::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("x1, a5, c1, a4") * (*ta2_)("a5, c3, a2, x1");
  madness::World::get_default().gop.fence();
}

void Task717::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, c3, a2, x1") += (*ta1_)("x1, x0") * (*ta2_)("a5, x0, c3, a2");
  madness::World::get_default().gop.fence();
}

void Task718::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, x0, c3, a2") += (*ta1_)("a5, x0, c3, a2") * (-2)
     + (*ta1_)("c3, x0, a5, a2");
  madness::World::get_default().gop.fence();
}

void Task719::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("x1, a4, c1, a5") * (*ta2_)("a5, c3, a2, x1");
  madness::World::get_default().gop.fence();
}

void Task720::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, c3, a2, x1") += (*ta1_)("x1, x0") * (*ta2_)("a5, x0, c3, a2");
  madness::World::get_default().gop.fence();
}

void Task721::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, x0, c3, a2") += (*ta1_)("a5, x0, c3, a2")
     + (*ta1_)("c3, x0, a5, a2") * (-2);
  madness::World::get_default().gop.fence();
}

void Task722::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("x1, a5, c1, a2") * (*ta2_)("a5, c3, a4, x1");
  madness::World::get_default().gop.fence();
}

void Task723::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, c3, a4, x1") += (*ta1_)("x1, x0") * (*ta2_)("a5, x0, c3, a4");
  madness::World::get_default().gop.fence();
}

void Task724::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, x0, c3, a4") += (*ta1_)("a5, x0, c3, a4") * 4
     + (*ta1_)("c3, x0, a5, a4") * (-2);
  madness::World::get_default().gop.fence();
}

void Task725::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, a4, c3") += (*ta1_)("x1, a2, c1, a5") * (*ta2_)("a5, c3, a4, x1");
  madness::World::get_default().gop.fence();
}

void Task726::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, c3, a4, x1") += (*ta1_)("x1, x0") * (*ta2_)("a5, x0, c3, a4");
  madness::World::get_default().gop.fence();
}

void Task727::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, x0, c3, a4") += (*ta1_)("a5, x0, c3, a4") * (-2)
     + (*ta1_)("c3, x0, a5, a4");
  madness::World::get_default().gop.fence();
}

void Task728::compute_() {
  madness::World::get_default().gop.fence();
  (*ta0_)("c2, a3, x0, a1") += (*ta1_)("a3, c2, x0, a1");
  madness::World::get_default().gop.fence();
}

void Task729::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a3, c2, x0, a1") += (*ta1_)("x1, a1") * (*ta2_)("a3, c2, x1, x0");
  madness::World::get_default().gop.fence();
}

void Task730::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a3, c2, x1, x0") += (*ta1_)("x3, x2, x1, x0") * (*ta2_)("x3, a3, c2, x2");
  madness::World::get_default().gop.fence();
}

void Task731::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x3, a3, c2, x2") += (*ta1_)("x3, a3, c2, x2") * (-1)
     + (*ta1_)("c2, a3, x3, x2") * 2;
  madness::World::get_default().gop.fence();
}

void Task732::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a3, c2, x0, a1") += (*ta1_)("x1, a3") * (*ta2_)("a1, c2, x0, x1");
  madness::World::get_default().gop.fence();
}

void Task733::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a1, c2, x0, x1") += (*ta1_)("x3, x0, x1, x2") * (*ta2_)("x3, a1, c2, x2");
  madness::World::get_default().gop.fence();
}

void Task734::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a1, c2, x0, x1") += (*ta1_)("x3, x2, x1, x0") * (*ta2_)("c2, a1, x3, x2") * (-1);
  madness::World::get_default().gop.fence();
}

void Task735::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a3, c2, x0, a1") += (*ta1_)("c2, a1") * (*ta2_)("a3, x0");
  madness::World::get_default().gop.fence();
}

void Task736::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a3, x0") += (*ta1_)("x3, x0, x2, x1") * (*ta2_)("x3, a3, x2, x1") * (-1);
  madness::World::get_default().gop.fence();
}

void Task737::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a3, c2, x0, a1") += (*ta1_)("c2, a3") * (*ta2_)("a1, x0");
  madness::World::get_default().gop.fence();
}

void Task738::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a1, x0") += (*ta1_)("x3, x0, x2, x1") * (*ta2_)("x3, a1, x2, x1") * 2;
  madness::World::get_default().gop.fence();
}

void Task739::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a3, c2, x0, a1") += (*ta1_)("c2, a3, c4, a1") * (*ta2_)("c4, x0");
  madness::World::get_default().gop.fence();
}

void Task740::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c4, x0") += (*ta1_)("x1, x0") * (*ta2_)("x1, c4") * (-4);
  madness::World::get_default().gop.fence();
}

void Task741::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c4, x0") += (*ta1_)("x3, x0, x2, x1") * (*ta2_)("x3, c4, x2, x1") * (-2);
  madness::World::get_default().gop.fence();
}

void Task742::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c4, x0") += (*ta1_)("x3, x2, x1, x0") * (*ta2_)("x3, x2, x1, c4") * (-2);
  madness::World::get_default().gop.fence();
}

void Task743::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a3, c2, x0, a1") += (*ta1_)("c2, a1, c4, a3") * (*ta2_)("c4, x0");
  madness::World::get_default().gop.fence();
}

void Task744::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c4, x0") += (*ta1_)("x1, x0") * (*ta2_)("x1, c4") * 2;
  madness::World::get_default().gop.fence();
}

void Task745::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c4, x0") += (*ta1_)("x3, x0, x2, x1") * (*ta2_)("x3, c4, x2, x1");
  madness::World::get_default().gop.fence();
}

void Task746::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c4, x0") += (*ta1_)("x3, x2, x1, x0") * (*ta2_)("x3, x2, x1, c4");
  madness::World::get_default().gop.fence();
}

void Task747::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a3, c2, x0, a1") += (*ta1_)("x1, x0") * (*ta2_)("c2, x1, a3, a1");
  madness::World::get_default().gop.fence();
}

void Task748::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c2, x1, a3, a1") += (*ta1_)("x1, a3, c4, a1") * (*ta2_)("c2, c4");
  madness::World::get_default().gop.fence();
}

void Task749::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c2, x1, a3, a1") += (*ta1_)("x1, a1, c4, a3") * (*ta2_)("c2, c4") * (-2);
  madness::World::get_default().gop.fence();
}

#endif
