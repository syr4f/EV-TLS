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

#ifndef EVUITM_TRACIALGORITHM_H_
#define EVUITM_TRACIALGORITHM_H_

namespace evuitm{

const double desired_speed = 70/3.6;    // desired speed of emergency vehicle [m/s]
const double t_x = 1.22;                // average reaction time of a driver [s]
const double t_a = 5.82;                // average time to accelerate to saturation speed [s]
const double L_hn = 18.7;               // saturation gap between vehicles [m]
const double q_ns = 0.5208;             // vehicle discharge speed [veh/s]
const double t_sw = 11.0;               // minimal time necessary to get back to the current phase if the phase is switched at this very moment [s]
const double t_min = 10.0;              // minimal time of green phase (green on main road cannot be shorter than t_min) [s]
const double t_conservative = 0.0;      // time added to preemption start, to make it more conservative [s]

double linApproxQueueDischarge(int num_vehicles, double t);
double calc_TA(double distance, double speed = desired_speed);
double calc_TL(int num_vehicles);
double calc_TX(int num_vehicles, double TL, double speed = desired_speed);
double expDelay(double time);  // expected delay created by additional cycle time

}
#endif /* EVUITM_TRACIALGORITHM_H_ */
