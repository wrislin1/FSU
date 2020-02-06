#include <linux/init.h> //For initializaton macros
#include <linux/module.h> //For module functions and macros
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <asm/atomic.h>
#include <asm/spinlock.h>

//Required -- declaring lisense.
MODULE_LICENSE("GPL");

#define ENGINEER 0
#define EXECUTIVE 1
#define ROBOT 2
#define LOAD_TIME 5
#define TRANSIT_TIME 200
#define MAX_COMPARTMENTS 50
#define OFFLINE 0
#define DEACTIVATING 1
#define MOVING 2
#define PARKED 3
#define PLAT1 1
#define PLAT2 2
#define PLAT3 3
#define PLAT4 4
#define PLAT5 5

static const char *PROC_NAME = "taxi";

// system calls
extern int (*STUB_start_taxi)(void);
extern int (*STUB_issue_request)(int passenger_type, int initial_platform, int destination_platform);
extern int (*STUB_stop_taxi)(void);

//taxi manager values
static struct task_struct *main_taxi;

static int status;
static int location;
const int COMPARTMENTS_NEEDED[3] = {1,2,4};
static int platform1[3];
static int platform2[3];
static int platform3[3];
static int platform4[3];
static int platform5[3];
static int passenger_total[3];
static int* origin;
static int* destination;
static int total_delivered;
static spinlock_t lock;

int start_taxi(void);
int issue_request(int passenger_type, int initial_platform, int destination_platform);
int stop_taxi(void);
int proc_read(char *page, char **pages, off_t offset, int page_size, int *eof, void *data);
void acquire_lock(void);
void release_lock(void);

int taxi_init(void)	
{
	printk(KERN_ALERT "Module loaded successfully, now where did I park my car?\n");

	struct proc_dir_entry *taxi_proc;

	// SYSTEM CALLS
	STUB_start_taxi = &(start_taxi);
	STUB_issue_request = &(issue_request);
	STUB_stop_taxi = &(stop_taxi);

	platform1[ENGINEER]=0;
	platform1[EXECUTIVE]=0;
	platform1[ROBOT]=0;
	platform2[ENGINEER]=0;
	platform2[EXECUTIVE]=0;
	platform2[ROBOT]=0;
	platform3[ENGINEER]=0;
	platform3[EXECUTIVE]=0;
	platform3[ROBOT]=0;
	platform4[ENGINEER]=0;
	platform4[EXECUTIVE]=0;
	platform4[ROBOT]=0;
	platform5[ENGINEER]=0;
	platform5[EXECUTIVE]=0;
	platform5[ROBOT]=0;
	passenger_total[ENGINEER]=0;
	passenger_total[EXECUTIVE]=0;
	passenger_total[ROBOT]=0;
	status = PARKED;
	location = PLAT3;
	origin=NULL;
	destination=NULL;

}


void taxi_exit(void)
{
	printk(KERN_ALERT "I was removed.\n");
}

int proc_read(char *page, char **pages, off_t offset, int page_size, int *eof, void *data)
{
}

//taxi_manager - main control loop
static int taxi_manager(void *args) {
	while (!kthread_should_stop()) {

	}
	return 0;
}

//RETURNS 0 FOR SUCCESS
//TODO - add return 1 for already started
int start_taxi(void)
{
	main_taxi = kthread_run(taxi_manager, NULL, "taxi");

	return 0;
}

int issue_request(int passenger_type, int initial_platform, int destination_platform)
{
	return 0;
}

int stop_taxi(void)
{
	int ret;

	ret = kthread_stop(main_taxi);
	if (ret == -EINTR)
		return 1;

	return 0;
}

//Macros to define functions to be called
module_init(taxi_init);
module_exit(taxi_exit);







