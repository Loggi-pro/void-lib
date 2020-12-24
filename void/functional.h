#pragma once
#include <void/type_traits.h>

namespace vd {
	namespace Private {
		//inline void* operator new (size_t n, void* ptr) { return ptr; };
		template<typename Callable>
		union storage {
			typedef typename remove_reference<Callable>::type T;
			storage() {}

			T callable;
			inline void* operator new (size_t n, void* ptr) { return ptr; };
		};

		//MY PLACEMENT NEW

		template<int, typename Callable, typename Ret, typename... Args>
		auto fnptr_(Callable&& c, Ret(*)(Args...)) {
			static bool used = false;
			static storage<Callable> s;
			using type = typename storage<Callable>::T;

			if (used)
			{ s.callable.~type(); }

			new (&s.callable) type(Callable(c));
			used = true;
			return [](Args... args) -> Ret {
				return Ret(s.callable(args...));
			};
		}
		//make function from lambda
		template<typename Fn, int N = 0, typename Callable>
		Fn * fnptr(Callable && c) {
			return fnptr_<N>(c, (Fn*)nullptr);
		}
	}



	template <typename UnusedType, typename UnusedType2 = UnusedType>
	class delegate_t;


	template <typename ReturnType, typename ... ArgumentTypes>
	class delegate_t <ReturnType(ArgumentTypes ...)> {
			typedef ReturnType(*FunctionT)(ArgumentTypes ...);
		public:

			delegate_t() : mInvoker() {}
			delegate_t(FunctionT f) : mInvoker(f) {}
			ReturnType operator ()(ArgumentTypes ... args) {
				return mInvoker.invoke(args ...);
			}
		private:
			class free_function_holder {
				private:
					FunctionT mFunction;
				public:
					free_function_holder(FunctionT func) : mFunction(func) {}

					ReturnType invoke(ArgumentTypes ... args) {
						return mFunction(args ...);
					}

			};

			free_function_holder mInvoker;
	};


	template <typename ReturnType, typename ... ArgumentTypes, class TObj>
	class delegate_t <ReturnType(ArgumentTypes ...), TObj> {
			typedef ReturnType(TObj::*FunctionT)(ArgumentTypes ...);
		public:
			delegate_t() : mInvoker() {}
			//template <typename FunctionT>
			delegate_t(TObj* obj, FunctionT f) : mInvoker(obj, f) {}
			ReturnType operator ()(ArgumentTypes ... args) {
				return mInvoker.invoke(args ...);
			}

		private:
			class object_function_holder {
				private:
					FunctionT mFunction;
					TObj* mObj;
				public:
					object_function_holder(TObj* obj, FunctionT func) : mObj(obj),
						mFunction(func) {}


					ReturnType invoke(ArgumentTypes ... args) {
						return (*mObj.*mFunction)(args ...);
					}
					void set(TObj* obj) {
						mObj = obj;
					}

			};

			object_function_holder mInvoker;
	};

	template <typename T>
	using fn_ptr = T(*)();


	template <typename T, typename... Args>

	typename vd::enable_if < !vd::is_class<T>::value,
	         fn_ptr<typename vd::func_parser<T>::ResultType >>::type
	bind(T f, Args... args) {
		typedef typename vd::func_parser<T>::ResultType Res;
		return Private::fnptr<Res()>([f, args...]() { return f(args...); });
	}
	template <typename O, typename T, typename... Args>

	typename vd::enable_if <
	vd::is_class <O>::value,
	fn_ptr<typename vd::func_parser<T>::ResultType >>::type
	bind(O& obj, T f, Args... args) {
		typedef typename vd::func_parser<T>::ResultType Res;
		return Private::fnptr<Res()>([&obj, f, args...]() mutable {
			return (obj.*f)(args...);
		});
	}

	struct delegate {
		private:



		public:

			template <typename T, typename... Args>

			static
			/* return type, only for free function*/
			typename vd::enable_if < !vd::is_class<T>::value,
			         delegate_t< typename vd::func_parser<T>::ResultType() >>::type
			make(T f, Args... args) {
				typedef typename vd::func_parser<T>::ResultType Res;
				return delegate_t<Res()>(bind<T, Args...>(f, args...));
			}
			template <typename O, typename T, typename... Args>
			static
			typename vd::enable_if <
			vd::is_class <O>::value,
			delegate_t <typename vd::func_parser<T>::ResultType() >>::type
			make(O& obj, T f, Args... args) {
				typedef typename vd::func_parser<T>::ResultType Res;
				return delegate_t<Res()>(bind<O, T, Args...>(obj, f, args...));
			}

	};
	//	delegate_t<TResultAsync<int>()> task2 = delegate::make(internalFunc2);
	//delegate_t<TResultAsync<int>()> task3 = delegate::make(fsm, &TTestFsm::internalFunc, 5);
	//auto f = bind(internalFunc, 5);
}
