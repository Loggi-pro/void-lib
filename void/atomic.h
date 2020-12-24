#pragma once
#include <void/platform_specific.h>

/*!
	\defgroup atomic Atomic
	\brief Atomic functions
	\{
	@file
*/


namespace vd {
	//! \ingroup atomic
	//! \brief Atomic guard type (RAII). On create will block any interrupts. On destroy  - behaviour is defined by Argument policy.
	//! \ingroup atomic
	//! \brief atomic_guard_t policy = RESTORE_STATE - restore interrupt states back on exit | FORCE_ON - enable interrupts on exit
	using ON_EXIT = vd::Private::ON_EXIT;
	template <ON_EXIT Type = ON_EXIT::RESTORE_STATE>
	using atomic_guard_t = vd::Private::atomic_guard_t<Type>;

	//! \ingroup atomic
	//! \brief Non-Atomic Policy -  can be used in class to change behaviour (atomic/non atomic). Contain mock atomic functions.
	using VoidAtomicPolicy = vd::Private::VoidAtomicPolicy;
	//! \ingroup atomic
	//! \brief Atomic Policy -  can be used in class to change behaviour (atomic/non atomic). Contain real atomic functions.
	using AtomicPolicy = vd::Private::AtomicPolicy;

	//! \ingroup atomic
	//! \brief atomic fetch value, modify and stores back
	//! \param [in] ptr - pointer to value
	//! \param [in] value - new value
	//! \return value before modify
	template<class T, class T2>
	inline T AtomicFetchAndAdd(volatile T* ptr, T2 value) {
		return vd::Private::AtomicPolicy::FetchAndAdd(ptr, value);
	}
	//! \ingroup atomic
	//! \brief atomic fetch value, modify and stores back
	//! \param [in] ptr - pointer to value
	//! \param [in] value - new value
	//! \return value after modify
	template<class T, class T2>
	inline T AtomicAddAndFetch(volatile T* ptr, T2 value) {
		return vd::Private::AtomicPolicy::AddAndFetch(ptr, value);
	}
	//! \ingroup atomic
	//! \brief atomic compare variable with value and set new
	//! \param [in] ptr - pointer to value
	//! \param [in] oldValue - value to compare
	//! \param [in] newValue - value to set
	//! \return if succeed
	template<class T, class T2>
	inline bool AtomicCompareExchange(T* ptr, T2 oldValue, T2 newValue) {
		return vd::Private::AtomicPolicy::CompareExchange(ptr, oldValue, newValue);
	}


}

//! \ingroup atomic
//! \brief Atomic block - all code inside this macro will be executed with disabled interrupts
//! \param [in] ... ON_EXIT - behaviour on exit: RESTORE_STATE or FORCE_ON
//! \note if no argument - RESTORE_STATE is assumed
#define ATOMIC_BLOCK(...) if(vd::atomic_guard_t<__VA_ARGS__> _atomic = vd::atomic_guard_t<__VA_ARGS__>()){}else

//! @}