/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef ALLOC_HPP
#define ALLOC_HPP

namespace utils {
	template<typename T>
	T* alloc(const T& data) {
		return new T(data);
	}
}

#endif
