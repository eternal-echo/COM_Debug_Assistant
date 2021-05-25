# COM_Debug_Assistant
串口调试助手
(MFC串口助手实现)

# MFC实现串口助手

学MFC，做了这个作业，写个学习笔记加深下印象，初学者，写的可能漏洞百出，很多地方没有完善，望谅解。

## 添加控件，修改控件ID

控件界面如下。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210514170931545.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)

其中mscomm控件虚右键对话框点击插入ActiveX控件。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210514192647769.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)
找到串行通讯控件
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210514192751953.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)

 1. 接收区、发送区、周期、Edit Ctrl属性设置，只可读，接收回车，如下
发送区需要滚动条
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210514202014972.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)

多行输入模式打开，接收回车
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210514200118102.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)
多行输入也要打开，设为只读模式。![在这里插入图片描述](https://img-blog.csdnimg.cn/20210514200237462.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)

 2. 成员变量如下
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210514171318944.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)



 3. 修改ComboBox的属性中的Data，设置下拉栏内容
**波特率**
9600;14400;19200;38400;56000;57600;115200;
**校验位**
无;奇;偶;
**数据位**
5;6;7;8
**停止位**
1;1.5;2;
 4. 单击打开串口按钮，进入单击事件写如下程序
```javascript
// 打开串口按钮单击事件函数
void CCOM_myDlg::OnBnClickedButtonSwitch()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_ConCom.get_PortOpen())//已打开串口 
	{
		m_ConCom.put_PortOpen(FALSE);//关闭串口
		m_CButton_Switch.SetWindowText("打开串口");
	}
	else//未打开串口
	{
		//获取端口号
		CString strPortID;
		m_ComboPortID.GetWindowText(strPortID);
		int nID=atol(strPortID.TrimLeft("COM"));//删减COM得端口号，str转换为int
		//获取波特率
		CString strBaudRate;
		m_ComboBaudRate.GetWindowText(strBaudRate);
		//获取校验位 无；奇；偶
		CString strParityBit;
		m_ComboParityBit.GetWindowTextA(strParityBit);
		if (strParityBit == "无")
			strParityBit = "n";
		else if (strParityBit == "奇")
			strParityBit = "o";
		else//偶
			strParityBit = "e";
		//获取数据位
		CString strDataBit;
		m_ComboDataBit.GetWindowText(strDataBit);
		//获取停止位
		CString strStopBit;
		m_ComboStopBit.GetWindowText(strStopBit);
		//配置参数
		CString strSetting= strBaudRate+","+ strParityBit + "," + strDataBit+","+ strStopBit;

		m_ConCom.put_CommPort(nID);//选择端口
		m_ConCom.put_Settings(strSetting);//设置
		m_ConCom.put_PortOpen(TRUE);//打开端口

		m_ConCom.put_InputMode(1);//输入方式为二进制
		m_ConCom.put_RThreshold(1);
		m_ConCom.put_InputLen(0);//设置当前接收区为零，重置接收区
		m_ConCom.get_Input();//读取缓存区，覆盖缓存区残留数据 发送区
		
		//打开串口结束，将控件修改为关闭串口，下次点击可关闭
		m_CButton_Switch.SetWindowText("关闭串口");

	}
}

```
 5. 进入 **BOOL CCOM_myDlg::OnInitDialog()** 初始化串口配置参数的ComboBOX控件；
 ```javascript
// 打开串口按钮单击事件函数

	// TODO: 在此添加额外的初始化代码
	//设置下拉栏默认选择
	m_ComboBaudRate.SetCurSel(0);
	m_ComboDataBit.SetCurSel(3);
	m_ComboParityBit.SetCurSel(2);
	m_ComboStopBit.SetCurSel(0);
	//获取串口列表 设置下拉串口
	const int COM_NUM = 15;//最大串口数
	int i = 1;
	for (i = 1; i <= COM_NUM; i++)//循环COM_NUM次，串口数最多的情况
	{
		//形成原始设备名称
		CString sPort;
		sPort.Format(_T("\\\\.\\COM%d"), i);
		//尝试打开该端口
		BOOL bSuccess = FALSE;
		HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		if (hPort == INVALID_HANDLE_VALUE)
		{
			DWORD dwError = GetLastError();

			if (dwError == ERROR_ACCESS_DENIED)
			{
				bSuccess = TRUE;
			}
		}
		else
		{
			//该端口已成功打开
			bSuccess = TRUE;
			//添加串口号
			CString strPortID;
			strPortID.Empty();
			strPortID.AppendFormat("COM%d", i);
			m_ComboPortID.AddString(strPortID);
			//不要忘记关闭端口，因为我们不会对它做任何事情
			CloseHandle(hPort);
		}
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

 ```
 需要注意自定义的初始化函数只能按照框架要求写在指定初始化代码的添加区域	
 ```
// TODO: 在此添加额外的初始化代码
 ```
如果随意添加在前面则会因对话框程序基本框架的初始化未完成而报错。


 6. 添加mscomm控件的消息处理函数
![类向导中加入消息处理函数](https://img-blog.csdnimg.cn/20210514192946374.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)
编写串行通讯的消息处理函数
 ```javascript
void CCOMDlg::OnCommMscomm1()//单击发送按钮后发送发送区的内容触发该消息响应函数
//读取缓存区并发送到接收区
{
	// TODO: 在此处添加消息处理程序代码
	COleSafeArray safeArray_inp;
	//串口控件可识别的数组
	BYTE rxdata[2048];
	//char数组存储
	CString strtemp;
	//string 类

	if (m_comCOM.get_CommEvent()==2)//若接收缓存区有字符（单击发送按钮后）
	{
		safeArray_inp = m_comCOM.get_Input();//用串口控件用的数组读取串口控件缓存区
		int len = safeArray_inp.GetOneDimSize();//得有效数据长度
		for (long k=0;k<len;k++)
			//循环遍历串口控件的数组一个一个元素的转
		{
			safeArray_inp.GetElement(&k, rxdata + k);//转换为BYTE型数组
		}
		rxdata[len] = '\0';//数组最后一位置零
		strtemp.Format("%s", rxdata);//char数组转换为Cstring
		m_strReceive += strtemp;//添加到接收区
		UpdateData(FALSE);
	}
}
 ```
发送按钮的消息处理函数也不能忘
```javascript
void CCOM_myDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSwitch;
	m_CButton_Switch.GetWindowText(strSwitch);
	if (strSwitch == "关闭串口")
	{
		UpdateData(TRUE);//接收
		m_ConCom.put_Output(COleVariant(m_strSend));//发送区内容发送到mscomm控件
	}
	else
		AfxMessageBox("请先打开串口！");
}

```


 7. 简单测试下函数是否正确
通过vspd虚拟两个串口，也可以使用单片机直接进行通讯
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210514201103795.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)
打开两个串口通信软件，这里我选择打开一个野火串口调试助手，一个运行的对话框。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210514201203358.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/20210514201235561.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)
经过测试没有问题，继续扩展功能。



 8. 添加清空接收区功能。
```javascript
void CCOM_myDlg::OnBnClickedButtonClearReceiveArea()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空接收区
	m_StrReceive.Empty();
	UpdateData(FALSE);//刷新界面

}
```
 9.**实现自动发送，自动换行功能**
 将上述的发送按钮的鼠标单击事件处理函数稍做更改，为自动发送的Check—Box添加变量m_BAutoSend ，当自动发送已被勾选时进入定时器，未被勾选则正常发送。
```javascript
void CCOM_myDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSwitch;
	m_CButton_Switch.GetWindowText(strSwitch);
	UpdateData(TRUE);
	if (strSwitch == "关闭串口")
	{
		if (m_BAutoSend == 1)
		{
			SetTimer(TIMER_AUTO_SEND,m_nPeriod,NULL);//隔m_nPeriod ms发送一次数据
		}
		else
		{
			UpdateData(TRUE);//接收
			if(m_BNewLine==1)//自动换行
				m_strSend += "\n";
			m_ConCom.put_Output(COleVariant(m_strSend));//发送区内容发送到mscomm控件
		}
	}
	else
		AfxMessageBox("请先打开串口！");
}
```
定时器函数如下，将发送按钮的两行代码复制过来即可，定时器的宏定义如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210522154222876.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)

自动换行的功能也一并实现，原理就是每次发送的字符串后面加个回车，较为简单，不过多赘述。
```javascript
void CCOM_myDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case TIMER_AUTO_SEND:
		UpdateData(TRUE);//接收
		if (m_BNewLine == 1)//自动换行
			m_strSend += "\n";
		m_ConCom.put_Output(COleVariant(m_strSend));//发送区内容发送到mscomm控件

		break;

	CDialogEx::OnTimer(nIDEvent);

}
```
取消勾选自动发送后，关闭定时器。
若勾选自动发送后，在发送按钮中进行检测，有勾选再开始自动发送。
```javascript
void CCOM_myDlg::OnBnClickedCheckAutoSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//获取勾选状态
	if (m_BAutoSend==0)
	{
		KillTimer(TIMER_AUTO_SEND);
	}
	else
	{
	}
}
```
 10.**实现定时扫描串口功能**
 原本的串口扫描在初始化中完成，只能执行一次，后续拔出或添加串口不能改变，只能关闭程序再打开，略显繁琐。
 现可用定时器进行循环扫描更新串口下拉列表，将之前的初始化代码转移到定时器事件中，稍作修改即可。
```javascript
 // CCOM_myDlg 消息处理程序

BOOL CCOM_myDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//设置下拉栏默认选择
	m_ComboBaudRate.SetCurSel(0);
	m_ComboDataBit.SetCurSel(3);
	m_ComboParityBit.SetCurSel(2);
	m_ComboStopBit.SetCurSel(0);
	//获取串口列表 设置下拉串口
	SetTimer(TIMER_COM_CHECK, 1000, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
```
基本原理是通过打开串口操作获取串口信息，可打开且下拉列表未添加，则添加该串口。不可打开而下拉列表已添加，则删除该串口。

```javascript
void CCOM_myDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case TIMER_AUTO_SEND:
		UpdateData(TRUE);//接收
		if (m_BNewLine == 1)//自动换行
			m_strSend += "\n";
		m_ConCom.put_Output(COleVariant(m_strSend));//发送区内容发送到mscomm控件

		break;
	case TIMER_COM_CHECK:
		const int COM_NUM = 15;//最大串口数
		int i = 1;
		for (i = 1; i <= COM_NUM; i++)//循环COM_NUM次，串口数最多的情况
		{
			//形成原始设备名称
			CString sPort;
			sPort.Format(_T("\\\\.\\COM%d"), i);
			//尝试打开该端口
			BOOL bSuccess = FALSE;
			HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

			//添加串口号
			CString strPortID;
			strPortID.Empty();
			strPortID.AppendFormat("COM%d", i);

			if (hPort == INVALID_HANDLE_VALUE)
				//串口打开失败
			{
				DWORD dwError = GetLastError();

				if (dwError == ERROR_ACCESS_DENIED)
				{
					bSuccess = TRUE;
				}
				int nDelIndex = m_ComboPortID.FindStringExact(-1, strPortID);
				if(nDelIndex!= CB_ERR)//串口存在列表中，则删除串口
					m_ComboPortID.DeleteString(nDelIndex);
			}
			else
			{
				//该端口已成功打开
				bSuccess = TRUE;
				//不要忘记关闭端口，因为我们不会对它做任何事情
				CloseHandle(hPort);
				if (m_ComboPortID.FindStringExact(-1, strPortID)== CB_ERR)//若串口不存在，则添加串口
					m_ComboPortID.AddString(strPortID);
			}
		}
		break;

	}
	CDialogEx::OnTimer(nIDEvent);

}
```
经过测试，串口可实时更新。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210522155354292.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)![添加5 6 串口](https://img-blog.csdnimg.cn/20210522155404453.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210522155424434.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)



参考资料：
  [1]:https://blog.csdn.net/weixin_44533976/article/details/103995759
  [2]:https://blog.csdn.net/cmp15845953187/article/details/46523231
  [3]: https://baike.baidu.com/item/mscomm/3252525?fr=aladdin
  [4]: https://blog.csdn.net/mingtian715/article/details/80266855
  [5]:https://blog.csdn.net/no_zhushenghui/article/details/81299010
