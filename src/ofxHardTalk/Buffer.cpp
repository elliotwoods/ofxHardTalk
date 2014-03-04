#include "Buffer.h"
#include <string>
#include <iostream>

using namespace std;

namespace ofxHardTalk {
	//----------
	Buffer::Buffer() {
		this->data = 0;
		this->size = 0;
		this->reserved = 0;
		this->readPosition = 0;
	}
	
	//----------
	Buffer::~Buffer() {
		this->deAllocate();
	}
	
	//----------
	void Buffer::reserve(size_t size) {
		if (size < this->reserved) {
			return; //no need, we're already large enough
		}
		
		//setup the new data
		auto newData = new unsigned char[size];
		
		//if we have existing allocation
		if (this->data) {
			//if we have existing data then copy it
			if (this->size > 0) {
				memcpy(newData, this->data, this->size);
			}
			//release existing allocation
			delete[] this->data;
		}
		
		//use the new memory location
		this->data = newData;
		
		//remember how much data we have reserved
		this->reserved = size;
	}
	
	//----------
	void Buffer::checkSpace(size_t size) {
		if (size > this->reserved) {
			//we need more space
			auto newSize = this->reserved;
			if (newSize == 0) {
				newSize = 1;
			}
			//go up by powers of 2
			while (newSize < size) {
				newSize *= 2;
			}
			
			this->reserve(newSize);
		}
	}
	
	//----------
	void Buffer::deAllocate() {
		if (this->data) {
			delete[] this->data;
			this->data = 0;
			this->size = 0;
			this->reserved = 0;
			this->readPosition = 0;
		}
	}	
	
	//----------
	void * Buffer::getPtr() {
		return this->data;
	}
	
	//----------
	void * Buffer::getWriteHead() {
		return this->data + this->size;
	}
							   
	//----------
	const void * Buffer::getReadHead() const {
		return this->data + this->readPosition;
	}
	
	//----------
	size_t Buffer::getSize() const {
		return this->size;
	}
							   
	//----------
	void Buffer::moveReadHead(size_t size) {
		this->readPosition += size;
	}
	
	//----------
	void Buffer::moveWriteHead(size_t size) {
		this->size += size;
	}
			
	//----------
	size_t Buffer::remainingReadSpace() const {
		return this->size - this->readPosition;
	}
	
	//----------
	void Buffer::put(const void * data, size_t objectSize) {
		this->checkSpace(this->size + objectSize);
		memcpy(this->getWriteHead(), data, objectSize);
		this->size += objectSize;
	}

	//----------
	bool Buffer::get(void * objectData, size_t objectSize) {
		if(this->readPosition + objectSize > this->size) {
			return false;
		}
		memcpy(objectData, this->getReadHead(), objectSize);
		this->moveReadHead(objectSize);
		return true;
	}
	
	//-----------
	bool Buffer::checkPeekTypeName(const char * name) {
		if (this->remainingReadSpace() < sizeof(TypeLength)) {
			return false;
		}
		auto typeLength = this->peek<TypeLength>();
		
		return strcmp((char *) (this->data + sizeof(TypeLength)), name);
	}
	
	//-----------
	ostream & operator<<(ostream & os, const Buffer & buffer) {
		os << "{";
		auto readHeader = (unsigned char * const) buffer.data;
		for(int i=0; i<buffer.size; i++) {
			os << (int) readHeader[i] << ", ";
		}
		os << "}";
		return os;
	}
}