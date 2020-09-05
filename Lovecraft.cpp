#include "LovecraftCore.cpp"
#include <string>
#include <sstream>
using namespace std;

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
} 

void Query()
{	
	char qry[2048];
	cout << "************************************************" << endl;
	cout << "*                      PGSQL                   *" << endl;
	cout << "*                 L O V E C R A F T            *" << endl;
	cout << "************************************************" << endl;
	cout << endl;
	cout << "************************************************" << endl;
	cout << "*               2. Build Query                 *" << endl;
	cout << "************************************************" << endl;
	cout << endl;
	printf("Query: ");
	cin.ignore();
	cin.getline(qry, 2048);
	LovecraftCore Core;
	cout << endl;
	string TormResult;
	LovecraftResult qryr;
	qryr = Core.G_Query(qry,0);
	std::stringstream ss;
	ss << qryr.CodeStatus;
	TormResult = "{\"Data\":[" + qryr.Data + "], \"CodeStatus\":\"" + ss.str() + "\", \"Msg\" : \"" + qryr.Msg + "\"}";
	cout << TormResult;
	cout << endl;	
	cout << endl;		
}

void Test()
{
	cout << endl;
	cout << "************************************************" << endl;
	cout << "*                      PGSQL                   *" << endl;
	cout << "*                 L O V E C R A F T            *" << endl;
	cout << "************************************************" << endl;
	cout << endl;
	cout << "************************************************" << endl;
	cout << "*    1. Test to Database Connection            *" << endl;
	cout << "************************************************" << endl;
	cout << endl;
	LovecraftCore Core;
	string TormResult;
	LovecraftResult qry;
	qry = Core.TestQuery();
	std::stringstream ss;
	ss << qry.CodeStatus;
	TormResult = "{\"Data\":[" + qry.Data + "], \"CodeStatus\":\"" + ss.str() + "\", \"Msg\" : \"" + qry.Msg + "\"}";
	cout << TormResult;
	cout << endl;	
	cout << endl;
}

void GetServiceNumber()
{	
	string x;
	char* y;
	cout << endl;
	cout << "************************************************" << endl;
	cout << "*                      PGSQL                   *" << endl;
	cout << "*                 L O V E C R A F T            *" << endl;
	cout << "************************************************" << endl;
	cout << endl;
	cout << "************************************************" << endl;
	cout << "*    3. Convert string to new Service number   *" << endl;
	cout << "************************************************" << endl;
	cout << endl;
	printf("Service Name: ");
	cin >> x;
	y = (char *)x.c_str();
	cout << endl;
	cout << str2int(y);	
	cout << endl;	
	cout << endl;
}

void Menu()
{
	cout.flush();
	int op;
	do
	{
		cout << "************************************************" << endl;
		cout << "*                      PGSQL                   *" << endl;
		cout << "*                 L O V E C R A F T            *" << endl;
		cout << "************************************************" << endl;
		cout << endl;
		cout << "************************************************" << endl;
		cout << "*                     Menu                     *" << endl;
		cout << "************************************************" << endl;
		cout << endl;
		cout << "1. Test to Database Connection " << endl;
		cout << "2. Build Query " << endl;
		cout << "3. Convert string to new Service number" << endl;
		cout << "4. Exit" << endl;
		cout << "Option: ";
		op = 0;
		cin >> op;
		if(!cin)
		{
			cin.clear(); 
    		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     	
		}
		system("clear");
		cout.flush();		
	} while ((op < 1) || (op > 4));

	switch (op)
	{
	case 1:
		Test();
		Menu();
		break;
	case 2:		
		Query();
		Menu();	
		break;
	case 3:		
		GetServiceNumber();
		Menu();	
		break;
	case 4:
		system("exit");
		break;
	}
}

int main()
{
	string server, port, database, schema, user, pass, confirm, config, line,confirm2;
	char ch;
	ifstream fileconf("Conf.lvc");
	Function f;
	try
	{
		cout << "************************************************" << endl;
		cout << "*                    Test PGSQL                *" << endl;
		cout << "*                 L O V E C R A F T            *" << endl;
		cout << "************************************************" << endl;
		cout << endl;
		system("clear");
		if (fileconf.is_open())
		{
			cout << "Lovecraft is ready!" << endl;
			fileconf.close();
			Menu();
		}
		else
		{
			do
			{
				system("clear");
				cout << "Configurations..." << endl;
				cout << "Server database:";
				cin >> server;
				cout << endl
					 << "Port:";
				cin >> port;
				cout << endl
					 << "Database:";
				cin >> database;
				cout << endl
					 << "Schema:";
				cin >> schema;
				cout << endl
					 << "User:";
				cin >> user;
				cout << endl
					 << "Password:";
				cin >> pass;

				cout << endl;
				cout << "Are you sure this is your configuration: (Server: " << server << " Database: " << database << " User: " << user << ")? 'y' to confirm" << endl;
				cin >> confirm;
				confirm = f.UpperString(confirm);
			} while (confirm != "Y");
			line = "\n";
			config = f.Encrypt(server) + line;
			config += f.Encrypt(port) + line;
			config += f.Encrypt(database) + line;
			config += f.Encrypt(schema) + line;
			config += f.Encrypt(user) + line;
			config += f.Encrypt(pass) + line;
			remove("Conf.lvc");
			ofstream fileconf;
			fileconf.open("Conf.lvc");
			fileconf << config;
			fileconf.close();
			LovecraftCore Core;
			if(Core.CreateSchema())
			{
				cout << "Complete!" << endl;
				cout << "Lovecraft is ready! " << endl;
				cout << "Conf.lvc can be used to Lovecraft, Yog Sothoth and Azathoth" << endl;			
				system("clear");
				Menu();
			}
			else
			{
				cout << "Are you create configuration file again? 'y' to confirm" << endl;
				cin >> confirm2;
				confirm2 = f.UpperString(confirm2);
				if(confirm2 == "Y")
				{
					remove("Conf.lvc");
					main();
				}
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
		Menu();
	}
	return 0;
}