#include "Set.h"
#include "ofLog.h"

using namespace std;

namespace ofxHardTalk {
	namespace Serialiser {
		//----------
		Set Set::Singleton = Set();
		
		//----------
		void Set::add(Base * serialiser) {
			const auto handledTypeName = string(serialiser->getHandledType().name());
			if(this->find(handledTypeName) != this->end()) {
				ofLogWarning("ofxHardTalk::Serialiser::Set") << "We already have a serialised for type [" << handledTypeName << "]";
			} else {
				this->insert(std::pair<string, Base*>(handledTypeName, serialiser));
			}
		}
	}
}