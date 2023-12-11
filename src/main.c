// std
#include <stdio.h>
#include <stdlib.h>

// headers
#include "distro.h"

// SYS (info
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#define _PROGRAM_NAME "whoami"
#include <pwd.h>

// X11 (for screen res)
#include <X11/Xlib.h>

struct time
{
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
};

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
struct time format_time(long time_s)
{
	struct time temp;
    temp.hour = (time_s/3600); 
    temp.minute = (time_s -(3600*temp.hour))/60;
    temp.second = (time_s -(3600*temp.hour)-(temp.minute*60));
	return temp;
}
char* get_shell()
{
  FILE *fp;
  char path[1035];

  /* Open the command for reading. */
  fp = popen("/bin/echo $SHELL", "r");
  if (fp == NULL) {
    return "Failed to find SHELL";
	pclose(fp);
  }

  char* temp;

  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path), fp) != NULL) {
	temp = path;
  }

  /* close */
  pclose(fp);
  return temp;

  //this is bad.
}

int main(int argc, char *argv[])
{ 
	// kernel info
	/*
	fprintf(stdout,kernel_utsname.nodename);
	fprintf(stdout,"@");··········································································································· ✔  21:05:21  ─╮
╰─ ./bfetch                                                                 
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

	*/
	struct sysinfo info;
	sysinfo(&info);

	struct utsname kernel_utsname;
	uname(&kernel_utsname);

	printf("%s@%s \n",getUserName(),kernel_utsname.nodename);
	printf("Kernel: %s \n", kernel_utsname.release);
	struct time tt = format_time(info.uptime);
	printf("Uptime: %uh %um %us \n", tt.hour, tt.minute, tt.second);
	printf("Packages: %i \n", 0); //TODO
	printf("Shell: %s ", get_shell());
	printf("Resolution: %s \n", "1920x1080"); //TODO

	return 0;
}
