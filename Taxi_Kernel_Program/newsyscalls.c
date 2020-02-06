//INCLUDES

#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>

//EXPORTS

int (*STUB_start_taxi)(void) = NULL;
EXPORT_SYMBOL(STUB_start_taxi);

int (*STUB_issue_request)(int passenger_type, int initial_platform, int destination_platform) = NULL;
EXPORT_SYMBOL(STUB_issue_request);

int (*STUB_stop_taxi)(void) = NULL;
EXPORT_SYMBOL(STUB_stop_taxi);

/*** LINKAGE ***/

asmlinkage int sys_start_taxi(void) {
  if (STUB_start_taxi)
    return STUB_start_taxi();
  else
    return -ENOSYS;
}

asmlinkage int sys_issue_request(int passenger_type, int initial_platform, int destination_platform) {
  if (STUB_issue_request)
    return STUB_issue_request(passenger_type,initial_platform,destination_platform);
  else
    return -ENOSYS;
}

asmlinkage int sys_stop_taxi(void) {
  if (STUB_stop_taxi)
    return STUB_stop_taxi();
  else
    return -ENOSYS;
}
