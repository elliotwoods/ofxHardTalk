#pragma once

#include "Base.h"

namespace ofxHardTalk {
	namespace Serialiser {
		class ofPixelsSerialiser : public Base {
		public:
			std::type_info getHandledType() override;
			void serialise(ofxHardTalk::Buffer &, void * object) override;
			void deSerialise(ofxHardTalk::Buffer &, void * object) override;
		};
	}
}