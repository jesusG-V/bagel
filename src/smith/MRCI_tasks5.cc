//
// BAGEL - Parallel electron correlation program.
// Filename: MRCI_tasks5.cc
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

#include <src/smith/MRCI_tasks5.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::MRCI;

void Task200::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, x0") += (*ta1_)("x3, x2, x0, x1") * (*ta2_)("x3, x2, c1, x1") * (-1);
  madness::World::get_default().gop.fence();
}

void Task201::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, x0, a2") += (*ta1_)("x0, x1") * (*ta2_)("c1, a2, c3, x1");
  madness::World::get_default().gop.fence();
}

void Task202::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c4, a2, c3, x1") * (*ta2_)("c1, c4") * (-2);
  madness::World::get_default().gop.fence();
}

void Task203::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c3, a2, c4, x1") * (*ta2_)("c1, c4");
  madness::World::get_default().gop.fence();
}

void Task204::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c4, a2, c1, x1") * (*ta2_)("c3, c4");
  madness::World::get_default().gop.fence();
}

void Task205::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c3, a4, c1, x1") * (*ta2_)("a4, a2") * (-1);
  madness::World::get_default().gop.fence();
}

void Task206::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c1, a2, c4, x1") * (*ta2_)("c3, c4") * (-2);
  madness::World::get_default().gop.fence();
}

void Task207::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c1, a4, c3, x1") * (*ta2_)("a4, a2") * 2;
  madness::World::get_default().gop.fence();
}

void Task208::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c5, a2, c4, x1") * (*ta2_)("c1, c5, c3, c4") * 2;
  madness::World::get_default().gop.fence();
}

void Task209::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c4, a2, c5, x1") * (*ta2_)("c1, c5, c3, c4") * (-1);
  madness::World::get_default().gop.fence();
}

void Task210::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c5, a4, c3, x1") * (*ta2_)("c1, c5, a4, a2") * (-2);
  madness::World::get_default().gop.fence();
}

void Task211::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c4, a5, c3, x1") * (*ta2_)("c1, a2, a5, c4") * 4;
  madness::World::get_default().gop.fence();
}

void Task212::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c3, a4, c5, x1") * (*ta2_)("c1, c5, a4, a2");
  madness::World::get_default().gop.fence();
}

void Task213::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c3, a5, c4, x1") * (*ta2_)("c1, a2, a5, c4") * (-2);
  madness::World::get_default().gop.fence();
}

void Task214::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c5, a4, c1, x1") * (*ta2_)("c3, c5, a4, a2");
  madness::World::get_default().gop.fence();
}

void Task215::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c4, a5, c1, x1") * (*ta2_)("c3, a2, a5, c4") * (-2);
  madness::World::get_default().gop.fence();
}

void Task216::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c1, a4, c5, x1") * (*ta2_)("c3, c5, a4, a2") * (-2);
  madness::World::get_default().gop.fence();
}

void Task217::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c1, a5, c4, x1") * (*ta2_)("c3, a2, a5, c4");
  madness::World::get_default().gop.fence();
}

void Task218::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c3, a5, c4, a2") * (*ta2_)("a5, x1, c1, c4");
  madness::World::get_default().gop.fence();
}

void Task219::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, x1, c1, c4") += (*ta1_)("a5, x1, c1, c4") * (-4)
     + (*ta1_)("c1, x1, a5, c4") * 2;
  madness::World::get_default().gop.fence();
}

void Task220::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c3, a2, c4, a5") * (*ta2_)("a5, x1, c1, c4");
  madness::World::get_default().gop.fence();
}

void Task221::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, x1, c1, c4") += (*ta1_)("a5, x1, c1, c4") * 2
     + (*ta1_)("c1, x1, a5, c4") * (-4);
  madness::World::get_default().gop.fence();
}

void Task222::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c1, a5, c4, a2") * (*ta2_)("a5, x1, c3, c4");
  madness::World::get_default().gop.fence();
}

void Task223::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, x1, c3, c4") += (*ta1_)("a5, x1, c3, c4") * 2
     + (*ta1_)("c3, x1, a5, c4") * (-4);
  madness::World::get_default().gop.fence();
}

void Task224::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c1, a2, c4, a5") * (*ta2_)("a5, x1, c3, c4");
  madness::World::get_default().gop.fence();
}

void Task225::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("a5, x1, c3, c4") += (*ta1_)("a5, x1, c3, c4") * (-4)
     + (*ta1_)("c3, x1, a5, c4") * 8;
  madness::World::get_default().gop.fence();
}

void Task226::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c1, a5, c3, a4") * (*ta2_)("a5, x1, a4, a2") * (-2);
  madness::World::get_default().gop.fence();
}

void Task227::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, a2, c3, x1") += (*ta1_)("c1, a4, c3, a5") * (*ta2_)("a5, x1, a4, a2") * 4;
  madness::World::get_default().gop.fence();
}

void Task228::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, x0, a2") += (*ta1_)("c1, x1") * (*ta2_)("a2, c3, x1, x0");
  madness::World::get_default().gop.fence();
}

void Task229::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c3, x1, x0") += (*ta1_)("x3, x1, x0, x2") * (*ta2_)("x3, a2, c3, x2");
  madness::World::get_default().gop.fence();
}

void Task230::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c3, x1, x0") += (*ta1_)("x3, x2, x0, x1") * (*ta2_)("c3, a2, x3, x2") * (-1);
  madness::World::get_default().gop.fence();
}

void Task231::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, x0, a2") += (*ta1_)("c3, x1") * (*ta2_)("a2, c1, x0, x1");
  madness::World::get_default().gop.fence();
}

void Task232::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, c1, x0, x1") += (*ta1_)("x3, x2, x0, x1") * (*ta2_)("x3, a2, c1, x2");
  madness::World::get_default().gop.fence();
}

void Task233::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("x3, a2, c1, x2") += (*ta1_)("x3, a2, c1, x2") * (-1)
     + (*ta1_)("c1, a2, x3, x2") * 2;
  madness::World::get_default().gop.fence();
}

void Task234::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, x0, a2") += (*ta1_)("c1, a4, c3, a2") * (*ta2_)("a4, x0");
  madness::World::get_default().gop.fence();
}

void Task235::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a4, x0") += (*ta1_)("x0, x1") * (*ta2_)("a4, x1") * (-2);
  madness::World::get_default().gop.fence();
}

void Task236::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a4, x0") += (*ta1_)("x0, x3, x2, x1") * (*ta2_)("a4, x3, x2, x1") * (-1);
  madness::World::get_default().gop.fence();
}

void Task237::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a4, x0") += (*ta1_)("x3, x2, x0, x1") * (*ta2_)("x3, x2, a4, x1") * (-1);
  madness::World::get_default().gop.fence();
}

void Task238::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, x0, a2") += (*ta1_)("c1, a2, c3, a4") * (*ta2_)("a4, x0");
  madness::World::get_default().gop.fence();
}

void Task239::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a4, x0") += (*ta1_)("x0, x1") * (*ta2_)("a4, x1") * 4;
  madness::World::get_default().gop.fence();
}

void Task240::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a4, x0") += (*ta1_)("x0, x3, x2, x1") * (*ta2_)("a4, x3, x2, x1") * 2;
  madness::World::get_default().gop.fence();
}

void Task241::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a4, x0") += (*ta1_)("x3, x2, x0, x1") * (*ta2_)("x3, x2, a4, x1") * 2;
  madness::World::get_default().gop.fence();
}

void Task242::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, x0, a2") += (*ta1_)("c1, x5, c3, x4") * (*ta2_)("a2, x5, x0, x4");
  madness::World::get_default().gop.fence();
}

void Task243::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, x5, x0, x4") += (*ta1_)("x3, x5, x0, x4, x2, x1") * (*ta2_)("x3, a2, x2, x1") * (-1);
  madness::World::get_default().gop.fence();
}

void Task244::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("a2, x5, x0, x4") += (*ta1_)("x1, x5, x0, x4, x3, x2") * (*ta2_)("x3, x2, x1, a2") * (-1);
  madness::World::get_default().gop.fence();
}

void Task245::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, x0, a2") += (*ta1_)("x1, c4, c1, a2") * (*ta2_)("c3, c4, x0, x1");
  madness::World::get_default().gop.fence();
}

void Task246::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c3, c4, x0, x1") += (*ta1_)("x0, x3, x1, x2") * (*ta2_)("c3, x3, c4, x2") * 4;
  madness::World::get_default().gop.fence();
}

void Task247::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, x0, a2") += (*ta1_)("x1, a2, c1, c4") * (*ta2_)("c3, c4, x0, x1");
  madness::World::get_default().gop.fence();
}

void Task248::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  ta1_->init();
  madness::World::get_default().gop.fence();
  (*ta0_)("c3, c4, x0, x1") += (*ta1_)("x0, x3, x1, x2") * (*ta2_)("c3, x3, c4, x2") * (-2);
  madness::World::get_default().gop.fence();
}

void Task249::compute_() {
  if (!ta0_->initialized())
    ta0_->fill_local(0.0);
  madness::World::get_default().gop.fence();
  (*ta0_)("c1, c3, x0, a2") += (*ta1_)("x1, c4, c3, a2") * (*ta2_)("c1, c4, x0, x1");
  madness::World::get_default().gop.fence();
}

#endif
