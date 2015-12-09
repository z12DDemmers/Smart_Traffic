#include <iostream>
#include <thread>
#include <queue>
#include <stdlib.h>

  
using namespace std;

class car{
	public:
	string Direction;
	bool isDriving;	
};

int carcount = 0;
queue <car> threads;
void createCar();
string randomdir();
void createThreads();
void processQueue();
int firstTime;


string randomdir()
{
  srand ( time(NULL) ); //initialize the random seed
  const string arraydir[4] = {"North", "South", "East", "West"};//the direction options available
  int RandIndex = rand() % 4; //generates a random number between 0 and 3
  return arraydir[RandIndex]; //returns random array index between 0 and 3
}

void createThreads()
{
	    thread t(createCar);
		t.join();			 
	//Thread randomly creates cars with a random direction	
}

void createCar()//this function is important in creating car objects with random direction and then load into a shared FIFO queue for processing
{
		car Car;
		Car.Direction = randomdir();
		Car.isDriving = true;
		threads.push(Car);
	
}

int carpassing = 1;
void processQueue()
{
		     while(!threads.empty())
		     {
			 	car Car = threads.front();
			 	time_t timer = 0;
			 		if(threads.front().isDriving == true)
	     			{
					
						cout << "Car Number with thread ID " << carpassing++<< " Is Passing in the " << Car.Direction << " direction!" << endl;
						for (int j = 0; j < 3; j++)
						 {
   							cout << "\rDriving Through Intersection   \rDriving Through Intersection";
   							for (int i = 0; i < 3; i++)
							    {
      								cout << ".";
      								this_thread::sleep_for(chrono::seconds(1));
								}
										break;
							}
						cout << endl;
						// this_thread::sleep_for(chrono::seconds(3));
	     				
	     				cout << "Car Passed through the intersection" << endl;
	     				cout << "Car spent " << time (&timer) - firstTime << " Seconds waiting since the first car passed!" <<endl <<endl;
						Car.isDriving == false;
						threads.pop();
		 			}	
				
		 }
}

void getFirstTime()
{
	time_t timer = 0;
	firstTime = time(&timer); 
}



int main()
{
	bool first = true;
	for(int i = 0; i<50; i++)
	{
		if(first == true)
		{
			createThreads();
			getFirstTime();
			processQueue();
			
			first = false;
		}
		else
		{
			createThreads();	
			processQueue();
		}
		
		
	}
	

	cout << "50 Threads Completed! " << endl;


}

