void led_status(bool r, bool y, bool b) 
{
  digitalWrite(red_led, y);
  digitalWrite(yellow_led, r);
  digitalWrite(blue_led, b);
}
