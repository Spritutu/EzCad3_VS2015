#pragma once


#define WM_USER_VIEWPORTCHANGED  (WM_USER+1)        //视口改变
#define WM_USER_CREATEGUIDELINE  (WM_USER+2)        //建立辅助线 
#define WM_USER_UNITCHANGE       (WM_USER+3)        //系统单位被修改  



#define WM_USER_CHANGEENTITY    (WM_USER+6)         //对象被改变
#define WM_USER_CHANGECURLAYER  (WM_USER+7)         //当前层被修改  
#define WM_USER_INITENTLIST       (WM_USER+8)       //初始化对象列表

#define WM_USER_PICKCHANGE       (WM_USER+11)       //选择集改变
#define WM_USER_PICKLOCKCHANGE   (WM_USER+12)       //选择锁集改变

#define WM_USER_ENTMODIFY        (WM_USER+14)       //对象参数被修改

#define WM_USER_TEXT_CHANGE      (WM_USER+15)       //文本对象内容改变

#define WM_USER_NODECMD          (WM_USER+16)       //节点编辑命令

#define  WM_USER_USBLMC_REMOVE   (WM_USER+17) 
#define  WM_USER_USBLMC_ARRIVE   (WM_USER+18) 

#define WM_USER_CHANGELASER      (WM_USER+19)       //激光器被修改
#define WM_USER_MARKLAYERCHANGE  (WM_USER+20)       //当前标刻层被修改

#define WM_USER_SHOWPARTTIME     (WM_USER+21)      
#define WM_USER_SHOWTOTALTIME    (WM_USER+22)      
#define WM_USER_SHOWPARTCOUNT    (WM_USER+23)       
#define WM_USER_SHOWTOTALCOUNT   (WM_USER+24)      

#define WM_USER_EDITTEXT_CHANGE  (WM_USER+25)       //文本对象内容改变

#define WM_USER_SHOW3DCMD        (WM_USER+26)       
 
#define WM_USER_LASERPARAMCHANGED        (WM_USER+27)       

#define WM_USER_MOTORMOVE        (WM_USER+28)    
#define WM_USER_STATUSPANEL        (WM_USER+29)   
#define WM_USER_UPDATECAMERAFRAME        (WM_USER+30)   
#define WM_USER_CHANGEENTITY_1    (WM_USER+31)  
#define WM_USER_Red    (WM_USER+32)  