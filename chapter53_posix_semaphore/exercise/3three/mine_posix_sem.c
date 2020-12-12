//sem_t *sem_open(const char *name, int oflag)
//sem_wait()
//sem_post()
//sem_getvalue()
//sem_unlink()
//sem_close()

int m_sem_open(const char *name , int oflag , ...)
{
	char buf[128] = {0};
	snprintf(buf, sizeof(buf), "/tmp/%+%s", name);
	key_t key = ftok(buf, 'x');
	stat(buf, &st);
	// ...
	// 创建这个文件
	int id = semget(key, 1, mode);
	va_list ap;
	//...
	semctl(id, 0, SETVAL, arg);//进行初始化
	
	return id;
}
int m_sem_wait(int id)
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = 0;
	semop(id, &buf,  1)
}

int m_sem_post(int id)
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	semop(id, &buf , 1);

}

int m_sem_getvalue()
{
	semctl(id, 0, GETVAL, ...);
}

int m_sem_unlink(const char *name)
{
	unlink(name);
}


int m_sem_close(int id)
{
	semctl(id, 0, IPC_RMID);
}


