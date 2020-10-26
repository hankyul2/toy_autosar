#include "vrtaCore.h"
#include "vrtaSampleDevices.h"
#include "vrtaLoggerDevice.h"
#include "VirtualDevices.h"

vrtaSensor DistanceSensor("distanceSensor");
vrtaSensor SteeringAngleSensor("SteeringAngleSensor");
vrtaSensor SpeedSensor("SpeedSensor");
vrtaSensor LightSensor("LightSensor");
vrtaSensor LightModeSensor("LightModeSensor");

vrtaActuator UPDOWNMotorActuator("UPDOWNMotorActuator");
vrtaActuator LEFTRIGHTMotorActuator("LEFTRIGHTMotorActuator");
vrtaActuator LowBeamActuator("LowBeamActuator");
vrtaActuator HighBeamActuator("HighBeamActuator");

void initSensor(void){
	DistanceSensor.SetValue(0);
	SteeringAngleSensor.SetValue(0);
	LightSensor.SetValue(0);
	SpeedSensor.SetValue(0);
	LightModeSensor.SetValue(0);
}

int GetDistanceSensor(void){
	return DistanceSensor.Value();
}

int GetSteeringAngleSensor(void){
	return SteeringAngleSensor.Value();
}

int GetSpeedSensor(void){
	return SpeedSensor.Value();
}

int GetLightSensor(void){
	return LightSensor.Value();
}

int GetLightModeSensor(void){
	return LightModeSensor.Value();
}

void SetUPDOWNMotorActuator(int value){
	UPDOWNMotorActuator.SetValue(value);
}

void SetLEFTRIGHTMotorActuator(int value){
	LEFTRIGHTMotorActuator.SetValue(value);
}

void SetLowBeamActuator(int value){
	LowBeamActuator.SetValue(value);
}

void SetHighBeamActuator(int value){
	HighBeamActuator.SetValue(value);
}



Logger Status("Status");

int status_printf(const vrtaTextPtr format, ...){
	va_list argptr;
	va_start(argptr, format);
	int ret = Status.printf(format, argptr);
	va_end(argptr);
	return ret;
}




void InitializeDevices(void){



}
