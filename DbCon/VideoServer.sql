BEGIN TRANSACTION;
.header on
.mode column

CREATE TABLE Tbl_user 
 (
  user_id numeric(6) primary key,
  user_name varchar(10) not null,
  user_pwd varchar(6),
  user_type char(1),
  user_stat char(1)
  --userRemark text default
  );
insert into Tbl_user values(1,'admin','123456','Y','1');
insert into Tbl_user values(2,'mick','000000','Y','1');
insert into Tbl_user values(3,'tom','888888','N','1');
insert into Tbl_user values(4,'jujy','123456','Y','1');
insert into Tbl_user values(5,'jack','123456','Y','1');

CREATE TABLE Tbl_role 
 (
   role_id numeric(6) primary key,
   role_name varchar(30)
 );
INSERT INTO Tbl_role VALUES(1000,'管理员');
INSERT INTO Tbl_role VALUES(1001,'业务员');
INSERT INTO Tbl_role VALUES(1002,'操作员');
CREATE TABLE Tbl_user_role
 (
   user_id numeric(6),
   role_id numeric(6)
 );
INSERT INTO "Tbl_user_role" VALUES(1,1000);
INSERT INTO "Tbl_user_role" VALUES(2,1001);
INSERT INTO "Tbl_user_role" VALUES(3,1002);
INSERT INTO "Tbl_user_role" VALUES(4,1001);
INSERT INTO "Tbl_user_role" VALUES(5,1000);

CREATE TABLE Tbl_role_menu
 (
   role_id numeric(6),
   menu_id numeric(6)
 );
INSERT INTO "Tbl_role_menu" VALUES(1000,2000);
INSERT INTO "Tbl_role_menu" VALUES(1000,2001);
INSERT INTO "Tbl_role_menu" VALUES(1000,2002);
INSERT INTO "Tbl_role_menu" VALUES(1000,2003);
INSERT INTO "Tbl_role_menu" VALUES(1000,2004);
INSERT INTO "Tbl_role_menu" VALUES(1001,2000);
INSERT INTO "Tbl_role_menu" VALUES(1001,2002);
INSERT INTO "Tbl_role_menu" VALUES(1001,2003);
INSERT INTO "Tbl_role_menu" VALUES(1001,2004);
INSERT INTO "Tbl_role_menu" VALUES(1002,2003);
INSERT INTO "Tbl_role_menu" VALUES(1002,2004);

CREATE TABLE Tbl_menu
 (
   menu_id numeric(6) primary key,
   menu_name VARCHAR(30) NOT NULL,
   menu_fid numeric(6),
   menu_stat char(1)
 );
 INSERT INTO Tbl_menu VALUES(2000,"system",0,'1');
 INSERT INTO Tbl_menu VALUES(2001,"manage",0,'1');
 INSERT INTO Tbl_menu VALUES(2002,"video",0,'1');
 INSERT INTO "Tbl_menu" VALUES(2003,"table",0,'1');
 INSERT INTO "Tbl_menu" VALUES(2004,"exit",0,'1');
 INSERT INTO "Tbl_menu" VALUES(2010,"a",2000,'1');
 INSERT INTO "Tbl_menu" VALUES(2011,"b",2000,'1');
 INSERT INTO "Tbl_menu" VALUES(2012,"c",2000,'1');
 INSERT INTO "Tbl_menu" VALUES(2013,"a",2001,'1');
 INSERT INTO "Tbl_menu" VALUES(2014,"b",2001,'1');
 INSERT INTO "Tbl_menu" VALUES(2015,"a",2002,'1');
 INSERT INTO "Tbl_menu" VALUES(2016,"b",2002,'1');
 INSERT INTO "Tbl_menu" VALUES(2017,"c",2002,'1');
 INSERT INTO "Tbl_menu" VALUES(2018,"d",2002,'1');
 INSERT INTO "Tbl_menu" VALUES(2019,"a",2003,'1');
 INSERT INTO "Tbl_menu" VALUES(2020,"logout",2004,'1');
 INSERT INTO "Tbl_menu" VALUES(2021,"exit",2004,'1');
 COMMIT;
