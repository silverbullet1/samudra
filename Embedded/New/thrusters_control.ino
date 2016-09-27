void forward()
{
  t3.writeMicroseconds(1300);
  t4.writeMicroseconds(1700);
}

void backward()
{
  t3.writeMicroseconds(1700);
  t4.writeMicroseconds(1300);
}

void right()
{ 
  t3.writeMicroseconds(1300);
  t4.writeMicroseconds(1520);
}

void left()
{ 
  t3.writeMicroseconds(1400);
  t4.writeMicroseconds(1700);
}

void up()
{ 
  t1.writeMicroseconds(1300);
  t2.writeMicroseconds(1700);
  t5.writeMicroseconds(1300);
  t6.writeMicroseconds(1700);
}

void down()
{
  t1.writeMicroseconds(1700);
  t2.writeMicroseconds(1300);
  t5.writeMicroseconds(1700);
  t6.writeMicroseconds(1300);
}

