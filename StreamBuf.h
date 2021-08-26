#pragma once

#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <utility>
#include <tuple>


class CStreamBuf : public std::vector<char> {
public:
	CStreamBuf() {
		m_iPos = 0;
	}
	~CStreamBuf(){}
	void Reset() {
		m_iPos = 0;
	}
	const char* GetData() {
		return &(*this)[0];
	}
	void Offset(int _k) {
		m_iPos += _k;
	}
	bool IsEOF() {
		return m_iPos >= (int)size();
	}
	void Input(char* _in, size_t _len) {
		insert(end(), _in, _in + _len);
	}

	template<typename T>
	void OutputType(T& t);

	template<typename T>
	void InputType(T t);

	template <typename T>
	CStreamBuf& operator<< (T t) {
		InputType(t);
		return *this;
	}
	template <typename T>
	CStreamBuf& operator>> (T& t) {
		OutputType(t);
		return *this;
	}

private:
	int m_iPos;
};

template <typename T>
inline void CStreamBuf::OutputType(T& _t) {
	int tSize = sizeof T;
	char* data = new char[tSize];
	if (!IsEOF()) {
		memcpy(data, &(*this)[m_iPos], tSize);
		Offset(tSize);
		_t = *reinterpret_cast<T*>(&data[0]);
	}
	delete[] data;
}
 // ÌØ»¯
template<>
inline void CStreamBuf::OutputType(std::string& _in) {
	int marklen = sizeof(uint16_t);
	char* d = new char[marklen];
	memcpy(d, &(*this)[m_iPos], marklen);
	int len = *reinterpret_cast<uint16_t*>(&d[0]);
	Offset(marklen);
	delete[] d;
	if (len == 0) return;
	_in.insert(_in.begin(), &(*this)[m_iPos], &(*this)[m_iPos] + len);
	Offset(len);
}

template<typename T>
inline void CStreamBuf::InputType(T t){
	int len = sizeof T;
	char* data = new char[len];
	const char* p = reinterpret_cast<const char*>(&t);
	memcpy(data, p, len);
	Input(data, len);
	delete[] data;
}

template<>
inline void CStreamBuf::InputType(std::string _in) {
	uint16_t len = _in.size();
	char* p = reinterpret_cast<char*>(&len);
	Input(p, sizeof(uint16_t));
	if (len == 0) return;
	char* d = new char[len];
	memcpy(d, _in.c_str(), len);
	Input(d, len);
	delete[] d;
}

template<>
inline void CStreamBuf::InputType(const char* _in) {
	InputType<std::string>(std::string(_in));
}