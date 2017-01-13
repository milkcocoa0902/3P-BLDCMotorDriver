/*
 * ControllerBase.cpp
 *
 *  Created on: 2016/12/11
 *      Author: Keita
 */

#include <ControllerBase.hpp>
#include <Trapezium.hpp>
#include <PIDControl.hpp>
#include <Timer.hpp>
#include <motor.hpp>
#include <Port.hpp>

namespace Middle {
	namespace Controller {
		ControlMode_e mMode;

		ControllerBase::ControllerBase(): mFreq(FREQ_DEFAULT) {

		}

		ControllerBase::~ControllerBase() {

		}

		void SwitchControlMode(ControlMode_e _mode){
			if(mMode == _mode)
				return;

			mMode = _mode;
			switch(mMode){
				case ControlMode_e::ModeTrapezium:{
					Trapezium* trap = new Trapezium();
					Device::Timer::SetAction(1, trap->GetFreq(), std::move(*trap));
					Device::Port::Set(Device::Port::PWMEN, true);
					Middle::Motor::ModeAs(Middle::Motor::Type::DCMotor);
					break;
				}case ControlMode_e::ModePID:{
					PID* pid = new PID();
					Device::Timer::SetAction(1, pid->GetFreq(), std::move(*pid));
					Device::Port::Set(Device::Port::PWMEN, true);
					Middle::Motor::ModeAs(Middle::Motor::Type::DCMotor);
					break;
				}default :{
					break;
				}
			}
		}
	
	} /* namespace Controller */
} /* namespace Middle */