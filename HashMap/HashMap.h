#pragma once
#include "HashNode.h"
#include "DefaultHashFunc.h"


template <typename K, typename V, size_t SIZE, typename F = DefaultHashFunc<K>>
class HashMap{
private:
	
	HashNode<K, V>* arr[SIZE];
	unsigned int size;
	F hashFunc;
	

public:
	HashMap() : arr(), hashFunc(), size(SIZE) {
		for (int i = 0; i < SIZE; i++) arr[i] = nullptr;
	}

	~HashMap();

	HashMap(const HashMap<K, V, SIZE, F>& other);

	HashMap& operator=(HashMap<K, V, SIZE, F> other);

	V operator[](const K key) throw(std::out_of_range);

	std::vector<V> getAllValues(const K key) const;

	bool get(const K& key, V& value) const;

	void add(const K& key, const V& value);

	int distinctKeys() const;

	void remove(const K& key);

	friend std::ostream& operator<<(std::ostream& out, const HashMap& hmap) {
		for (int i = 0; i < hmap.size; i++) {
			if (hmap.arr[i] != nullptr) {
				HashNode<K, V>* it = hmap.arr[i];
				while (it != nullptr) {
					out << it->getKey() << " : " << it->getValue() << std::endl;
					it = it->getNext();

				}
			}
		}
		return out;
	}

};

template<typename K, typename V, size_t SIZE, typename F>
HashMap<K, V, SIZE, F>::~HashMap() {
	for (size_t i = 0; i < SIZE; ++i) {
		delete arr[i];
		arr[i] = nullptr;
	}
}

template<typename K, typename V, size_t SIZE, typename F>
HashMap<K, V, SIZE, F>::HashMap(const HashMap<K, V, SIZE, F>& other) :arr() {
	for (int i = 0; i < SIZE; i++) {
		if (other.arr[i] != nullptr) {
			HashNode<K, V>* tmp = new HashNode<K, V>(*other.arr[i]);
			arr[i] = tmp;
		}
	}
	hashFunc = other.hashFunc;
}

template<typename K, typename V, size_t SIZE, typename F>
std::vector<V> HashMap<K, V, SIZE, F>::getAllValues(const K key) const {
	std::vector<V> rs;
	unsigned long hashValue = hashFunc(key);
	HashNode<K, V>* entry = arr[hashValue];

	while (entry != nullptr) {
		if (entry->getKey() == key) {
			return entry->getAllValues();
		}

		entry = entry->getNext();
	}
	return rs;
}

template<typename K, typename V, size_t SIZE, typename F>
bool HashMap<K, V, SIZE, F>::get(const K& key, V& value) const {
	unsigned long hashValue = hashFunc(key);
	HashNode<K, V>* entry = arr[hashValue];

	while (entry != nullptr) {
		if (entry->getKey() == key) {
			value = entry->getValue();
			return true;
		}
		entry = entry->getNext();
	}
	return false;
}

template<typename K, typename V, size_t SIZE, typename F>
void HashMap<K, V, SIZE, F>::add(const K& key, const V& value) {
	unsigned long hashValue = hashFunc(key);
	HashNode<K, V>* prev = nullptr;
	HashNode<K, V>* entry = arr[hashValue];

	while (entry != nullptr && entry->getKey() != key) {
		prev = entry;
		entry = entry->getNext();
	}

	if (entry == nullptr) {
		entry = new HashNode<K, V>(key, value);

		if (prev == nullptr) {
			arr[hashValue] = entry;
			entry->setIsFirst(true);
		}
		else {
			prev->setNext(entry);
		}

	}
	else {
		entry->setValue(value);
	}
}

template<typename K, typename V, size_t SIZE, typename F>
int HashMap<K, V, SIZE, F>::distinctKeys() const {
	int rs = 0;
	for (int i = 0; i < SIZE; i++) if (arr[i] != nullptr) rs++;
	return rs;
}

template<typename K, typename V, size_t SIZE, typename F>
void HashMap<K, V, SIZE, F>::remove(const K& key) {
	unsigned long hashValue = hashFunc(key);
	HashNode<K, V>* prev = nullptr;
	HashNode<K, V>* entry = arr[hashValue];

	while (entry != nullptr && entry->getKey() != key) {
		prev = entry;
		entry = entry->getNext();
	}

	if (entry == nullptr) {
		return;

	}
	else {
		if (prev == nullptr) {
			arr[hashValue] = entry->getNext();
		}
		else {
			prev->setNext(entry->getNext());
		}

		delete entry;
	}
}

template<typename K, typename V, size_t SIZE, typename F>
V HashMap<K, V, SIZE, F>::operator[](const K key) throw(std::out_of_range) {
	V value;
	if (!get(key, value)) throw std::out_of_range("No element with this key in the hashmap");
	return value;
}

template<typename K, typename V, size_t SIZE, typename F>
HashMap<K,V,SIZE,F>& HashMap<K, V, SIZE, F>::operator=(HashMap<K, V, SIZE, F> other) {
	std::swap(arr, other.arr);
	hashFunc = other.hashFunc;
	return *this;
}