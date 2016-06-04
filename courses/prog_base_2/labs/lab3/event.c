#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include "alert.h"
#include "event.h"
#include "machine.h"
// max amount of users that are able to be subscribed to the same event at the same time
#define USERS_MAXSIZE 100

struct alert_s {
	user_t * receiver;
	alert func;
};
typedef struct alert_s alert_t;
struct event_s {
	char desc[100];
	alert_t * alert_array;
};

event_t * event_new(char * description) {
	event_t * eventSmp = malloc(sizeof(struct event_s));
	strcpy(eventSmp->desc, description);
	eventSmp->alert_array = alertArr_new(USERS_MAXSIZE);
	return eventSmp;
}

void event_free(event_t * self) {
	int size = alertArr_getSize(self->alert_array);
	for (int i = 0; i < size; i++) {
		free(alertArr_getByInd(self->alert_array, i));
	}
	alertArr_free(self->alert_array);
	free(self);
}

char * event_getDesc(event_t * self) {
	char * desc = malloc((strlen(self->desc) + 1) * sizeof(char));
	strcpy(desc, self->desc);
	return desc;
}
void event_addAlertSingle(user_t * userPtr, event_t * evPtr, alert function) {
	alert_t * alertSmp = malloc(sizeof(struct alert_s));
	alertSmp->receiver = userPtr;
	alertSmp->func = function;
	alertArr_addLast(evPtr->alert_array, alertSmp);
}

void event_addAlertSeveral(user_t ** userArray, int userSize, event_t * evPtr, alert function) {
	for (int i = 0; i < userSize; i++) {
		event_addAlertSingle(userArray[i], evPtr, function);
	}
}
static void event_trigger(event_t * self) {
	event_t * event = self;
	int size = alertArr_getSize(self->alert_array);
	for (int i = 0; i < size; i++) {
		alert_t * alert = (alert_t *)alertArr_getByInd(self->alert_array, i);
		alert->func(alert->receiver, self);
	}
}

static int event_firstEvent(event_t * self, machine_t * myMachine) {

    if (machine_firstEvent(myMachine) == 0) {
		return 0;//false
	}
	else {
		event_trigger(self);
	}
}
static int event_secondEvent(event_t * self, machine_t * myMachine) {
    if (machine_secondEvent(myMachine) == 0) {
		return 0;
	}
	else {
		event_trigger(self);
	}
}
static int event_thirdEvent(event_t * self, machine_t * myMachine) {
	 if (machine_thirdEvent(myMachine) == 0) {
		return 0;//false
	}
	else {
		event_trigger(self);
	}
}
void event_start(event_t * firstEv, event_t * secondEv, event_t * thirdEv, machine_t * myMachine) {
	puts("\n====================Game Starting====================\n");
	machine_fillWithRandom(myMachine);
    machine_print(myMachine);
	int check;

	check = event_firstEvent(firstEv, myMachine);
	check = event_secondEvent(secondEv, myMachine);
	check = event_thirdEvent(thirdEv, myMachine);
	if(check==1)
        Sleep(5000);
	puts("\n\n");
}
