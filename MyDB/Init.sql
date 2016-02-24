BEGIN TRANSACTION;


---------------------------------系统用户管理关系表--------------------------------------------------------------------
CREATE TABLE Tbl_user --用户表
 (
  user_id numeric(6) PRIMARY KEY,--用户序号
  user_name varchar(15) not null,--用户名
  user_pwd varchar(10),          --用户密码
  user_account varchar(15),      --用户帐号
  user_stat integer default 1,   --用户状态
  user_remark text               --备注
  );
  
INSERT INTO "Tbl_user" VALUES(1,'admin','123456','100000',1,'管理员');
INSERT INTO "Tbl_user" VALUES(2,'mick','000000','100001',1,'');
INSERT INTO "Tbl_user" VALUES(3,'tom','888888','100002',1,'');
INSERT INTO "Tbl_user" VALUES(4,'jujy','123456','100003',1,'');
INSERT INTO "Tbl_user" VALUES(5,'jack','123456','100004',1,'');
INSERT INTO "Tbl_user" VALUES(6,'test1','0','100005',1,'NULL');
INSERT INTO "Tbl_user" VALUES(7,'test2','0','100006',1,'NULL');
INSERT INTO "Tbl_user" VALUES(8,'test3','0','100007',1,'NULL');
INSERT INTO "Tbl_user" VALUES(9,'test4','0','100008',1,'NULL');
INSERT INTO "Tbl_user" VALUES(10,'test5','0','100009',1,'NULL');
INSERT INTO "Tbl_user" VALUES(11,'test8','0','100010',1,'NULL');
INSERT INTO "Tbl_user" VALUES(12,'test9','0','100011',1,'NULL');
INSERT INTO "Tbl_user" VALUES(13,'test6','0','100012',1,'');
INSERT INTO "Tbl_user" VALUES(14,'test7','0','100013',1,'test');
INSERT INTO "Tbl_user" VALUES(15,'貂蝉','0','100014',1,'落雁');
INSERT INTO "Tbl_user" VALUES(16,'孙策','0','100015',1,'伯符');
INSERT INTO "Tbl_user" VALUES(17,'吕布','0','100016',1,'奉先');
INSERT INTO "Tbl_user" VALUES(18,'鲁肃','0','100017',1,'子敬');
INSERT INTO "Tbl_user" VALUES(19,'庞统','0','100018',1,'士元');
INSERT INTO "Tbl_user" VALUES(20,'水镜先生','0','100019',1,'未祥');
INSERT INTO "Tbl_user" VALUES(21,'吕蒙','0','100020',1,'子明');
INSERT INTO "Tbl_user" VALUES(22,'郭嘉','0','100021',1,'奉孝');
CREATE TABLE Tbl_role --角色表
 (
   role_id numeric(6) PRIMARY KEY,
   role_name varchar(30)
 );
 
INSERT INTO "Tbl_role" VALUES(1000,'管理员');
INSERT INTO "Tbl_role" VALUES(1001,'业务员');
INSERT INTO "Tbl_role" VALUES(1002,'操作员');
CREATE TABLE Tbl_user_role--用户角色关系表
 (
   user_id numeric(6) NOT NULL,
   role_id numeric(6) NOT NULL
 );
INSERT INTO "Tbl_user_role" VALUES(1,1000);
INSERT INTO "Tbl_user_role" VALUES(2,1001);
INSERT INTO "Tbl_user_role" VALUES(3,1002);
INSERT INTO "Tbl_user_role" VALUES(4,1001);
INSERT INTO "Tbl_user_role" VALUES(5,1000);
INSERT INTO "Tbl_user_role" VALUES(6,1002);
INSERT INTO "Tbl_user_role" VALUES(7,1002);
INSERT INTO "Tbl_user_role" VALUES(8,1002);
INSERT INTO "Tbl_user_role" VALUES(9,1002);
INSERT INTO "Tbl_user_role" VALUES(10,1002);
INSERT INTO "Tbl_user_role" VALUES(11,1002);
INSERT INTO "Tbl_user_role" VALUES(12,1002);
INSERT INTO "Tbl_user_role" VALUES(13,1002);
INSERT INTO "Tbl_user_role" VALUES(14,1002);
INSERT INTO "Tbl_user_role" VALUES(15,1002);
INSERT INTO "Tbl_user_role" VALUES(16,1002);
INSERT INTO "Tbl_user_role" VALUES(17,1002);
INSERT INTO "Tbl_user_role" VALUES(18,1001);
INSERT INTO "Tbl_user_role" VALUES(19,1001);
INSERT INTO "Tbl_user_role" VALUES(20,1001);
INSERT INTO "Tbl_user_role" VALUES(21,1001);
INSERT INTO "Tbl_user_role" VALUES(22,1001);


CREATE TABLE Tbl_role_menu--角色菜单关系表
 (
   role_id numeric(6) NOT NULL,
   menu_id numeric(6) NOT NULL
 );
INSERT INTO "Tbl_role_menu" VALUES(1000,2000);
INSERT INTO "Tbl_role_menu" VALUES(1000,2001);
INSERT INTO "Tbl_role_menu" VALUES(1000,2002);
INSERT INTO "Tbl_role_menu" VALUES(1000,2003);
INSERT INTO "Tbl_role_menu" VALUES(1000,2004);
INSERT INTO "Tbl_role_menu" VALUES(1001,2001);
INSERT INTO "Tbl_role_menu" VALUES(1001,2002);
INSERT INTO "Tbl_role_menu" VALUES(1001,2003);
INSERT INTO "Tbl_role_menu" VALUES(1001,2004);
INSERT INTO "Tbl_role_menu" VALUES(1002,2003);
INSERT INTO "Tbl_role_menu" VALUES(1002,2004);
CREATE TABLE Tbl_menu--菜单表
 (
   menu_id numeric(6) PRIMARY KEY,
   menu_name VARCHAR(30) NOT NULL,
   menu_fid numeric(6)
 );
 
INSERT INTO "Tbl_menu" VALUES(2000,'系统管理',0);
INSERT INTO "Tbl_menu" VALUES(2001,'客户端管理',0);
INSERT INTO "Tbl_menu" VALUES(2002,'视频管理',0);
INSERT INTO "Tbl_menu" VALUES(2003,'报表统计',0);
INSERT INTO "Tbl_menu" VALUES(2004,'退出登录',0);
INSERT INTO "Tbl_menu" VALUES(2010,'组织机构管理',2000);
INSERT INTO "Tbl_menu" VALUES(2011,'用户管理',2000);
INSERT INTO "Tbl_menu" VALUES(2012,'系统参数设置',2000);
INSERT INTO "Tbl_menu" VALUES(2013,'用户管理',2001);
INSERT INTO "Tbl_menu" VALUES(2014,'用户点播管理',2001);
INSERT INTO "Tbl_menu" VALUES(2015,'频道信息管理',2002);
INSERT INTO "Tbl_menu" VALUES(2016,'分类信息管理',2002);
INSERT INTO "Tbl_menu" VALUES(2017,'地区信息管理',2002);
INSERT INTO "Tbl_menu" VALUES(2018,'视频信息管理',2002);
INSERT INTO "Tbl_menu" VALUES(2019,'点播报表',2003);
INSERT INTO "Tbl_menu" VALUES(2020,'注销',2004);
INSERT INTO "Tbl_menu" VALUES(2021,'退出',2004);
------------------------------------客户端用户管理表--------------------------------------------------------------------
CREATE TABLE Tbl_cuser   --客户端用户表
 (
   user_id numeric(6) PRIMARY KEY,
   user_name VARCHAR(30) NOT NULL,
   user_pwd varchar(10),
   user_account varchar(15),  --用户帐号
   user_stat integer,
   user_logintime TEXT,
   user_remark TEXT
 );
INSERT INTO "Tbl_cuser" VALUES(1,'songjiang','a',"100000",1,'2013-09-01','student');
INSERT INTO "Tbl_cuser" VALUES(2,'mick','000000',"100001",1,'2013-04-04','NULL');
INSERT INTO "Tbl_cuser" VALUES(3,'tom','888888',"100002",1,'2013-05-10','student');
INSERT INTO "Tbl_cuser" VALUES(4,'taiseng','123456',"100003",1,'2013-09-17','teacher');
INSERT INTO "Tbl_cuser" VALUES(5,'xiaosi','888888',"100004",1,'2013-08-12','student');
INSERT INTO "Tbl_cuser" VALUES(6,'xiaowu','123456',"100005",1,'2012-12-12','poet');
INSERT INTO "Tbl_cuser" VALUES(7,'xiaoxi','888888','100006',1,'2013-07-13','drewer');
INSERT INTO "Tbl_cuser" VALUES(8,'xiaoming','123456','100007',1,'2013-01-12','singer');


--------------------------------------报表统计关系表--------------------------------------------------------------------
 CREATE TABLE Tbl_video_message  --视频信息表
(
  video_id numeric(6) PRIMARY KEY,--视频ID
  channel_id numeric(6),--频道ID
  area_id numeric(6),--地区ID
  type_id numeric(6),--分类ID
  video_name text--视频名称
  --play_count integer--播放次数
 );
 INSERT INTO "Tbl_video_message" VALUES(1000,2,1,4,'英雄');
 INSERT INTO "Tbl_video_message" VALUES(1001,2,2,3,'海角七号');
 INSERT INTO "Tbl_video_message" VALUES(1002,2,4,1,'指环王');
 INSERT INTO "Tbl_video_message" VALUES(1003,1,1,5,'神雕侠侣');
 INSERT INTO "Tbl_video_message" VALUES(1004,3,1,6,'天天向上');
 INSERT INTO "Tbl_video_message" VALUES(1005,2,3,3,'阿甘正传');
 INSERT INTO "Tbl_video_message" VALUES(1006,2,4,3,'忠犬八公');
 INSERT INTO "Tbl_video_message" VALUES(1007,2,1,3,'唐山大地震');
 INSERT INTO "Tbl_video_message" VALUES(1008,2,2,3,'天台');
 INSERT INTO "Tbl_video_message" VALUES(1009,1,1,5,'步步惊心');
 INSERT INTO "Tbl_video_message" VALUES(1010,2,1,2,'龙门飞甲');
 INSERT INTO "Tbl_video_message" VALUES(1011,2,4,1,'蜘蛛侠');
 INSERT INTO "Tbl_video_message" VALUES(1012,2,4,1,'变形金刚');
 INSERT INTO "Tbl_video_message" VALUES(1013,3,1,6,'中国好声音');
 INSERT INTO "Tbl_video_message" VALUES(1014,2,2,3,'岁月神偷');
 INSERT INTO "Tbl_video_message" VALUES(1015,4,3,7,'红日');
 INSERT INTO "Tbl_video_message" VALUES(1016,4,3,7,'传奇');
 INSERT INTO "Tbl_video_message" VALUES(1017,4,3,7,'浮夸');
 INSERT INTO "Tbl_video_message" VALUES(1018,4,3,7,'谁明浪子心');
 INSERT INTO "Tbl_video_message" VALUES(1019,3,4,6,'达人秀');
 INSERT INTO "Tbl_video_message" VALUES(1020,3,2,6,'康熙来了');
 INSERT INTO "Tbl_video_message" VALUES(1021,1,2,5,'还珠格格');
 INSERT INTO "Tbl_video_message" VALUES(1022,1,3,5,'四大才子');
 INSERT INTO "Tbl_video_message" VALUES(1023,1,1,4,'小李飞刀');
 INSERT INTO "Tbl_video_message" VALUES(1024,1,1,4,'天涯明月刀');


 CREATE TABLE Tbl_video_area  --视频地区信息表
(
  area_id varchar(6) PRIMARY KEY,--地区ID
  area_name text--地区名称
 );
 INSERT INTO "Tbl_video_area" VALUES('','全部');
 INSERT INTO "Tbl_video_area" VALUES('1','大陆');
 INSERT INTO "Tbl_video_area" VALUES('2','台湾');
 INSERT INTO "Tbl_video_area" VALUES('3','香港');
 INSERT INTO "Tbl_video_area" VALUES('4','其他');
 
 CREATE TABLE Tbl_video_channel  --视频频道信息表
(
  channel_id varchar(6) PRIMARY KEY,--频道ID
  channel_name text--频道名称
 );
 INSERT INTO "Tbl_video_channel" VALUES('','全部');
 INSERT INTO "Tbl_video_channel" VALUES('1','电视剧');
 INSERT INTO "Tbl_video_channel" VALUES('2','电影');
 INSERT INTO "Tbl_video_channel" VALUES('3','综艺');
 INSERT INTO "Tbl_video_channel" VALUES('4','音乐');
 
 CREATE TABLE Tbl_video_type  --视频分类信息表
(
  type_id varchar(6) PRIMARY KEY,--分类ID
  type_name text--分类名称
 );
 INSERT INTO "Tbl_video_type" VALUES('','全部');
 INSERT INTO "Tbl_video_type" VALUES('1','战争');
 INSERT INTO "Tbl_video_type" VALUES('2','动作');
 INSERT INTO "Tbl_video_type" VALUES('3','文艺');
 INSERT INTO "Tbl_video_type" VALUES('4','武侠');
 INSERT INTO "Tbl_video_type" VALUES('5','古装');
 INSERT INTO "Tbl_video_type" VALUES('6','选秀');
 INSERT INTO "Tbl_video_type" VALUES('7','MV');
 
 CREATE TABLE Tbl_video_details
 (
    video_id numeric(6),--视频ID
    play_time text,
	play_count integer
  );
  INSERT INTO "Tbl_video_details" VALUES(1012,'2013-09-28',10);
  INSERT INTO "Tbl_video_details" VALUES(1012,'2013-09-28',14);
  INSERT INTO "Tbl_video_details" VALUES(1000,'2013-09-27',17);
  INSERT INTO "Tbl_video_details" VALUES(1000,'2013-09-28',13);
  INSERT INTO "Tbl_video_details" VALUES(1002,'2013-09-25',22);
  INSERT INTO "Tbl_video_details" VALUES(1002,'2013-09-25',19);
  INSERT INTO "Tbl_video_details" VALUES(1001,'2013-09-26',18);
  INSERT INTO "Tbl_video_details" VALUES(1001,'2013-09-28',17);
  INSERT INTO "Tbl_video_details" VALUES(1001,'2013-09-27',16);
  INSERT INTO "Tbl_video_details" VALUES(1003,'2013-09-28',14);
  INSERT INTO "Tbl_video_details" VALUES(1003,'2013-09-22',13);
  INSERT INTO "Tbl_video_details" VALUES(1004,'2013-09-27',15);
  INSERT INTO "Tbl_video_details" VALUES(1004,'2013-09-25',19);
  INSERT INTO "Tbl_video_details" VALUES(1005,'2013-09-27',16);
  INSERT INTO "Tbl_video_details" VALUES(1005,'2013-09-28',10);
  INSERT INTO "Tbl_video_details" VALUES(1006,'2013-09-26',21);
  INSERT INTO "Tbl_video_details" VALUES(1006,'2013-09-25',12);
  INSERT INTO "Tbl_video_details" VALUES(1007,'2013-09-28',13);
  INSERT INTO "Tbl_video_details" VALUES(1007,'2013-09-27',11);
  INSERT INTO "Tbl_video_details" VALUES(1008,'2013-09-25',12);
  INSERT INTO "Tbl_video_details" VALUES(1008,'2013-09-22',11);
  INSERT INTO "Tbl_video_details" VALUES(1008,'2013-09-28',13);
  INSERT INTO "Tbl_video_details" VALUES(1008,'2013-09-28',12);
  INSERT INTO "Tbl_video_details" VALUES(1009,'2013-09-22',17);
  INSERT INTO "Tbl_video_details" VALUES(1009,'2013-09-27',16);
  INSERT INTO "Tbl_video_details" VALUES(1018,'2013-09-27',15);
  INSERT INTO "Tbl_video_details" VALUES(1018,'2013-09-27',12);
  INSERT INTO "Tbl_video_details" VALUES(1018,'2013-09-27',13);
  INSERT INTO "Tbl_video_details" VALUES(1018,'2013-09-27',11);
  INSERT INTO "Tbl_video_details" VALUES(1015,'2013-09-28',11);
  INSERT INTO "Tbl_video_details" VALUES(1015,'2013-09-28',17);
  INSERT INTO "Tbl_video_details" VALUES(1015,'2013-09-28',18);
  INSERT INTO "Tbl_video_details" VALUES(1016,'2013-09-28',19);
  INSERT INTO "Tbl_video_details" VALUES(1016,'2013-09-28',16);
  INSERT INTO "Tbl_video_details" VALUES(1016,'2013-09-28',18);
  INSERT INTO "Tbl_video_details" VALUES(1013,'2013-09-01',17);
  INSERT INTO "Tbl_video_details" VALUES(1013,'2013-09-02',16);
  INSERT INTO "Tbl_video_details" VALUES(1013,'2013-09-24',15);
  INSERT INTO "Tbl_video_details" VALUES(1013,'2013-09-11',10);
  INSERT INTO "Tbl_video_details" VALUES(1013,'2013-09-23',12);
  INSERT INTO "Tbl_video_details" VALUES(1013,'2013-09-23',10);
  INSERT INTO "Tbl_video_details" VALUES(1022,'2013-09-29',21);
  INSERT INTO "Tbl_video_details" VALUES(1022,'2013-09-28',33);
  INSERT INTO "Tbl_video_details" VALUES(1011,'2013-09-23',22);
  INSERT INTO "Tbl_video_details" VALUES(1011,'2013-09-27',11);
  INSERT INTO "Tbl_video_details" VALUES(1011,'2013-09-29',23);
  INSERT INTO "Tbl_video_details" VALUES(1019,'2013-09-21',30);
  INSERT INTO "Tbl_video_details" VALUES(1010,'2013-09-22',21);
  INSERT INTO "Tbl_video_details" VALUES(1010,'2013-09-30',1);
  INSERT INTO "Tbl_video_details" VALUES(1024,'2013-09-28',23);
  INSERT INTO "Tbl_video_details" VALUES(1023,'2013-09-05',41);
  INSERT INTO "Tbl_video_details" VALUES(1024,'2013-09-22',21);
  INSERT INTO "Tbl_video_details" VALUES(1023,'2013-09-30',12);



 CREATE TABLE Tbl_video_menu  --视频统计字段
(
  menu_id varchar(6) PRIMARY KEY,--统计ID
  menu_name text	--统计名称
 );
 INSERT INTO "Tbl_video_menu" VALUES('','全部');
 INSERT INTO "Tbl_video_menu" VALUES('1001','今日播放最多');
 INSERT INTO "Tbl_video_menu" VALUES('1002','本周播放最多');
 INSERT INTO "Tbl_video_menu" VALUES('1003','本月播放最多');
COMMIT;
