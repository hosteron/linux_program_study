#ifndef _UGID_FUNCTIONS_H_
#define _UGID_FUNCTIONS_H_
#include <pwd.h>
#include <grp.h>
#include <ctype.h>
char *userNameFromId(uid_t uid);
uid_t userIdFromName(const char *name);
char *groupNameFromdId(gid_t gid);
gid_t groupIdFromName(const char *name);
#endif
