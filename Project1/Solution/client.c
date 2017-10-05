/* Doti SandhyaRani 
   A04714047
 client.c */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#define SERVER_PORT 5432
#define MAX_LINE 256
int main(int argc, char * argv[])
{

	struct hostent *hp;
	struct sockaddr_in sin;
	char *host;
	char buff[MAX_LINE];
	int s;
	char arr[3];
	char buff2[256];
	int select;
	int len;
	if (argc==2) {
		host = argv[1];
	}
	else {
		fprintf(stderr, "usage: simplex-talk host\n");
	exit(1);
	}

	/* translate host name into peer's IP address */
	hp = gethostbyname(host);
	if (!hp) {
		fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
		exit(1);
	}

	/* build address data structure */
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
	sin.sin_port = htons(SERVER_PORT);

	/* active open */
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("simplex-talk: socket");
		exit(1);
	}
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("simplex-talk: connect");
		close(s);
		exit(1);
	}


 	printf("\n");
        printf("**********************************************************\n");
        printf("*                                                        *\n");
        printf("*    	Texas State University Courses            	 *\n");
        printf("*                                                       *\n");
        printf("*********************************************************\n");


	  do{
		
	  	
	   printf(" \n 1: List all \n 2: Search \n 3: Add \n 4: Delete \n 5: Quit \n Enter your choice : ");
	   scanf("%d", &select);
	   printf("\n");
	
	 //1.List all	
	 if(select == 1){
		write (s, &select, sizeof(select));
     	        read (s, &buff, sizeof(buff));
		fputs(buff,stdout);
		

		}

	//2.Search
	else if(select == 2){
		write (s, &select, sizeof(select));
		printf("What do you want to search? Please enter here...! \n");
		scanf("%s",&buff);
		send(s,&buff,sizeof(buff),0);		
		printf("The Course details are \n");
		len = recv(s,&buff,sizeof(buff),0);
		fputs(buff,stdout);		
		

	}

	//3.Add
	else if(select == 3){

			write (s, &select, sizeof(select));
			printf("enter details\n");
      			printf("enter CourseName  \n");
     			scanf("%s", &buff);
			write(s, &buff,sizeof(buff));	

			printf("enter CourseID :\n");
			scanf("%s",&buff);
			write(s, &buff,sizeof(buff));	

			printf("enter Number of Vacancies :\n");
			scanf("%s",&buff);
			write(s, &buff,sizeof(buff));	

			printf("enter number of seats available :\n");
			scanf("%s",&buff);
			write(s, &buff,sizeof(buff));	
			 
			printf("enter Time Offered : \n");
			scanf("%s",&buff);
			write(s, &buff,sizeof(buff));	
	
		}

	//4.Delete
	else if(select == 4){
		write (s, &select, sizeof(select));

		printf("What do you want to delete? Please enter here...! \n");
		scanf("%s",&buff);

		write(s,&buff,sizeof(buff));
		printf("You successfully deleted %s details...!!! \n",buff);
	}
		
	else if (select == 5){
		printf("Terminating the program \n");
		exit(1);

		}

	}while(select!=5);


	close(s);
		
}

