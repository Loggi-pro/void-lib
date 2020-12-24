#pragma once
#include <void/meta.h>
#include <void/type_traits.h>
#include <void/tuple.h>
namespace vd {

	template <typename ROOT, typename ... CHILDREN>
	struct tree {
		ROOT value;
		vd::tuple<CHILDREN...> children;

		//static constexpr const size_t childCount = sizeof...(CHILDREN);

		//tree(TreeLocation)
		template <class LOC>
		auto& subtree(const LOC& location) {

			if constexpr (location.isRoot()) {
				return *this;
			}
			else {
				//	return child<location.head()>().subtree(location.tail());
				return child<LOC::head>().subtree(location.tail());
			}
			//}
		}

		constexpr tree() = default;

		template <typename ROOT_ARG>
		constexpr tree(ROOT_ARG&& rootArgs) : value(vd::forward<ROOT_ARG>(rootArgs)) {

		}


		template <size_t INDEX>
		auto& child() {
			return vd::get<INDEX>(children);
		}
	};


	template <class SEQ>
	struct Location {
	private:
		template <typename T>
		struct value_extractor {};
		template<typename T>
		struct value_extractor<vd::fn::just_type<T>> {
			constexpr static size_t value = T::value;
		};

		template<>
		struct value_extractor<vd::fn::empty_list> {
			constexpr static size_t value = 0;
		};


	public:
		constexpr Location() = default;
		template <size_t index>
		constexpr static auto ofChild() {
			vd::fn::just_type<vd::integral_constant<size_t, index>> newValue;
			return Location <decltype(vd::fn::push_back(SEQ{}, newValue)) > {};
		}
		constexpr static auto ofParent() {
			return Location <decltype(vd::fn::pop_back(SEQ{})) > {};
		}
		constexpr static bool isRoot() {
			return vd::is_same<SEQ, vd::fn::empty_list>::value;
		}
		using value_type = decltype(vd::fn::head(SEQ{}));
		constexpr static size_t head = value_extractor<value_type>::value;
		/*constexpr static size_t head() {
			return decltype(vd::fn::head(SEQ{}))::type::value;
		}*/
		constexpr static auto tail() {
			return Location<decltype (vd::fn::tail(SEQ{})) > {};
		}

	};


	template <class TREE, class LOC>
	struct context {
		TREE& tr;
		using location = LOC;
		constexpr context(TREE& tree) : tr(tree) {}
		constexpr context(TREE& tree, LOC& location) : tr(tree) {}
		template <typename M>
		void sendDown(const M& message) {
			auto& parentTree = tr.subtree(LOC{});
			parentTree.children.times.with_index([&](const auto val) {
				const size_t index = decltype(val)::value;
				auto childLocation = LOC::template ofChild<index>();
				context<TREE, decltype(childLocation)> childContext{ tr,childLocation };
				auto& newTree = tr.subtree(childLocation);
				newTree.value.handle(message, childContext);
				childContext.sendDown(message);
				});
		}
		template <typename M>
		void sendUp(const M& message) {
			if constexpr (!LOC::isRoot()) {
				auto parentLocation = LOC::ofParent();
				auto& parentTree = tr.subtree(parentLocation);
				context<decltype(parentTree), decltype(parentLocation)> parentContext{ parentTree,parentLocation };
				parentTree.value.handle(message, parentContext);
				parentContext.sendUp(message);
			}
		}

	};

template<class TREE> context(TREE&)->context < TREE, Location<vd::fn::empty_list>>; // #3
}
/*


struct start {};
struct tick  {};
struct tock  {};
struct ping  {};
struct tick_tock {
	template <typename Context>
	void handle(const start& message, Context context) {
		std::cout << "start: " << std::endl;
		context.sendDown(tick{});
	}
	template <typename Context>
	void handle(const tock& message, Context context) {
		std::cout << "tock tick_tock!" << std::endl;
	}
	template <typename Context>
	void handle(const tick& message, Context context) {
		std::cout << "tick tick_tock!" << std::endl;
	}
	template <typename Context>
	void handle(const ping& message, Context context) {
		std::cout << "ping tick_tock!" << std::endl;
	}

};


struct responder {
	template <typename Context>
	void handle(const tick& message, Context context) {
		std::cout << "tick responder!" << std::endl;
		context.sendUp(tock{});
	}

	template <typename Context>
	void handle(const tock& message, Context context) {
		std::cout << "tock responder!" << std::endl;
		//context.sendUp(tock{});
	}

	template <typename Context>
	void handle(const ping& message, Context context) {
		std::cout << "ping responder!" << std::endl;
	}
	template <typename Context>
	void handle(const start& message, Context context) {
		//std::cout << "ping responder!" << std::endl;
	}
};

//....

tree<tick_tock,
		tree<responder>, tree<responder>> t;
	context ctx{ t};
	auto& child = t.child<0>();
	t.value.handle(start{},ctx);
	const auto a = Location<vd::fn::list<vd::integral_constant<size_t, 0>>>::head;
	auto& z = t.child<a>();
	*/