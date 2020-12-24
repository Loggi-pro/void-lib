#pragma once
namespace vd {
	namespace details {
// Forward declaration
		template<typename T, bool IS_NATIVE>
		struct TLittleEndian;
		template<typename T, bool IS_NATIVE>
		struct TBigEndian;

		namespace platform {
			struct IS_LE_NATIVE {
				#ifdef IS_LITTLE_ENDIAN
				enum { value = true };
				#else
				enum {value = false};
				#endif
			};


			struct IS_BE_NATIVE {
				#ifdef IS_BIG_ENDIAN
				enum { value = true };
				#else
				enum { value = false };
				#endif
			};
		}





// Little-Endian template

		_PACKED(SINGLE_ARG(template<typename T, bool IS_NATIVE = platform::IS_LE_NATIVE::value>
		                  struct TLittleEndian{}));
//PACKED(SINGLE_ARG(
		template<typename T>
		struct TLittleEndian<T, false> {
			union {
				unsigned char bytes[sizeof(T)];
				T raw_value;
			};
			TLittleEndian(T t = T()) {
				operator =(t);
			}
			TLittleEndian(const TLittleEndian<T, false>& t) {
				raw_value = t.raw_value;
			}
			TLittleEndian(const TBigEndian<T, true>& t) {
				for (unsigned i = 0; i < sizeof(T); i++)
				{ bytes[i] = t.bytes[sizeof(T) - 1 - i]; }
			}
			operator const T() const {
				T t = T();

				for (unsigned i = 0; i < sizeof(T); i++)
				{ t |= T(bytes[i]) << (i << 3); }

				return t;
			}
			const T operator = (const T t) {
				for (unsigned i = 0; i < sizeof(T); i++)
				{ bytes[i] = t >> (i << 3); }

				return t;
			}
// operators
			const T operator += (const T t) {
				return (*this = *this + t);
			}
			const T operator -= (const T t) {
				return (*this = *this - t);
			}
			const T operator *= (const T t) {
				return (*this = *this * t);
			}
			const T operator /= (const T t) {
				return (*this = *this / t);
			}
			const T operator %= (const T t) {
				return (*this = *this % t);
			}
			TLittleEndian<T, false> operator ++ (int) {
				TLittleEndian<T, false> tmp(*this);
				operator ++ ();
				return tmp;
			}
			TLittleEndian<T, false>& operator ++ () {
				for (unsigned i = 0; i < sizeof(T); i++) {
					++bytes[i];

					if (bytes[i] != 0)
					{ break; }
				}

				return (*this);
			}
			TLittleEndian<T, false> operator -- (int) {
				TLittleEndian<T, false> tmp(*this);
				operator -- ();
				return tmp;
			}
			TLittleEndian<T, false>& operator -- () {
				for (unsigned i = 0; i < sizeof(T); i++) {
					--bytes[i];

					if (bytes[i] != (T)(-1))
					{ break; }
				}

				return (*this);
			}
		}
//))
		;

_PACKED(SINGLE_ARG(
		template<typename T>
		struct TLittleEndian<T, true> {
			union {
				unsigned char bytes[sizeof(T)];
				T raw_value;
			};
			TLittleEndian(T t = T()) {
				operator =(t);
			}
			TLittleEndian(const TLittleEndian<T, true>& t) {
				raw_value = t.raw_value;
			}
			TLittleEndian(const TBigEndian<T, false>& t) {
				for (unsigned i = 0; i < sizeof(T); i++) {
					bytes[i] = t.bytes[sizeof(T) - 1 - i];
				}
			}
			operator const T() const {
				return raw_value;
			}
			const T operator = (const T t) {
				raw_value = t;
				return t;
			}
			// operators
			const T operator += (const T t) {
				return (*this = *this + t);
			}
			const T operator -= (const T t) {
				return (*this = *this - t);
			}
			const T operator *= (const T t) {
				return (*this = *this * t);
			}
			const T operator /= (const T t) {
				return (*this = *this / t);
			}
			const T operator %= (const T t) {
				return (*this = *this % t);
			}
			TLittleEndian<T, true> operator ++ (int) {
				TLittleEndian<T, true> tmp(*this);
				operator ++ ();
				return tmp;
			}
			TLittleEndian<T, true>& operator ++ () {
				++raw_value;
				return (*this);
			}
			TLittleEndian<T, true> operator -- (int) {
				TLittleEndian<T, true> tmp(*this);
				operator -- ();
				return tmp;
			}
			TLittleEndian<T, true>& operator -- () {
				--raw_value;
				return (*this);
			}
		}
))
		;
// Big-Endian template
		_PACKED(SINGLE_ARG(template<typename T, bool IS_NATIVE = platform::IS_BE_NATIVE::value>
		                  struct TBigEndian {}));

		_PACKED(SINGLE_ARG(template<typename T>
		struct TBigEndian<T, false> {
			union {
				unsigned char bytes[sizeof(T)];
				T raw_value;
			};
			TBigEndian(T t = T()) {
				operator =(t);
			}
			TBigEndian(const TBigEndian<T, false>& t) {
				raw_value = t.raw_value;
			}
			TBigEndian(const TLittleEndian<T, true>& t) {
				for (unsigned i = 0; i < sizeof(T); i++) {
					bytes[i] = t.bytes[sizeof(T) - 1 - i];
				}
			}
			operator const T() const {
				T t = T();

				for (unsigned i = 0; i < sizeof(T); i++) {
					t |= T(bytes[sizeof(T) - 1 - i]) << (i << 3);
				}

				return t;
			}
			const T operator = (const T t) {
				for (unsigned i = 0; i < sizeof(T); i++) {
					bytes[sizeof(T) - 1 - i] = t >> (i << 3);
				}

				return t;
			}
			// operators
			const T operator += (const T t) {
				return (*this = *this + t);
			}
			const T operator -= (const T t) {
				return (*this = *this - t);
			}
			const T operator *= (const T t) {
				return (*this = *this * t);
			}
			const T operator /= (const T t) {
				return (*this = *this / t);
			}
			const T operator %= (const T t) {
				return (*this = *this % t);
			}
			TBigEndian<T, false> operator ++ (int) {
				TBigEndian<T, false> tmp(*this);
				operator ++ ();
				return tmp;
			}
			TBigEndian<T, false>& operator ++ () {
				for (unsigned i = 0; i < sizeof(T); i++) {
					++bytes[sizeof(T) - 1 - i];

					if (bytes[sizeof(T) - 1 - i] != 0) {
						break;
					}
				}

				return (*this);
			}
			TBigEndian<T, false> operator -- (int) {
				TBigEndian<T, false> tmp(*this);
				operator -- ();
				return tmp;
			}
			TBigEndian<T, false>& operator -- () {
				for (unsigned i = 0; i < sizeof(T); i++) {
					--bytes[sizeof(T) - 1 - i];

					if (bytes[sizeof(T) - 1 - i] != (T)(-1)) {
						break;
					}
				}

				return (*this);
			}
		}));
		_PACKED(SINGLE_ARG(template<typename T>
		struct TBigEndian<T, true> {
			union {
				unsigned char bytes[sizeof(T)];
				T raw_value;
			};
			TBigEndian(T t = T()) {
				operator =(t);
			}
			TBigEndian(const TBigEndian<T, true>& t) {
				raw_value = t.raw_value;
			}
			TBigEndian(const TLittleEndian<T, false>& t) {
				for (unsigned i = 0; i < sizeof(T); i++) {
					bytes[i] = t.bytes[sizeof(T) - 1 - i];
				}
			}
			operator const T() const {
				return raw_value;
			}
			const T operator = (const T t) {
				raw_value = t;
				return t;
			}
			// operators
			const T operator += (const T t) {
				return (*this = *this + t);
			}
			const T operator -= (const T t) {
				return (*this = *this - t);
			}
			const T operator *= (const T t) {
				return (*this = *this * t);
			}
			const T operator /= (const T t) {
				return (*this = *this / t);
			}
			const T operator %= (const T t) {
				return (*this = *this % t);
			}
			TBigEndian<T, true> operator ++ (int) {
				TBigEndian<T, true> tmp(*this);
				operator ++ ();
				return tmp;
			}
			TBigEndian<T, true>& operator ++ () {
				++raw_value;
				return (*this);
			}
			TBigEndian<T, true> operator -- (int) {
				TBigEndian<T, true> tmp(*this);
				operator -- ();
				return tmp;
			}
			TBigEndian<T, true>& operator -- () {
				--raw_value;
				return (*this);
			}
		}));
	}
}