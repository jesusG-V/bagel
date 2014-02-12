//
// BAGEL - Parallel electron correlation program.
// Filename: determinants.h
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
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


#ifndef __SRC_FCI_DETERMINANTS_H
#define __SRC_FCI_DETERMINANTS_H

#include <src/ciutil/determinants_base.h>

namespace bagel {

class Determinants : public Determinants_base<FCIString>,
                     public std::enable_shared_from_this<Determinants> {
  protected:
    /* Links to other determinant spaces accessible by one annihilation or creation operation */
    std::weak_ptr<Determinants> addalpha_;
    std::weak_ptr<Determinants> addbeta_;
    std::weak_ptr<Determinants> remalpha_;
    std::weak_ptr<Determinants> rembeta_;

  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int) {
    }

  public:
    Determinants() { }
    Determinants(const int norb, const int nelea, const int neleb, const bool compress = true, const bool mute = false);
    Determinants(std::shared_ptr<const FCIString> ast, std::shared_ptr<const FCIString> bst, const bool compress = true, const bool mute = false);
    Determinants(std::shared_ptr<const CIStringSet<FCIString>> ast, std::shared_ptr<const CIStringSet<FCIString>> bst, const bool compress = true, const bool mute = false);
    Determinants(std::shared_ptr<const Determinants> o, const bool compress = true, const bool mute = false) :
      Determinants(o->norb(), o->nelea(), o->neleb(), compress, mute) {} // Shortcut to change compression of Det

    std::shared_ptr<Determinants> clone(const int nelea, const int neleb) const {
      return std::make_shared<Determinants>(norb(), nelea, neleb, false, true);
    }

    std::shared_ptr<Determinants> transpose() const { return std::make_shared<Determinants>(norb(), neleb(), nelea(), compress_, true); }

    std::pair<std::vector<std::tuple<int, int, int>>, double> spin_adapt(const int, std::bitset<nbit__>, std::bitset<nbit__>) const;

    std::shared_ptr<const Determinants> addalpha() const { return addalpha_.lock();}
    std::shared_ptr<const Determinants> remalpha() const { return remalpha_.lock();}
    std::shared_ptr<const Determinants> addbeta() const { return addbeta_.lock();}
    std::shared_ptr<const Determinants> rembeta() const { return rembeta_.lock();}
    void set_addalpha(std::shared_ptr<Determinants> o) { addalpha_ = o;}
    void set_remalpha(std::shared_ptr<Determinants> o) { remalpha_ = o;}
    void set_addbeta (std::shared_ptr<Determinants> o) { addbeta_ = o;}
    void set_rembeta (std::shared_ptr<Determinants> o) { rembeta_ = o;}

    template<int Spin>
    size_t lexical(const std::bitset<nbit__>& bit) const { return lexical_zero<Spin>(bit); }

    template<int spin>
    void link(std::shared_ptr<Determinants> odet) { bagel::link<spin, FCIString>(shared_from_this(), odet); }

    void link(std::shared_ptr<Determinants> odet, std::shared_ptr<CIStringSpace<CIStringSet<FCIString>>>, std::shared_ptr<CIStringSpace<CIStringSet<FCIString>>>);
};


}

#include <src/util/archive.h>
BOOST_CLASS_EXPORT_KEY(bagel::Determinants)

#endif
