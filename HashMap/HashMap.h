#pragma once
#include "HashNode.h"


template <typename K, typename V, size_t tableSize, typename F>
class HashMap
{
private:
	
	HashNode<K, V>* table[tableSize];
	unsigned int size;
	F hashFunc;
	

public:
	HashMap() :
		table(),
		hashFunc(),
		size(tableSize) {
		for (int i = 0; i < tableSize; i++) table[i] = nullptr;
	}

	~HashMap(){
		for (size_t i = 0; i < tableSize; ++i) {
			delete table[i];
			table[i] = nullptr;
		}
	}

	HashMap(const HashMap<K,V,tableSize,F> & other):table() {
		for (int i = 0; i < tableSize; i++) {
			if (other.table[i] != nullptr) {
				HashNode<K, V>* tmp = new HashNode<K, V>(*other.table[i]);
				table[i] = tmp;
			}
				
		}
		hashFunc = other.hashFunc;
	} 
	HashMap& operator=( HashMap<K, V, tableSize, F> other) {
		std::swap(table, other.table);
		hashFunc = other.hashFunc;
		return *this;
	}

	V operator[](const K key) {
		V value;
		get(key, value);
		return value;
	}

	std::vector<V> getAllValues(const K key) {
		std::vector<V> rs;
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V>* entry = table[hashValue];

		while (entry != nullptr) {
			if (entry->getKey() == key) {
				return entry->getAllValues();
			}

			entry = entry->getNext();
		}

		return rs;

	}

	bool get(const K& key, V& value)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V>* entry = table[hashValue];

		while (entry != nullptr) {
			if (entry->getKey() == key) {
				value = entry->getValue();
				return true;
			}

			entry = entry->getNext();
		}

		return false;
	}

	void put(const K& key, const V& value)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V>* prev = nullptr;
		HashNode<K, V>* entry = table[hashValue];

		while (entry != nullptr && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == nullptr) {
			entry = new HashNode<K, V>(key, value);

			if (prev == nullptr) {
				table[hashValue] = entry;
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

	int distinctKeys() {
		int rs = 0;
		for (int i = 0; i < tableSize; i++) if (table[i] != nullptr) rs++;
		return rs;
	}

	void remove(const K& key)
	{
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V>* prev = nullptr;
		HashNode<K, V>* entry = table[hashValue];

		while (entry != nullptr && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == nullptr) {
			return;

		}
		else {
			if (prev == nullptr) {
				table[hashValue] = entry->getNext();
			}
			else {
				prev->setNext(entry->getNext());
			}

			delete entry;
		}
	}
	friend std::ostream& operator<<(std::ostream& out, const HashMap& hmap) {
		for (int i = 0; i < hmap.size; i++) {
			if (hmap.table[i] != nullptr) {
				HashNode<K, V>* it = hmap.table[i];
				while (it != nullptr) {
					out << it->getKey() << " : " << it->getValue() << std::endl;
					it = it->getNext();

				}
			}
		}
		return out;
	}

};


