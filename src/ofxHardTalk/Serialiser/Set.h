#pragma once

#include "Base.h"
#include <map>
#include <string>

namespace ofxHardTalk {
	class Buffer;
	
	namespace Serialiser {
		class Set : std::map<std::string, Base *> {
		public:
			static Set Singleton;

			void add(Base *);
			
			template<typename T>
			Base * getSerialiser() {
				auto it = this->find(std::string(typeid(T).name()));
				if (it != this->end()) {
					return it->second;
				} else {
					return 0;
				}
			}
		};
	}
}