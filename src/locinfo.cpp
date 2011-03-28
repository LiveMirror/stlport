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

#define _CRTIMP2_PURE __declspec(dllexport)
#define _CRTIMP_PURE __declspec(dllexport)

#include "stlport_prefix.h"

#include <string>
#include <stl/_locinfo.h>

_STLP_DECLSPEC _Cvtvec _STLP_CALL _Getcvt()
{
  return _Cvtvec();
}
_STLP_DECLSPEC _Collvec _STLP_CALL _Getcoll()
{
  return _Collvec();
}
_STLP_DECLSPEC _Ctypevec _STLP_CALL _Getctype()
{
  return _Ctypevec();
}

_STLP_DECLSPEC int _STLP_CALL _Getdateorder()
{
  return 0;
}

_STLP_BEGIN_NAMESPACE

// TODO implement
void _STLP_CALL _Locinfo::_Locinfo_ctor(_Locinfo *, const char *) {}
void _STLP_CALL _Locinfo::_Locinfo_ctor(_Locinfo *, const string&) {}
void _STLP_CALL _Locinfo::_Locinfo_ctor(_Locinfo *, int, const char *) {}
void _STLP_CALL _Locinfo::_Locinfo_dtor(_Locinfo *) {}
_Locinfo& _STLP_CALL _Locinfo::_Locinfo_Addcats(_Locinfo * cat, int n, const char * c) 
{
  return *cat;
}


_Locinfo::_Locinfo(int __pos, const char *__name) {
  _Locinfo_ctor(this, __pos, __name);
}

_Locinfo::_Locinfo(const char* __name)   {
  _Locinfo_ctor(this, __name);
}

_Locinfo::_Locinfo(const string& __name) {
  _Locinfo_ctor(this, __name);
}

_Locinfo::~_Locinfo() {
  _Locinfo_dtor(this);
}
	
_Locinfo& _Locinfo::_Addcats(int pos, const char * name) {
  return _Locinfo_Addcats(this, pos, name);
}

string  _Locinfo::_Getname() const {
  return (_Newlocname);
}

_Locinfo::_Collvec  _Locinfo::_Getcoll() const { 
  return (::_Getcoll());
}
	
_Locinfo::_Ctypevec  _Locinfo::_Getctype() const {
  return (::_Getctype());
}

_Locinfo::_Cvtvec  _Locinfo::_Getcvt() const {
  return (::_Getcvt());
}
	
const lconv * _Locinfo::_Getlconv() const {
  return (localeconv());
}

_Locinfo::_Timevec  _Locinfo::_Gettnames() const {
  return (_Timevec(::_Gettnames()));
}

const char* _DefaultDays = ":Sun:Sunday:Mon:Monday:Tue:Tuesday:Wed:Wednesday"
	  ":Thu:Thursday:Fri:Friday:Sat:Saturday";
	
const char* _DefaultMonths = ":Jan:January:Feb:February:Mar:March"
":Apr:April:May:May:Jun:June"
":Jul:July:Aug:August:Sep:September"
":Oct:October:Nov:November:Dec:December";

const char* _Locinfo::_Getdays() const
{
  if (_Days.empty())
    const_cast<_Locinfo*>(this)->_Days = _DefaultDays;
  return _Days.c_str();
}

const char* _Locinfo::_Getmonths() const
{
  if (_Months.empty())
    const_cast<_Locinfo*>(this)->_Months = string(_DefaultMonths);

  return _Months.c_str();
}

const char* _Locinfo::_Getfalse() const
{
  return ("false");
}

const char* _Locinfo::_Gettrue() const
{
  return ("true");
}

int  _Locinfo::_Getdateorder() const
{
  return ::_Getdateorder();
}

_STLP_END_NAMESPACE




// Local Variables:
// mode:C++
// End:

