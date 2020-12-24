#pragma once
namespace vd {
template<typename T>
struct optional_t {
	bool res;
	T value;
	optional_t(): res(false), value() {}
	optional_t(T val): res(true), value(val) {}
	explicit operator bool() const {
		return res;
	}
	T& operator *() {
		return value;
	}
	const T& operator *()const {
		return value;
	}
};

}