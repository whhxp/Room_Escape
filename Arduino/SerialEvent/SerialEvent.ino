/*串口接收数据最大长度*/
#define _SER_RECBUFSIZE 512
char serial_recive[_SER_RECBUFSIZE] ="";	/*串口数据接收字符串*/


/*
	读取串口输入(单个字节延迟2ms)
*/
int Serial_Read(char* result)
{
	int single = 0;
	while(Serial.available() > 0)
	{
		single = Serial.read();
		delay(2);
		if(single == '\n')
		{
			*(result++) = '\0';
			Serial.flush();
			return 0;
		}
		if(single != '\r')
			*(result++) = single;
	}
}

/*
	清空串口接收缓冲区
*/
void Serial_BuffClear()
{
    for(int i = 0 ; i < _SER_RECBUFSIZE ;i++)
    {
        serial_recive[i] = 0x00 ;
    }
}


void setup()
{
  Serial.begin(9600);
}
void loop()
{
  while(Serial_Read(serial_recive) == 0)
  {
    if(strlen(serial_recive) > 0)
    {
      Serial.println(serial_recive);
      Serial_BuffClear();
    }
  }
}
