#pragma once
#include <vector>

template <typename K, typename V>
class HashNode{
private:
	K key;
	V value;
	bool isFirst;
	HashNode* next;


public:
	HashNode(const K& __key, const V& __value, bool __isFirst = false) :
		key(__key), value(__value), next(nullptr), isFirst(__isFirst)
	{}

	K getKey() const {
		return key;
	}

	V getValue() const {
		return value;
	}

	void setValue(V value){
		value = value;
	}

	HashNode* getNext() const {
		return next;
	}

	void setNext(HashNode* __next) {
		next = __next;
	}

	void setNext(HashNode __next) {
		next = new HashNode(__next);
	}

	void setIsFirst(bool val) {
		isFirst = val;
	}

	HashNode(const HashNode& other);

	HashNode& operator=(const HashNode& other);

	~HashNode();

	std::vector<V> getAllValues();
};

template<typename K, typename V>
HashNode<K, V>::HashNode(const HashNode& other) {
	key = other.getKey();
	value = other.getValue();
	if (other.getNext() == nullptr) {
		next = nullptr;
	}
	else {
		HashNode<K, V>* it = new HashNode<K, V>(other.next->key, other.next->value);
		HashNode<K, V>* curr = it;
		next = curr;
		it = it->next;
		while (it != nullptr) {

			HashNode<K, V>* tmp = new HashNode<K, V>(it->key, it->value);
			curr->next = tmp;
			curr = tmp;
			it = it->next;
		}
	}
}

template<typename K, typename V>
HashNode<K, V>::~HashNode() {
	if (!isFirst) return;
	HashNode<K, V>* it = next;
	HashNode<K, V>* prev = it;
	while (it != nullptr) {
		prev = it;
		it = it->next;
		delete prev;
		prev = nullptr;
	}
}

template<typename K, typename V>
std::vector<V> HashNode<K, V>::getAllValues() {
	std::vector<V> rs;
	HashNode<K, V>* it = this;
	while (it != nullptr) {
		rs.push_back(it->value);
		it = it->next;
	}
	return rs;
}

template<typename K, typename V>
HashNode<K,V>& HashNode<K, V>::operator=(const HashNode& other) {
	std::swap(key, other.key);
	std::swap(value, other.value);
	std::swap(next, other.next);
}