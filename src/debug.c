#include "philosophers.h"

void	print_table(t_philosopher *philosopher)
{
	printf("\n	TIME TO DIE:	%dms\n", philosopher->times->time_to_die);
	printf("	TIME TO EAT:	%dms\n", philosopher->times->time_to_eat);
	printf("	TIME TO SLEEP:	%dms\n\n", philosopher->times->time_to_sleep);
	printf("--- TABLE: ----------------------------\n");
	while (philosopher)
	{
		printf("> %s	%lu\n", philosopher->name, philosopher->thread);
		philosopher = philosopher->next;
	}
	printf("---------------------------------------\n");
	printf("DINNER TIME! :)\n\n");
}
