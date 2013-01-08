// Copyright (c) 2013, Adam Harrison*
// http://www.ualberta.ca/~apharris/
// All rights reserved.

// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

// -Redistributions of source code must retain the above copyright notice, the footnote below, this list of conditions and the following disclaimer.
// -Redistributions in binary form must reproduce the above copyright notice, the footnote below, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// -Neither the name of the University of Alberta nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// *This work originated as part of a Ph.D. project under the supervision of Dr. Dileepan Joseph at the Electronic Imaging Lab, University of Alberta.


#ifndef MIA_H
#define MIA_H

#include <array>
#include "Index.h"
#include "MIA_Expr.h"
#include "Util.h"

namespace LibMIA
{

namespace internal
{
template<class Derived>
struct order<MIA<Derived> >: public order<Derived> {};
}


/** \addtogroup mia Multi-Index Array Classes
*  @{
*/

//!  Base class for multi-index array classes.
/*!
  This class acts as the base class for the parametric subclass pattern,
  which is more commonly known as the CTRP. It is the base class for all
  multi-index array types. Provides common operations and functions.

  \tparam Derived   should only be DenseMIABase or SparseMIABase type.
*/
template
<

    class Derived
>
class MIA
{

public:

    typedef typename internal::index_type<Derived>::type index_type;
    Derived& derived() { return *static_cast<Derived*>(this); }
    /** \returns a const reference to the derived object */
    const Derived& derived() const { return *static_cast<const Derived*>(this); }

    template<class...Ts>
    auto operator()(Ts...ts)->MIA_Atom<Derived,typename internal::Indicial_Sequence<Ts...>::sequence> {

        return MIA_Atom<Derived,typename internal::Indicial_Sequence<Ts...>::sequence>(derived());

    }

    MIA(std::array<index_type,internal::order<MIA>::value > &_dims): m_dims(_dims),m_dimensionality(compute_dimensionality()) {}

    template<typename... Dims>
    MIA(Dims... dims):m_dims{{dims...}},m_dimensionality(compute_dimensionality()) {

    }

//    toLatticeExpression(std::array<size_t> outer_product_indices, std::array<size_t> inner_product_indices,,std::array<size_t> inter_product_indices){
//        return toLatticeCopy(outer_product_indices, inner_product_indices, inter_product_indices );
//
//    }
//
    /** Sets all mia data to one.*/
    void ones(){
        std::fill ( derived().data_begin(), derived().data_end(), 1);
    }

    /** Sets all mia data to one.*/
    void zeros(){
        std::fill ( derived().data_begin(), derived().data_end(), 0);
    }

    index_type dim(size_t i) const{
        assert(i<m_order);
        return m_dims[i];
    }

protected:

    index_type compute_dimensionality(){
        index_type running_product=1;
        for(auto i=this->m_dims.begin();i<this->m_dims.end();i++){

            running_product*=*i;

        }
        return running_product;
    };

    void init(){
        m_dimensionality=compute_dimensionality();

    }

    constexpr static size_t m_order=internal::order<Derived>::value;
    std::array<index_type,m_order> m_dims;
    index_type m_dimensionality;


};



/*! @} */


} //namespace LibMIA


#endif // MIA_H