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

	~HashMap(){
		for (size_t i = 0; i < SIZE; ++i) {
			delete arr[i];
			arr[i] = nullptr;
		}
	}

	HashMap(const HashMap<K,V,SIZE,F> & other):arr() {
		for (int i = 0; i < SIZE; i++) {
			if (other.arr[i] != nullptr) {
				HashNode<K, V>* tmp = new HashNode<K, V>(*other.arr[i]);
				arr[i] = tmp;
			}
		}
		hashFunc = other.hashFunc;
	} 

	HashMap& operator=( HashMap<K, V, SIZE, F> other) {
		std::swap(arr, other.arr);
		hashFunc = other.hashFunc;
		return *this;
	}

	V operator[](const K key) {
		V value;
		get(key, value);
		return value;
	}

	std::vector<V> getAllValues(const K key) const  {
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

	bool get(const K& key, V& value) const {
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

	void add(const K& key, const V& value){
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

	int distinctKeys() const {
		int rs = 0;
		for (int i = 0; i < SIZE; i++) if (arr[i] != nullptr) rs++;
		return rs;
	}

	void remove(const K& key){
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


