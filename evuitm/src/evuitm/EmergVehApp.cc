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

#include "evuitm/EmergVehApp.h"
#include "evuitm/EmergBeacon_m.h"


using namespace veins;
using namespace evuitm;

Define_Module(evuitm::EmergVehApp);

void EmergVehApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        mobility = TraCIMobilityAccess().get(getParentModule());
        //traci = mobility->getCommandInterface();
        traciVehicle = mobility->getVehicleCommandInterface();
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }
}

void EmergVehApp::finish()
{
    DemoBaseApplLayer::finish();
    // statistics recording goes here
}

void EmergVehApp::onBSM(DemoSafetyMessage* bsm)
{
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here

    EV << "EmergVehApp onBSM\n";
}

void EmergVehApp::onWSM(BaseFrame1609_4* wsm)
{
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples

    EV << "EmergVehApp onWSM \n";
}

void EmergVehApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
    EV << "EmergVehApp onWSA\n";
}

void EmergVehApp::handleSelfMsg(cMessage* msg)
{
    if (EmergBeacon* wsm = dynamic_cast<EmergBeacon*>(msg)) {
        // send this message on the service channel until the counter is 3 or higher.
        // this code only runs when channel switching is enabled
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() + 1);
        if (wsm->getSerial() >= 1) { //normally 3
            // stop service advertisements
            stopService();
            delete (wsm);
        }
        else {
            scheduleAt(simTime() + 1, wsm);
        }
    }
    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void EmergVehApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class
    std::string laneId = traciVehicle->getLaneId();
    double carSpeed = traciVehicle->getSpeed();

    double stop = 0.0;

    if(carSpeed == stop){
       EV << "Emergency Vehicle Send Beacon To The RSU\n";
       EmergBeacon* wsm = new EmergBeacon();
       populateWSM(wsm);
       wsm->AtLanes = laneId;
       sendDown(wsm);

    }


}
