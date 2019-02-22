#ifndef MYSET_HPP
#define MYSET_HPP

#include <ostream>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <stdexcept>
#include <cassert>

/**
 * @file myset.hpp
 * @brief Declaration of the class MySet
**/

/**
 * @brief Dynamic set of template type T
 * 
 * This class represents a dynamic set of template type T.
 * MySet is a dynamic set in which is not allowed duplicate elements.
 * It is possible to add a new element if it isn't already in the set, 
 * and remove an existing one. 
 * @tparam T The type of the elements contained in MySet.
 * @tparam E The functor used to check if two elements in MySet are equals or not. 
**/
template <typename T, typename E>
class MySet {

    struct Node {

        T value;
        Node* next;

        Node() : next(0) {}
        Node(const Node& other) : value(other.value), next(other.next) {}
        explicit Node(const T& v) : value(v), next(0) {}

    };

    Node* _head; 
    Node* _tail; 
    unsigned int _size; 
    E _equal;

    void swap(MySet& other) {
        std::swap(_head, other._head);
        std::swap(_tail, other._tail);
        std::swap(_size, other._size);
    }

    bool findValue(const T& value) const {
        Node* currentNode = _head;
        bool valueFound = false;
        while(currentNode != 0 && !valueFound) {
            if(_equal(currentNode->value, value))
                valueFound = true;
            else
                currentNode = currentNode->next;
        }
        return valueFound;
    }

    void removeAll() {
        Node* currentNode = _head;
        while(currentNode != 0) {
            Node* tmp = currentNode->next;
            delete currentNode;
            currentNode = 0;
            currentNode = tmp;
        }
        _head = 0;
        _size = 0;
        _tail = 0;
    }

public:

    /**
     * @brief Default constructor
     * 
     * Default constructor allows to create an empty MySet.
     * It is the only constructor that allows to create an array of MySet.
    **/
    MySet() : _head(0), _tail(0), _size(0) {}

    /**
     * @brief Copy constructor
     * 
     * This allows to create a MySet from another MySet, passed by reference.
     * @param other Const reference to another MySet used to create the current MySet.
     * @throw std::exception if something goes wrong during the construction.
    **/
    MySet(const MySet& other) : _head(0), _tail(0), _size(0) {
        Node* currentNode = other._head;
        try {
            while(currentNode != 0) {
                add(currentNode->value);
                currentNode = currentNode->next;
            }
        }
        catch(...) {
            removeAll();
            throw;
        }
    }

    /**
     * @brief Extra constructor with iterator
     * 
     * This constructor allows to create a MySet from iterators.
     * @tparam Q The type of the iterators passed as parameter.
     * @param b Begin iterator.
     * @param e End iterator.
     * @throw std::exception if something goes wrong during the construction.
     */
    template <typename Q>
    MySet(Q b, Q e) : _head(0), _tail(0), _size(0) {
        try {
            while(b != e) {
                add(static_cast<T>(*b));
                ++b;
            }
        }
        catch(...){
            removeAll();
            throw;
        }
    }

    /**
     * @brief Assignment operator
     * 
     * It allows to assign another MySet to the current MySet.
     * @param other Const reference to another MySet that will be assigned to  the current MySet.
     * @return Reference to the current MySet.
    **/
    MySet& operator=(const MySet& other) {
        if(this != &other) {
            MySet tmp(other);
            swap(tmp);
        }
        return *this;
    }

    /**
     * @brief Destroyer
     * 
     * It destroys the current MySet destroying all his elements.
    **/
    ~MySet() {
        removeAll();
    }

    /**
     * @brief The size of the current MySet
     * 
     * It allows to get the size of the current Myset.
     * @return current MySet's size.
    **/
    unsigned int size() const {
        return _size;
    }

    /**
     * @brief Add a new element
     * 
     * It allows to add a new element inside the current MySet, only if does not already exist.
     * @param value Const reference to the element that will be added.
     * @throw std::runtime_error in the case of a duplicate element.
    **/
    void add(const T& value) {
        Node* newNode = new Node(value);
        if(_head == 0) {
            _head = newNode;
            _tail = newNode;
        }
        else {
            bool valueFound = findValue(value);
            if(valueFound) {
                delete newNode;
                newNode = 0;
                throw std::runtime_error("MySet.add(value) - The value already exists");
            }
            else {
                _tail->next = newNode;
                _tail = newNode;
            }
        }
        ++_size;
    }

    /**
     * @brief Remove an existing element
     * 
     * It allows to remove an existing element from the current MySet.
     * @param Const reference to the element that will be removed from the current MySet, only if it exists.
     * @throw std::runtime_error if the element isn't in the current MySet.
    **/
    void remove(const T& value) {
        Node* prev = _head;
        Node* currentNode = _head;
        bool elementDeleted = false;
        while(currentNode != 0 && !elementDeleted) {
            if(_equal(currentNode->value, value)) {
                if(currentNode == _head && currentNode != _tail)
                    _head = _head->next;
                else if(currentNode == _tail && currentNode != _head) {
                    prev->next = 0;
                    _tail = prev;
                }
                else if(currentNode == _head && currentNode == _tail) {
                    _head = 0;
                    _tail = 0;
                }
                else
                    prev->next = currentNode->next;
                delete currentNode;
                elementDeleted = true;
            }
            else {
                prev = currentNode;
                currentNode = currentNode->next; 
            }
        }
        if(currentNode == 0)
            throw std::runtime_error("MySet.remove(value) - value does not exist");
        else
            --_size;
    }

    /**
     * @brief Random access
     * 
     * It allows to access to the element in a specified position.
     * The element returned can't be modified, it is read-only.
     * Note that, if the specified position is out of range, an assertion will fail.
     * @param index The position of the element that will be returned.
     * @return Const reference to the element in a specified position.
    **/
    const T& operator[](unsigned int index) const {
        assert(index < _size);
        Node* currentNode = _head;
        T* value = 0;
        unsigned int i = 0;
        while(currentNode != 0 && i <= index) {
            if(i == index)
                value = &(currentNode->value);
            currentNode = currentNode->next;
            ++i;
        }
        return *value;
    }

    /**
     * @brief Const forward iterator of MySet class
     * 
     * This class allows to iterate on the elements contained in the current MySet.
     * Since it is a forward_iterator type, the iteration can be done only from the beginning to the end.
    **/
    class const_iterator {
		const Node* _node;	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

        /**
         * @brief Defult constructor
         * 
         * It allows to create an empty const_iterator.
        **/
		const_iterator() : _node(0){}
		
        /**
         * @brief Copy constructor
         * 
         * It allows to create a new const_iterator from another const_iterator, passed by reference.
         * @param other Const reference to another const_iterator.
        **/
		const_iterator(const const_iterator& other) : _node(other._node){}

        /**
         * @brief Assignment operator
         * 
         * It allows to assign another const_iterator to the current const_iterator.
         * @param other Const reference to another const_iterator that will be assigned to the current const_iterator.
         * @return Reference to the current const_iterator.
        **/
		const_iterator& operator=(const const_iterator &other) {
			_node = other._node;
			return *this;
		}

        /**
         * @brief Destroyer
         * 
         * It destoys the current const_iterator.
        **/
		~const_iterator() {}

        /**
         * @brief Dereferance operator
         * 
         * It allows to retrieve a reference to the current element.
         * @return A reference to the current element contained in the current const_iterator.
        **/
		reference operator*() const {
			return _node -> value;
		}

		/**
         * @brief Arrow operator
         * 
         * It allows to retrieve a pointer to the current element.
         * @return A pointer to the current element contained in the current const_iterator.
        **/
		pointer operator->() const {
			return &(_node->value);
		}

        /**
         * @brief Post-increment operator
         * 
         * It allows the current const_iterator to point to the next element.
         * @return Reference to the current const_iterator.
        **/
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			_node = _node -> next;
			return tmp;
		}

        /**
         * @brief Pre-increment operator
         * 
         * It allows to the current const_iterator to increase himself before use.
         * @return The same const_iterator.
        **/
		const_iterator& operator++() {
			_node = _node->next;
			return *this;
		}

        /**
         * @brief Equal operator
         * 
         * It allows to compare the current const_itererator with another const_iterator.
         * @param other Const reference to another const_iterator that will be compared with the current const_iterator.
         * @return True if the current const_iterator is equal to the other const_iterator passed. Otherwise false. 
        **/
		bool operator==(const const_iterator& other) const {
			return _node == other._node;
		}
		
        /**
         * @brief Unequal operator
         * 
         * It allows to compare the current const_itererator with another const_iterator.
         * @param other Const reference to another const_iterator that will be compared with current const_iterator.
         * @return True if current const_iterator is unequal to the other const_iterator passed. Otherwise false. 
        **/
		bool operator!=(const const_iterator& other) const {
			return _node != other._node;
		}

	private:

		friend class MySet;
        
		const_iterator(const Node* node) : _node(node){}
		
	};

    /**
     * @brief The beginning of the series of elements
     * 
     * It allows to retrieve the const_iterator to the first element in the current MySet.
     * @return Const_iterator that points to the first element.
    **/

	const_iterator begin() const {
		return const_iterator(_head);
	}
	
    /**
     * @brief The end of the series of elements
     * 
     * It allows to retrive the const_iterator to the end of the series of elements in the current MySet.
     * @return Const_iterator that points to the end of the series of elements.
    **/
	const_iterator end() const {
		return const_iterator(0);
	}

};

/**
 * @brief Stream out operator
 * 
 * This method allows to print a MySet.
 * @tparam T The type of the elements contained in MySet.
 * @tparam E The functor used to check if two elements in MySet are equals or not.
 * @param os Reference to a std::ostream object.
 * @param mySet Const reference to a MySet of type T and with E functor to check the equality of his elements.
 * @return A reference to std::ostream os, filled with the elements contained in mySet.
**/
template <typename T, typename E>
std::ostream& operator<<(std::ostream& os, const MySet<T, E>& mySet) {
    typename MySet<T, E>::const_iterator i = mySet.begin(), e = mySet.end();
    os << "{";
	while(i != e){
		os << *i;
		if(++i != e)
			os << ", ";
	}
    os << "}";
    return os;
}

/**
 * @brief Global method
 * 
 * This method filters a MySet removing the elements that satisfy the functor pred.
 * @tparam T The type of the elements contained in MySet.
 * @tparam E The functor used to check if two elements in MySet are equals or not.
 * @tparam P The functor used to filter the elements contained in MySet.
 * @param mySet Const reference to a MySet of type T and with E functor to check the equality of his elements.
 * @param pred Const reference to a functor of type P passed as parameter.
 * @return A copy of a new MySet filtered without elements that satisfy pred.
**/
template<typename T, typename E, typename P>
MySet<T, E> filter_out(const MySet<T, E>& mySet, const P& pred) {
    typename MySet<T, E>::const_iterator b = mySet.begin(), e = mySet.end();
    MySet<T, E> result;
    while(b != e){
        if(!pred(*b))
            result.add(*b);
        ++b;
    }
    return result;
}

/**
 * @brief Concatenation operator
 * 
 * This method concats two MySet.
 * @tparam T The type of the elements contained in MySet.
 * @tparam E The functor used to check if two elements in MySet are equals or not.
 * @param sx Const reference to a MySet of type T and with E functor to check the equality of his elements.
 * @param dx Const reference to a MySet of type T and with E functor to check the equality of his elements.
 * @return A copy of a new MySet optained by the concatenation of two MySet passed as parameter.
**/
template<typename T, typename E>
MySet<T, E> operator+(const MySet<T, E>& sx, const MySet<T, E>& dx) {
	MySet<T, E> result(sx);
	typename MySet<T, E>::const_iterator b = dx.begin(), e = dx.end();
	while(b != e){
		result.add(*b);
		++b;
	}
	return result;
}
#endif