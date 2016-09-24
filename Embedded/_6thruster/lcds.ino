void lcd_display(String arg)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  if (arg.length() > 16)
  {
    if(arg.length()>32)
    {
      lcd.print("ERROR PRINT");
      return;
    }
    lcd.print(arg.substring(0,16));
    lcd.setCursor(0, 1);
    lcd.print(arg.substring(16,abs(16-arg.length())));
  }
  else {
    lcd.print(arg);
  }
}
void lcd_backlight_enable(boolean arg){
  digitalWrite(LCD_BACKLIGHT,arg);
}
void lcd_status(bool file){
  String data="";
  data+="ahrs";
    data+=", ";
 (file==true?data+="FILE":data+="!!file");
  data+=" STATUS ";
  lcd_display(data);
  }

