#ifdef __cplusplus
extern "C" {
#endif

extern int status_printf(const vrtaTextPtr format, ...);
extern int AccelSensorValue(void);
extern void  setActuatorLevel(int level);
extern int DistanceSensorValue(void);
extern void setDistanceSensor(int distance);

void initSensor(void);

extern int GetDistanceSensor(void);
extern int GetSteeringAngleSensor(void);
extern int GetSpeedSensor(void);
extern int GetLightSensor(void);
extern int GetLightModeSensor(void);

extern void SetUPDOWNMotorActuator(int value);
extern void SetLEFTRIGHTMotorActuator(int value);
extern void SetLowBeamActuator(int value);
extern void SetHighBeamActuator(int value);

#ifdef __cplusplus
}
#endif
