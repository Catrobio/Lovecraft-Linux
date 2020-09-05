#include <algorithm>
#include <fstream>
#include <ctime>
#include <string>
#include <../../postgresql/libpq-fe.h>
#include "LovecraftResult.cpp"
#include "Functions.cpp"
#include "dbscript.cpp"
using namespace std;

class LovecraftCore
{
private:
	PGconn *cnn = NULL;
	PGresult *result = NULL;
	char *host;
	char *port;
	char *dataBase;
	char *user;
	char *passwd;
	char *Qry;
	string err;
	Function f;
	string strHost, strPort, strDataBase, strSchema, strUser, strPassword;
	bool Connect()
	{
		string line;
		int con = 0;
		ifstream fileconf("/Conf.lvc");
		fileconf.open("Conf.lvc");
		if (fileconf.is_open())
		{
			while (!fileconf.eof())
			{
				getline(fileconf, line);
				if (con == 0)
				{
					strHost = f.Descrypt(line);
				}
				if (con == 1)
				{
					strPort = f.Descrypt(line);
				}
				if (con == 2)
				{
					strDataBase = f.Descrypt(line);
				}
				if (con == 3)
				{
					strSchema = f.Descrypt(line);
				}
				if (con == 4)
				{
					strUser = f.Descrypt(line);
				}
				if (con == 5)
				{
					strPassword = f.Descrypt(line);
				}
				con++;
			}
			host = (char *)strHost.c_str();
			port = (char *)strPort.c_str();
			dataBase = (char *)strDataBase.c_str();
			user = (char *)strUser.c_str();
			passwd = (char *)strPassword.c_str();
			cnn = PQsetdbLogin(host, port, NULL, NULL, dataBase, user, passwd);
			if (PQstatus(cnn) != CONNECTION_BAD)
				return true;
			else
			{
				err = PQerrorMessage(cnn);
				return false;
			}
				
		}
		else
		{
			perror("Conf.lvc");
			return false;
		}
	}

	bool Disconnect()
	{
		PQfinish(cnn);
		return true;
	}

	bool ValidQuery(string sql)
	{
		int tf = 0;
		if (f.Isreplace(sql, "ALTER ", ""))
			tf += 1;
		if (f.Isreplace(sql, "DROP ", ""))
			tf += 1;
		if (f.Isreplace(sql, "TRUNCATE ", ""))
			tf += 1;
		if (f.Isreplace(sql, "LOCKET ", ""))
			tf += 1;
		if (f.Isreplace(sql, "TABLE ", ""))
			tf += 1;
		if (f.Isreplace(sql, "SHOW ", ""))
			tf += 1;
		if (f.Isreplace(sql, "DATABASE ", ""))
			tf += 1;
		if (f.Isreplace(sql, "DECLARE ", ""))
			tf += 1;
		if (tf == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ValidQuerySelect(string sql)
	{
		int tf = 0;
		sql = f.UpperString(sql);
		if (ValidQuery(sql))
		{
			if (f.Isreplace(sql, "INSERT ", ""))
				tf += 1;
			if (f.Isreplace(sql, "UPDATE ", ""))
				tf += 1;
			if (f.Isreplace(sql, "DELETE ", ""))
				tf += 1;
		}
		else
		{
			return false;
		}
		if (tf == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ValidQueryDelete(string sql)
	{
		int tf = 0;
		if (ValidQuery(sql))
		{
			sql = f.UpperString(sql);
			if (f.Isreplace(sql, "INSERT ", ""))
				tf += 1;
			if (f.Isreplace(sql, "UPDATE ", ""))
				tf += 1;
		}
		if (tf == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ValidQueryUpdate(string sql)
	{
		int tf = 0;
		if (ValidQuery(sql))
		{
			sql = f.UpperString(sql);
			if (f.Isreplace(sql, "INSERT ", ""))
				tf += 1;
			if (f.Isreplace(sql, "DELETE ", ""))
				tf += 1;
		}
		if (tf == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ValidQueryInsert(string sql)
	{
		int tf = 0;
		if (ValidQuery(sql))
		{
			sql = f.UpperString(sql);
			if (f.Isreplace(sql, "UPDATE ", ""))
				tf += 1;
			if (f.Isreplace(sql, "DELETE ", ""))
				tf += 1;
		}
		if (tf == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}	
public:
	LovecraftResult G_Query(string qry, int test)
	{
		LovecraftResult Res;
		Res.CodeStatus = 0;
		Res.Msg = "";
		Res.Data = "";
		if (ValidQuery(qry))
		{
			qry = f.replace(qry, "\\", "");
			if (Connect())
			{
				if (test == 1)
					qry += "'" + strSchema + "'";
				Qry = (char *)qry.c_str();
				result = PQexec(cnn, Qry);
				if (PQresultStatus(result) == PGRES_TUPLES_OK || PQresultStatus(result) == PGRES_COMMAND_OK)
				{
					int rows = PQntuples(result);
					int fields = PQnfields(result);
					if (fields != 0 && rows != 0)
					{
						for (int j = 0; j < rows; j++)
						{
							Res.Data = Res.Data + "{";
							for (int i = 0; i < fields; i++)
							{
								Res.Data = Res.Data + "\"" + PQfname(result, i) + "\"" + ":";
								Res.Data = Res.Data + "\"" + PQgetvalue(result, j, i) + "\"" + ",";
							}
							Res.Data = f.RTrim(Res.Data, ",");
							Res.Data = Res.Data + "},";
						}
						Res.Data = f.RTrim(Res.Data, ",");					
					}
					else
					{
						Res.Msg = "{}";
					}
				}
				else
				{					
					Res.CodeStatus = -101;
					err = f.replaceAll(PQerrorMessage(cnn),"\n"," ");        		
					Res.Msg = "There was an error in the query: "+f.replaceAll(f.replaceAll(err,"\""," "),"^","");
				}
				PQclear(result);
				Disconnect();
				return Res;
			}
			else
			{
				Res.CodeStatus = -100;
				Res.Msg = "Fail to connect to database: "+err;
			}
			Disconnect();
		}
		else
		{
			Res.CodeStatus = -1;
			Res.Msg = "invalid SQL!";
		}
		return Res;
	}

	LovecraftResult TestQuery()
	{
		string qry;
		qry = "select tablename from pg_tables where schemaname = ";
		return G_Query(qry, 1);
	}

	bool CreateSchema()
	{			
		if (Connect())
		{
			DBScript dbs;	
			string DBscript = dbs.scriptCreate(strSchema);
			Qry = (char *)DBscript.c_str();
			result = PQexec(cnn, Qry);
			if (PQresultStatus(result) == PGRES_COMMAND_OK)
			{
				return true;
				PQclear(result);
				Disconnect();
			}
			else
			{
				cout << endl
				<< "There was an error in create connection: "<<PQerrorMessage(cnn)
				<< endl;
				return false;
			}			
		}
		else
		{
			cout << endl
			<< "There was an error in create connection: "+err
			<< endl;
			return false;
		}
		
	}
};
