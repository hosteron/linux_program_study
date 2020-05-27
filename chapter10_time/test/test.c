#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void printtm(struct tm *tm)
{
		if(!tm) return;
		printf("%d/%d/%d %d:%d:%d \n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}
int main()
{
	//putenv("TZ=20");
	printf("TZ=%s\n", getenv("TZ"));
	
	time_t tm = 0;
	printf("%s", ctime(&tm));
	time_t t = time(NULL);
	printf("%ld\n", t);
	t = 1590417666;
	struct tm *tm1 = gmtime(&t);
	printf("tm1:%p, gtmime->DST:%d\n", tm1, tm1->tm_isdst);
	printtm(tm1);
	tm1->tm_isdst = 1;
	time_t a = mktime(tm1);
	printf("a = %ld, DST:%d\n", a, tm1->tm_isdst);
	struct tm *tm2 = localtime(&t);
	printf("tm2:%p, locatime->DST:%d\n", tm2, tm1->tm_isdst);
	printtm(tm2);
	//tm2->tm_isdst = 1;
	time_t b = mktime(tm2);
	printf("b = %ld, DST:%d\n", b, tm2->tm_isdst);
	
}
