 #include <unistd.h>
       #include <linux/reboot.h>
//这个linus自己和女儿们的生日
int main()
{
	//printf("LINUX_REBOOT_MAGIC1=%ld, %x\n", LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC1);
	printf("LINUX_REBOOT_MAGIC2=%x\n", LINUX_REBOOT_MAGIC2);
	printf("LINUX_REBOOT_MAGIC2A=%x\n", LINUX_REBOOT_MAGIC2A);
	printf("LINUX_REBOOT_MAGIC2B=%x\n", LINUX_REBOOT_MAGIC2B);
	printf("LINUX_REBOOT_MAGIC2C=%x\n", LINUX_REBOOT_MAGIC2C);
}
