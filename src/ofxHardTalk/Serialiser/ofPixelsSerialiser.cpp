#include "ofPixelsSerialiser.h"
#include "../Buffer.h"
#include "ofPixels.h"

using namespace std;

namespace ofxHardTalk {
	namespace Serialiser {
		//----------
		const type_info & ofPixelsSerialiser::getHandledType() const {
			return typeid(ofPixels);
		}
		
		//----------
		void ofPixelsSerialiser::put(ofxHardTalk::Buffer & buffer, const void *object) const {
			auto & pixels = * (ofPixels *) object;
			buffer.put(typeid(ofPixels));
			
			
			buffer.put(pixels.isAllocated());
		}
	}
}