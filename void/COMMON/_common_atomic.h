#pragma once
namespace vd {

	namespace Private {
		//! \ingroup atomic
		//! \brief atomic guard policy
		enum ON_EXIT {
			RESTORE_STATE, //!< \brief restore interrupts state on exit
			FORCE_ON //!< \brief enable interrupts on exit
		};
		template<ON_EXIT T = RESTORE_STATE>
		class atomic_guard_t {};

		template<>
		class atomic_guard_t<RESTORE_STATE> {
				vd::Private::TControlRegType _controlReg;
			public:
				atomic_guard_t() {
					_controlReg = vd::Private::getControlReg();
					vd::Private::DisableInterrupts();
				}
				~atomic_guard_t() {
					vd::Private::restoreControlReg(&_controlReg);
				}
				operator bool() {
					return false;
				}
		};

		template<>
		class atomic_guard_t<FORCE_ON> {
			public:
				atomic_guard_t() {
					vd::Private::DisableInterrupts();
				}
				~atomic_guard_t() {
					vd::Private::EnableInterrupts();
				}
				operator bool() {
					return false;
				}

		};
	}
}