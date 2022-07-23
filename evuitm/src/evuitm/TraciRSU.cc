//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "evuitm/TraciRSU.h"
#include "evuitm/EmergBeacon_m.h"

using namespace veins;
using namespace evuitm;

Define_Module(evuitm::TraciRSU);

void TraciRSU::onBSM(DemoSafetyMessage* bsm) {
    // decrement hopCount and re-send if hopCount >= 0
    findHost()->getDisplayString().setTagArg("i", 1, "green");
    if (EmergBeacon* msg = dynamic_cast<EmergBeacon*>(bsm)){
        msg->setHopCount(msg->getHopCount()-1);
        if (msg->getHopCount() >= 0)
            sendDelayedDown(msg->dup(), uniform(0.01, 0.2));
    }
}

void TraciRSU::onWSM(BaseFrame1609_4* wsm) {
}

void TraciRSU::onWSA(DemoServiceAdvertisment* wsa) {
}
