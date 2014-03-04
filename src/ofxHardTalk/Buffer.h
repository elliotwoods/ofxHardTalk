#pragma once

#include "Serialiser/Set.h"

#include "ofLog.h"

#include <cstddef>
#include <typeinfo>
#include <iostream>

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
		template<typename T>
		void serialise(const T & object) {
			const auto typeString = std::string(typeid(T).name());
			this->put((TypeLength) typeString.length());
			this->put(& typeString[0], typeString.length());
			
			auto serialiser = Serialiser::Set::Singleton.getSerialiser<T>();
			
			if (serialiser) {
				serialiser->put(* this, & object);
			} else {
				this->put(& object, sizeof(T));
			}
		}
		
		template<typename T>
		bool deSerialise(T & object) {
			const auto targetTypeString = string(typeid(T).name());
			
			//check the type
			if (this->checkPeekTypeName(targetTypeString.c_str())) {
				return false;
			} else {
				this->moveReadHead(sizeof(TypeLength) + targetTypeString.length());
			}
			
			//pull the data
			auto serialiser = Serialiser::Set::Singleton.getSerialiser<T>();
			if (serialiser) {
				return serialiser->get(* this, & object);
			} else {
				//check if can pull the data
				const auto objectSize = sizeof(T);
				if(this->remainingReadSpace() < objectSize) {
					return false;
				}
				return this->get(& object, objectSize);
			}
		}
		
		template<typename T>
		Buffer & operator<<(const T & object) {
			this->serialise(object);
		}
		
		template<typename T>
		Buffer & operator>>(T & object) {
			if (!this->deSerialise(object)) {
				ofLogError("ofxHardTalk::Buffer") << "Failed to deserialise [" << typeid(T).name() << "]";
			}
			return * this;
		}
		//
		//--
		
		
		//--
		// Raw functions
		//
		void * getPtr();
		void * getWriteHead();
		const void * getReadHead() const;
		size_t getSize() const;
		
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
		
		friend ostream & operator<<(std::ostream &, const Buffer &);
		
	protected:
		unsigned char * data;
		size_t reserved;
		size_t readPosition;
		size_t size;
	};
}