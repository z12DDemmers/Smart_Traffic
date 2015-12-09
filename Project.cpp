#include <iostream>
#include <thread>
#include <queue>
#include <stdlib.h>

  
using namespace std;
//this class represents a car object that contains two identifying members, the direction the car is driving and 
//whether or not the car is driving or waiting
class car{
	public:
	string Direction;
	bool isDriving;	
};

int carcount = 0; // variable to count the # of cars
queue <car> threads;//queue to hold threaded cars
void createCar();//creates a car object with a randomized direction
string randomdir();//create a random direction using a four option array
void createThreads();//spawns the threads that handle car creation
void processQueue();//processes the cars in the queue and lets one car go at a time while holding the others in a sleep state
int firstTime;//this gets the initial computer time when the cars start spawning to allow for a calculation of the time the car spent waiting
//at the intersection and in the queue



//the randomdir function is responsible for creating a randomized direction. This uses the srand time seed to randomize 
//a number between 0 and three that corresspondes to an index in a four member array. By randomly spawning a number, you are able to
//access directions in that array in random mannor without being able to predict the direction.
string randomdir()
{
  srand ( time(NULL) ); //initialize the random seed
  const string arraydir[4] = {"North", "South", "East", "West"};//the direction options available
  int RandIndex = rand() % 4; //generates a random number between 0 and 3
  return arraydir[RandIndex]; //returns random array index between 0 and 3
}



//createThreads is responsible for creating system threads and syncrhonizing them while in execution.
//The thread handles the creation of the car. 
void createThreads()
{
	    thread t(createCar);
		t.join();			 
	//Thread randomly creates cars with a random direction	
}




//this function is important in creating car objects with random direction and then load into a shared FIFO queue for processing
void createCar()
{
		car Car;//creates an empty object
		Car.Direction = randomdir();//initializes random direction
		Car.isDriving = true;//initializes the driving car
		threads.push(Car);//loads into queue for handling
	
}



int carpassing = 1;//the number of the car that passed through the intersection
void processQueue()
{
		     while(!threads.empty())//while the queue has car to proccess, it continues to proccess
		     {
			 	car Car = threads.front();//creates member to handle first car
			 	time_t timer = 0;
			 		if(threads.front().isDriving == true)//if car is driving
	     			{
					
						cout << "Car Number with thread ID " << carpassing++<< " Is Passing in the " << Car.Direction << " direction!" << endl;
						for (int j = 0; j < 3; j++)
						 {
   							cout << "\rDriving Through Intersection   \rDriving Through Intersection";
   							for (int i = 0; i < 3; i++)
							    {
      								cout << ".";
      								this_thread::sleep_for(chrono::seconds(1)); //sleeps the rest of the cars in queue and allows this car to pass the intersection
      								//in three seconds
								}
										break;
							}
						cout << endl;
	     				cout << "Car Passed through the intersection" << endl;
	     				cout << "Car spent " << time (&timer) - firstTime << " Seconds waiting since the first car passed!" <<endl <<endl; //calculates the 
	     				//amount of time the car spent both waiting in queue and passing through the intersection
						Car.isDriving == false;// car no longer needs to be considered driving because it has already passed
						threads.pop();// gets ride of it in the queue
		 			}	
				
		 }
}

void getFirstTime()//gets initialized time when the first car passes the intersection to allow the calculation of time cars spent waiting to be processed
{
	time_t timer = 0;
	firstTime = time(&timer); 
}



int main()
{
	bool first = true;
	for(int i = 0; i<15; i++)//spawn 15 threads and handle them
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
	

	cout << "15 Threads Completed! " << endl;


}

