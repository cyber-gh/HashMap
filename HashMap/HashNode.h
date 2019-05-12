#pragma once
#include <vector>

template <typename K, typename V>
class HashNode
{
public:
	HashNode(const K& key, const V& value, bool isFirst = false) :
		_key(key), _value(value), _next(nullptr), _isFirst(isFirst)
	{
	}

	K getKey() const
	{
		return _key;
	}

	V getValue() const
	{
		return _value;
	}

	void setValue(V value)
	{
		_value = value;
	}

	HashNode* getNext() const
	{
		return _next;
	}

	void setNext(HashNode* next)
	{
		_next = next;
	}

	void setNext(HashNode next)
	{
		_next = new HashNode(next);
	}

	HashNode(const HashNode& other) {
		_key = other.getKey();
		_value = other.getValue();
		if (other.getNext() == nullptr) {
			_next = nullptr;
		}
		else {
			HashNode<K, V>* it = new HashNode<K, V>(other._next->_key, other._next->_value);
			HashNode<K, V>* curr = it;
			_next = curr;
			it = it->_next;
			while (it != nullptr) {
				
				HashNode<K, V>* tmp = new HashNode<K, V>(it->_key, it->_value);
				curr->_next = tmp;
				curr = tmp;
				it = it->_next;
			}
		}
	}
	HashNode& operator=(const HashNode& other) {
		std::swap(_key, other._key);
		std::swap(_value, other._value);
		std::swap(_next, other._next);
	}

	~HashNode() {
		if (!_isFirst) return;
		HashNode<K, V>* it = _next;
		HashNode<K, V>* prev = it;
		while (it != nullptr) {
			prev = it;
			it = it->_next;
			delete prev;
			prev = nullptr;
		}
	}

	std::vector<V> getAllValues() {
		std::vector<V> rs;
		HashNode<K, V>* it = this;
		while (it != nullptr) {
			rs.push_back(it->_value);
			it = it->_next;
		}
		return rs;
	}

	void setIsFirst(bool val) {
		_isFirst = val;
	}

private:
	// key-value pair
	K _key;
	V _value;
	bool _isFirst;
	HashNode* _next;
	
};
