#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define MAXNICK 32

int GetTimeStamp();
/*int JoinSeconds();
int LeaveSeconds();
int GetSessionInSeconds();*/
char *Time_Handler(char *command, char *user, const char *message);

struct Users
{
	struct Users *next;
	int JoinTime;
	int LeaveTime;
	int TotalTime;
	char user[MAXNICK];
};

/*struct OfflineUsers
{
	struct OfflineUsers *next;
	char user[MAXNICK];
	int TotalTime;
};*/

static struct Users *head = NULL;
/*static struct OfflineUsers *head = NULL;*/

int main()
{
	return 0;
}

int GetTimeStamp()
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	printf("%s\n", asctime(tm));
	return 0;
}

/*int JoinSeconds()
{
	time_t now = time(NULL);
	struct tm *tm;
	if ((tm = localtime (&now)) == NULL)
	{
        	printf ("Error getting minutes\n");
        	return 1;
    	}
	printf ("%d\n", tm->tm_sec);
	return tm->tm_sec;
}

int LeaveSeconds()
{
	time_t now = time(NULL);
	struct tm *tm;
	if ((tm = localtime (&now)) == NULL)
	{
        	printf ("Error getting minutes\n");
        	return 1;
    	}
	printf ("%d\n", tm->tm_sec);
	return tm->tm_sec;
}

int GetSessionInSeconds()
{
	double seconds;
	seconds = difftime(LeaveSeconds(), JoinSeconds());
	printf("%.f seconds\n", seconds);
	return 0;
}*/

char *Time_Handler(char *command, char *user, const char *message)
{
	struct Users *onlinenode;
	struct Users *newnode;
	char *ret = NULL;
	
	if(strncmp("PRIVMSG", command, 7) == 0)
	{
		if(strncmp(message, "~online", 7) == 0)
		{
			/*Search for username at character 8 in message, if they exist give online status by last time they joined is after the last time they left, and if they're offline, the last time they left is after the last time they joined, IF ONLINE: they have been online for certain amount of time, AND the total amount of time ever online. IF OFFLINE: Been offline for certain amount of time, and the total amount of time ever online*/
			onlinenode = head;
			while(onlinenode != NULL)/*make sure to end with the last node*/
			{
				if(strncmp(onlinenode->user,message+9,MAXNICK)==0)
				{
					if (onlinenode->JoinTime > onlinenode->LeaveTime)
					{
						int diff = difftime(onlinenode->TotalTime,GetTimeStamp());
						ret = malloc(512);
						sprintf(ret,"%d,%d",diff,onlinenode->TotalTime);
						return ret;
					}

					ret = malloc(512);
					sprintf(ret,"%d",onlinenode->TotalTime);
					return ret;/*What do I return?*/
				}
				onlinenode = onlinenode->next;
			}
		}

		return ret;
	}
	else if(strncmp("JOIN", command, 4) == 0)
	{
		/*If join, is there currently a struct for that user, if there is, update the join time, if there is not, make new element on list with username and jointime*/
		onlinenode = head;
		while(onlinenode->next != NULL)/*make sure to end with the last node*/
		{
			if(strncmp(onlinenode->user,user,MAXNICK)==0)
			{
				onlinenode->JoinTime = GetTimeStamp();

				ret = malloc(512);
				strcpy(ret, "User Found");
				return ret;/*What do I return?*/
			}
			onlinenode = onlinenode->next;
		}
		if(strncmp(onlinenode->user,user,MAXNICK)==0)/*check last node in list*/
		{
			onlinenode->JoinTime = GetTimeStamp();
			ret = malloc(512);
			strcpy(ret, "User Found");
			return ret;/*What do I return?*/
		}
		
		/*make new node since user does not exist*/
		newnode = malloc(sizeof(struct Users));
		onlinenode->next = newnode;
		strcpy(newnode->user, user);
		newnode->JoinTime = GetTimeStamp();
		newnode->LeaveTime = 0;
		newnode->TotalTime = 0;
		newnode->next = NULL;
		
		ret = malloc(512);
		strcpy(ret, "Made New User");
		return ret;/*What do I return?*/
	}
	else if(strncmp("QUIT", command, 4) == 0 || strncmp("PART", command, 4) == 0)
	{
		/*Search for user, if there is already that user, update leavetime and totalsessiontime by comparing leave and join time and add to a total time, if not, ignore */
		onlinenode = head;
		while(onlinenode != NULL)/*make sure to end with the last node*/
		{
			if(strncmp(onlinenode->user,user,MAXNICK)==0)
			{
				onlinenode->LeaveTime = GetTimeStamp();
				onlinenode->TotalTime = onlinenode->TotalTime + difftime(onlinenode->LeaveTime, onlinenode->JoinTime);

				ret = malloc(512);
				strcpy(ret, "User Logged Out");
				return ret;/*What do I return?*/
			}
			onlinenode = onlinenode->next;
		}
		
		printf("User left without enough information.\n");
		ret = malloc(512);
		strcpy(ret, "User left without enough information");
		return ret;
	}
	return ret;
}
