void controller() {

  if (handshake == true && zero_ref == true)
  {
    if (pid_angle == true)
    {
      out_angle_x = PIDrol_angle.ComputeFixedHz(kalRoll, zero_angle_roll, 20);
      out_angle_y = PIDpitch_angle.ComputeFixedHz(kalPitch, zero_angle_pitch, 20);
      //out_angle_z = PIDyaw_angle.ComputeFixedHz(kalYaw, zero_angle_yaw, 20);
      out_angle_z = PIDyaw_angle.ComputeFixedHz(yawError, 0, 20);

    }

    if (pid_rate_angle == false)

    {
      out_rate_x = PIDrol_rate.Compute(gyroRoll, zero_rate_roll);
      out_rate_y = PIDpitch_rate.Compute(gyroPitch, zero_rate_pitch);
      out_rate_z = PIDyaw_rate.Compute(gyroYaw, zero_rate_yaw);
    }
    else if (pid_angle == true)
    {
      out_rate_x = PIDrol_rate.Compute(gyroRoll, zero_rate_roll, out_angle_x);
      out_rate_y = PIDpitch_rate.Compute(gyroPitch, zero_rate_pitch, out_angle_y);
      out_rate_z = PIDyaw_rate.Compute(gyroYaw, zero_rate_yaw, out_angle_z);
    }

    if (pid_alt == true)
    {
      out_alt = PIDalt.Compute(altError, 0, 0);
      b_speed = constrain(threshold + int(out_alt), 0, 200);
    }
sfl.writeMicroseconds(signal1);
 cl_pwm= constrain(int(out_rate_z), MIN, MAX_FDIR);
 cr_pwm= constrain(int(out_rate_z), MIN, MAX_RDIR);
    scl.writeMicroseconds(cl_pwm);
    scr.writeMicroseconds(cr_pwm );
fl_pwm = constrain(int(out_rate_x) - int(out_rate_y), MIN, MAX_FDIR);
fr_pwm = constrain(int(out_rate_x) - int(out_rate_y), MIN, MAX_RDIR);
    sfl.writeMicroseconds(fl_pwm);
    sfr.writeMicroseconds(fr_pwm);
 bl_pwm = constrain(int(out_rate_x) + int(out_rate_y), MIN, MAX_FDIR);
 br_pwm = constrain(int(out_rate_x) + int(out_rate_y), MIN, MAX_RDIR);
    sbl.writeMicroseconds(bl_pwm);
    sbr.writeMicroseconds(br_pwm);

  }
}



void setAttitudeAndRate()
{
  if (millis() - timer_sp > 4000 && !(millis() - timer_sp > 7000))
  {
    //all these equation are averaging equation ,i,e, it averages output from sensors in the time frame from 4sec to 7 sec from the start
    //of arduino
    //after this time frame function is not executed
    zero_angle_roll = compAngleSet * zero_angle_roll + (1 - compAngleSet) * kalRoll;
    zero_angle_pitch = compAngleSet * zero_angle_pitch + (1 - compAngleSet) * kalPitch;
    zero_angle_yaw = compAngleSet * zero_angle_yaw + (1 - compAngleSet) * kalYaw;

    zero_rate_roll = compRateSet * zero_rate_roll + (1 - compRateSet) * gyroRoll;
    zero_rate_pitch = compRateSet * zero_rate_pitch + (1 - compRateSet) * gyroPitch;
    zero_rate_yaw = compRateSet * zero_rate_yaw + (1 - compRateSet) * gyroYaw;


  }

  else if (millis() - timer_sp > 7000)
  {
    zero_ref = true;
    led_status(LOW, HIGH, LOW);

    //hanshake is done after 7seconds ,i,e, after setpoint are calculated
    //during setpoint time frame no motor is driven or started
    //syn_abc(); function is used for handshaking
    //to disable the handhake procedure just change the global variable HANDSHAKE
    //DON"T COMMENT OUT THIS FUNCTION(syn_sbc())
    syn_sbc();

    //it activiates the PID functions
    //it is used here as before 7sec, motors are not being driven and handshake is in while loop until handhskaee procesdure gets finishe

    //time taked in handshaking depends upon response from gui
    //arduino is ready for hanshaking after it has calculated setpoints
    PIDrol_rate.reset();
    PIDpitch_rate.reset();
    PIDyaw_rate.reset();

    PIDrol_angle.reset();
    PIDpitch_angle.reset();
    PIDyaw_angle.reset();
  }
}

