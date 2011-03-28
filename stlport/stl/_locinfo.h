/*
 * Copyright (c) 2011
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
// WARNING: This is an internal header file, included by other C++
// standard library headers.  You should not attempt to use this header
// file directly.


#ifndef _STLP_INTERNAL_LOCINFO_H
#define _STLP_INTERNAL_LOCINFO_H

#include <stl/_locale.h>
#include <xlocinfo.h>

_STLP_BEGIN_NAMESPACE

class _STLP_DECLSPEC _Timevec
{
 public:
  _Timevec(void *__p = 0): _M_p(__p) {}
    _Timevec(const _Timevec& __rhs) {
      _M_p = __rhs._M_p;
    }
    ~_Timevec() {}

    _Timevec& operator=(const _Timevec& __rhs)
      { _M_p = __rhs._M_p; return *this; }
    
    void* _Getptr() const { return _M_p; }
    
 private:
    void *_M_p;
};

class _STLP_DECLSPEC _Locinfo
{
public:
	typedef ::_Collvec _Collvec;
	typedef ::_Ctypevec _Ctypevec;
	typedef ::_Cvtvec _Cvtvec;
	typedef std::_Timevec _Timevec;
	
	static void _STLP_CALL _Locinfo_ctor(_Locinfo*, const char *);
	static void _STLP_CALL _Locinfo_ctor(_Locinfo*, const string&);
	static void _STLP_CALL _Locinfo_ctor(_Locinfo*, int, const char*);
	static void _STLP_CALL _Locinfo_dtor(_Locinfo*);
	static _Locinfo& _STLP_CALL _Locinfo_Addcats(_Locinfo *, int, const char *);

	
	_Locinfo(int __pos, const char *__name);
	_Locinfo(const char* __name = "C");
	_Locinfo(const string& __name);
	~_Locinfo();
	_Locinfo& _Addcats(int __pos, const char *__name);
	string  _Getname() const;
	_Collvec  _Getcoll() const;
	_Ctypevec  _Getctype() const;
	_Cvtvec  _Getcvt() const;
	const lconv * _Getlconv() const;
	_Timevec  _Gettnames() const;
	const char * _Getdays() const;
	const char * _Getmonths() const;
	const char * _Getfalse() const;
	const char * _Gettrue() const;
	int  _Getdateorder() const;

 private:
	//	_Lock
	string _Days;
	string _Months;
	string _Oldlocname;
	string _Newlocname;
};
_STLP_END_NAMESPACE

#endif
