bool decimal = false;
int input,j=0,k=0;
int buff[5];
int A[2];

void setup()
{
    Serial.begin(9600);
}
void calc()
{
    int num=0,x=0;
    for(int x=2;x<k;x++) //skip the first bracket and extra symbol in the beginning of $(x,y) or #(x,y)
    {
    if(buff[x]=='.')
      decimal = true;
    if(buff[x]==',')
    {
      A[0] = num;
      decimal = false; //for the 2nd number
    }
    if(buff[x]==')')
    {
      A[1] = num;
      decimal = false;
    }
     if(!decimal)
          num=num+(buff[x]-48)*pow(10,j-x);
     else
          num=num+(buff[x]-48)*pow(10,x-j);
    }
}
 
double calculateAngle()
{
    double angle = 0.0;
    for(int x=2;x<k;x++)
    {
      if(buff[x]=='.')
      decimal = true;
    if(!decimal)
          angle=angle+(buff[x]-48)*pow(10,j-x);
     else
          angle=angle+(buff[x]-48)*pow(10,x-j);
      return angle;
      }
}
    
void loop()
{   
    k = 0,j = 0;
    if(Serial.available()>0)
    {
        input=Serial.read();
        //Serial.print("\n");
        //Serial.print(input);
        k++; 
        if(input=='\n') //one value has been found
        {
           switch(buff[0])
           {
             case '$' : calc();
             Serial.print(A[0]);
             Serial.print(" ");
             Serial.print(A[1]);
             Serial.print("\n");
             break;
             
             case '#' : calc();
             Serial.print(A[0]);
             Serial.print(" ");
             Serial.print(A[1]);
             Serial.print("\n");
             break;
             
             case 'A' : Serial.print(calculateAngle());
             Serial.print("\n");
             break;
           
           }
        }
        else
        {
            buff[j++]=input;
        }
    }
}
