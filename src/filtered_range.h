/**
 * @file filtered_range.h
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Jul, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Class to browse a vector filtered by a predicate
 */
#ifndef SRC_FILETERED_RANGE_H_
#define SRC_FILETERED_RANGE_H_

#include <algorithm>

template<typename T, typename Predicate, typename Container = std::vector<T> >
class FilteredRange {
public:
	typedef typename Container::reference reference;
	typedef typename Container::const_reference const_reference;
	typedef typename Container::reference pointer;
	typedef typename Container::const_reference const_pointer;

private:
	typedef typename Container::iterator container_iterator;

	/// internal implementation class (implementation-defined)
	template<typename BaseIterator>
	class iterator_impl {
		friend class cci_filtered_range;

	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef typename BaseIterator::value_type value_type;
		typedef typename BaseIterator::difference_type difference_type;
		typedef typename BaseIterator::pointer pointer;
		typedef typename BaseIterator::reference reference;

		iterator_impl() :
				m_current(), m_fr(NULL) {
		}
		;

	private:
		iterator_impl(container_iterator it) :
				m_current(it), m_fr(NULL) {
		}

		iterator_impl(container_iterator it, const FilteredRange* fr) :
				m_current(it), m_fr(fr) {
		}

	public:
		iterator_impl& operator--() {
			decrement();
			return *this;
		}

		iterator_impl& operator++() {
			increment();
			return *this;
		}

		iterator_impl operator--(int) {
			iterator_impl ret = *this;
			decrement();
			return ret;
		}

		iterator_impl operator++(int) {
			iterator_impl ret = *this;
			increment();
			return ret;
		}

		reference operator*() const {
			return *m_current;
		}

		pointer operator->() const {
			return &(*m_current);
		}

		bool operator==(const iterator_impl& it) const {
			return m_current == it.m_current;
		}

		bool operator!=(const iterator_impl& it) const {
			return !(*this == it);
		}

	private:
		void increment() {
			if (m_fr) {
				if (m_current != m_fr->m_container.end()) {
					++m_current;
				}
				while ((m_current != m_fr->m_container.end())
						&& (!m_fr->m_pred(*(m_current)))) {
					++m_current;
				}
			}
		}

		void decrement() {
			if (m_fr) {
				if (m_current != m_fr->m_begin) {
					--m_current;
				}
				while ((m_current != m_fr->m_begin)
						&& (!m_fr->m_pred(*(m_current)))) {
					--m_current;
				}
			}
		}

		container_iterator m_current;
		const FilteredRange* m_fr;
	};

public:
	typedef iterator_impl<typename Container::iterator> iterator;
	typedef iterator_impl<typename Container::const_iterator> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	FilteredRange(const Predicate& pred, const Container& container) :
			m_pred(pred), m_container(container), m_begin(m_container.begin(),
					this) {
		init();
	}

	iterator begin() {
		return m_begin;
	}

	iterator end() {
		return m_container.end();
	}

	const_iterator begin() const {
		const_iterator it(m_begin.m_current, this);
		return it;
	}

	const_iterator end() const {
		return m_container.end();
	}

	const_iterator cbegin() const {
		return begin();
	}

	const_iterator cend() const {
		return end();
	}

	reverse_iterator rbegin() {
		return reverse_iterator(iterator(m_container.end(), this));
	}

	const_reverse_iterator rbegin() const {
		return crbegin();
	}

	const_reverse_iterator crbegin() const {
		return const_reverse_iterator(const_iterator(m_container.end(), this));
	}

	reverse_iterator rend() {
		return reverse_iterator(iterator(m_begin.m_current, this));
	}

	const_reverse_iterator rend() const {
		return crend();
	}

	const_reverse_iterator crend() const {
		return const_reverse_iterator(const_iterator(m_begin.m_current, this));
	}

public:
	void init() {
		if ((m_begin != end()) && (!m_pred(*m_begin))) {
			++m_begin; // Internally call increment() to setup the invariant
		}
	}

	Predicate m_pred;
	Container m_container;
	iterator m_begin;
};

#endif /* SRC_FILETERED_RANGE_H_ */
