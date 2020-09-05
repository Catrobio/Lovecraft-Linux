#include <string>
#include <iostream>

using namespace std;

class DBScript
{
public:
    string scriptCreate(string sch)
    {
        string script = "create schema \""+sch+"\"; \n"+                
        "CREATE TABLE \""+sch+"\".lvc_typeauthentication ("+
            "idtypeauthentication serial NOT NULL,"+
            "typeauthenticationdescription varchar(100) NOT NULL,"+
            "active int4 NOT NULL,"+
            "CONSTRAINT pk_lvc_typeauthenticati PRIMARY KEY (idtypeauthentication)"+
        "); \n"+                
        "CREATE TABLE \""+sch+"\".lvc_usersdesactive ("+
            "iduserdesactive serial NOT NULL,"+
            "iduser int4 NOT NULL,"+
            "username varchar(200) NOT NULL,"+
            "pass varchar(200) NOT NULL,"+
            "identy varchar(45) NULL,"+
            "names varchar(100) NOT NULL,"+
            "lastname varchar(100) NULL,"+
            "datecreate timestamp NOT NULL,"+
            "datebirthday date NULL,"+
            "iduserstatus int4 NOT NULL,"+
            "idusertype int4 NOT NULL,"+
            "idtypeauthentication int4 NOT NULL,"+
            "CONSTRAINT pk_lvc_usersdesactive PRIMARY KEY (iduserdesactive)"+
        "); \n"+                               
        "CREATE TABLE \""+sch+"\".lvc_userstatus ("+
            "iduserstatus serial NOT NULL,"+
            "statusdescription varchar(100) NOT NULL,"+
            "active int4 NOT NULL,"+
            "CONSTRAINT pk_lvc_userstatus PRIMARY KEY (iduserstatus)"+
        "); \n"+        
        "CREATE TABLE \""+sch+"\".lvc_usertype ("+
            "idusertype serial NOT NULL,"+
            "usertypedescription varchar(200) NOT NULL,"+
            "active int4 NOT NULL,"+
            "CONSTRAINT pk_lvc_usertype PRIMARY KEY (idusertype)"+
        "); \n"+
        "CREATE TABLE \""+sch+"\".lvc_users ("+
            "iduser serial NOT NULL,"+
            "username varchar(200) NOT NULL,"+
            "pass varchar(200) NOT NULL,"+
            "identy varchar(45) NOT NULL,"+
            "names varchar(100) NOT NULL,"+
            "lastname varchar(100) NULL,"+
            "datecreate timestamp  NULL,"+
            "datebirthday date NULL,"+
            "ispublic int4 NULL,"+
            "emailuser varchar(200) NULL,"+
            "phoneuser varchar(16) NULL,"+
            "iduserstatus int4  NULL,"+
            "idusertype int4  NULL,"+
            "idtypeauthentication int4 NOT NULL,"+
            "CONSTRAINT pk_lvc_users PRIMARY KEY (iduser),"+
            "CONSTRAINT fk_lvc_users_lvc_typeauthentication FOREIGN KEY (idtypeauthentication) REFERENCES \""+sch+"\".lvc_typeauthentication(idtypeauthentication),"+
            "CONSTRAINT fk_lvc_users_lvc_userstatus FOREIGN KEY (iduserstatus) REFERENCES \""+sch+"\".lvc_userstatus(iduserstatus),"+
            "CONSTRAINT fk_lvc_users_lvc_usertype FOREIGN KEY (idusertype) REFERENCES \""+sch+"\".lvc_usertype(idusertype)"+
        "); \n"+         
        "CREATE TABLE \""+sch+"\".lvc_userauthentication ("+
            "iduserauthentication serial NOT NULL,"+
            "usertoken varchar(32) NOT NULL,"+
            "dateconnection timestamp NOT NULL,"+
            "dateexpiration timestamp NOT NULL,"+
            "infoconnection varchar(200) NOT NULL,"+
            "isactive int4 NOT NULL,"+
            "user_iduser int4 NOT NULL,"+
            "CONSTRAINT pk_lvc_userauthenticati PRIMARY KEY (iduserauthentication),"+
            "CONSTRAINT fk_lvc_userauthentication_lvc_users FOREIGN KEY (user_iduser) REFERENCES \""+sch+"\".lvc_users(iduser)"+            
        "); \n"+              
        "ALTER TABLE \""+sch+"\".lvc_userauthentication ADD CONSTRAINT lvc_userauthentication_un UNIQUE (usertoken); \n"+             
        "INSERT INTO \""+sch+"\".lvc_usertype"+
        "(idusertype, usertypedescription, active)"+
        "VALUES(1, 'Initial', 1); \n"+
        "INSERT INTO \""+sch+"\".lvc_usertype"+
        "(idusertype, usertypedescription, active)"+
        "VALUES(2, 'Administrator', 1); \n"+
        "INSERT INTO \""+sch+"\".lvc_usertype"+
        "(idusertype, usertypedescription, active)"+
        "VALUES(3, 'User Initial', 1); \n"+        
        "INSERT INTO \""+sch+"\".lvc_userstatus"+
        "(iduserstatus, statusdescription, active)"+
        "VALUES(1, 'Active', 1); \n"+
        "INSERT INTO \""+sch+"\".lvc_userstatus"+
        "(iduserstatus, statusdescription, active)"+
        "VALUES(2, 'Unabled', 1); \n"+
        "INSERT INTO \""+sch+"\".lvc_userstatus"+
        "(iduserstatus, statusdescription, active)"+
        "VALUES(3, 'Block', 1); \n"+        
        "INSERT INTO \""+sch+"\".lvc_typeauthentication"+
        "(idtypeauthentication, typeauthenticationdescription, active)"+
        "VALUES(1, 'Form', 1); \n";        
        return script;     
    }
};