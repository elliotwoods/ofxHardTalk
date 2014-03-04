#pragma once

#include <typeinfo>

namespace ofxHardTalk {
	
	class Buffer;
	
	namespace Serialiser {
		class Base {
		public:
			virtual const std::type_info & getHandledType() const = 0;
			virtual void put(ofxHardTalk::Buffer &, const void * object) const = 0;
			virtual bool get(ofxHardTalk::Buffer &, void * object) const = 0;
		};
	}
}