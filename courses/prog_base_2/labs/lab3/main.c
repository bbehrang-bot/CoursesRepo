#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "machine.h"
#include "userHeader.h"
void alert_master(user_t * receiver, event_t * event);
void alert_common(user_t * receiver, event_t * event);

int main(void) {
	srand(time(NULL));

	puts("\nPress ANY KEY to proceed to actually program...");
	getch();
	system("cls");
	machine_t * msrmQueue = machine_new();
	user_t * ruslan = user_new("Mario");
	user_t * press = user_new("LA TIMES");
	user_t * userArr[] = { ruslan};//, alpha, bravo, charlie, delta };
	int userArrSize = sizeof(userArr) / sizeof(userArr[0]);
	event_t * firstEvent = event_new("Almost wining");
	event_t * secondEvent = event_new("WON");
	event_t * thirdEvent = event_new("JACKPOT");
	event_addAlertSingle(ruslan, thirdEvent, alert_master);
	event_addAlertSingle(press, third, alert_master);
	while (!kbhit()) {
		event_start(firstEvent, secondEvent, thirdEvent, msrmQueue);
	}
	event_free(firstEvent);
	event_free(secondEvent);
	event_free(thirdEvent);
	for (int i = 0; i < userArrSize; i++) {
		user_free(userArr[i]);
	}
	machine_free(msrmQueue);


	getch();
	puts("Press ANY KEY to exit the program...");
	getch();
	return 0;
}
void alert_master(user_t * receiver, event_t * event) {
	char * name = user_getName(receiver);
	char * desc = event_getDesc(event);

	printf("\nADMIN %s WAS INFORMED\n", name);
	printf("%s\n\n", desc);

	free(name);
	free(desc);
}
void alert_common(user_t * receiver, event_t * event) {
	char * name = user_getName(receiver);
	char * desc = event_getDesc(event);

	printf("PRESS  %s WERE INFORMED.\n", name);
	printf("%s\n\n", desc);

	free(name);
	free(desc);
}
