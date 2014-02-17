//
// BAGEL - Parallel electron correlation program.
// Filename: determinants.h
// Copyright (C) 2014 Toru Shiozaki
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


#ifndef __SRC_CIUTIL_DETERMINANTS_BASE_H
#define __SRC_CIUTIL_DETERMINANTS_BASE_H

#include <src/ciutil/ciblock.h>
#include <src/ciutil/cistringset.h>
#include <src/ciutil/cistringspace.h>

namespace bagel {

template <class StringType>
class Determinants_base {
  protected:
    std::vector<std::shared_ptr<const CIBlockInfo<StringType>>> blockinfo_;

    std::shared_ptr<const CIStringSet<StringType>> alphaspaces_;
    std::shared_ptr<const CIStringSet<StringType>> betaspaces_;

    bool compress_;
    size_t size_;

    // configuration list i^dagger j compressed
    std::shared_ptr<const StringMap> phia_;
    std::shared_ptr<const StringMap> phib_;

    // configuration list i^dagger j uncompressed
    std::shared_ptr<const StringMap> phia_uncompressed_;
    std::shared_ptr<const StringMap> phib_uncompressed_;

    // configuration list i^dagger
    std::shared_ptr<const StringMap> phiupa_;
    std::shared_ptr<const StringMap> phiupb_;

    // configuration list i
    std::shared_ptr<const StringMap> phidowna_;
    std::shared_ptr<const StringMap> phidownb_;

    const std::shared_ptr<const CIBlockInfo<StringType>>& blockinfo(const int i) const { return blockinfo_[i]; }

  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int) {
    }

  public:
    Determinants_base() { }
//  Determinants_base(std::shared_ptr<const StringType> ast, std::shared_ptr<const StringType> bst, const bool compress = true, const bool mute = false) { }

    // some functions to retrieve members of CIBlockInfo<StringType>
    // block-independent members
    int norb() const { return alphaspaces_->norb(); }
    int nelea() const { return alphaspaces_->nele(); }
    int neleb() const { return betaspaces_->nele(); }
    int nspin() const { return nelea() - neleb(); }
    // block dependent members
    size_t lena() const { return alphaspaces_->size(); }
    size_t lenb() const { return betaspaces_->size(); }
    size_t size() const { return size_; }

    template<int spin>
    int sign(const std::bitset<nbit__>& bit, const size_t pos) const {
      auto iter = std::find_if(blockinfo_.begin(), blockinfo_.end(), [](const std::shared_ptr<const CIBlockInfo<StringType>>& o){ return !o->empty(); });
      return (*iter)->sign<spin>(bit, pos);
    }

    static int sign(const std::bitset<nbit__>& bit, const size_t pos0, const size_t pos1) {
      return CIBlockInfo<StringType>::sign(bit, pos0, pos1);
    }

    template <int spin>
    size_t lexical_zero(const std::bitset<nbit__>& bit)   const { return (spin == 0 ? alphaspaces_ : betaspaces_)->lexical_zero(bit); }
    template <int spin>
    size_t lexical_offset(const std::bitset<nbit__>& bit) const { return (spin == 0 ? alphaspaces_ : betaspaces_)->lexical_offset(bit); }

    const std::vector<std::shared_ptr<const CIBlockInfo<StringType>>>& blockinfo() const { return blockinfo_; }
    const std::shared_ptr<const CIStringSet<StringType>>& stringspacea() const { return alphaspaces_; }
    const std::shared_ptr<const CIStringSet<StringType>>& stringspaceb() const { return betaspaces_; }

    const std::bitset<nbit__>& string_bits_a(const size_t i) const { return alphaspaces_->strings(i); }
    const std::bitset<nbit__>& string_bits_b(const size_t i) const { return betaspaces_->strings(i); }
    const std::vector<std::bitset<nbit__>>& string_bits_a() const { return alphaspaces_->strings(); }
    const std::vector<std::bitset<nbit__>>& string_bits_b() const { return betaspaces_->strings(); }

    bool operator==(const Determinants_base<StringType>& o) const
      { return (norb() == o.norb() && nelea() == o.nelea() && neleb() == o.neleb() && compress_ == o.compress_); }

    bool compress() const { return compress_; }

    // single index goes to normal versions (compressed based on compress_)
    const std::vector<DetMap>& phia(const int i) const { return phia_->data(i); }
    const std::vector<DetMap>& phib(const int i) const { return phib_->data(i); }

    // two indices goes to uncompressed versions
    const std::vector<DetMap>& phia(const int i, const int j) const { return phia_uncompressed_->data(i + j*norb()); }
    const std::vector<DetMap>& phib(const int i, const int j) const { return phib_uncompressed_->data(i + j*norb()); }

    const std::vector<DetMap>& phiupa(const int i) const { return phiupa_->data(i); }
    const std::vector<DetMap>& phiupb(const int i) const { return phiupb_->data(i); }
    const std::vector<DetMap>& phidowna(const int i) const { return phidowna_->data(i); }
    const std::vector<DetMap>& phidownb(const int i) const { return phidownb_->data(i); }
    void set_phiupa(std::shared_ptr<const StringMap> o) { phiupa_ = o; }
    void set_phiupb(std::shared_ptr<const StringMap> o) { phiupb_ = o; }
    void set_phidowna(std::shared_ptr<const StringMap> o) { phidowna_ = o; }
    void set_phidownb(std::shared_ptr<const StringMap> o) { phidownb_ = o; }

};

template<int spin, typename StringType, class DetClass> void link(std::shared_ptr<DetClass> mdet, std::shared_ptr<DetClass> odet) {
  std::shared_ptr<DetClass> plusdet;
  std::shared_ptr<DetClass> det;

  const int de = spin == 0 ? mdet->nelea() - odet->nelea() : mdet->neleb() - odet->neleb();
  if      (de ==  1) std::tie(det, plusdet) = make_pair(odet, mdet);
  else if (de == -1) std::tie(det, plusdet) = make_pair(mdet, odet);
  else throw std::logic_error("Determinants::link failed");

  const int fac = (spin == 1 && (mdet->nelea() & 1)) ? -1 : 1;
  CIStringSpace<CIStringSet<StringType>> space{spin==0?mdet->stringspacea():mdet->stringspaceb(),
                                               spin==0?odet->stringspacea():odet->stringspaceb()};
  space.build_linkage(fac);

  // finally link
  if (spin == 0) {
    plusdet->set_remalpha(det);
    plusdet->set_phidowna(space.phidown(plusdet->stringspacea()));

    det->set_addalpha(plusdet);
    det->set_phiupa(space.phiup(det->stringspacea()));
  } else {
    plusdet->set_rembeta(det);
    plusdet->set_phidownb(space.phidown(plusdet->stringspaceb()));

    det->set_addbeta(plusdet);
    det->set_phiupb(space.phiup(det->stringspaceb()));
  }
}

}

#if 0
#include <src/util/archive.h>
BOOST_CLASS_EXPORT_KEY(bagel::Determinants)
#endif

#endif