//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: CASPT2_tasks8.cc
// Copyright (C) 2014 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
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

#include <bagel_config.h>
#ifdef COMPILE_SMITH

#include <src/smith/caspt2/CASPT2_tasks8.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::CASPT2;

void Task350::Task_local::compute() {
  const Index x1 = b(0);
  const Index a2 = b(1);
  // tensor label: I407
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a2)]);
  std::fill_n(odata.get(), out()->get_size(x1, a2), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, a2), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& c3 : *range_[0]) {
      for (auto& c1 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
        sort_indices<3,2,0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        // tensor label: I408
        std::unique_ptr<double[]> i1data = in(1)->get_block(c1, c3, x1, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, c3, x1, x0)]);
        sort_indices<3,1,0,2,0,1,1,1>(i1data, i1data_sorted, c1.size(), c3.size(), x1.size(), x0.size());
        dgemm_("T", "N", a2.size(), x1.size(), c1.size()*c3.size()*x0.size(),
               1.0, i0data_sorted, c1.size()*c3.size()*x0.size(), i1data_sorted, c1.size()*c3.size()*x0.size(),
               1.0, odata_sorted, a2.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, a2.size(), x1.size());
  out()->add_block(odata, x1, a2);
}

void Task351::Task_local::compute() {
  const Index c1 = b(0);
  const Index c3 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I408
  std::unique_ptr<double[]> odata(new double[out()->get_size(c1, c3, x1, x0)]);
  std::fill_n(odata.get(), out()->get_size(c1, c3, x1, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c1, c3, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c3, x1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma3
      std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x3, x0, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x3, x0, x2)]);
      sort_indices<1,3,0,2,0,1,1,1>(i0data, i0data_sorted, x1.size(), x3.size(), x0.size(), x2.size());
      // tensor label: t2
      std::unique_ptr<double[]> i1data = in(1)->get_block(c1, x3, c3, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, x3, c3, x2)]);
      sort_indices<1,3,0,2,0,1,-2,1>(i1data, i1data_sorted, c1.size(), x3.size(), c3.size(), x2.size());
      dgemm_("T", "N", x1.size()*x0.size(), c1.size()*c3.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), c1.size(), c3.size());
  out()->add_block(odata, c1, c3, x1, x0);
}

void Task352::Task_local::compute() {
  const Index a2 = b(0);
  const Index c1 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c1)]);
  std::fill_n(odata.get(), out()->get_size(a2, c1), 0.0);
  {
    // tensor label: I410
    std::unique_ptr<double[]> i0data = in(0)->get_block(a2, c1);
    sort_indices<0,1,1,1,1,1>(i0data, odata, a2.size(), c1.size());
  }
  out()->add_block(odata, a2, c1);
}

void Task353::Task_local::compute() {
  const Index a2 = b(0);
  const Index c1 = b(1);
  // tensor label: I410
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c1)]);
  std::fill_n(odata.get(), out()->get_size(a2, c1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c1), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& c3 : *range_[0]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x0);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
      sort_indices<3,2,0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
      // tensor label: I411
      std::unique_ptr<double[]> i1data = in(1)->get_block(c3, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, x0)]);
      sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, c3.size(), x0.size());
      dgemm_("T", "N", a2.size()*c1.size(), 1, c3.size()*x0.size(),
             1.0, i0data_sorted, c3.size()*x0.size(), i1data_sorted, c3.size()*x0.size(),
             1.0, odata_sorted, a2.size()*c1.size());
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c1.size(), a2.size());
  out()->add_block(odata, a2, c1);
}

void Task354::Task_local::compute() {
  const Index c3 = b(0);
  const Index x0 = b(1);
  // tensor label: I411
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, x0)]);
  std::fill_n(odata.get(), out()->get_size(c3, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: Gamma12
        std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x0, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x2, x0, x1)]);
        sort_indices<0,1,3,2,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), x0.size(), x1.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(1)->get_block(x3, x2, c3, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, x2, c3, x1)]);
        sort_indices<0,1,3,2,0,1,2,1>(i1data, i1data_sorted, x3.size(), x2.size(), c3.size(), x1.size());
        dgemm_("T", "N", x0.size(), c3.size(), x3.size()*x2.size()*x1.size(),
               1.0, i0data_sorted, x3.size()*x2.size()*x1.size(), i1data_sorted, x3.size()*x2.size()*x1.size(),
               1.0, odata_sorted, x0.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x0.size(), c3.size());
  out()->add_block(odata, c3, x0);
}

void Task355::Task_local::compute() {
  const Index a2 = b(0);
  const Index c3 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c3)]);
  std::fill_n(odata.get(), out()->get_size(a2, c3), 0.0);
  {
    // tensor label: I413
    std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2);
    sort_indices<1,0,1,1,1,1>(i0data, odata, c3.size(), a2.size());
  }
  out()->add_block(odata, a2, c3);
}

void Task356::Task_local::compute() {
  const Index c3 = b(0);
  const Index a2 = b(1);
  // tensor label: I413
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a2)]);
  std::fill_n(odata.get(), out()->get_size(c3, a2), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, a2), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& c1 : *range_[0]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x0);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
      sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
      // tensor label: I414
      std::unique_ptr<double[]> i1data = in(1)->get_block(c1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, x0)]);
      sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, c1.size(), x0.size());
      dgemm_("T", "N", c3.size()*a2.size(), 1, c1.size()*x0.size(),
             1.0, i0data_sorted, c1.size()*x0.size(), i1data_sorted, c1.size()*x0.size(),
             1.0, odata_sorted, c3.size()*a2.size());
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, a2.size(), c3.size());
  out()->add_block(odata, c3, a2);
}

void Task357::Task_local::compute() {
  const Index c1 = b(0);
  const Index x0 = b(1);
  // tensor label: I414
  std::unique_ptr<double[]> odata(new double[out()->get_size(c1, x0)]);
  std::fill_n(odata.get(), out()->get_size(c1, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: Gamma12
        std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x0, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x2, x0, x1)]);
        sort_indices<0,1,3,2,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), x0.size(), x1.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(1)->get_block(x3, x2, c1, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, x2, c1, x1)]);
        sort_indices<0,1,3,2,0,1,-1,1>(i1data, i1data_sorted, x3.size(), x2.size(), c1.size(), x1.size());
        dgemm_("T", "N", x0.size(), c1.size(), x3.size()*x2.size()*x1.size(),
               1.0, i0data_sorted, x3.size()*x2.size()*x1.size(), i1data_sorted, x3.size()*x2.size()*x1.size(),
               1.0, odata_sorted, x0.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x0.size(), c1.size());
  out()->add_block(odata, c1, x0);
}

void Task358::Task_local::compute() {
  const Index c3 = b(0);
  const Index a2 = b(1);
  // tensor label: I413
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a2)]);
  std::fill_n(odata.get(), out()->get_size(c3, a2), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, a2), 0.0);
  for (auto& a4 : *range_[2]) {
    for (auto& c1 : *range_[0]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, a4);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, a4)]);
      sort_indices<3,0,1,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), a4.size());
      // tensor label: I570
      std::unique_ptr<double[]> i1data = in(1)->get_block(a4, c1);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a4, c1)]);
      sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, a4.size(), c1.size());
      dgemm_("T", "N", c3.size()*a2.size(), 1, a4.size()*c1.size(),
             1.0, i0data_sorted, a4.size()*c1.size(), i1data_sorted, a4.size()*c1.size(),
             1.0, odata_sorted, c3.size()*a2.size());
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, a2.size(), c3.size());
  out()->add_block(odata, c3, a2);
}

void Task359::Task_local::compute() {
  const Index a4 = b(0);
  const Index c1 = b(1);
  // tensor label: I570
  std::unique_ptr<double[]> odata(new double[out()->get_size(a4, c1)]);
  std::fill_n(odata.get(), out()->get_size(a4, c1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a4, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a4, c1), 0.0);
  for (auto& x1 : *range_[1]) {
    for (auto& x0 : *range_[1]) {
      // tensor label: Gamma38
      std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0)]);
      sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size());
      // tensor label: I571
      std::unique_ptr<double[]> i1data = in(1)->get_block(x1, a4, c1, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, a4, c1, x0)]);
      sort_indices<0,3,1,2,0,1,1,1>(i1data, i1data_sorted, x1.size(), a4.size(), c1.size(), x0.size());
      dgemm_("T", "N", 1, a4.size()*c1.size(), x1.size()*x0.size(),
             1.0, i0data_sorted, x1.size()*x0.size(), i1data_sorted, x1.size()*x0.size(),
             1.0, odata_sorted, 1);
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, a4.size(), c1.size());
  out()->add_block(odata, a4, c1);
}

void Task360::Task_local::compute() {
  const Index x1 = b(0);
  const Index a4 = b(1);
  const Index c1 = b(2);
  const Index x0 = b(3);
  // tensor label: I571
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a4, c1, x0)]);
  std::fill_n(odata.get(), out()->get_size(x1, a4, c1, x0), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, a4, c1, x0);
    sort_indices<0,1,2,3,1,1,2,1>(i0data, odata, x1.size(), a4.size(), c1.size(), x0.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a4, x1, x0);
    sort_indices<2,1,0,3,1,1,-4,1>(i1data, odata, c1.size(), a4.size(), x1.size(), x0.size());
  }
  out()->add_block(odata, x1, a4, c1, x0);
}

void Task361::Task_local::compute() {
  const Index x1 = b(0);
  const Index x2 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, x2)]);
  std::fill_n(odata.get(), out()->get_size(x1, x2), 0.0);
  {
    // tensor label: I416
    std::unique_ptr<double[]> i0data = in(0)->get_block(x2, x1);
    sort_indices<1,0,1,1,1,1>(i0data, odata, x2.size(), x1.size());
  }
  out()->add_block(odata, x1, x2);
}

void Task362::Task_local::compute() {
  const Index x2 = b(0);
  const Index x1 = b(1);
  // tensor label: I416
  std::unique_ptr<double[]> odata(new double[out()->get_size(x2, x1)]);
  std::fill_n(odata.get(), out()->get_size(x2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& x3 : *range_[1]) {
      // tensor label: Gamma152
      std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x3, x2, x1);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x3, x2, x1)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x0.size(), x3.size(), x2.size(), x1.size());
      // tensor label: I417
      std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x3);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x3)]);
      sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, x0.size(), x3.size());
      dgemm_("T", "N", x2.size()*x1.size(), 1, x0.size()*x3.size(),
             1.0, i0data_sorted, x0.size()*x3.size(), i1data_sorted, x0.size()*x3.size(),
             1.0, odata_sorted, x2.size()*x1.size());
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x2.size(), x1.size());
  out()->add_block(odata, x2, x1);
}

void Task363::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  // tensor label: I417
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x3)]);
  std::fill_n(odata.get(), out()->get_size(x0, x3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x3), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c1 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2, c1, x3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a2, c1, x3)]);
        sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c3.size(), a2.size(), c1.size(), x3.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
        sort_indices<2,1,0,3,0,1,-1,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        dgemm_("T", "N", x3.size(), x0.size(), c3.size()*a2.size()*c1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c1.size(), i1data_sorted, c3.size()*a2.size()*c1.size(),
               1.0, odata_sorted, x3.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x3.size(), x0.size());
  out()->add_block(odata, x0, x3);
}

void Task364::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  // tensor label: I417
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x3)]);
  std::fill_n(odata.get(), out()->get_size(x0, x3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x3), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c3 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x3)]);
        sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x3.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
        sort_indices<0,1,2,3,0,1,2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        dgemm_("T", "N", x3.size(), x0.size(), c3.size()*a2.size()*c1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c1.size(), i1data_sorted, c3.size()*a2.size()*c1.size(),
               1.0, odata_sorted, x3.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x3.size(), x0.size());
  out()->add_block(odata, x0, x3);
}

void Task365::Task_local::compute() {
  const Index x2 = b(0);
  const Index x1 = b(1);
  // tensor label: I416
  std::unique_ptr<double[]> odata(new double[out()->get_size(x2, x1)]);
  std::fill_n(odata.get(), out()->get_size(x2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, x1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x0 : *range_[1]) {
      // tensor label: Gamma60
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x0, x2, x1);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x0, x2, x1)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x0.size(), x2.size(), x1.size());
      // tensor label: I626
      std::unique_ptr<double[]> i1data = in(1)->get_block(x0, x3);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, x3)]);
      sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, x0.size(), x3.size());
      dgemm_("T", "N", x2.size()*x1.size(), 1, x0.size()*x3.size(),
             1.0, i0data_sorted, x0.size()*x3.size(), i1data_sorted, x0.size()*x3.size(),
             1.0, odata_sorted, x2.size()*x1.size());
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x2.size(), x1.size());
  out()->add_block(odata, x2, x1);
}

void Task366::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  // tensor label: I626
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x3)]);
  std::fill_n(odata.get(), out()->get_size(x0, x3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x3), 0.0);
  for (auto& a3 : *range_[2]) {
    for (auto& c2 : *range_[0]) {
      for (auto& a1 : *range_[2]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a3, c2, a1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, a3, c2, a1)]);
        sort_indices<1,2,3,0,0,1,1,1>(i0data, i0data_sorted, x3.size(), a3.size(), c2.size(), a1.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(0)->get_block(x0, a1, c2, a3);
        std::unique_ptr<double[]> i1data_sorted(new double[in(0)->get_size(x0, a1, c2, a3)]);
        sort_indices<3,2,1,0,0,1,-1,1>(i1data, i1data_sorted, x0.size(), a1.size(), c2.size(), a3.size());
        dgemm_("T", "N", x3.size(), x0.size(), a3.size()*c2.size()*a1.size(),
               1.0, i0data_sorted, a3.size()*c2.size()*a1.size(), i1data_sorted, a3.size()*c2.size()*a1.size(),
               1.0, odata_sorted, x3.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x3.size(), x0.size());
  out()->add_block(odata, x0, x3);
}

void Task367::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  // tensor label: I626
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x3)]);
  std::fill_n(odata.get(), out()->get_size(x0, x3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x3), 0.0);
  for (auto& a1 : *range_[2]) {
    for (auto& c2 : *range_[0]) {
      for (auto& a3 : *range_[2]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a1, c2, a3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, a1, c2, a3)]);
        sort_indices<1,2,3,0,0,1,1,1>(i0data, i0data_sorted, x3.size(), a1.size(), c2.size(), a3.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(0)->get_block(x0, a1, c2, a3);
        std::unique_ptr<double[]> i1data_sorted(new double[in(0)->get_size(x0, a1, c2, a3)]);
        sort_indices<1,2,3,0,0,1,2,1>(i1data, i1data_sorted, x0.size(), a1.size(), c2.size(), a3.size());
        dgemm_("T", "N", x3.size(), x0.size(), a3.size()*c2.size()*a1.size(),
               1.0, i0data_sorted, a3.size()*c2.size()*a1.size(), i1data_sorted, a3.size()*c2.size()*a1.size(),
               1.0, odata_sorted, x3.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x3.size(), x0.size());
  out()->add_block(odata, x0, x3);
}

void Task368::Task_local::compute() {
  const Index c4 = b(0);
  const Index c1 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(c4, c1)]);
  std::fill_n(odata.get(), out()->get_size(c4, c1), 0.0);
  {
    // tensor label: I422
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, c4);
    sort_indices<1,0,1,1,1,1>(i0data, odata, c1.size(), c4.size());
  }
  out()->add_block(odata, c4, c1);
}

void Task369::Task_local::compute() {
  const Index c1 = b(0);
  const Index c4 = b(1);
  // tensor label: I422
  std::unique_ptr<double[]> odata(new double[out()->get_size(c1, c4)]);
  std::fill_n(odata.get(), out()->get_size(c1, c4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c1, c4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c4), 0.0);
  for (auto& a2 : *range_[2]) {
    for (auto& c3 : *range_[0]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c4, a2, c3, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c4, a2, c3, x1)]);
        sort_indices<1,2,3,0,0,1,1,1>(i0data, i0data_sorted, c4.size(), a2.size(), c3.size(), x1.size());
        // tensor label: I423
        std::unique_ptr<double[]> i1data = in(1)->get_block(c3, a2, c1, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, a2, c1, x1)]);
        sort_indices<1,0,3,2,0,1,1,1>(i1data, i1data_sorted, c3.size(), a2.size(), c1.size(), x1.size());
        dgemm_("T", "N", c4.size(), c1.size(), c3.size()*a2.size()*x1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*x1.size(), i1data_sorted, c3.size()*a2.size()*x1.size(),
               1.0, odata_sorted, c4.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c4.size(), c1.size());
  out()->add_block(odata, c1, c4);
}

void Task370::Task_local::compute() {
  const Index c3 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x1 = b(3);
  // tensor label: I423
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma16
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<3,0,1,2,0,1,-2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), c3.size()*a2.size()*c1.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), c1.size(), a2.size(), c3.size());
  out()->add_block(odata, c3, a2, c1, x1);
}

void Task371::Task_local::compute() {
  const Index c1 = b(0);
  const Index c4 = b(1);
  // tensor label: I422
  std::unique_ptr<double[]> odata(new double[out()->get_size(c1, c4)]);
  std::fill_n(odata.get(), out()->get_size(c1, c4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c1, c4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c1, c4), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2, c4, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a2, c4, x1)]);
        sort_indices<0,1,3,2,0,1,1,1>(i0data, i0data_sorted, c3.size(), a2.size(), c4.size(), x1.size());
        // tensor label: I426
        std::unique_ptr<double[]> i1data = in(1)->get_block(c3, a2, c1, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, a2, c1, x1)]);
        sort_indices<0,1,3,2,0,1,1,1>(i1data, i1data_sorted, c3.size(), a2.size(), c1.size(), x1.size());
        dgemm_("T", "N", c4.size(), c1.size(), c3.size()*a2.size()*x1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*x1.size(), i1data_sorted, c3.size()*a2.size()*x1.size(),
               1.0, odata_sorted, c4.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c4.size(), c1.size());
  out()->add_block(odata, c1, c4);
}

void Task372::Task_local::compute() {
  const Index c3 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x1 = b(3);
  // tensor label: I426
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma16
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<3,0,1,2,0,1,1,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), c3.size()*a2.size()*c1.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), c1.size(), a2.size(), c3.size());
  out()->add_block(odata, c3, a2, c1, x1);
}

void Task373::Task_local::compute() {
  const Index c4 = b(0);
  const Index c3 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(c4, c3)]);
  std::fill_n(odata.get(), out()->get_size(c4, c3), 0.0);
  {
    // tensor label: I428
    std::unique_ptr<double[]> i0data = in(0)->get_block(c3, c4);
    sort_indices<1,0,1,1,1,1>(i0data, odata, c3.size(), c4.size());
  }
  out()->add_block(odata, c4, c3);
}

void Task374::Task_local::compute() {
  const Index c3 = b(0);
  const Index c4 = b(1);
  // tensor label: I428
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, c4)]);
  std::fill_n(odata.get(), out()->get_size(c3, c4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, c4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, c4), 0.0);
  for (auto& a2 : *range_[2]) {
    for (auto& c1 : *range_[0]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c4, a2, c1, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c4, a2, c1, x1)]);
        sort_indices<1,2,3,0,0,1,1,1>(i0data, i0data_sorted, c4.size(), a2.size(), c1.size(), x1.size());
        // tensor label: I429
        std::unique_ptr<double[]> i1data = in(1)->get_block(c3, a2, c1, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, a2, c1, x1)]);
        sort_indices<1,2,3,0,0,1,1,1>(i1data, i1data_sorted, c3.size(), a2.size(), c1.size(), x1.size());
        dgemm_("T", "N", c4.size(), c3.size(), a2.size()*c1.size()*x1.size(),
               1.0, i0data_sorted, a2.size()*c1.size()*x1.size(), i1data_sorted, a2.size()*c1.size()*x1.size(),
               1.0, odata_sorted, c4.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c4.size(), c3.size());
  out()->add_block(odata, c3, c4);
}

void Task375::Task_local::compute() {
  const Index c3 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x1 = b(3);
  // tensor label: I429
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma16
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<3,0,1,2,0,1,1,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), c3.size()*a2.size()*c1.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), c1.size(), a2.size(), c3.size());
  out()->add_block(odata, c3, a2, c1, x1);
}

void Task376::Task_local::compute() {
  const Index c3 = b(0);
  const Index c4 = b(1);
  // tensor label: I428
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, c4)]);
  std::fill_n(odata.get(), out()->get_size(c3, c4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, c4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, c4), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c4, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c4, x1)]);
        sort_indices<0,1,3,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c4.size(), x1.size());
        // tensor label: I435
        std::unique_ptr<double[]> i1data = in(1)->get_block(c3, a2, c1, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, a2, c1, x1)]);
        sort_indices<2,1,3,0,0,1,1,1>(i1data, i1data_sorted, c3.size(), a2.size(), c1.size(), x1.size());
        dgemm_("T", "N", c4.size(), c3.size(), a2.size()*c1.size()*x1.size(),
               1.0, i0data_sorted, a2.size()*c1.size()*x1.size(), i1data_sorted, a2.size()*c1.size()*x1.size(),
               1.0, odata_sorted, c4.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c4.size(), c3.size());
  out()->add_block(odata, c3, c4);
}

void Task377::Task_local::compute() {
  const Index c3 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x1 = b(3);
  // tensor label: I435
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma16
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<3,0,1,2,0,1,-2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), c3.size()*a2.size()*c1.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), c1.size(), a2.size(), c3.size());
  out()->add_block(odata, c3, a2, c1, x1);
}

void Task378::Task_local::compute() {
  const Index a2 = b(0);
  const Index a4 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, a4)]);
  std::fill_n(odata.get(), out()->get_size(a2, a4), 0.0);
  {
    // tensor label: I431
    std::unique_ptr<double[]> i0data = in(0)->get_block(a2, a4);
    sort_indices<0,1,1,1,1,1>(i0data, odata, a2.size(), a4.size());
  }
  out()->add_block(odata, a2, a4);
}

void Task379::Task_local::compute() {
  const Index a2 = b(0);
  const Index a4 = b(1);
  // tensor label: I431
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, a4)]);
  std::fill_n(odata.get(), out()->get_size(a2, a4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, a4), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& c1 : *range_[0]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a4, c1, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a4, c1, x1)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), a4.size(), c1.size(), x1.size());
        // tensor label: I432
        std::unique_ptr<double[]> i1data = in(1)->get_block(c3, a2, c1, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, a2, c1, x1)]);
        sort_indices<0,2,3,1,0,1,1,1>(i1data, i1data_sorted, c3.size(), a2.size(), c1.size(), x1.size());
        dgemm_("T", "N", a4.size(), a2.size(), c3.size()*c1.size()*x1.size(),
               1.0, i0data_sorted, c3.size()*c1.size()*x1.size(), i1data_sorted, c3.size()*c1.size()*x1.size(),
               1.0, odata_sorted, a4.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, a4.size(), a2.size());
  out()->add_block(odata, a2, a4);
}

void Task380::Task_local::compute() {
  const Index c3 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x1 = b(3);
  // tensor label: I432
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma16
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<3,0,1,2,0,1,-1,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), c3.size()*a2.size()*c1.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), c1.size(), a2.size(), c3.size());
  out()->add_block(odata, c3, a2, c1, x1);
}

void Task381::Task_local::compute() {
  const Index a2 = b(0);
  const Index a4 = b(1);
  // tensor label: I431
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, a4)]);
  std::fill_n(odata.get(), out()->get_size(a2, a4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, a4), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& c3 : *range_[0]) {
      for (auto& x1 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a4, c3, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a4, c3, x1)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a4.size(), c3.size(), x1.size());
        // tensor label: I438
        std::unique_ptr<double[]> i1data = in(1)->get_block(c3, a2, c1, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, a2, c1, x1)]);
        sort_indices<2,0,3,1,0,1,1,1>(i1data, i1data_sorted, c3.size(), a2.size(), c1.size(), x1.size());
        dgemm_("T", "N", a4.size(), a2.size(), c3.size()*c1.size()*x1.size(),
               1.0, i0data_sorted, c3.size()*c1.size()*x1.size(), i1data_sorted, c3.size()*c1.size()*x1.size(),
               1.0, odata_sorted, a4.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, a4.size(), a2.size());
  out()->add_block(odata, a2, a4);
}

void Task382::Task_local::compute() {
  const Index c3 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x1 = b(3);
  // tensor label: I438
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma16
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<3,0,1,2,0,1,2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), c3.size()*a2.size()*c1.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), c1.size(), a2.size(), c3.size());
  out()->add_block(odata, c3, a2, c1, x1);
}

void Task383::Task_local::compute() {
  const Index x1 = b(0);
  const Index c1 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, c1)]);
  std::fill_n(odata.get(), out()->get_size(x1, c1), 0.0);
  {
    // tensor label: I440
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, c1);
    sort_indices<0,1,1,1,1,1>(i0data, odata, x1.size(), c1.size());
  }
  out()->add_block(odata, x1, c1);
}

void Task384::Task_local::compute() {
  const Index x1 = b(0);
  const Index c1 = b(1);
  // tensor label: I440
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, c1)]);
  std::fill_n(odata.get(), out()->get_size(x1, c1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x1, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, c1), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& c3 : *range_[0]) {
      for (auto& a2 : *range_[2]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
        sort_indices<3,2,1,0,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        // tensor label: I441
        std::unique_ptr<double[]> i1data = in(1)->get_block(a2, c3, x1, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a2, c3, x1, x0)]);
        sort_indices<3,1,0,2,0,1,1,1>(i1data, i1data_sorted, a2.size(), c3.size(), x1.size(), x0.size());
        dgemm_("T", "N", c1.size(), x1.size(), a2.size()*c3.size()*x0.size(),
               1.0, i0data_sorted, a2.size()*c3.size()*x0.size(), i1data_sorted, a2.size()*c3.size()*x0.size(),
               1.0, odata_sorted, c1.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c1.size(), x1.size());
  out()->add_block(odata, x1, c1);
}

void Task385::Task_local::compute() {
  const Index a2 = b(0);
  const Index c3 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I441
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c3, x1, x0)]);
  std::fill_n(odata.get(), out()->get_size(a2, c3, x1, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c3, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c3, x1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma22
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x1, x0, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x1, x0, x2)]);
      sort_indices<0,3,1,2,0,1,1,1>(i0data, i0data_sorted, x3.size(), x1.size(), x0.size(), x2.size());
      // tensor label: t2
      std::unique_ptr<double[]> i1data = in(1)->get_block(x3, a2, c3, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, a2, c3, x2)]);
      sort_indices<0,3,1,2,0,1,1,1>(i1data, i1data_sorted, x3.size(), a2.size(), c3.size(), x2.size());
      dgemm_("T", "N", x1.size()*x0.size(), a2.size()*c3.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size(), a2.size(), c3.size());
  out()->add_block(odata, a2, c3, x1, x0);
}

void Task386::Task_local::compute() {
  const Index a2 = b(0);
  const Index c3 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I441
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c3, x1, x0)]);
  std::fill_n(odata.get(), out()->get_size(a2, c3, x1, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c3, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c3, x1, x0), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma12
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x0, x1);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x2, x0, x1)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), x0.size(), x1.size());
      // tensor label: t2
      std::unique_ptr<double[]> i1data = in(1)->get_block(c3, a2, x3, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, a2, x3, x2)]);
      sort_indices<2,3,0,1,0,1,-1,1>(i1data, i1data_sorted, c3.size(), a2.size(), x3.size(), x2.size());
      dgemm_("T", "N", x0.size()*x1.size(), c3.size()*a2.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x0.size()*x1.size());
    }
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), c3.size(), a2.size());
  out()->add_block(odata, a2, c3, x1, x0);
}

void Task387::Task_local::compute() {
  const Index x1 = b(0);
  const Index c3 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, c3)]);
  std::fill_n(odata.get(), out()->get_size(x1, c3), 0.0);
  {
    // tensor label: I443
    std::unique_ptr<double[]> i0data = in(0)->get_block(x1, c3);
    sort_indices<0,1,1,1,1,1>(i0data, odata, x1.size(), c3.size());
  }
  out()->add_block(odata, x1, c3);
}

void Task388::Task_local::compute() {
  const Index x1 = b(0);
  const Index c3 = b(1);
  // tensor label: I443
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, c3)]);
  std::fill_n(odata.get(), out()->get_size(x1, c3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x1, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, c3), 0.0);
  for (auto& x0 : *range_[1]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c1 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
        sort_indices<3,1,0,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        // tensor label: I444
        std::unique_ptr<double[]> i1data = in(1)->get_block(a2, c1, x0, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a2, c1, x0, x1)]);
        sort_indices<2,0,1,3,0,1,1,1>(i1data, i1data_sorted, a2.size(), c1.size(), x0.size(), x1.size());
        dgemm_("T", "N", c3.size(), x1.size(), a2.size()*c1.size()*x0.size(),
               1.0, i0data_sorted, a2.size()*c1.size()*x0.size(), i1data_sorted, a2.size()*c1.size()*x0.size(),
               1.0, odata_sorted, c3.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c3.size(), x1.size());
  out()->add_block(odata, x1, c3);
}

void Task389::Task_local::compute() {
  const Index a2 = b(0);
  const Index c1 = b(1);
  const Index x0 = b(2);
  const Index x1 = b(3);
  // tensor label: I444
  std::unique_ptr<double[]> odata(new double[out()->get_size(a2, c1, x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(a2, c1, x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a2, c1, x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a2, c1, x0, x1), 0.0);
  for (auto& x3 : *range_[1]) {
    for (auto& x2 : *range_[1]) {
      // tensor label: Gamma12
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x0, x1);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x2, x0, x1)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), x0.size(), x1.size());
      // tensor label: I445
      std::unique_ptr<double[]> i1data = in(1)->get_block(x3, a2, c1, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, a2, c1, x2)]);
      sort_indices<0,3,1,2,0,1,1,1>(i1data, i1data_sorted, x3.size(), a2.size(), c1.size(), x2.size());
      dgemm_("T", "N", x0.size()*x1.size(), a2.size()*c1.size(), x3.size()*x2.size(),
             1.0, i0data_sorted, x3.size()*x2.size(), i1data_sorted, x3.size()*x2.size(),
             1.0, odata_sorted, x0.size()*x1.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), a2.size(), c1.size());
  out()->add_block(odata, a2, c1, x0, x1);
}

void Task390::Task_local::compute() {
  const Index x3 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x2 = b(3);
  // tensor label: I445
  std::unique_ptr<double[]> odata(new double[out()->get_size(x3, a2, c1, x2)]);
  std::fill_n(odata.get(), out()->get_size(x3, a2, c1, x2), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a2, c1, x2);
    sort_indices<0,1,2,3,1,1,-1,1>(i0data, odata, x3.size(), a2.size(), c1.size(), x2.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a2, x3, x2);
    sort_indices<2,1,0,3,1,1,2,1>(i1data, odata, c1.size(), a2.size(), x3.size(), x2.size());
  }
  out()->add_block(odata, x3, a2, c1, x2);
}

void Task391::Task_local::compute() {
  const Index x1 = b(0);
  const Index a4 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a4)]);
  std::fill_n(odata.get(), out()->get_size(x1, a4), 0.0);
  {
    // tensor label: I452
    std::unique_ptr<double[]> i0data = in(0)->get_block(a4, x1);
    sort_indices<1,0,1,1,1,1>(i0data, odata, a4.size(), x1.size());
  }
  out()->add_block(odata, x1, a4);
}

void Task392::Task_local::compute() {
  const Index a4 = b(0);
  const Index x1 = b(1);
  // tensor label: I452
  std::unique_ptr<double[]> odata(new double[out()->get_size(a4, x1)]);
  std::fill_n(odata.get(), out()->get_size(a4, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a4, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a4, x1), 0.0);
  for (auto& x0 : *range_[1]) {
    // tensor label: Gamma16
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size());
    // tensor label: I453
    std::unique_ptr<double[]> i1data = in(1)->get_block(x0, a4);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, a4)]);
    sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, x0.size(), a4.size());
    dgemm_("T", "N", x1.size(), a4.size(), x0.size(),
           1.0, i0data_sorted, x0.size(), i1data_sorted, x0.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), a4.size());
  out()->add_block(odata, a4, x1);
}

void Task393::Task_local::compute() {
  const Index x0 = b(0);
  const Index a4 = b(1);
  // tensor label: I453
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, a4)]);
  std::fill_n(odata.get(), out()->get_size(x0, a4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, a4), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& c3 : *range_[0]) {
      for (auto& a2 : *range_[2]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a4, c3, a2);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a4, c3, a2)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a4.size(), c3.size(), a2.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
        sort_indices<0,2,1,3,0,1,-2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        dgemm_("T", "N", a4.size(), x0.size(), c3.size()*a2.size()*c1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c1.size(), i1data_sorted, c3.size()*a2.size()*c1.size(),
               1.0, odata_sorted, a4.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, a4.size(), x0.size());
  out()->add_block(odata, x0, a4);
}

void Task394::Task_local::compute() {
  const Index x0 = b(0);
  const Index a4 = b(1);
  // tensor label: I453
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, a4)]);
  std::fill_n(odata.get(), out()->get_size(x0, a4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, a4), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c3 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, a4);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, a4)]);
        sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), a4.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
        sort_indices<0,1,2,3,0,1,4,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        dgemm_("T", "N", a4.size(), x0.size(), c3.size()*a2.size()*c1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c1.size(), i1data_sorted, c3.size()*a2.size()*c1.size(),
               1.0, odata_sorted, a4.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, a4.size(), x0.size());
  out()->add_block(odata, x0, a4);
}

void Task395::Task_local::compute() {
  const Index a1 = b(0);
  const Index x2 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(a1, x2)]);
  std::fill_n(odata.get(), out()->get_size(a1, x2), 0.0);
  {
    // tensor label: I458
    std::unique_ptr<double[]> i0data = in(0)->get_block(x2, a1);
    sort_indices<1,0,1,1,1,1>(i0data, odata, x2.size(), a1.size());
  }
  out()->add_block(odata, a1, x2);
}

void Task396::Task_local::compute() {
  const Index x2 = b(0);
  const Index a1 = b(1);
  // tensor label: I458
  std::unique_ptr<double[]> odata(new double[out()->get_size(x2, a1)]);
  std::fill_n(odata.get(), out()->get_size(x2, a1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, a1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, a1), 0.0);
  for (auto& x1 : *range_[1]) {
    for (auto& c2 : *range_[0]) {
      for (auto& x0 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(x0, a1, c2, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, a1, c2, x1)]);
        sort_indices<3,2,0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), a1.size(), c2.size(), x1.size());
        // tensor label: I459
        std::unique_ptr<double[]> i1data = in(1)->get_block(c2, x1, x2, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c2, x1, x2, x0)]);
        sort_indices<1,0,3,2,0,1,1,1>(i1data, i1data_sorted, c2.size(), x1.size(), x2.size(), x0.size());
        dgemm_("T", "N", a1.size(), x2.size(), c2.size()*x1.size()*x0.size(),
               1.0, i0data_sorted, c2.size()*x1.size()*x0.size(), i1data_sorted, c2.size()*x1.size()*x0.size(),
               1.0, odata_sorted, a1.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, a1.size(), x2.size());
  out()->add_block(odata, x2, a1);
}

void Task397::Task_local::compute() {
  const Index c2 = b(0);
  const Index x1 = b(1);
  const Index x2 = b(2);
  const Index x0 = b(3);
  // tensor label: I459
  std::unique_ptr<double[]> odata(new double[out()->get_size(c2, x1, x2, x0)]);
  std::fill_n(odata.get(), out()->get_size(c2, x1, x2, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(c2, x1, x2, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(c2, x1, x2, x0), 0.0);
  for (auto& x5 : *range_[1]) {
    for (auto& x4 : *range_[1]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: Gamma28
        std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, x1, x3, x2, x0);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, x4, x1, x3, x2, x0)]);
        sort_indices<0,1,3,2,4,5,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), x1.size(), x3.size(), x2.size(), x0.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(1)->get_block(x5, x4, c2, x3);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x5, x4, c2, x3)]);
        sort_indices<0,1,3,2,0,1,-1,1>(i1data, i1data_sorted, x5.size(), x4.size(), c2.size(), x3.size());
        dgemm_("T", "N", x1.size()*x2.size()*x0.size(), c2.size(), x5.size()*x4.size()*x3.size(),
               1.0, i0data_sorted, x5.size()*x4.size()*x3.size(), i1data_sorted, x5.size()*x4.size()*x3.size(),
               1.0, odata_sorted, x1.size()*x2.size()*x0.size());
      }
    }
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x1.size(), x2.size(), x0.size(), c2.size());
  out()->add_block(odata, c2, x1, x2, x0);
}

void Task398::Task_local::compute() {
  const Index c3 = b(0);
  const Index x2 = b(1);
  // tensor label: r
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, x2)]);
  std::fill_n(odata.get(), out()->get_size(c3, x2), 0.0);
  {
    // tensor label: I461
    std::unique_ptr<double[]> i0data = in(0)->get_block(x2, c3);
    sort_indices<1,0,1,1,1,1>(i0data, odata, x2.size(), c3.size());
  }
  out()->add_block(odata, c3, x2);
}

void Task399::Task_local::compute() {
  const Index x2 = b(0);
  const Index c3 = b(1);
  // tensor label: I461
  std::unique_ptr<double[]> odata(new double[out()->get_size(x2, c3)]);
  std::fill_n(odata.get(), out()->get_size(x2, c3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x2, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x2, c3), 0.0);
  for (auto& a1 : *range_[2]) {
    for (auto& c2 : *range_[0]) {
      for (auto& x3 : *range_[1]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a1, c2, x3);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a1, c2, x3)]);
        sort_indices<1,2,3,0,0,1,1,1>(i0data, i0data_sorted, c3.size(), a1.size(), c2.size(), x3.size());
        // tensor label: I462
        std::unique_ptr<double[]> i1data = in(1)->get_block(c2, a1, x3, x2);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c2, a1, x3, x2)]);
        sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, c2.size(), a1.size(), x3.size(), x2.size());
        dgemm_("T", "N", c3.size(), x2.size(), c2.size()*a1.size()*x3.size(),
               1.0, i0data_sorted, c2.size()*a1.size()*x3.size(), i1data_sorted, c2.size()*a1.size()*x3.size(),
               1.0, odata_sorted, c3.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c3.size(), x2.size());
  out()->add_block(odata, x2, c3);
}

#endif