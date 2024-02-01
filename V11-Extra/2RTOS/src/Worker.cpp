/*
 * Worker.cpp
 *
 *  Created on: 17 Jan 2024
 *      Author: jondurrant
 */

#include "Worker.h"
#include "Counter.h"
#include <pi_spigot/pi_spigot.h>

Worker::Worker(uint8_t id) {
	xId = id;

}

Worker::~Worker() {
	// TODO Auto-generated destructor stub
}


/***
 * Task main run loop
 */
void Worker::run(){
	for (;;){
		if (doWork()){
			Counter::getInstance()->inc(xId);
		}
	}
}

/***
 * Get the static depth required in words
 * @return - words
 */
configSTACK_DEPTH_TYPE Worker::getMaxStackSize(){
	return 5000;
}

bool Worker::doWork(){
	using pi_spigot_type = math::constants::pi_spigot<1000, 9>;

	using input_container_type  = std::vector<std::uint32_t>;
	using output_container_type = std::vector<std::uint8_t>;

	input_container_type  pi_in(pi_spigot_type::get_input_static_size());
	output_container_type pi_out(pi_spigot_type::get_output_static_size());


	pi_spigot_type ps;
	ps.calculate(pi_in.begin(), pi_out.begin());

	return true;
}

