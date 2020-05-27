#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
extern char *tzname[2];
extern int daylight;
extern long timezone;
void printtm(struct tm *tm)
{
	if(!tm) return;
	printf("%d/%d/%d %d:%d:%d tm_isdst:%d\n", tm->tm_year + 1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tm->tm_isdst);
}
int main()
{
		printf("sysconf(_SC_CLK_TCK) = %ld, CLOCKS_PER_SEC=%d\n", sysconf(_SC_CLK_TCK),CLOCKS_PER_SEC);
		char *loc = setlocale(LC_ALL,NULL);
		printf("locale:%s\n", loc);
		time_t t = time(NULL);
		printf("time=%ld\n", t);
		struct tm *tm1 = gmtime(&t);
		printtm(tm1);
		tm1->tm_isdst =0;
		time_t a = mktime(tm1);
		printf("atim=%ld, mktime->tm_isdst:%d\n", a, tm1->tm_isdst);
		printf("%s", asctime(tm1));
		char buf[32] = {0};
		int ret = strftime(buf,sizeof(buf),"%c",tm1);
		printf("ret=%d, buf=%s\n", ret, buf);
		printf("-----------------------------------\n");
		struct tm *tm2 = localtime(&t);
		printtm(tm2);
		tm2->tm_isdst = 0;
		time_t b = mktime(tm2);
		printf("btim=%ld, mktime->tm_isdst:%d\n", b, tm2->tm_isdst);
		printf("%s", asctime(tm2));
		memset(buf, 0, sizeof(buf));
		ret = strftime(buf, sizeof(buf), "%c", tm2);
		printf("ret=%d, buf=%s\n", ret, buf);
		printf("tzname[0]:%s, tzname[1]:%s, dayligth:%d, timezone:%d\n", tzname[0],tzname[1],daylight, timezone);
		
		struct timeval tv;
		gettimeofday(&tv, NULL);
		ret = settimeofday(&tv, NULL);
		printf("ret = %d, %s\n", ret ,strerror(errno));
}
