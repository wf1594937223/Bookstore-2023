#pragma once
#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include <memory>
#include <cstddef>

namespace sjtu {


/**
 * @tparam T Type of the elements.
 * Be careful that T may not be default constructable.
 * 
 * @brief A list that supports operations like std::list.
 * 
 * We encourage you to design the implementation yourself.
 * As for the memory management, you may use std::allocator,
 * new/delete, malloc/free or something else.
*/
template <typename T>
class list {
  public:
    class iterator;
    class const_iterator;

  public:
	struct node
	{
		T val;
		node *pre, *next;
		node(const T& value)
		{
			pre = nullptr; next = nullptr;
			val = value;
		}
	};
	node *head, *tail;
	size_t siz;

  public:

    /**
     * Constructs & Assignments
     * At least three: default constructor, copy constructor/assignment
     * Bonus: move/initializer_list constructor/assignment
     */
    list()
	{
		node *tmp = new node(0);
		head = tmp; tail = tmp;
		siz = 0;
	}
    list(const list &other)
	{
		node *tmp = new node(0);
		head = tmp; tail = tmp;
		siz = 0;
		node *now = other.head;
		while (now != nullptr)
		{
			push_back(now->val);
			now = now->next;
		}
	}
    list &operator=(const list &other)
	{
		if (this == &other) return *this;
		clear();
		node *now = other.head;
		while (now != tail)
		{
			push_back(now->val);
			now = now->next;
		}
		return *this;
	}

    /* Destructor. */
    ~list()
	{
		clear();
		delete tail;
	}

    /* Access the first / last element. */
    T &front() noexcept
	{
		return head->val;
	}
    T &back()  noexcept
	{
		return (tail->pre)->val;
	}
    const T &front() const noexcept
	{
		return head->val;
	}
    const T &back()  const noexcept
	{
		return (tail->pre)->val;
	}

    /* Return an iterator pointing to the first element. */
    iterator begin() noexcept
	{
		return iterator(head);
	}
    const_iterator cbegin() const noexcept
	{
		return const_iterator(head);
	}

    /* Return an iterator pointing to one past the last element. */
    iterator end() noexcept
	{
		return iterator(tail);
	}
    const_iterator cend() const noexcept
	{
		return const_iterator(tail);
	}

    /* Checks whether the container is empty. */
    bool empty() const noexcept
	{
		if (siz) return false;
		else return true;
	}
    /* Return count of elements in the container. */
    size_t size() const noexcept
	{
		return siz;
	}

    /* Clear the contents. */
    void clear() noexcept
	{
		while (siz)
		{
			siz--;
			node *tmp = head;
			head = head->next;
			delete tmp;
		}
	}

    /**
     * @brief Insert value before pos (pos may be the end() iterator).
     * @return An iterator pointing to the inserted value.
     * @throw Throw if the iterator is invalid.
     */
    iterator insert(iterator pos, const T &value)
	{
		if (pos.now == nullptr) throw "Throw";
		node *tmp = new node(value);
		tmp->pre = (pos.now)->pre; tmp->next = (pos.now);
		if ((pos.now)->pre != nullptr) ((pos.now)->pre)->next = tmp;
		else head = tmp;
		(pos.now)->pre = tmp;
		siz++;
		return iterator(tmp);
	}

    /**
     * @brief Remove the element at pos (remove end() iterator is invalid).
     * returns an iterator pointing to the following element, if pos pointing to
     * the last element, end() will be returned.
     * @throw Throw if the container is empty, or the iterator is invalid.
     */
    iterator erase(iterator pos) noexcept
	{
		if (pos.now == nullptr || pos.now == tail) throw "Throw";
		if ((pos.now)->pre == nullptr)
		{
			((pos.now)->next)->pre = nullptr;
			head = (pos.now)->next;
			siz--;
			delete (pos.now);
			return iterator((pos.now)->next);
		}
		((pos.now)->next)->pre = (pos.now)->pre;
		((pos.now)->pre)->next = (pos.now)->next;
		delete (pos.now);
		return iterator((pos.now)->next);
	}

    /* Add an element to the front/back. */
    void push_front(const T &value)
	{
		insert(iterator(head), value);
		return;
	}
    void push_back (const T &value)
	{
		insert(iterator(tail), value);
		return;
	}

    /* Removes the first/last element. */
    void pop_front() noexcept
	{
		erase(iterator(head));
		return;
	}
    void pop_back () noexcept
	{
		erase(iterator(tail->pre));
		return;
	}

  public:

    /**
     * Basic requirements:
     * operator ++, --, *, ->
     * operator ==, != between iterators and const iterators
     * constructing a const iterator from an iterator
     * 
     * If your implementation meets these requirements,
     * you may not comply with the following template.
     * You may even move this template outside the class body,
     * as long as your code works well.
     * 
     * Contact TA whenever you are not sure.
     */
    class iterator
	{
      private:
        /**
         * TODO just add whatever you want.
         */
		node *now;

      public:
	    iterator (node* tmp)
		{
			now = tmp;
		}
        iterator &operator++()
		{
			now = now->next;
			return (*this);
		}
        iterator &operator--()
		{
			now = now->pre;
			return (*this);
		}
        iterator operator++(int)
		{
			iterator tmp = *this;
			now = now->next;
			return tmp;
		}
        iterator operator--(int)
		{
			iterator tmp = *this;
			now = now->pre;
			return tmp;
		}

        T &operator*()  const noexcept
		{
			return now->val;
		}
        T *operator->() const noexcept
		{
			return &(now->val);
		}

        /* A operator to check whether two iterators are same (pointing to the same memory) */
        friend bool operator == (const iterator &a, const iterator &b)
		{
			return a.now == b.now;
		}
        friend bool operator != (const iterator &a, const iterator &b)
		{
			return a.now != b.now;
		}
    };

    /**
     * Const iterator should have same functions as iterator, just for a const object.
     * It should be able to construct from an iterator.
     * It should be able to compare with an iterator.
     */
    class const_iterator
	{
      private:
        /**
         * TODO just add whatever you want.
         */
		node *now;

      public:
	    const_iterator (const iterator &tmp)
		{
			now = tmp.now;
		}
	    const_iterator (node* tmp)
		{
			now = tmp;
		}

        const T &operator*()  const noexcept
		{
			return now->val;
		}
        const T *operator->() const noexcept
		{
			return &(now->val);
		}

        /* A operator to check whether two iterators are same (pointing to the same memory) */
        friend bool operator == (const iterator &a, const iterator &b)
		{
			return a.now == b.now;
		}
        friend bool operator != (const iterator &a, const iterator &b)
		{
			return a.now != b.now;
		}
    };
};

} // namespace sjtu

#endif // SJTU_LIST_HPP
