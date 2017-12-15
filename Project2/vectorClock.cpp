
/*Doti SandhyaRani 
 (A04714047)
  Advanced OS Project2*/

#include<iostream>
using namespace std;

int main(){

	int process;
	int events;
	int ps,es,pr,er;
	int a[10][10][10];

	cout << "**************************"<< endl;
	cout << "VectorClock Timestamps" << endl;
	cout <<"***************************" << endl; 
	cout << "Enter the number of processes: ";
	cin >> process;
	cout << "Enter the number of events: ";
	cin >> events;

	
	//intializing local timestamps
	for(int i = 0;i<process;i++)
	{
		for(int j =0;j<events; j++)
		{

			for(int k=0;k<3;k++) 
			{
				if(i == k){
				  a[i][j][k] = j+1;}

				else{
				   a[i][j][k] = 0; 
					
				   }	
			
			}


		}

	}


    //sending the messages from sender event to receiver event
    for(int l = 0;l<4;l++){

		cout << "Enter sender's process no and event no. " << endl;
		cin >> ps >> es;
		cout << "Enter receiver's process no and event no. " << endl;
		cin >> pr >> er;
				

		

	for(int i = 0;i<process;i++)
	{

		for( int j =0;j<events; j++)
		{

			for(int k=0;k<3;k++) 
			{
				
				if((i==pr-1 && j == er-1)){

					a[i][j][k] = a[ps-1][es-1][k] + a[i][j][k];

					
				}
				else if( i==pr-1 && j > er-1 ){

					if(k!=i && er!= j-2){
						a[i][j][k] = a[i][j-1][k];

					}
					else
						a[i][j][k]=a[i][j][k];	

					}
 
				else{

					a[i][j][k]=a[i][j][k];

					}
				
				}

	
			}

		}
	}

	//displaying the timestamps of the events
	for(int i = 0;i<process;i++)
	{

		for( int j =0;j<events; j++)
		{
			cout << i+1 << "-" << j+1 <<  ":  (" ;

			for(int k=0;k<3;k++) 
			{
				cout << a[i][j][k];
				if(k!=2)
				cout << " ";

			}
			cout << ")  ";
		
		}
		
		cout << endl;
	}

	return 0;

}
