#define S(n) Serial.print(n)
#define Sln(nn) Serial.println(nn)
#define enter() S("enter function\t");Sln(__FUNCTION__)
#define DH(n1)	digitalWrite(n1,HIGH)
#define DL(n2)	digitalWrite(n2,LOW)
#define LIGHTOFF(n3)	DH(n3)
#define LIGHTON(n4)		DL(n4)