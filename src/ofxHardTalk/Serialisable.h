#pragma once

namespace ofxHardTalk {
	class Buffer;

	class Serialiser {
		
	};

	class Serialisable {
	public:
		virtual void serialise(Buffer &) = 0;
		virtual void deSerialise(Buffer &) = 0;
	};
}