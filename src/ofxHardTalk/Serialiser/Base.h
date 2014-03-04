#pragma once

#include <typeinfo>

namespace ofxHardTalk {
	
	class Buffer;
	
	namespace Serialiser {
		class Base {
		public:
			virtual std::type_info getHandledType() const = 0;
			virtual void serialise(ofxHardTalk::Buffer &, const void * object) const = 0;
			virtual void deSerialise(ofxHardTalk::Buffer &, void * object) const = 0;
		};
	}
}