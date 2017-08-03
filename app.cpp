#include "app.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#define DEBUG
#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

static void system_init()
{
	ev3_led_set_color(LED_ORANGE);
}

static void system_destroy()
{
	ev3_led_set_color(LED_RED);
}

void ev3_cyc_tracer(intptr_t exinf)
{
	act_tsk(TRACER_TASK);
}

void main_task(intptr_t unused)
{

	system_init();

	while (1)
	{
		if (ev3_button_is_pressed(BACK_BUTTON))
			break;

		tslp_tsk(4);
	}

	ter_tsk(TRACER_TASK);
	system_destroy();
	ext_tsk();
}

void tracer_task(intptr_t exinf)
{
	if (ev3_button_is_pressed(BACK_BUTTON))
		wup_tsk(MAIN_TASK);

	ext_tsk();
}
}