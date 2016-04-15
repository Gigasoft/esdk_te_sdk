// -*- C++ -*-
//
//$Id: Refcountable.inl 69051 2005-10-28 16:14:56Z ossama $

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
ACE_Refcountable::ACE_Refcountable (int refcount)
  : refcount_ (refcount)
{
}

ACE_INLINE int
ACE_Refcountable::increment (void)
{
  return ++this->refcount_;
}

ACE_INLINE int
ACE_Refcountable::decrement (void)
{
  return --this->refcount_;
}

ACE_INLINE int
ACE_Refcountable::refcount (void) const
{
  return this->refcount_;
}

ACE_END_VERSIONED_NAMESPACE_DECL
