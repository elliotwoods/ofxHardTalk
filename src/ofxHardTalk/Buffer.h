#pragma once
#include <cstddef>
#include <typeinfo>

#include "Serialisable.h"

namespace ofxHardTalk {	
	class Buffer {
	public:
		typedef unsigned short TypeLength;
		
		Buffer();
		virtual ~Buffer();
		
		void reserve(size_t);
		void deAllocate();
		
		/// Allocate if we don't have space for this position
		void checkSpace(size_t);
		
		
		//--
		// Managed serialisation functions
		//
		void serialise(void * data, size_t size, const std::type_info &);
		bool deSerialise(void * data, size_t size, const std::type_info &);
		
		template<typename T>
		Buffer & operator<<(const T & data) {
			auto asSerialisable = static_cast<Serialisable*>(&data);
			if (asSerialisable) {
				//use its own serialiser
				asSerialisable->serialise(*this);
			} else {
				//use our serialise
				this->serialise(&data, sizeof(T), typeid(data));
			}
		}
		
		template<typename T>
		Buffer & operator>>(const T & data) {
			auto asSerialisable = static_cast<Serialisable*>(&data);
			if (asSerialisable) {
				//use its own serialiser
				asSerialisable->deSerialise(*this);
			} else {
				//use our serialise
				this->deSerialise(&data, sizeof(T), typeid(data));
			}
		}
		//
		//--
		
		
		//--
		// Raw functions
		//
		void * getWriteHead();
		const void * getReadHead() const;
		void moveReadHead(size_t);
		void moveWriteHead(size_t);
		size_t remainingReadSpace() const;
		
		void put(const void *, size_t);
		template<typename T>
		void put(const T & object) {
			this->put(& object, sizeof(T));
		}
		
		bool get(void *, size_t);
		template<typename T>
		bool get(T & object) {
			return this->get(& object, sizeof(T));
		}
		
		template<typename T>
		T & peek() {
			return * (T *) this->getReadHead();
		}
		//
		//--
		
	protected:
		unsigned char * data;
		size_t reserved;
		size_t readPosition;
		size_t size;
	};
}