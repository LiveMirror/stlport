/*
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#ifndef _STLP_MOVE_CONSTRUCT_FWK_H
#define _STLP_MOVE_CONSTRUCT_FWK_H

#ifndef _STLP_TYPE_MANIPS_H
# include <stl/type_manips.h>
#endif

_STLP_BEGIN_NAMESPACE

/*************************************************************
 * Move construct feature
 *************************************************************/

/*************************************************************
 *Partial move:
 *The source HAS to be destroyable after the move!
 *************************************************************/
template <class _Tp>
class __partial_move_source {
	_Tp &_data;
public:
	explicit __partial_move_source (_Tp &_src) : _data(_src)
	{};

	_Tp& get() const
	{return _data;}
};

class __partial_move_supported {};

//prefered way of signaling partial move support: template specialization
template <class _Tp>
struct __partial_move_traits {
  //default value based on the alternative way to signal full move support: derivation
  typedef typename __is_convertible<_Tp, __partial_move_supported>::_Answer _Supported;
};

template <class _Tp>
struct _PartialMoveSourceTraits {
  typedef typename __partial_move_traits<_Tp>::_Supported _PartialMvSupRet;
  enum {_PartialMvSup = __type2bool<_PartialMvSupRet>::_Ret};
  typedef typename __select<_PartialMvSup,
                            __partial_move_source<_Tp>,
                            _Tp const&>::_Ret _Type;
};

template <class _Tp>
inline _STLP_TYPENAME_ON_RETURN_TYPE _PartialMoveSourceTraits<_Tp>::_Type
_AsPartialMoveSource (_Tp &src) {
  typedef typename _PartialMoveSourceTraits<_Tp>::_Type _SrcType;
  return _SrcType(src);
};

/*************************************************************
 *Full move:
 *The source do not required to be destroyable after the move!
 *************************************************************/
template <class _Tp>
class __full_move_source {
  _Tp &_data;
public:
  explicit __full_move_source (_Tp &_src) : _data(_src)
  {};

  _Tp& get() const
  {return _data;}
};

class __full_move_supported {};

//prefered way of signaling full move support: template specialization
template <class _Tp>
struct __full_move_traits {
  //default value based on the alternative way to signal full move support: derivation
  typedef typename __is_convertible<_Tp, __full_move_supported>::_Answer _Supported;
};

template <class _Tp>
struct _FullMoveSourceTraits {
	typedef typename __full_move_traits<_Tp>::_Supported _FullMvSupRet;
  enum {_FullMvSup = __type2bool<_FullMvSupRet>::_Ret};
  typedef typename __select<_FullMvSup,
                            __full_move_source<_Tp>,
                            _Tp const&>::_Ret _Type;
};

/*
template <class _Tp>
inline  _STLP_TYPENAME_ON_RETURN_TYPE _FullMoveSourceTraits<_Tp>::_Type
_AsFullMoveSource(_Tp &src) {
	typedef typename _FullMoveSourceTraits<_Tp>::_Type _MvSrcType;
	return _MvSrcType(src);
}
*/

//To implement a full move constructor, the aggregated datas has also to handle the
//full move constructor as no destruction will occur, this can be done with the 
//following method.
template <class _Tp>
inline  __full_move_source<_Tp>
_FullMoveSource(_Tp &src) {
	return __full_move_source<_Tp>(src);
}



template <class _Tp>
struct _MoveConstructSupported {
	typedef typename __partial_move_traits<_Tp>::_Supported _PartialSup;
	typedef typename __full_move_traits<_Tp>::_Supported _FullSup;

	typedef typename _Lor2<_PartialSup, _FullSup>::_Ret _Ret;
	static _Ret _Answer() {return _Ret();}
};

template<class _Tp>
_MoveConstructSupported<_Tp> _IsMoveConstructSupported (_Tp const* pt)
{return _MoveConstructSupported()}

template <class _Tp>
struct _MoveSourceTraits {
  typedef typename _PartialMoveSourceTraits<_Tp>::_Type _PartialSrcType;
	typedef typename __full_move_traits<_Tp>::_Supported _FullMvSupRet;
  enum {_FullMvSup = __type2bool<_FullMvSupRet>::_Ret};
  typedef typename __select<_FullMvSup,
                            __full_move_source<_Tp>,
                            _PartialSrcType>::_Ret _Type;
};

template <class _Tp>
inline _STLP_TYPENAME_ON_RETURN_TYPE _MoveSourceTraits<_Tp>::_Type 
_AsMoveSource(_Tp &src) {
	typedef typename _MoveSourceTraits<_Tp>::_Type _MvSrcType;
	return _MvSrcType(src);
}



/*********************************************/
template <class _Tp>
struct __action_on_move {
	typedef __false_type _Swap;
};

class __enable_swap_on_move {};

#ifndef _STLP_PARTIAL_SPEC
#define _STLP_SWAP_ON_MOVE ,public __enable_swap_on_move
#else
#define _STLP_SWAP_ON_MOVE
#endif /* _STLP_PARTIAL_SPEC */

template <class _Tp>
struct _SwapOnMove {
	typedef typename __action_on_move<_Tp>::_Swap _Ret1;
	typedef typename __is_convertible<_Tp, __enable_swap_on_move>::_Answer _Ret2;

	typedef typename _Lor2<_Ret1, _Ret2>::_Ret _Result;
	static _Result _Ret() {return _Result()}
};

template<class _Tp>
_SwapOnMove<_Tp> _DoSwapOnMove (_Tp const* pt)
{return _SwapOnMove()}

_STLP_END_NAMESPACE

#endif /* _STLP_MOVE_CONSTRUCT_FWK_H */
