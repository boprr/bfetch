#include <stdio.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#define _PROGRAM_NAME "whoami"
#include <pwd.h>
#include "distro.h"
#include <sys/sysinfo.h>

const char *getUserName()
{
  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  if (pw)
  {
    return pw->pw_name;
  }

  return "";
}
int main(int argc, char *argv[])
{ 
	// kernel info
	struct utsname kernel_utsname;
	uname(&kernel_utsname);

	fprintf(stdout,kernel_utsname.nodename);
	fprintf(stdout,"@");
	fprintf(stdout,getUserName());

	fprintf(stdout,"\n");

	fprintf(stdout,"Kernel: ");
	fprintf(stdout,kernel_utsname.release);

	// user info
	struct sysinfo info;
	sysinfo(&info);
	fprintf(stdout,"\n");

	fprintf(stdout,"Uptime: ");
	const int ONE_HOUR = 60 * 60;
        const int ONE_MINUE = 60;
        long time_target = info.uptime;
        int hour;
        int min;
	hour=time_target/ONE_HOUR;
        time_target-=hour*ONE_HOUR;
        min=time_target/ONE_MINUE;
        time_target-=min*ONE_HOUR;
	printf("%dh %dm",hour,min);


	return 0;
}
