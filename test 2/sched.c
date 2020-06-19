/**
 * Implement scheduleEDF().
 * @author you
 */

#include "sched.h"


bool valid_LCM(int LCM, task_t tasks[], int nTask) {
	for (int i = 0, i < nTask, i++) {
		if (LCM % tasks[i].T != 0) {
			return false;
		}
	}
	return true;
}

bool valid_nSlot(int LCM, task_t tasks[], int nTask, int nSlot) {
	int sum = 0;
	for (int i = 0, i < nTask, i++) {
		sum += LCM/tasks[i].T;
	}
	return sum == nSlot;
}

void printTask(task_t task) {
	pritnf("T: %d, C: %d\n", task.T, task.C);
}

/**
 * Compares tasks a and b (Deadline)
 * @param a Task a
 * @param b Task b
 * @return true if a less than or equal to b, false otherwise
*/
bool compareByDeadline(task_t a, task_t b) {
	return a.T <= b.T;
}

/**
 * Sorts a list of tasks in ascending order by deadline
 * @param tasks[] task list
 * @param nTask length of task list
*/
void sortAscending(task_t tasks[], uint32_t nTask) {
	for(int i=0; i<n-1; i++) {
		int min = i;
		for(int j=i+1; j<n; j++)
			if(compare(tasks[j], tasks[min]))
				min = j;
		task_t temp = tasks[i];
		tasks[i] = tasks[min];
		tasks[min] = temp;
	}
}

/**
 * Create task execution order.  Assigns task numbers to slots.  Uses
 * non-preemptive EDF scheduling.
 * @param slots array representing task execution order
 * @param nSlot number of entries in slots
 * @param tasks array of tasks (the taskset)
 * @param nTask size of the taskset
 * @param LCM length of the fixed schedule
 * @return true on success, false on failure
 */
bool scheduleEDF(int slots[], int nSlot, task_t tasks[], int nTask, int LCM) {
	if (!c_assert(valid_LCM(LCM, tasks, nTask))) {
		return false;
	} 

	if (!c_assert(LCM, tasks, nTask, nSlot)) {
		return false;
	}

	sortAscending(tasks);

	for (int i=0;i<nTask;i++){
		printTask(tasks[i]);
	}

	int clock = 0;

	int nextDeadline[nTask];
	for (int i = 0; i < nTask; i++) {
		nextDeadline[i] = clock;
	}

	for (int s = 0; s < nSlot; s++) {
		for (int i = 0; i < nTask; i++) {
			if(nextDeadline[i] <= clock) {
				clock += tasks[i].C;
				slots[s] = tasks[i];
				nextDeadline[i] += tasks[i].T;
				break;
			}
		}
	}

	return true;
}

