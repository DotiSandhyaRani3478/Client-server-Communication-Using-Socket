/* Doti SandhyaRani 
 A04714047 
 server.c  */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 256
int main()
{
	struct sockaddr_in sin;
	int len;
	FILE * fp;
	int select;
	int s, new_s;
	char a[4];
	char arr[30];
	int ret;
	char buff1[256];
	char buff2[256];
	char buff3[400];
	char buff4[256];
	char temp[256];
	char linec[256];
	FILE *fp1;
	int line_num = 1;
	int find_result = 0;
	unsigned char buff[256]={0};

	/* build address data structure */
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	/* setup passive open */
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("simplex-talk: socket");
		exit(1);
	}
	if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
		perror("simplex-talk: bind");
		exit(1);
	}

	listen(s, MAX_PENDING);
	
	new_s = accept(s, (struct sockaddr *)&sin, &len);
	
	/* wait for connection, then receive and print text */
	while(len = recv(new_s, &select, sizeof(select),0)) {

    
	//1.List all
	if(select == 1){
		fp = fopen("original_file.txt", "r");
   		fread(&buff, sizeof(buff), 1, fp); 
    		write (new_s, &buff, sizeof(buff));
		}

	//2.Search
	else if(select == 2){

		fp = fopen("original_file.txt", "r");
		len = recv(new_s,&buff,sizeof(buff),0);		
		while(fgets(temp,256,fp) != NULL){

        		if((strstr(temp, buff)) != NULL) {
				send(new_s,&temp,sizeof(temp),0);
			}	
		}	
		
	 }
	
	//3.Add
	else if(select == 3){
		read (new_s, &buff, sizeof(buff));
    		
		fp = fopen("original_file.txt","a+b");
	
		read (new_s, &buff1, sizeof(buff1));
		fp = fopen("original_file.txt","a+b");
		
		read (new_s, &buff2, sizeof(buff2));
		fp = fopen("original_file.txt","a+b");
		
		read (new_s, &buff3, sizeof(buff3));
		fp = fopen("original_file.txt","a+b");
		
		read (new_s, &buff4, sizeof(buff4));
		fp = fopen("original_file.txt","a+b");
		
		fputs(buff,fp);
		fprintf(fp,"\n%s\t%s\t%s\t%s\t%s",buff,buff1,buff2,buff3,buff4);
		fclose(fp);
	}

	//4.Delete
	else if(select == 4)
	{
		
		int i = 0;
		fp = fopen("original_file.txt", "r");
		fp1 = fopen("new_file.txt", "w+");
		read(new_s, &buff, sizeof(buff));

		while(fgets(temp,256,fp) != NULL){
			
        		if((strstr(temp, buff)) != NULL) {

			}
			else{
			   fprintf(fp1,temp);
			}	

		}
		
		fclose(fp);
		fclose(fp1);
		remove("original_file.txt");
		rename("new_file.txt","original_file.txt");	
				
	}	
 
  }
	close(new_s);
        sleep(1);
}

