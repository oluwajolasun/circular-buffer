#define _CRT_SECURE_NO_WARNINGS
//OLUWAJOLASUN OLUFEMI JAIYESIMI B514802
//OBJECT ORIENTED PROGRAMMING

// A program to demonstrate the operation of a circular buffer.
//
// General description
// A circular buffer is a type of first-in first-out queue, normally fixed in length
// and is used as a temporary store of information that needs to be transmitted 
// asynchronously from one process to another.
//
// Implementation details
// The circular buffer holds messages entered by the user which are to be sent to the
// screen. The operation of the buffer is controlled by a menu from which the user can
// choose one of the following: enter a new message, send (consume) a message from the
// buffer or display the contents of the buffer.
//
// The buffer is implemented as a fixed length array. Once all the elements in the array
// have been filled, the first element will need to be used again. As an example of the
// operation of the circular buffer, assume that there are 10 elements in the array,
// 9 messages have been entered by the producer, 6 have been consumed and then a further 5
// produced. The next message to be consumed (tail of the buffer) would be the 7th element
// in the array and the next message entered (head of the buffer) would become the 5th 
// element in the array.

#include <iostream>
#include <string>
#include <time.h>
using namespace std;

struct message							     // the format of the messages in the buffer
{
	unsigned char data;						 // single byte of information to be sent
	time_t time;							 // number of seconds since 1 January 1970
};

#define BUFFER_LENGTH 10					 // The length value of the array buffer
char UserInput;								 // Global variable user input for main function 

/*Initialising buffer tail and buffer head to -1 to always start the buffer as an empty array*/
int buffer_tail = -1;
int buffer_head = -1;

message buffer[BUFFER_LENGTH];				 // Creating the buffer array
unsigned char data;
time_t current_time;
string BufferString;

/************************************* DEFINING CLASSES *************************************/
//The buffer class containing the three main functions for this code.
class MyBuffers
{
public:
	void Produce();
	void Consume();
	void Show();
};

class BufferMain
{
public:
	void Main();
};

int main()
{
	BufferMain BufferMains;
	BufferMains.Main();
}

// Create a new message and add it to the head of the buffer.
// The data for the message is obtained from the user and a time stamp is obtained from the
// time() function in the C standard library.
void MyBuffers::Produce()
{
	char UserInput;

	/*If the buffer is full*/
	if ((buffer_head == 0 && buffer_tail == BUFFER_LENGTH - 1) || (buffer_tail + 1 == buffer_head))
	{
		cout << "Error! Message cannot produced, Queue overflow" << endl;
		return;
	}

	/*if the buffer is not full*/
	cout << "What message will you like to store in the buffer? ";	// get the value of the data for the message from the user
	cin >> UserInput;
	if (buffer_head == -1)
	{
		buffer_head = 0, buffer_tail = 0;
	}
	else
	{
		if (buffer_tail == BUFFER_LENGTH - 1)
			buffer_tail = 0;
		else
			buffer_tail++;
	}
	buffer[buffer_tail].data = UserInput;        // get the value of the time for the message
	buffer[buffer_tail].time = time(&current_time);  //this will be the time in seconds since 1st jan 1970
	cout << endl;
	cout << "You have added '" << buffer[buffer_tail].data << "' to the buffer" << endl;
}

// Consumes the message at the head of the buffer and displays it after consumption.
void MyBuffers::Consume()
{
	if (buffer_head == -1)
	{
		cout << "The buffer is empty, nothing to consume" << endl;
		return;
	}

	cout << "You have consumed message '" << buffer[buffer_head].data << "' from the buffer" << endl;
	if (buffer_head == buffer_tail)
	{
		buffer_head = -1, buffer_tail = -1;
	}
	else
	{
		if (buffer_head == BUFFER_LENGTH - 1)
		{
			buffer_head = 0;
		}
		else
		{
			buffer_head++;
		}
	}
}


// Display all of the messages in the buffer and seconcds added since 1st of January 1970.
void MyBuffers::Show()
{
	int head_position = buffer_head;
	int tail_position = buffer_tail;

	// if the buffer is empty, display an error statement
	if (buffer_head == -1)
	{
		cout << "The buffer is empty, nothing to display" << endl;
		return;
	}

	//if the buffer is not empty, display all messages in the buffer
	if (head_position <= tail_position)
	{
		while (head_position <= tail_position)
		{
			cout << endl;
			cout << "The message '" << buffer[head_position].data << "' was added to the buffer" << endl;
			cout << buffer[head_position].time << " secs since 1st of January 1970" << endl;
			head_position++;
		}
	}

	else {
		while (head_position <= BUFFER_LENGTH - 1)
		{
			cout << endl;
			cout << "The message '" << buffer[head_position].data << "' was added to the buffer" << endl;
			cout << buffer[head_position].time << " secs since 1st of January 1970" << endl;
			head_position++;
		}

		head_position = 0;
		while (head_position <= tail_position)
		{
			cout << endl;
			cout << "The message '" << buffer[head_position].data << "' was added to the buffer" << endl;
			cout << buffer[head_position].time << " secs since 1st of January 1970" << endl;
			head_position++;
		}
	}
}

/*The main Fuction*/
void BufferMain::Main()
{
	while (1)
	{
		// show the menu of options
		cout << endl;
		cout << "----------------------" << endl;
		cout << "Buffer Management Menu" << endl;
		cout << "----------------------" << endl;
		cout << "1. Produce a new message for the buffer" << endl;
		cout << "2. Consume a message from the buffer" << endl;
		cout << "3. View the contents of the buffer" << endl;
		cout << "4. Exit from the program" << endl << endl;

		//cout << "front " << buffer_head << endl;
		//cout << "rear " << buffer_tail << endl;
		//cout << BUFFER_LENGTH << endl;

		// get the user's choice
		cout << "Enter your option: ";
		cin >> UserInput;
		cout << endl;

		MyBuffers MyBuffer;

		// act on the user's input
		switch (UserInput)
		{
		case '1':
			MyBuffer.Produce();
			break;

		case '2':
			MyBuffer.Consume();
			break;

		case '3':
			MyBuffer.Show();
			break;

		case '4':
			return;

		default:
			cout << "Invalid entry, try again." << endl << endl;
			break;
		}
	}
}