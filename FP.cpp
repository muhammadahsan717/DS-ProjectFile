#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>
#include<string>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<string>
#include<vector>
#include<sstream>
#include<stack>

using namespace std;

void input();
int main();
void LOGO();
char AddData();

class Node{
	public:
		string vehicleNumber, bodyType, city, engineType, exteriorColor, fuelType, interiorColor, url, majorOptions, make;
		string seatingCapacity, modelName, transmission, transmissionDisplay, wheelSystem, WSD, engineDisplacement, hp;
		string mileage, price, year, listing_color;
		Node *left, *right;
		int height;
		
		Node(string vin, string body_type, string city, string eD, string eT, string exc, string fT, string hp, 
			string iC, string url, string make_name, string maximum_seating, string mileage,
				string model_name, string price, string ts, string tsD, string wheel_system,
				string wheel_system_display, string year, string major_options, string list_color)
		{
			this->vehicleNumber = vin;
			this->bodyType = body_type;
			this->city = city;
			this->engineDisplacement = eD;
			this->engineType = eT;
			this->exteriorColor = exc;
			this->fuelType = fT;
			this->hp = hp;
			this->interiorColor = iC;
			this->url = url;
			this->make = make_name;
			this->seatingCapacity = maximum_seating;
			this->mileage = mileage;
			this->modelName = model_name;
			this->price = price;
			this->transmission = ts;
			this->transmissionDisplay = tsD;
			this->wheelSystem = wheel_system;
			this->WSD = wheel_system_display;
			this->year = year;
			this->majorOptions = major_options;
			this->listing_color = list_color;
			left = NULL;
			right = NULL;
		}
};

class BST
{
	private:
		Node *root;
//		BST()
//		{
//			root = NULL;
//		}
		
		Node *insert(string vin, string body_type, string city, string eD, string eT, string exC, string fT, string hp, 
		string iC, string url, string make, string seat, string mileage, string model_name, string price, string ts, 
		string tsD, string ws, string WSD, string year, string ma_op, string list_color, Node *p)
		{
			if( p == NULL )
			{
				p = new Node(vin, body_type, city, eD, eT, exC, fT, hp, iC, url, make, seat, mileage, 
				model_name, price, ts, tsD, ws, WSD, year, ma_op, list_color);
				p->height = 0;
				p->left = p->right = NULL;
			}
			else if(price < p->price)
			{
				p->left = insert(vin, body_type, city, eD, eT, exC, fT, hp, iC, url, make, seat, mileage, 
				model_name, price, ts, tsD, ws, WSD, year, ma_op, list_color, p->left);
				
				if(Height(p->left) - Height(p->right) == 2)
				{
					if (price < p->left->price)
                    	p = SingleRightRotate(p);
                else
                    p = DoubleRightRotate(p);
				}
			}
			
			else if(price > p->price)
			{
				p->right = insert(vin, body_type, city, eD, eT, exC, fT, hp, iC, url, make, seat, mileage, 
				model_name, price, ts, tsD, ws, WSD, year, ma_op, list_color, p->right);
				
				if (Height(p->right) - Height(p->left) == 2)
	            {
	                if (price > p->right->price)
	                    p = SingleLeftRotate(p);
	                else
	                    p = DoubleLeftRotate(p);
	            }	
			}
			
			p->height = Max(Height(p->left), Height(p->right)) + 1;
			return p;
		}
		
		int Max(int a, int b)
		{
			if(a > b)
				return a;
				
			else
				return b;
		}
	
		void MakeEmpty(Node *p)
	    {
	        if (p == NULL)
	            return;
	        MakeEmpty(p->left);
	        MakeEmpty(p->right);
	        delete p;
	    }
	    
		Node *SingleRightRotate(Node *&p)
	    {
	        Node *u = p->left;
	        p->left = u->right;
	        u->right = p;
	        p->height = Max(Height(p->left), Height(p->right)) + 1;
	        u->height = Max(Height(u->left), p->height) + 1;
	        return u;
	    }
	    
	    Node *SingleLeftRotate(Node *&p)
	    {
	        Node *u = p->right;
	        p->right = u->left;
	        u->left = p;
	        p->height = Max(Height(p->left), Height(p->right)) + 1;
	        u->height = Max(Height(u->right), p->height) + 1;
	        return u;
	    }
	
	    Node *DoubleLeftRotate(Node *&p)
	    {
	        p->right = SingleRightRotate(p->right);
	        return SingleLeftRotate(p);
	    }
	
	    Node *DoubleRightRotate(Node *&p)
	    {
	        p->left = SingleLeftRotate(p->left);
	        return SingleRightRotate(p);
	    }
	    
	    Node *FindMin(Node *p)
	    {
	        if (p == NULL)
	            return NULL;
	        else if (p->left == NULL)
	            return p;
	        else
	            return FindMin(p->left);
	    }
	
	    Node *FindMax(Node *p)
	    {
	        if (p == NULL)
	            return NULL;
	        else if (p->right == NULL)
	            return p;
	        else
	            return FindMax(p->right);
	    }
	
	    Node *Remove(string vin, string price, Node *p)
	    {
	        Node *temp;
	        // Element not found
	        if (p == NULL)
	            return NULL;
	
	        // Searching for element
	        else if (price < p->price)
	            p->left = Remove(vin, price, p->left);
	        else if (price > p->price)
	            p->right = Remove(vin, price, p->right);
	
	        // Element found
	        // With 2 children
	        else if (p->left && p->right && p->vehicleNumber == vin)
	        {
	            temp = FindMin(p->right);
//	            p->data = temp->data;
				p->vehicleNumber = temp->vehicleNumber;
				p->bodyType = temp->bodyType;
				p->city = temp->city;
				p->engineDisplacement = temp->engineDisplacement;
				p->engineType = temp->engineType;
				p->exteriorColor = temp->exteriorColor;
				p->fuelType = temp->fuelType;
				p->hp = temp->hp;
				p->interiorColor = temp->interiorColor;
				p->url = temp->url;
				p->make = temp->make;
				p->seatingCapacity = temp->seatingCapacity;
				p->mileage = temp->mileage;
				p->modelName = temp->modelName;
				p->price = temp->price;
				p->transmission = temp->transmission;
				p->transmissionDisplay = temp->transmissionDisplay;
				p->wheelSystem = temp->wheelSystem;
				p->WSD = temp->WSD;
				p->year = temp->year;
				p->majorOptions = temp->majorOptions;
				p->listing_color = temp->listing_color;
	            p->right = Remove(p->vehicleNumber, p->price, p->right);
	        }
	        // With one or zero child
	        else
	        {
	            temp = p;
	            if (p->left == NULL)
	                p = p->right;
	            else if (p->right == NULL)
	                p = p->left;
	            delete temp;
	        }
	        if (p == NULL)
	            return p;
	
	        p->height = Max(Height(p->left), Height(p->right)) + 1;
	
	        // If node is unbalanced
	        // If left node is deleted, right case
	        if (Height(p->left) - Height(p->right) == 2)
	        {
	            // right right case
	            if (Height(p->left->left) - Height(p->left->right) == 1)
	                return SingleLeftRotate(p);
	            // right left case
	            else
	                return DoubleLeftRotate(p);
	        }
	        // If right node is deleted, left case
	        else if (Height(p->right) - Height(p->left) == 2)
	        {
	            // left left case
	            if (Height(p->right->right) - Height(p->right->left) == 1)
	                return SingleRightRotate(p);
	            // left right case
	            else
	                return DoubleRightRotate(p);
	        }
	        return p;
	    }
	
	    int Height(Node *p)
	    {
	        return (p == NULL ? -1 : p->height);
	    }
	
	    int GetBalance(Node *p)
	    {
	        if (p == NULL)
	            return 0;
	        else
	            return Height(p->left) - Height(p->right);
	    }
	
	    
	    virtual void visit(Node *p)
		{
			cout << "Vehicle Number: " << p->vehicleNumber << endl;
			cout << "Body Type: " << p->bodyType << endl;
			cout << "City Registered: " << p->city << endl;
			cout << "Engine Displacement: " << p->engineDisplacement << " CC" << endl;
			cout << "Engine Type: " << p->engineType << endl;
			cout << "Exterior Color: " << p->exteriorColor << endl;
			cout << "InteriorColor: " << p->interiorColor << endl;
			cout << "Color: " << p->listing_color << endl;
			cout << "Horse Power: " << p->hp << endl;
			cout << "Fuel Type: " << p->fuelType << endl;
			cout << "Image Link: " << p->url << endl;
			cout << "Company Make: " << p->make << endl;
			cout << "Car Name: " << p->modelName << endl;
			cout << "Seating Capacity: " << p->seatingCapacity << endl;
			cout << "Mileage Driven: " << p->mileage << endl;
			cout << "Price: " << p->price << endl;
			cout << "Transmission: " << p->transmission << " - " << p->transmissionDisplay << endl;
			cout << "Wheel Drive: " << p->wheelSystem << " - " << p->WSD << endl;
			cout << "Year Registered: " << p->year << endl;
			cout << "MajorOptions: " << p->majorOptions << endl << endl;
		}
		
		void pre_order(Node *p)
		{
			if(p != 0)
			{
				pre_order(p->left);
				visit(p);
				pre_order(p->right);
			}
		}	    
	    
	    public:
	    	BST()
	    	{
	    		root = NULL;
			}
			
			void Insert(string vin, string body_type, string city, string eD, string eT, string exC, string fT, string hp, 
			string iC, string url, string make, string seat, string mileage, string model_name, string price, string ts, 
			string tsD, string ws, string WSD, string year, string ma_op, string list_color)
			{
				root = insert(vin, body_type, city, eD, eT, exC, fT, hp, iC, url, make, seat, mileage, 
				model_name, price, ts, tsD, ws, WSD, year, ma_op, list_color, root);
			}
			
			void remove(string vin, string price)
		    {
		        root = Remove(vin, price, root);
		    }
		    
		    void preOrder()
		    {
		    	pre_order(root);
			}
			
			~BST()
			{
				MakeEmpty(root);
			}
};

void input(string company, string CarName, string YearReg, string trans, string max_mile, string color)
{
	BST b;
	int it = 0;
	ifstream i;
	i.open("cars_data.csv");	
	if(!i.is_open())
	{
		cout << "File Not Opened!..." ;
	}
	else
	{
		string vin, body_type, city, eD, eT, exc, fT, hp, iC, list_color, url, make_name, seat, mileage, model_name, price, ts, 
		tsD, ws, wsD, year, maj_opt;
		
		while(i.good())
		{
			getline(i, vin, ',');
			getline(i, body_type, ',');
			getline(i, city, ',');
			getline(i, eD, ',');
			getline(i, eT, ',');
			getline(i, exc, ',');
			getline(i, fT, ',');
			getline(i, hp, ',');
			getline(i, iC, ',');
			getline(i, list_color, ',');
			getline(i, url, ',');
			getline(i, make_name, ',');
			getline(i, seat, ',');
			getline(i, mileage, ',');
			getline(i, model_name, ',');
			getline(i, price, ',');
			getline(i, ts, ',');
			getline(i, tsD, ',');
			getline(i, ws, ',');
			getline(i, wsD, ',');
			getline(i, year, ',');
			getline(i, maj_opt, '\n');
			
			if(make_name == company && model_name == CarName && ts == trans && year > YearReg && list_color == color && mileage < max_mile)
			{
				b.Insert(vin, body_type, city, eD, eT, exc, fT, hp, iC, url, make_name, seat, mileage, 
				model_name, price, ts, tsD, ws, wsD, year, maj_opt, list_color)	;
				it++;
			}
			
			if(it > 149)
			{
				break;
			}
		}
		
	}
	system("cls");
	LOGO();
	b.preOrder();
	cout << endl << endl <<"Showing Results For " << it << " Cars " << endl << endl;
	system("pause");
}

int t(void)
{
 	time_t t = time(0);   
    struct tm * now = localtime( & t );
	cout<<"Date : "<<__DATE__ << endl;
	cout<<"Time : "<<__TIME__ << endl;
	return 0;
}

void LOGO()
{
	cout<<"\t\t\t\t\t\t*****************************\n";
	cout<<"\t\t\t\t\t\t        US USED CARS\t\t\n";
	cout<<"\t\t\t\t\t\t*****************************\n";
	
	cout<<"\n";
}

char Search()
{
	string carName, yearReg, trans, company, max_mile, color;
	system("cls");
	LOGO();
	cout << endl << endl;
	
	cout << endl << "Enter Company Of The Car: " ;
	cin >> company;
	company[0] = toupper(company[0]);
	
	cout << "What Car Do You Want ? " ;
	cin >> carName;
	carName[0] = toupper(carName[0]);
	
	cout << "Enter Year Of Car To Be Registered or Least Year Registered: " ;
	cin >> yearReg;
	
	cout << "What transmission would you prefer ? For Automatic press A, For Manual Press M  " ;
	cin >> trans;
	
	trans[0] = toupper(trans[0]);
	
	cout << "Maximum mileage ? ";
	cin >> max_mile;
	
	cout << "Enter Car Preferred Color: " ;
	cin >> color;
	
	transform(color.begin(), color.end(), color.begin(), ::toupper);
	
	input(company, carName, yearReg, trans, max_mile, color);
	
	char ch;
	
	cout << endl << "Want To Search More Y/N\n";
	cin >> ch;
	
	while(! (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N'))
	{
		cout << "Wrong Choice\nEnter Again: ";
		cin >> ch;
	}
	
	return ch;
}

char Recommend(vector<string> arr)
{
	string comp, seating, bodyType;
	int seatChoice;
	
	cout << endl << "Enter Preferred Company: " ;
	fflush(stdin);
	getline(cin, comp);
	comp[0] = toupper(comp[0]);
	
	cout << endl << "For 5 seater Car Press 5 - For 7 Seater Car Press 7 - For 2 seater Car press 2 - For 8 seater Car press 8\n" ;
	cin >> seatChoice;
	
	while(! (seatChoice == 2 || seatChoice == 5 || seatChoice == 7 || seatChoice == 8))
	{
		cout << "Wrong Choice\nEnter Again: ";
		cin >> seatChoice;
	}
	
	if(seatChoice == 5)
	{
		seating = "5 seats";
	}
	else if(seatChoice == 7)
	{
		seating = "7 seats";
	}
	else if(seatChoice == 2)
	{
		seating = "2 seats";
	}
	else if(seatChoice == 8)
	{
		seating = "8 seats";
	}
	
	int opt;
	cout << endl << "Select Preferred Body Type\nFor Sedan Press 1\nFor SUV Press 2\nFor Hatchback Press 3\nFor Wagon Press 4\nFor Minivan Press 5\nFor Pickup Truck Press 6\nFor Coupe Press 7\n";
	cin >> opt;
	
	while(! (opt >= 1 && opt <= 7))
	{
		cout << "Wrong Choice\nEnter Again: ";
		cin >> opt;
	}
	
	if(opt == 1)
	{
		bodyType = "Sedan";
	}
	else if(opt == 2)
	{
		bodyType = "SUV / Crossover";
	}
	else if(opt == 3)
	{
		bodyType = "Hatchback";
	}
	else if(opt == 4)
	{
		bodyType = "Wagon";
	}
	else if(opt == 5)
	{
		bodyType = "Minivan";
	}
	else if(opt == 6)
	{
		bodyType = "Pickup Truck";
	}
	else
	{
		bodyType = "Coupe";
	}
	ifstream i;
	i.open("cars_data_0.csv");
	if(!i.is_open())
	{
		cout << "File Not Opened!..." ;
	}
	else
	{
		string vin, body_type, city, eD, eT, exc, fT, hp, iC, list_color, url, make_name, seat, mileage, model_name, price, ts, 
		tsD, ws, wsD, year, maj_opt;
		int it = 0, flag = 0;
		while(i.good())
		{
			getline(i, vin, ',');
			getline(i, body_type, ',');
			getline(i, city, ',');
			getline(i, eD, ',');
			getline(i, eT, ',');
			getline(i, exc, ',');
			getline(i, fT, ',');
			getline(i, hp, ',');
			getline(i, iC, ',');
			getline(i, list_color, ',');
			getline(i, url, ',');
			getline(i, make_name, ',');
			getline(i, seat, ',');
			getline(i, mileage, ',');
			getline(i, model_name, ',');
			getline(i, price, ',');
			getline(i, ts, ',');
			getline(i, tsD, ',');
			getline(i, ws, ',');
			getline(i, wsD, ',');
			getline(i, year, ',');
			getline(i, maj_opt, '\n');
			
			if(make_name == comp && body_type == bodyType && seat == seating)
			{
				flag = 0;
				
				for(int y = 0 ; y < arr.size() ; y++)
				{
					if(model_name == arr[y])
					{
						flag = 1;
					}
				}
				
				if(flag == 0)
				{
					arr.push_back(model_name);
//					cout << "Pushed!";
//					cout << model_name;
					it++;
				}
			}
		
		}
		if(it != 0)
		{
			system("cls");
			LOGO();
			char ch;
			cout << endl << "Recommended Cars: " << endl << endl;
			for(int x = 0 ; x < arr.size() ; x++ )
			{
				cout << x+1 << ". ";
				cout << arr[x] << endl;
			}
			
			cout << endl << "Want More Recommendations Y/N\n";
			cin >> ch;
			
			while(! (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N'))
			{
				cout << "Wrong Choice\nEnter Again: ";
				cin >> ch;
			}
			
			return ch;
		}
		else
		{
			cout << "No Such Car Exists In Our Record!...\nTry Searching With Another Details...\n";
			Recommend(arr);
		}
	}	

}

char AddData()
{
	system("cls");
	LOGO();
	string vin, body_type, city, engineDisplacement, engineType, exteriorColor, fuelType, horsepower, interiorColor;
	string listing_color, main_picture_url, majorOptions, make_name, maximum_seating, mileage, model_name, price;
	string transmission, transmission_display, wheel_system, wheel_system_display, year;
		
	ofstream file("cars_data.csv", ios::app);
	ofstream myfile("newdata.csv", ios::app);
		
	cout << "Enter Vehicle Number: " ;
	fflush(stdin);
	getline(cin, vin);
	
	cout << "Enter Vehicle Body Type: ";
	getline(cin, body_type);
	
	cout << "Enter Vehicle's Registration City: ";
	getline(cin, city);
	
	cout << "Enter Engine Displacement: " ;
	getline(cin, engineDisplacement);
	
	cout << "Enter Engine Type/Name: " ;
	getline(cin, engineType);
	
	cout << "Enter Vehicle's Exterior Color: ";
	getline(cin, exteriorColor);
	
	cout << "Enter Vehicle Fuel Type: " ;
	getline(cin, fuelType);
	
	cout << "Enter Vehicle's HorsePower: " ;
	getline(cin, horsepower);
	
	cout << "Enter Vehicle's Interior Color: " ;
	getline(cin, interiorColor);
	
	cout << "Enter Vehicle's Exterior Color Category: ";
	getline(cin, listing_color);
	
	cout << "Enter Vehicle's Image Link(optional): ";
	getline(cin, main_picture_url);
	
	cout << "Enter Vehicle's Company Name: ";
	getline(cin, make_name);
	
	cout << "Enter Vehicles's Seating Capacity: ";
	getline(cin, maximum_seating);
	
	cout << "Enter Vehicle's mileage: " ;
	getline(cin, mileage);
	
	cout << "Enter Vehicle's Name: ";
	getline(cin, model_name);

	cout << "Enter Price: " ;
	getline(cin, price);
	
	cout << "Enter Transmission(Short Form): ";
	getline(cin, transmission);
	
	cout << "Enter Transmission Display(Full Form): " ;
	getline(cin, transmission_display);
	
	cout << "Enter Wheel System(Short Form): ";
	getline(cin, wheel_system);
	
	cout << "Enter Wheel System Display(Full Form): ";
	getline(cin, wheel_system_display);
	
	cout << "Enter Year Registered: ";
	getline(cin, year);
	
	cout << "Enter Vehicle's Major Options: ";
	getline(cin, majorOptions);
	
	system("pause");
	
	file << vin << "," << body_type << "," << city << "," << engineDisplacement << "," << engineType << "," <<
	exteriorColor << "," << fuelType << "," << horsepower << "," << interiorColor << "," << listing_color << "," 
	<< main_picture_url << "," << make_name << "," << maximum_seating << "," << mileage << "," << model_name
	<< "," << price << "," << transmission << "," << transmission_display << "," << wheel_system << "," 
	<< wheel_system_display << "," << year << "," << majorOptions << endl;
	
	myfile << vin << "," << body_type << "," << city << "," << engineDisplacement << "," << engineType << "," <<
	exteriorColor << "," << fuelType << "," << horsepower << "," << interiorColor << "," << listing_color << "," 
	<< main_picture_url << "," << make_name << "," << maximum_seating << "," << mileage << "," << model_name
	<< "," << price << "," << transmission << "," << transmission_display << "," << wheel_system << "," 
	<< wheel_system_display << "," << year << "," << majorOptions << endl;
	
	
	cout << "DATA ENTERED IN FILE SUCCESSFULLY!..." ;
	file.close();
	
	char ch;
	
	cout << endl << "Want To ADD More Y/N\n";
	cin >> ch;
	
	while(! (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N'))
	{
		cout << "Wrong Choice\nEnter Again: ";
		cin >> ch;
	}

	return ch;
}

void menu()
{
	cout << endl << endl << "\t\t\t\t\t\tWelcome To US Used Car Portal" << endl;
	cout << endl << "1. Recommendation For Your Car\n2. Search For Specific Car\n3. Add Your Car For Selling\n4. Exit\n\nEnter Your Choice: " ;
	int choice;
	cin >> choice;
	
	while(! (choice >= 1 && choice <= 4) )
	{
		cout << "Wrong Choice\nEnter Again: ";
		cin >> choice;
	}
	
	if(choice == 1)
	{
		char ch;
		vector<string> arr;
		ch = Recommend(arr);
		while((ch == 'Y' || ch == 'y'))
		{
			ch = Recommend(arr);
		}
	}
	
	if(choice == 2)
	{
		char ch;
		ch = Search();
		while((ch == 'Y' || ch == 'y'))
		{
			ch = Search();
		}
	}
	
	if(choice == 3)
	{
		char ch;
		ch = AddData();
		while((ch == 'Y' || ch == 'y'))
		{
			ch = AddData();
		}
	}
	
	if(choice == 4)
	{
		return;
	}
	system("cls");
	LOGO();
	menu();
}

int main()
{
	system("cls");
	system("color F9");
	LOGO();
	t();
	menu();
	return 0;
}
