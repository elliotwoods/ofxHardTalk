#pragma once

#include "Base.h"

namespace ofxHardTalk {
	namespace Serialiser {
		class ofPixelsSerialiser : public Base {
		public:
			const std::type_info & getHandledType() const override;
			void put(ofxHardTalk::Buffer &, const void * object) const override;
			bool get(ofxHardTalk::Buffer &, void * object) const override;
		};
	}
}