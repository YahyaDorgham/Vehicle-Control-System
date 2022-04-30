#ifndef HEAD_H_
#define HEAD_H_

#define WITH_ENGINE_TEMP_CONTROLLER 1  /*to change the options that depend on ENGINE TEMP CONTROLLER */
                                       /*               by changing this definition                  */

typedef enum { /* OFF-> 0 , ON -> 1*/
	OFF, ON
} STATE;

typedef struct{
 STATE EngineState;
 STATE AC;
 int VehicleSpeed;
 int RoomTemperature;
 STATE ETCS; //ETCS ==> Engine Temperature Controller State
 int EngineTemperature;
 }VehicleState;

char input; /*global variable to use it when we need user to chose */

/*functions Prototypes*/
/* all functions pass struct by address*/
void DisplayVehicleState(VehicleState *VS);
void SensorSetMenu(VehicleState *VS);
void SetTrafficLight(VehicleState *VS);
void SetRoomTempreture(VehicleState *VS);
void SetEngineTempreture(VehicleState *VS);

#endif /* HEAD_H_ */
