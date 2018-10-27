#pragma once

#define SOFT_VERSION 3

#ifdef EZCAD3_WELD_LMC1
#define INTERFACE_VERSION 2001
#else
#define INTERFACE_VERSION 1001
#endif

#define BUILD_VERSION 1296 //20180905  增加对象更改后自动投影；修改螺旋线外轮廓的bug；修改海康相机的曝光强度
//#define BUILD_VERSION 1295 //20180904  增加关闭相机按钮
//#define BUILD_VERSION 1294 //20180903  增加6轴功能，修改读slc的bug
//#define BUILD_VERSION 1293 //20180821  增加9030驱动
//#define BUILD_VERSION 1292 //20180821  修改螺旋线多直线的问题；修改飞行系数为um；
//#define BUILD_VERSION 1291 //20180816  支持设置最大z为z坐标
//#define BUILD_VERSION 1290 //20180815  支持新的slc格式，修改模拟飞行的打标方向；修改条码镜像时飞行方向的问题
//#define BUILD_VERSION 1289 //20180808  开发库增加暂停命令;增加usb监控
//#define BUILD_VERSION 1288 //20180807  增加分割Y向优先
//#define BUILD_VERSION 1287 //20180806  增加条码显示校验码功能；修改文件后提示保存
//#define BUILD_VERSION 1286 //20180803  修改极小图形的填充问题;修改更改笔参数未提示保存文件的问题
//#define BUILD_VERSION 1285 //20180801  修改脱机的激光器开启bug
//#define BUILD_VERSION 1284 //20180731  修改大数据填充bug，修改读dxf的block的问题
//#define BUILD_VERSION 1283 //20180726  增加焊接卡扩展端口功能
//#define BUILD_VERSION 1282 //20180726  修改群组和组合可以自动统一z坐标,增加隐藏笔列表功能
//#define BUILD_VERSION 1281 //20180725  修改红光指示可以修改扩展轴速度
//#define BUILD_VERSION 1280 //20180724  修改系统工具条放在垂直位置
//#define BUILD_VERSION 1279 //20180724  修改使能限位信号的问题
//#define BUILD_VERSION 1278 //20180723  修改背景填充死机的bug
//#define BUILD_VERSION 1277 //20180720  增加多层加工可以一直等待输入信号
//#define BUILD_VERSION 1276 //20180719  增加4轴限位处理 
//#define BUILD_VERSION 1275 //20180719  增加多层加工开始结束延时，修改字体数为0预览错误
//#define BUILD_VERSION 1274 //20180718  增加字体预览
//#define BUILD_VERSION 1273 //20180711  增加曲面精度
//#define BUILD_VERSION 1272 //20180710  填充计算增加多线程并行计算
//#define BUILD_VERSION 1271 //20180709  增加用户可选计算线程数   
//#define BUILD_VERSION 1270 //20180704  加快投影速度，增加双向包裹，修改单向包裹
//#define BUILD_VERSION 1269 //20180703  增加YLPN的状态检测
//#define BUILD_VERSION 1268 //20180702  增加曲线旋转可以选择曲面跟随旋转
//#define BUILD_VERSION 1267 //20180629  内核修改
//#define BUILD_VERSION 1266 //20180628  修改背景文件格式为bmp
//#define BUILD_VERSION 1265 //20180626  1.动态文本增加到极限值用户选择是否继续；2.增加激光器待机功率
//#define BUILD_VERSION 1264 //20180625  优化读取STL二进制文件速度;
//#define BUILD_VERSION 1263 //20180625  为大文件存储修改存储格式和提升存储速度;
//#define BUILD_VERSION 1262 //20180621  修改包裹以对象中心为基点
//#define BUILD_VERSION 1261 //20180621  增加软件一键打包错误文件功能
//#define BUILD_VERSION 1260 //20180619  修改软件默认启动时输出口状态
//#define BUILD_VERSION 1259 //20180617  增加分割禁止分割文本，修改9030的回零，修改网络文件存储速度
//#define BUILD_VERSION 1258 //20180616  改分割排序反向和预览
//#define BUILD_VERSION 1257 //20180614  修改材料助手放大移动错误
//#define BUILD_VERSION 1256 //20180611  增加设置相机参数
//#define BUILD_VERSION 1255 //20180608  修改分割标刻bug
//#define BUILD_VERSION 1254 //20180606  增加圆柱包裹是否使能
//#define BUILD_VERSION 1253 //20180601  修改Ez3文件格式版本
//#define BUILD_VERSION 1252 //20180530  增加MicroPDF417条码
//#define BUILD_VERSION 1251 //20180529  修改填充自动旋转参数的功能
//#define BUILD_VERSION 1250 //20180528  增加系统单位mm变成inch的一些bug
//#define BUILD_VERSION 1249 //20180524  增加YAG的激光器类型
//#define BUILD_VERSION 1248 //20180522  修改底层bug
//#define BUILD_VERSION 1247 //20180521  增加多图层加工次数
//#define BUILD_VERSION 1247 //20180519  修改jsf字体读取的尺寸限制
//#define BUILD_VERSION 1246 //20180515  增加读MatJob文件的功能
//#define BUILD_VERSION 1245 //20180514  修改禁止投影对象排序
//#define BUILD_VERSION 1244 //20180511  修改gerber文件矩形路径
//#define BUILD_VERSION 1243 //20180505  增加图层可以禁止A轴加工
//#define BUILD_VERSION 1242 //20180504  增加圆指令
//#define BUILD_VERSION 1241  //20180502  增加初始化如果有多卡则让用户选择 2.增加位图修改真实DPI功能 3.支持位图飞行
//#define BUILD_VERSION 1240  //20180427  增加按辅助线盒自由分割
//#define BUILD_VERSION 1239  //20180426   1.材料助手增加红光指示 2.SDK增加标刻标准九点的功能
//#define BUILD_VERSION 1238  //20180424   1.修改XY分割模式可以组合
//#define BUILD_VERSION 1237  //20180423   1.修改扩展轴文本加工输出到指定文件，检查是否加工的异常 2.更改单位时动态聚集校正文件有bug 3.修改svg的bug
//#define BUILD_VERSION 1236  //20180419   1.修改扩展轴运动bug
//#define BUILD_VERSION 1235  //20180417   1.增加扩展轴自由移动模式
//#define BUILD_VERSION 1234  //20180416   1.修改DM码ASCII编码模式 2.增加文本检查是否已经加工
//#define BUILD_VERSION 1233  //20180410   增加DLC自带扩展轴功能
//#define BUILD_VERSION 1232  //20180409   修改曲线段插补时间小于10us时延时
//#define BUILD_VERSION 1231  //20180404   修改螺旋形加工时的离散精度 
//#define BUILD_VERSION 1230  //20180402  1.修改位图dpi限制 2.增加一些开发函数
//#define BUILD_VERSION 1229  //20180328  修改文本动态文本阵列距离的显示
//#define BUILD_VERSION 1228  //20180327  1.增加排序按钮 2.增加智能加工参数功能
//#define BUILD_VERSION 1227  //20180326  1.修改防止标刻面板显示不完整
//#define BUILD_VERSION 1226  //20180325  1.自动去除水平工具条之间的空间 2.增加排序
//#define BUILD_VERSION 1225  //20180322  1.修改Skywrite 2.增加激光冷却启动延时
//#define BUILD_VERSION 1224  //20180319  1.修改SPI的IO显示文本问题 2.Skywrite不加工问题
//#define BUILD_VERSION 1223  //20180312  1.修改读PNG文件 2.增加自动处理振镜加减速
//#define BUILD_VERSION 1222  //20180309  开发库增加基础标刻函数
//#define BUILD_VERSION 1221  //20180308 1.修改GS1-128条码编码，2增加DLC校正
//#define BUILD_VERSION 1220  //20180306 1.修改DM的矩形模式的编码,2增加按键盘o建自动居中
//#define BUILD_VERSION 1219  //20180305 1.修改输出口显示问题
//#define BUILD_VERSION 1218  //20180227 1.增加支持SL2-100 2.增加鼠标滚轮缩放反转
//#define BUILD_VERSION 1217  //20180223 修改改变系统单位时扩展轴参数未改的问题
//#define BUILD_VERSION 1216  //20180206 1.增加多卡所有曲线可以同步.2 PDF条码使能~,修改PDF内存泄漏
//#define BUILD_VERSION 1215  //20180205 1参数激光器类型选择YAG，使能电流输出软件卡死.2.旋转体Y方向包裹，包裹内容没有贴在旋转体表面 3.用户管理器中用户登入密码错误。4.修改软件打开红光输出口有效时关闭红光输出口
//#define BUILD_VERSION 1214  //20180202增加模拟首脉冲抑制功能
//#define BUILD_VERSION 1213  //20180131修改读svg问题
//#define BUILD_VERSION 1212  //20180129增加支持频率1M
//#define BUILD_VERSION 1211  //20180119增加自动检测跳转参数功能
//#define BUILD_VERSION 1210  //20180118修改笔盒工具栏按回车后消失的问题
//#define BUILD_VERSION 1209  //20180116修改一些小bug
//#define BUILD_VERSION 1208  //20180110修改Gerber文件变成单线模式
//#define BUILD_VERSION 1207  //20180108增加A轴循环加工模式
//#define BUILD_VERSION 1206  //20180103增加打开文件刷新激光参数,2修改不标刻低灰度位图错误,3plt读入错误
//#define BUILD_VERSION 1205  //20171228修改旋转体绕X轴加工的问题
//#define BUILD_VERSION 1204  //20171227修改位图不标刻低灰度点的问题
//#define BUILD_VERSION 1203  //20171226修改填充对象保存问题
//#define BUILD_VERSION 1202  //图层增加为8个图像标记点
//#define BUILD_VERSION 1201  //1.修改不能保存错误 2.DM码X12编码问题
//#define BUILD_VERSION 1200  //所有功能移动到Ezcad3Kernel内
//#define BUILD_VERSION 1142  //修改读dxf文件插入变换问题
//#define BUILD_VERSION 1141  //修改读Gerber文件圆弧问题
//#define BUILD_VERSION 1140  //修改双轴飞行
//#define BUILD_VERSION 1139  //修改手轮程序
//#define BUILD_VERSION 1138  //修改投影时去除多余未相交线段的错误
//#define BUILD_VERSION 1137  //添加手轮
//#define BUILD_VERSION 1136  //修改条码对象会默认设置为笔号0的问题
//#define BUILD_VERSION 1135  //去除显示填充对话框进程
//#define BUILD_VERSION 1134  //1.分割功能增加以分割盒为中心，2.增加轴移动到起始点 3.增加可以隐藏原点功能
//#define BUILD_VERSION 1133  //修改底层延时计算越界问题
//#define BUILD_VERSION 1132  //支持3d加工z偏移，增加扩展轴反向间隙
//#define BUILD_VERSION 1131  //支持Sky writing,增加可以禁止PRR同步
//#define BUILD_VERSION 1130  //增加SPI状态显示
//#define BUILD_VERSION 1129  //增加双编码器飞行
//#define BUILD_VERSION 1128  //修改重复填充问题
//#define BUILD_VERSION 1127  //支持新卡的输入口控制
//#define BUILD_VERSION 1126  //激光开始延时只在起始段有效
//#define BUILD_VERSION 1125  //增加渲染线显示模式，增加捕捉曲面顶点,加了工作空间背景
//#define BUILD_VERSION 1124  //修改扩展轴红光预览，增加隐藏绘制命令
//#define BUILD_VERSION 1123  //支持地球仪标刻
//#define BUILD_VERSION 1122  //支持波斯文
//#define BUILD_VERSION 1121  //修改IPG_E激光器脉冲宽度设置
//#define BUILD_VERSION 1120  //修改扩展轴A的组合
//#define BUILD_VERSION 1119  //修改如果找不到校正文件，则自动改成在CORFILE目录下找
//#define BUILD_VERSION 1118  //修改可以中断轴运动
//#define BUILD_VERSION 1117  //修复仿宋_GB2312
//#define BUILD_VERSION 1116  //修改软件启动关闭指定程序
//#define BUILD_VERSION 1115  //重新增加普通包裹功能
//#define BUILD_VERSION 1114  //修改填充多打几次的错误
//#define BUILD_VERSION 1113  //增加分层加工的延迟暂停
//#define BUILD_VERSION 1112  //增加Io稳定时间
//#define BUILD_VERSION 1111  //配合dsp=0x0146的位图缓冲区限制
//#define BUILD_VERSION 1110  //1.修改文本宽度处理。2.修改背景logo裁剪刷新
//#define BUILD_VERSION 1109  //1.红光预览跳过隐藏对象。2。使能按分割线分割之后，Z轴总会是运动到零点打标。3）变量文本打标顺序错误
//#define BUILD_VERSION 1108  //1.修改光纤激光器的连续加工模式MO开启2.内部验证dll
//#define BUILD_VERSION 1107  //修改语言文件
//#define BUILD_VERSION 1106  //增加背景logo功能
//#define BUILD_VERSION 1105  //修改掉卡提示
//#define BUILD_VERSION 1104  //增加扩展轴解决方案ZA，XZA，XA，YA，修改用户可以设置焦点位置，修改扩展轴加工的连续模式无效
//#define BUILD_VERSION 1103  //1.修改QRCode的一个编码问题，2.修改读入空3d文件的错误
//#define BUILD_VERSION 1102  //修改加密库269错误,2读dxf的3d曲线问题
//#define BUILD_VERSION 1101  //禁止双列表和修改单列表bug,去除普通包裹功能 
//#define BUILD_VERSION 1100  //1.修改menu的自动显示最近命令的功能,2.扩展轴联动
//#define BUILD_VERSION 1099  //1.增加转镜功能,2.QCW当选择连续模式去除脉宽50%的限制
//#define BUILD_VERSION 1098  //增加文件锁定客户id功能
//#define BUILD_VERSION 1097  //修改底层脱机模式
//#define BUILD_VERSION 1096  //修改背景相机显示裁剪问题
//#define BUILD_VERSION 1095  //1.修改YAG模式保存脉冲宽度参数；2.界面增加可设置模拟飞行速度
//#define BUILD_VERSION 1094  //修改DataMatrix条码C40编码的结束字符问题
//#define BUILD_VERSION 1093  //增加旋转体包裹
//#define BUILD_VERSION 1092  //增加索引和CCD对象
