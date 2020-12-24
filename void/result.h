#pragma once
namespace vd {
	enum class ResultState {
		NO_RESULT = 0,
		E_WAIT,
		E_ERR,
		E_TIMEOUT,
		E_USER,
		E_SOFTWARE,
		S_DONE
	};

	template<typename T = void>
	class Result {
		private:
			ResultState _isComplete;
			T _value;
		public:
			typedef T type;
			Result(T aResValue) : _isComplete(ResultState::S_DONE),
				_value(aResValue) {}
			Result(ResultState state = ResultState::NO_RESULT) : _isComplete(state),
				_value() {}
			template <class U>
			Result(const Result<U>& other, T value) : _isComplete(other.state()), _value(value) {
			}

			bool isComplete() const {
				return _isComplete != ResultState::NO_RESULT;
			}
			bool isSuccess() const {
				return _isComplete == ResultState::S_DONE;
			}
			bool isFail() const {
				return (isComplete()) && (!isSuccess());
			}
			ResultState state() const {
				return _isComplete;
			}
			const T& value()const {
				return _value;
			}
			explicit operator bool()const {
				return isComplete();
			}
	};

	template<>
	class Result<void> {
		private:
			ResultState _isComplete;
		public:
			Result(ResultState state = ResultState::NO_RESULT) : _isComplete(
				    state) {}
			Result(bool result) : _isComplete(result == true ? ResultState::S_DONE :
				                                  ResultState::E_ERR) {}
			bool isComplete()const {
				return _isComplete != ResultState::NO_RESULT;
			}
			bool isSuccess()const {
				return _isComplete == ResultState::S_DONE;
			}
			bool isFail()const {
				return (isComplete()) && (!isSuccess());
			}
			explicit operator bool()const {
				return isComplete();
			}
			ResultState state() const {
				return _isComplete;
			}
	};

}
