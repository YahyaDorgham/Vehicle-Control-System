/*
 ============================================================================
 Name        : mini_project.c
 Author      : Yahya
 Description : Vehicle Control system
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "head.h"

//void DisplayVehicleState();
int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	VehicleState VS; /*initializing struct VS from type VehicleState */
	/* initializing VS element values */
	VS.EngineState = OFF;
	VS.AC = OFF;
	VS.VehicleSpeed = 0;
	VS.RoomTemperature = 25;
#if WITH_ENGINE_TEMP_CONTROLLER /*the compiler will compile this code only if WITH_ENGINE_TEMP_CONTROLLER defined*/
	VS.ETCS = OFF;
	VS.EngineTemperature = 90;
#endif
	/*******************************/
	/* infinite loop */
	for (;;) {
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n");
		scanf(" %c", &input); /*take the input from the user*/
		switch (input) {
		case 'a':
		case 'A':
			VS.EngineState = ON; /*turn on the vehicle engine*/
			VS.VehicleSpeed = 100; /* and start speed from  */
			SensorSetMenu(&VS);
			break;
		case 'b':
		case 'B':
			printf("Turn off the vehicle engine \n");
			break;
		case 'c':
		case 'C':
			printf("Quit the system\n");
			return 0;
			break;
		}
	}
	return 0;
}

void SensorSetMenu(VehicleState *VS) {
	while (VS->EngineState) { /* while Engine State is on stay in this loop*/
		printf("a. Turn off the engine \n");
		printf("b. Set the traffic light color \n");
		printf("c. Set the room temperature \n");
#if WITH_ENGINE_TEMP_CONTROLLER  /*if the vhicle WITH_ENGINE_TEMP_CONTROLLER compile the code */
		printf("d. Set the engine temperature \n");
#endif
		scanf(" %c", &input);
		switch (input) {
		case 'a':
		case 'A':
			VS->EngineState = OFF;
			printf("Turn off the vehicle engine \n");
			return;
			break;

		case 'b':
		case 'B':
			SetTrafficLight(VS); /*pass struct by address as VS is address in the SensorSetMenu function */
			break;
		case 'c':
		case 'C':
			SetRoomTempreture(VS);
			break;
#if WITH_ENGINE_TEMP_CONTROLLER
		case 'd':
		case 'D':
			SetEngineTempreture(VS);
			break;
#endif
		}
		if (VS->VehicleSpeed == 30) {
			VS->AC = ON;
			VS->RoomTemperature = VS->RoomTemperature * (5 / 4) + 1;
#if WITH_ENGINE_TEMP_CONTROLLER
			VS->ETCS = ON;
			VS->EngineTemperature = VS->EngineTemperature * (5 / 4) + 1;
#endif
		}
		DisplayVehicleState(VS);
	}
}
/***********************************************************************/
void SetTrafficLight(VehicleState *VS) {
	printf("Enter the required color: \n");
	scanf(" %c", &input);
	switch (input) {
	case 'g':
	case 'G':
		VS->VehicleSpeed = 100;
		break;
	case 'o':
	case 'O':
		VS->VehicleSpeed = 30;
		break;
	case 'r':
	case 'R':
		VS->VehicleSpeed = 0;
		break;
	}
}
/***********************************************************************/
void SetRoomTempreture(VehicleState *VS) {
	printf("Enter the Room Temperature : \n");
	scanf(" %d", &VS->RoomTemperature);
	if (VS->RoomTemperature < 10 || VS->RoomTemperature > 30) {
		VS->AC = ON;
		VS->RoomTemperature = 20;
	} else
		VS->AC = OFF;
}
/***********************************************************************/
void SetEngineTempreture(VehicleState *VS) {
	printf("Enter the Engine Temperature : \n");
	scanf(" %d", &VS->EngineTemperature);
	if (VS->EngineTemperature < 100 || VS->EngineTemperature > 150) {
		VS->ETCS = ON;
		VS->EngineTemperature = 125;
	} else
		VS->ETCS = OFF;
}
/***********************************************************************/
void DisplayVehicleState(VehicleState *VS) {
	/*************************Engine State************************/
	if (VS->EngineState)
		printf("Engine is ON \n");
	else
		printf("Engine is OFF \n");
	/***************************AC*********************************/
	if (VS->AC)
		printf("AC is ON \n");
	else
		printf("AC is OFF \n");
	/**********************Vehicle Speed**************************/
	printf("Vehicle Speed is %d Km/Hr \n", VS->VehicleSpeed);
	/*******************Room Temperature*************************/
	printf("Room Temperature is %d C\n", VS->RoomTemperature);
	/************Engine Temperature Controller State*************/
#if WITH_ENGINE_TEMP_CONTROLLER
	if (VS->ETCS)
		printf("Engine Temperature Controller State is ON \n");
	else
		printf("Engine Temperature Controller State is OFF \n");
	/*******************Engine Temperature**********************/
	printf("Engine Temperature is %d C\n \n", VS->EngineTemperature);
#endif
}
