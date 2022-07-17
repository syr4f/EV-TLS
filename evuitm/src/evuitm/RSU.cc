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

#include "RSU.h"
#include "evuitm/EmergBeacon_m.h"


using namespace veins;
using namespace evuitm;

Define_Module(evuitm::RSU);

void RSU::onWSM(BaseFrame1609_4* frame) {

    findHost()->getDisplayString().setTagArg("i", 1, "green");
    if (EmergBeacon* wsm = check_and_cast<EmergBeacon*>(frame)){
        std:: string laneId = wsm->getAtLanes();
        EV << "RSU Receive Beacon From EVs\n";

                     if(laneId == "persiarankayangannorth#2_0" || laneId == "persiarankayangannorth#2_1" || laneId == "persiarankayangannorth#1_1" || laneId == "persiarankayangannorth#1_0"){
                          //EVs at north lanes
                          traci->trafficlight("cluster_144084639_252529291_255540900_6503456532").setPhaseIndex(0);
                          EV << "Emergency Vehicle is at Jalan Persiaran Kayangan\n";
                      }
                     else if (laneId == "persiarankayangansouth#3_1" || laneId == "persiarankayangansouth#3_0" || laneId == "persiarankayangansouth#2_0" || laneId == "persiarankayangansouth#2_1"){
                          //EVS at south lanes
                          traci->trafficlight("cluster_144084639_252529291_255540900_6503456532").setPhaseIndex(1);
                          EV << "Emergency Vehicle is at Jalan Persiaran Kayangan\n";
                      }
                     else if (laneId == "persiaranpermai#2_0" || laneId == "persiaranpermai#1_0"){
                          //EVs at west lanes
                          traci->trafficlight("cluster_144084639_252529291_255540900_6503456532").setPhaseIndex(2);
                          EV << "Emergency Vehicle is at Jalan Permai\n";
                      }
                     else {
                          //EVs at east lanes
                          traci->trafficlight("cluster_144084639_252529291_255540900_6503456532").setPhaseIndex(3);
                          EV << "Emergency Vehicle is at Jalan Pintar\n";
                      }


    }

}

