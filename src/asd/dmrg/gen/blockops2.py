from __future__ import print_function
import sys
import math as m

class Op:
    spin = False
    creation = False

    def __init__(self, sp, cr):
        self.spin = sp
        self.creation = cr

    def conjugate(self):
        return Op(self.spin, not self.creation)

    def GammaSQ(self):
        out = "GammaSQ::"
        out += "Create" if self.creation else "Annihilate"
        out += "Alpha" if self.spin else "Beta"
        return out

    def __str__(self):
        label = "A" if self.spin else "B"
        if (self.creation):
          label += "^t"
        return label

    def __eq__(self, other):
        return self.spin==other.spin and self.creation==other.creation

    def __ne__(self, other):
        return not self==other

class OpList:
    ops = []

    def __init__(self, oplist):
        self.ops = oplist

    def conjugate(self):
        return OpList([k.conjugate() for k in reversed(self.ops)])

    def reverse(self):
        return OpList([k for k in reversed(self.ops)])

    def __str__(self):
        out = ""
        if (len(self.ops)!=0):
            for o in self.ops:
                out += " %s" % o
            out += " "
            return out
        else:
            return "  I"

    def __len__(self):
        return len(self.ops)

    def __eq__(self, other):
        if len(self)!=len(other):
            return False
        else:
            for s, o in zip(self.ops, other.ops):
                if (s!=o):
                    return False
            return True

    def __getitem__(self, i):
        return self.ops[i]

    def split(self, partition):
        leftops = []
        rightops = []
        for i, o in enumerate(self.ops):
              if ((partition & (1 << i))):
                  leftops.append(o)
              else:
                  rightops.append(o)
        return (OpList(leftops), OpList(rightops))

    def alpha_change(self):
        out = 0
        for o in self.ops:
            if o.spin:
                if o.creation:
                    out += 1
                else:
                    out -= 1
        if out==0:
            return "  "
        elif out > 0:
            return "+%s" % out
        else:
            return "%2s" % out

    def beta_change(self):
        out = 0
        for o in self.ops:
            if not o.spin:
                if o.creation:
                    out += 1
                else:
                    out -= 1
        if out==0:
            return "  "
        elif out > 0:
            return "+%s" % out
        else:
            return "%2s" % out

def CreaA():
    return Op(True, True)

def AnniA():
    return Op(True, False)

def CreaB():
    return Op(False, True)

def AnniB():
    return Op(False, False)

allowed_list = [
    OpList([CreaA()]),
    OpList([CreaB()]),
    OpList([AnniA(), AnniA()]),
    OpList([AnniB(), AnniB()]),
    OpList([AnniB(), AnniA()]),
    OpList([CreaA(), AnniA()]),
    OpList([CreaB(), AnniB()]),
    OpList([CreaB(), AnniA()]),
    OpList([CreaB(), CreaA(), AnniA()]),
    OpList([CreaA(), CreaA(), AnniA()]),
    OpList([CreaB(), CreaB(), AnniB()]),
    OpList([CreaA(), CreaB(), AnniB()])
]

class Term(OpList):
    rev = False
    conj = False

    def __init__(self, oplist):
        self.ops = oplist
        if len(oplist)==0:
            self.rev, self.conj = False, False
        elif oplist in allowed_list:
            self.rev, self.conj = False, False
        elif oplist.conjugate() in allowed_list:
            self.rev, self.conj = False, True
        elif oplist.reverse() in allowed_list:
            self.rev, self.conj = True, False
        elif oplist.reverse().conjugate() in allowed_list:
            self.rev, self.conj = True, True
        else:
            raise Exception("This should not have happened!")

    def get_allowed(self):
        if not self.rev and not self.conj:
            return self.ops
        elif self.rev and not self.conj:
            return self.reverse()
        elif not self.rev and self.conj:
            return self.conjugate()
        else:
            return self.reverse().conjugate()

    def factor(self):
        return 1.0 if not self.rev else -1.0

    def matel(self, label):
        bra = label + "'"
        ket = label
        out = "<%s|%s|%s>" % (bra, OpList.__str__(self), ket)
        return out

    def GammaSQ(self):
        oplist = self.get_allowed()
        out = "%s" % oplist[0].GammaSQ()
        for i in range(1, len(oplist)):
            out += ", %s" % oplist[i].GammaSQ()
        return out

    def __str__(self):
        out = "-" if self.rev else ""
        out += "%s" % OpList.__str__(self)
        return str(out)

    def __len__(self):
        return len(self.ops)

level = 0
def indent():
    return "  "*level

def open_code_block():
    global level
    level += 1

def close_code_block():
    global level
    level -= 1
    print("%s}" % indent())

def pow(name, exponent):
    exp = int(exponent)
    if (exp < 1):
        raise Exception("pow function not designed for zero exponents")
    return name + ("*" + name) * (exp-1)

input_indices = [ "i", "j", "k" ]
left_indices = [ "a", "b", "c" ]
right_indices = [ "p", "q", "r" ]

norb = "norb"
lnorb = "lnorb"
rnorb = "rnorb"
loffset = "loffset"
roffset = "roffset"
mo2e = "mo2e"

class ContractedOperator(OpList):
    integrals = ""
    factor = 1.0

    def __init__(self, ops, integrals, factor):
        self.ops = ops
        self.integrals = integrals
        self.factor = factor

class Integrals:
    partition = bin(0)
    size = 1
    reverseL = False
    reverseR = False
    int_type = "J"

    def index(self, indices):
        out = ""
        for i, index in enumerate(indices):
            out += "%s(%s)%s" % ("" if i==0 else "+", index, i*("*"+norb))
        return out

    def __init__(self, partition, size, rL, rR, it):
        self.size = size
        self.partition = bin(partition)[2:]
        self.partition = "0"*(size - len(self.partition)) + self.partition
        self.reverseL = rL
        self.reverseR = rR
        self.int_type = it

    def __call__(self, ptr_name, Cindices, Lindices, Rindices):
        if self.reverseL:
            Lindices.reverse()
        if self.reverseR:
            Rindices.reverse()

        size = len(Lindices) + len(Rindices)

        if len(self.partition) != size:
            self.partition = "0"*(size - len(self.partition)) + self.partition

        total_indices = []
        for i in reversed(range(size)):
            if self.partition[i] == "1":
                total_indices.append(Lindices.pop(0) + "+" + loffset)
            else:
                total_indices.append(Rindices.pop(0) + "+" + roffset)

        if self.int_type == "QJ":
            assert size == 2
            out = "%s[%s]" % (ptr_name, self.index( [total_indices[0], Cindices[0], total_indices[1], Cindices[1]] ))
        elif self.int_type == "QK":
            assert size == 2
            out = "%s[%s]" % (ptr_name, self.index( [total_indices[0], total_indices[1], Cindices[1], Cindices[0]] ))
        elif self.int_type == "QJK":
            assert size == 2
            out = "(%s[%s] - %s[%s])" % (ptr_name, self.index([total_indices[0], Cindices[0], total_indices[1], Cindices[1]]),
                                         ptr_name, self.index([Cindices[0], total_indices[0], total_indices[1], Cindices[1]]))
        elif self.int_type == "P":
            assert size == 2
            out = "%s[%s]" % (ptr_name, self.index([total_indices[0], total_indices[1], Cindices[1], Cindices[0]]))
        elif self.int_type == "PJK":
            assert size == 2
            out = "(%s[%s] - %s[%s])" % (ptr_name, self.index([total_indices[0], total_indices[1], Cindices[1], Cindices[0]]),
                                         ptr_name, self.index([total_indices[0], total_indices[1], Cindices[0], Cindices[1]]))
        elif self.int_type == "S":
            assert size == 3
            out = "%s[%s]" % (ptr_name, self.index([Cindices[0], total_indices[1], total_indices[0], total_indices[2]]))
        elif self.int_type == "SJK":
            assert size == 3
            out = "(%s[%s] - %s[%s])" % (ptr_name, self.index([Cindices[0], total_indices[1], total_indices[0], total_indices[2]]),
                                         ptr_name, self.index([Cindices[0], total_indices[0], total_indices[1], total_indices[2]]))
        else:
            raise Exception("Undefined integral type!")

        return out


class OperatorProduct:
    left = Term([])
    right = Term([])
    fac = 0.0
    integrals = Integrals(0, 1, False, False, "")

    def __init__(self, lterm, rterm, integrals, fac):
        self.left = lterm
        self.right = rterm
        self.integrals = integrals
        self.fac = fac

    def factor(self):
        return self.fac * self.left.factor() * self.right.factor()

    def action(self):
        return self.left.alpha_change() + self.left.beta_change() + self.right.alpha_change() + self.right.beta_change()

    def compatible(self, other):
        return OpList.__eq__(self.left, other.left) and OpList.__eq__(self.right, other.right) and \
               (self.integrals.int_type == "S" and other.integrals.int_type == "S" or \
                self.integrals.int_type == "P" and other.integrals.int_type == "P")

    def combine(self, other):
        fac = 0.0
        partition = 0
        if self.integrals.int_type == "S":
            if self.integrals.partition in [ "101", "001" ]:
                assert other.integrals.partition in [ "110", "010" ]
                fac = self.factor()
                for i, p in enumerate(reversed(self.integrals.partition)):
                    if p == "1":
                        partition += 1 << i
            elif self.integrals.partition in [ "110", "010" ]:
                assert other.integrals.partition in [ "101", "001" ]
                fac = other.factor()
                for i, p in enumerate(reversed(other.integrals.partition)):
                    if p == "1":
                        partition += 1 << i
            else:
                raise Exception("Incompatible!")
            return OperatorProduct(self.left, self.right, Integrals(partition, 3, False, False, "SJK"), fac)
        elif self.integrals.int_type == "P":
            if self.integrals.partition == "01":
                assert other.integrals.partition == "10"
                fac = self.factor()
                for i, p in enumerate(reversed(self.integrals.partition)):
                    if p == "1":
                        partition += 1 << i
            elif self.integrals.partition == "10":
                assert other.integrals.partition == "01"
                fac = other.factor()
                for i, p in enumerate(reversed(other.integrals.partition)):
                    if p == "1":
                        partition += 1 << i
            else:
                raise Exception("Incompatible!")
            return OperatorProduct(self.left, self.right, Integrals(partition, 2, self.left.conj, self.left.rev, "PJK"), fac)

    def __str__(self):
        return "%1.1f <L'|%s|L> (x) <R'|%s|R>" % (self.factor(), self.left, self.right)

def generate_operator(opname, contracted_operators, ninput):
    nsummed_indices = 4 - ninput
    def_inp_string = "const int %s" % input_indices[0]
    inp_string = input_indices[0]
    for i in range(1,ninput):
        inp_string += ", %s" % input_indices[i]
        def_inp_string += ", const int %s" % input_indices[i]
    print("%sshared_ptr<BlockSparseMatrix> BlockOperators2::%s(BlockKey bk, %s) const {" % (indent(), opname, def_inp_string))
    open_code_block()

    # action needs to be the same for all of them, so figure out action from the first one
    action = (contracted_operators[0].alpha_change(), contracted_operators[0].beta_change())
    global_action = action[0] + action[1]

    opcollection = {}
    opcollection["    %s" % global_action] = []
    opcollection["%s    " % global_action] = []
    # preprocess into OperatorProducts
    for op in contracted_operators:
        size = len(op)
        npart = 1 << size
        for partitioning in range(1, npart - 1):
            # used to figure out the sign of rearranging the operators so all of the "right" operators are on the right
            split_factor = -1.0 if partitioning==2 or partitioning==5 else 1.0
            (left, right) = op.split(partitioning)
            (lterm, rterm) = (Term(left), Term(right))
            op_prod = OperatorProduct(lterm, rterm, Integrals(partitioning, nsummed_indices, lterm.rev ^ lterm.conj, rterm.rev ^ rterm.conj, op.integrals), op.factor*split_factor)
            if op_prod.action() in opcollection:
                opcollection[op_prod.action()].append(op_prod)
            else:
                opcollection[op_prod.action()] = [ op_prod ]
    diag = action[0]=="  " and action[1]=="  "

    if not diag:
        print("%sBlockKey target_bk(bk.nelea%s,bk.neleb%s);" % (indent(), action[0].strip(), action[1].strip()))
        print("%sassert(blocks_->contains(target_bk));" % indent())
        print()

    svec = "pvec" if diag else "source_pvec"
    tvec = "pvec" if diag else "target_pvec"

    print("%sconst vector<DMRG::BlockPair>& %s = blocks_->blockpairs(bk);" % (indent(), svec))
    if not diag:
        print("%sconst vector<DMRG::BlockPair>& %s = blocks_->blockpairs(target_bk);" % (indent(), tvec))

    print()

    sinfo = "binfo" if diag else "source_info"
    tinfo = "binfo" if diag else "target_info"

    print("%sconst BlockInfo %s = blocks_->blockinfo(bk);" % (indent(), sinfo))
    if not diag:
        print("%sconst BlockInfo %s = blocks_->blockinfo(target_bk);" % (indent(), tinfo))

    print()

    print("%sconst int %s = jop_->nocc();" % (indent(), norb))
    print("%sconst int %s = blocks_->left_block()->norb();" %(indent(), lnorb))
    print("%sconst int %s = blocks_->right_block()->norb();" %(indent(), rnorb))
    print("%sconst int %s = %s - (%s + %s); // convenience variable for offset of left orbitals from zero" % (indent(), loffset, norb, lnorb, rnorb))
    print("%sconst int %s = %s - %s; // convenience variable for offset of right orbitals from zero" % (indent(), roffset, norb, rnorb))
    print()

    print("%sconst double* %s = jop_->mo2e()->data();" % (indent(), mo2e))
    print()

    print("%sconst int max_L_M = max_element(blocks_->left_block()->blocks().begin(), blocks_->left_block()->blocks().end()," % indent())
    print("%s                                 [] (const BlockInfo& a, const BlockInfo& b)" % indent())
    print("%s                                   { return a.nstates < b.nstates; })->nstates;" % indent())
    print("%sconst int max_R_M = max_element(blocks_->right_block()->blocks().begin(), blocks_->right_block()->blocks().end()," % indent())
    print("%s                                 [] (const BlockInfo& a, const BlockInfo& b)" % indent())
    print("%s                                   { return a.nstates < b.nstates; })->nstates;" % indent())
    print("%sconst size_t max_L_intermediate = max_L_M * max_L_M * %s;" % (indent(), rnorb))
    print("%sconst size_t max_R_intermediate = max_R_M * max_R_M * %s;" % (indent(), lnorb))
    print("%sconst size_t max_intermediate = max(max_L_intermediate, max_R_intermediate);" % (indent()))
    print("%sunique_ptr<double[]> scratch(new double[max_intermediate]);" % indent())
    print()
    print("%sconst size_t max_coulomb_size = lnorb < rnorb ? %s*%s : %s*%s;" % (indent(), rnorb + (nsummed_indices-2)*("*"+rnorb), lnorb, lnorb + (nsummed_indices-2)*("*"+lnorb), rnorb))
    print("%sunique_ptr<double[]> coulomb(new double[max_coulomb_size]);" % indent())

    print("%smap<pair<size_t, size_t>, shared_ptr<Matrix>> out;" % (indent()))
    print()
    print("%sfor (auto& spair : %s) {" % (indent(), svec))
    open_code_block()

    print("%s// phase accumulated by moving an operator past the whole left ket block" % indent())
    print("%sconst int left_phase = 1 - (((spair.left.nelea+spair.left.neleb)%%2) << 1);" % indent());

    for key, collection in opcollection.iteritems():
        pure_left = False
        pure_right = False
        terms_computed = ""
        if key == ("    %s"%global_action):
            pure_right = True
            terms_computed += " I (x) %s" % opname
        if key == ("%s    "%global_action):
            pure_left = True
            if terms_computed != "":
                terms_computed += " + "
            terms_computed += " %s (x) I " % opname
        for i, t in enumerate(collection):
            sgn = ""
            if t.factor() > 0:
                sgn = " + "
            elif t.factor() < 0:
                sgn = " - "
            terms_computed += "%s%1.1f %s (x) %s" % (sgn, abs(t.factor()), t.left.matel("L"), t.right.matel("R"))
        print()
        print("%s{ // %s" % (indent(), terms_computed.strip()))
        open_code_block()

        la = key[0:2]
        lb = key[2:4]
        ra = key[4:6]
        rb = key[6:8]

        #print(la, lb, ra, rb)

        both_diag = (la, lb, ra, rb) == ("  ", "  ", "  ", "  ")

        if not both_diag:
            if (la, lb)==("  ", "  "):
                print("%sconst BlockKey left_target = spair.left.key();" % indent())
            else:
                print("%sconst BlockKey left_target(spair.left.nelea%s, spair.left.neleb%s);" % (indent(), la.strip(), lb.strip()))
            if (ra, rb)==("  ", "  "):
                print("%sconst BlockKey right_target = spair.right.key();" % indent())
            else:
                print("%sconst BlockKey right_target(spair.right.nelea%s, spair.right.neleb%s);" % (indent(), ra.strip(), rb.strip()))
            print()
            print("%sauto iter = find_if(%s.begin(), %s.end(), [&left_target, &right_target] (DMRG::BlockPair bp)" % (indent(), tvec, tvec))
            print("%s  { return make_pair(bp.left.key(), bp.right.key())==make_pair(left_target, right_target); }" % indent())
            print("%s);" % indent())

            print("%sif(iter!=%s.end()) {" % (indent(), tvec))
            open_code_block()

            print("%sDMRG::BlockPair tpair = *iter;" % indent())
            print()

        tpair = "spair" if both_diag else "tpair"
        nops = 0

        print("%sauto out_block = make_shared<Matrix>(%s.nstates(), spair.nstates(), true);" % (indent(), tpair))

        if (pure_right):
            nops += 1
            print()
            print("%s// I (x) %s" % (indent(), opname))
            print("%sright_ops_->%s_copy_to(scratch.get(), spair.right.key(), %s);" % (indent(), opname, inp_string))
            phase = "left_phase" if (ninput%2==1) else "1.0"
            print("%skronecker_product_A_I(%s, false, %s.right.nstates, spair.right.nstates, scratch.get(), %s.right.nstates, spair.left.nstates, out_block->data(), out_block->ndim());" % (indent(), phase, tpair, tpair))

        if (pure_left):
            nops += 1
            print()
            print("%s// %s (x) I" % (indent(), opname))
            print("%sleft_ops_->%s_copy_to(scratch.get(), spair.left.key(), %s);" % (indent(), opname, inp_string))
            print("%skronecker_product_I_B(1.0, spair.right.nstates, false, %s.left.nstates, spair.left.nstates, scratch.get(), %s.left.nstates, out_block->data(), out_block->ndim());" % (indent(), tpair, tpair))

        # preprocess collection into terms that can be combined
        combined_collection = []
        while len(collection) != 0:
            seed = collection.pop(0)
            for i in reversed(range(len(collection))):
                if seed.compatible(collection[i]):
                    seed = seed.combine(collection.pop(i))
            combined_collection.append(seed)

        processed_collection = []
        while len(combined_collection) != 0:
            seed =  [ combined_collection.pop(0) ]
            for i in reversed(range(len(combined_collection))):
                #if len(seed[0].left) ==1 and len(combined_collection[i].left) ==1 and len(seed[0].right)==2 and OpList.__eq__(seed[0].left, combined_collection[i].left) or \
                #   len(seed[0].right)==1 and len(combined_collection[i].right)==1 and len(seed[0].left) ==2 and OpList.__eq__(seed[0].right, combined_collection[i].right):
                if len(seed[0].left) ==1 and len(combined_collection[i].left) ==1 and OpList.__eq__(seed[0].left, combined_collection[i].left) or \
                   len(seed[0].right)==1 and len(combined_collection[i].right)==1 and OpList.__eq__(seed[0].right, combined_collection[i].right):
                    seed.append(combined_collection.pop(i))
            processed_collection.append(seed)

        nops += len(processed_collection)

        for oprodvec in processed_collection:
            oprod = oprodvec[0]

            if nops > 1:
                term_string = [ "%s"%x for x in oprodvec ]
                print()
                print("%s{ // %s" % (indent(), term_string))
                open_code_block()

            shorter = "left" if len(oprod.left)==1 and len(oprod.right)==2 else "right"

            lgammas = [ ]
            rgammas = [ ]
            lbra, lket = "tpair", "spair"
            if oprod.left.conj:
                lbra, lket = lket, lbra
            rbra, rket = "tpair", "spair"
            if oprod.right.conj:
                rbra, rket = rket, rbra
            if len(oprodvec)==1:
                lgammas.append( ("Lgamma", oprod.left.GammaSQ(), lbra, lket) )
                rgammas.append( ("Rgamma", oprod.right.GammaSQ(), rbra, rket) )
            elif len(oprodvec)==2:
                if shorter == "left":
                    lgammas.append( ("Lgamma", oprod.left.GammaSQ(), lbra, lket) )
                    rgammas.append( ("Rgamma1", oprodvec[0].right.GammaSQ(), rbra, rket) )
                    rgammas.append( ("Rgamma2", oprodvec[1].right.GammaSQ(), rbra, rket) )
                else:
                    rgammas.append( ("Rgamma", oprod.right.GammaSQ(), rbra, rket) )
                    lgammas.append( ("Lgamma1", oprodvec[0].left.GammaSQ(), lbra, lket) )
                    lgammas.append( ("Lgamma2", oprodvec[1].left.GammaSQ(), lbra, lket) )
            else:
                raise Exception("NO")

            # find individual tensors
            if nops <= 1:
                print()

            for LG in lgammas:
                print("%sshared_ptr<const btas::Tensor3<double>> %s = blocks_->left_block()->coupling({%s}).at({%s.left.key(),%s.left.key()}).data;" % (indent(), LG[0], LG[1], LG[2], LG[3]))
            for RG in rgammas:
                print("%sshared_ptr<const btas::Tensor3<double>> %s = blocks_->right_block()->coupling({%s}).at({%s.right.key(),%s.right.key()}).data;" % (indent(), RG[0], RG[1], RG[2], RG[3]))

            print()

            #print("%sMatrix Lmat(%s->extent(0), %s->extent(1), true);" % (indent(), lgammas[0][0], lgammas[0][0]))
            #print("%sMatrix Rmat(%s->extent(0), %s->extent(1), true);" % (indent(), rgammas[0][0], rgammas[0][0]))

            print("%sconst int Lndim = %s->extent(0);" % (indent(), lgammas[0][0]))
            print("%sconst int Lmdim = %s->extent(1);" % (indent(), lgammas[0][0]))
            print("%sconst int Lsize = %s->extent(0) * %s->extent(1);" % (indent(), lgammas[0][0], lgammas[0][0]))
            print()
            print("%sconst int Rndim = %s->extent(0);" % (indent(), rgammas[0][0]))
            print("%sconst int Rmdim = %s->extent(1);" % (indent(), rgammas[0][0]))
            print("%sconst int Rsize = %s->extent(0) * %s->extent(1);" % (indent(), rgammas[0][0], rgammas[0][0]))

            print()

            abc = "%s" % left_indices[0]
            for i in range(1, len(oprod.left)):
                abc += " + %s%s" % (left_indices[i], ("*" + lnorb)*i)

            pqr = "%s" % right_indices[0]
            for i in range(1,len(oprod.right)):
                pqr += " + %s%s" %(right_indices[i], ("*" + rnorb)*i)

            integral_strings = [x.integrals(mo2e, input_indices[0:ninput], left_indices[0:len(x.left)], right_indices[0:len(x.right)]) for x in oprodvec]

            collected_by_integral = {}
            for i in range(len(integral_strings)):
                if i in collected_by_integral:
                    collected_by_integral[i].append(i)
                else:
                    collected_by_integral[i] = [i]

            if len(oprod.right) > len(oprod.left): # inner loop is over right terms
                print("%s// fill in coulomb part" % indent())
                print("%sassert(max_coulomb_size >= %s*%s);" % (indent(), lnorb, pow(rnorb, len(oprod.right))))
                print("%sfill_n(scratch.get(), Rsize * lnorb, 0.0);" % (indent()))
                for operation_index in range(len(integral_strings)):
                    coulomb_index = ""
                    stride = ""
                    for i in range(len(oprod.right)):
                        if (i != 0):
                            coulomb_index += " + "
                        coulomb_index += right_indices[i] + stride
                        stride += "*" + rnorb
                    for i in range(len(oprod.left)):
                        coulomb_index += " + "
                        coulomb_index += left_indices[i] + stride
                        stride += "*" + lnorb

                    for i in range(len(oprod.left)):
                        print("%sfor (int %s = 0; %s < %s; ++%s) {" % (indent(), left_indices[i], left_indices[i], lnorb, left_indices[i]))
                        open_code_block()
                    for i in range(len(oprod.right)):
                        print("%sfor (int %s = 0; %s < %s; ++%s) {" % (indent(), right_indices[i], right_indices[i], rnorb, right_indices[i]))
                        open_code_block()
                    print("%scoulomb[%s] = %s;" % (indent(), coulomb_index, integral_strings[operation_index]))
                    for i in range(len(oprod.right) + len(oprod.left)):
                        close_code_block()
                    print()
                    print("%sdgemm_(\"N\", \"N\", Rsize, lnorb, %s, %1.1f, %s->data(), Rsize, coulomb.get(), %s, 1.0, scratch.get(), Rsize);" \
                                % (indent(), pow(rnorb, len(oprod.right)), oprodvec[operation_index].factor(), rgammas[operation_index][0], pow(rnorb, len(oprod.right))))

                rtrans = "true" if oprod.right.conj else "false"
                ltrans = "true" if oprod.left.conj else "false"

                phase = "left_phase" if len(oprod.right)%2==1 else 1.0

                for i in range(len(oprod.left)):
                    print("%sfor (int %s = 0; %s < %s; ++%s) {" % (indent(), left_indices[i], left_indices[i], lnorb, left_indices[i]))
                    open_code_block()
                print("%sconst double* ldata = Lgamma->data() + Lsize * %s;" % (indent(), left_indices[0]))
                print("%sconst double* rdata = scratch.get() + Rsize * %s;" % (indent(), left_indices[0]))
                print("%skronecker_product(%s, %s, Rndim, Rmdim, rdata, Rndim, %s, Lndim, Lmdim, ldata, Lndim, out_block->data(), out_block->ndim());" \
                                                % (indent(), phase, rtrans, ltrans))
                for i in range(len(oprod.left)):
                    close_code_block()

            else: #inner loop is over left terms
                print("%s// fill in coulomb part" % indent())
                print("%sassert(max_coulomb_size >= %s*%s);" % (indent(), rnorb, pow(lnorb, len(oprod.left))))
                print("%sfill_n(scratch.get(), Lsize * rnorb, 0.0);" % (indent()))

                for operation_index in range(len(integral_strings)):
                    coulomb_index = ""
                    stride = ""
                    for i in range(len(oprod.left)):
                        if (i != 0):
                            coulomb_index += " + "
                        coulomb_index += left_indices[i] + stride
                        stride += "*" + lnorb
                    for i in range(len(oprod.right)):
                        coulomb_index += " + "
                        coulomb_index += right_indices[i] + stride
                        stride += "*" + rnorb

                    for i in range(len(oprod.right)):
                        print("%sfor (int %s = 0; %s < %s; ++%s) {" % (indent(), right_indices[i], right_indices[i], rnorb, right_indices[i]))
                        open_code_block()
                    for i in range(len(oprod.left)):
                        print("%sfor (int %s = 0; %s < %s; ++%s) {" % (indent(), left_indices[i], left_indices[i], lnorb, left_indices[i]))
                        open_code_block()
                    print("%scoulomb[%s] = %s;" % (indent(), coulomb_index, integral_strings[operation_index]))
                    for i in range(len(oprod.right) + len(oprod.left)):
                        close_code_block()
                    print()
                    print("%sdgemm_(\"N\", \"N\", Lsize, rnorb, %s, %1.1f, %s->data(), Lsize, coulomb.get(), %s, 1.0, scratch.get(), Lsize);" \
                                % (indent(), pow(lnorb, len(oprod.left)), oprodvec[operation_index].factor(), lgammas[operation_index][0], pow(lnorb, len(oprod.left))))

                rtrans = "true" if oprod.right.conj else "false"
                ltrans = "true" if oprod.left.conj else "false"

                phase = "left_phase" if len(oprod.right)%2==1 else 1.0

                for i in range(len(oprod.right)):
                    print("%sfor (int %s = 0; %s < %s; ++%s) {" % (indent(), right_indices[i], right_indices[i], rnorb, right_indices[i]))
                    open_code_block()
                print("%sconst double* ldata = scratch.get() + Lsize * %s;" % (indent(), right_indices[0]))
                print("%sconst double* rdata = Rgamma->data() + Rsize * %s;" % (indent(), right_indices[0]))
                print("%skronecker_product(%s, %s, Rndim, Rmdim, rdata, Rndim, %s, Lndim, Lmdim, ldata, Lndim, out_block->data(), out_block->ndim());" \
                                                % (indent(), phase, rtrans, ltrans))
                # close Right loops
                for i in range(len(oprod.right)):
                    close_code_block()

            if nops > 1:
                close_code_block()
                #print()

        print("\n%s// add to map if large enough" % indent())
        print("%sif (out_block->rms() > thresh_)" % indent())
        print("%s  out.emplace(make_pair<size_t, size_t>(%s.offset, spair.offset), out_block);" % (indent(), tpair))

        if not both_diag:
            close_code_block()

        close_code_block()
        #print()

    close_code_block()
    print()
    print("%sreturn make_shared<BlockSparseMatrix>(%s.nstates, %s.nstates, out);" % (indent(), tinfo, sinfo))
    close_code_block()


generate_operator("S_a", [ContractedOperator([CreaA(), CreaA(), AnniA()], "S", 1.0), ContractedOperator([CreaA(), CreaB(), AnniB()], "S", 1.0)], 1)
print()
print()
generate_operator("S_b", [ContractedOperator([CreaB(), CreaB(), AnniB()], "S", 1.0), ContractedOperator([CreaB(), CreaA(), AnniA()], "S", 1.0)], 1)
print()
print()
generate_operator("Q_aa", [ContractedOperator([CreaA(), AnniA()], "QJK", 1.0), ContractedOperator([CreaB(), AnniB()], "QJ", 1.0)], 2)
print()
print()
generate_operator("Q_bb", [ContractedOperator([CreaB(), AnniB()], "QJK", 1.0), ContractedOperator([CreaA(), AnniA()], "QJ", 1.0)], 2)
print()
print()
generate_operator("Q_ab", [ContractedOperator([CreaB(), AnniA()], "QK", -1.0)], 2)
print()
print()
generate_operator("P_aa", [ContractedOperator([AnniA(), AnniA()], "P", 0.5)], 2)
print()
print()
generate_operator("P_bb", [ContractedOperator([AnniB(), AnniB()], "P", 0.5)], 2)
print()
print()
generate_operator("P_ab", [ContractedOperator([AnniB(), AnniA()], "P", 1.0)], 2)
