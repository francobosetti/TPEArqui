#include <time.h>
#include <naiveConsole.h>

static uint64_t ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

uint64_t seconds_elapsed() {
	return ticks / 18;
}
