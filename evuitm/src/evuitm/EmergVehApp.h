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

#pragma once

#include "evuitm/evuitm.h"

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"


namespace evuitm {


class EVUITM_API EmergVehApp : public veins::DemoBaseApplLayer {
public:
    void initialize(int stage) override;
    void finish() override;



protected:
    simtime_t lastDroveAt;
    bool sentMessage;
    int currentSubscribedServiceId;

    void onWSM(veins::BaseFrame1609_4* wsm) override;
    void onBSM(veins::DemoSafetyMessage* bsm) override;
    void onWSA(veins::DemoServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;

protected:


    std::string trafficLightId;
    cMessage* initMsg;
    cMessage* phaseMsg;

};

} // namespace veins
