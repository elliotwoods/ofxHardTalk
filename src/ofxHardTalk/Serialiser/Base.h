#pragma once

#include <typeinfo>

namespace ofxHardTalk {
	
	class Buffer;
	
	namespace Serialiser {
		class Base {
		public:
			virtual std::type_info getHandledType() = 0;
			virtual void serialise(ofxHardTalk::Buffer &, void * object) = 0;
			virtual void deSerialise(ofxHardTalk::Buffer &, void * object) = 0;
		};
	}
}