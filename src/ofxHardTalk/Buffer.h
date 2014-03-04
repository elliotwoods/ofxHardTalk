#pragma once

#include "Serialiser/Set.h"

#include <cstddef>
#include <typeinfo>

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
		void serialise(const void * data, size_t objectSize, const std::type_info &);
		bool deSerialise(void * data, size_t objectSize, const std::type_info &);
		
		template<typename T>
		Buffer & operator<<(const T & data) {
			auto serialiser = Serialiser::Set::Singleton.getSerialiser<T>();
			if (serialiser) {
				serialiser->serialise(* this, & data);
			} else {
				this->serialise(& data, sizeof(T), typeid(T));
			}
		}
		
		template<typename T>
		Buffer & operator>>(T & data) {
			auto serialiser = Serialiser::Set::Singleton.getSerialiser<T>();
			if (serialiser) {
				serialiser->deSerialise(* this, & data);
			} else {
				this->deSerialise(& data, sizeof(T), typeid(T));
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
		template<typename T>
		void moveReadHead() {
			this->moveReadHead(sizeof(T));
		}
		
		void moveWriteHead(size_t);
		template<typename T>
		void moveWriteHead() {
			this->moveWriteHead(sizeof(T));
		}
		
		size_t remainingReadSpace() const;
		
		void put(const void *, size_t);
		template<typename T>
		void put(const T & object) {
			this->put(& object, sizeof(T));
		}
		template<typename T>
		void putTypeName() {
			this->put((TypeLength) sizeof(T));
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
		
		bool checkPeekTypeName(const char *);
		template<typename T>
		bool checkPeekTypeName() {
			this->checkPeekTypeName(typeid(T).name());
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