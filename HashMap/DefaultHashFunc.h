#pragma once

const unsigned long MODULO = 111;
template<typename K>
class DefaultHashFunc {
public:
	//broken, returns different values for same key
	unsigned long operator()(const K& key) const{
		return reinterpret_cast<unsigned long>(&key) % MODULO;
	}
};



