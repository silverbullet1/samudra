
PID_SAM::PID_SAM(double Kp, double Ki, double Kd, double Min, double Max)
{
  reset();
  PID_SAM::SetOutputLimits(Min, Max);
  PID_SAM::SetTunings(Kp, Ki, Kd);
}



double PID_SAM::Compute(double input, double zero, double Setpoint)
{

  unsigned long now = millis();
  SampleTime = (now - lastTime);

  /*Compute all the working error variables*/
  error = (Setpoint + zero) - input;
  SampleTimeInSec = ((double)SampleTime) / 1000;

  ITerm += (ki * error * SampleTimeInSec);
  dInput = (input - lastInput);

  /*Compute PID_SAM Output*/
  output = kp * error + ITerm - (kd * dInput) / SampleTimeInSec;

  if (output > outMax) output = outMax;
  else if (output < outMin) output = outMin;

  /*Remember some variables for next time*/
  lastInput = input;
  lastTime = now;
  return output;
}


double PID_SAM::ComputeFixedHz(double input, double zero, double sampletime, double Setpoint)
{
  unsigned long now = millis();
  unsigned long timeChange = (now - lastTime);
  if (timeChange >= sampletime)
  {
    /*Compute all the working error variables*/
    error = (Setpoint + zero) - input;
    SampleTimeInSec = ((double)sampletime) / 1000;

    ITerm += (ki * error * SampleTimeInSec);
    //dInput = (input - lastInput);

    /*Compute PID_SAM Output*/
    output = kp * error + ITerm/*- (kd * dInput)/SampleTimeInSec*/;

    if (output > outMax) output = outMax;
    else if (output < outMin) output = outMin;

    /*Remember some variables for next time*/
    lastInput = input;
    lastTime = now;
  }
  return output;
}



void PID_SAM::SetTunings(double Kp, double Ki, double Kd)
{
  kp = Kp;
  ki = Ki;
  kd = Kd;
}




void PID_SAM::SetOutputLimits(double Min, double Max)
{
  if (Min >= Max) return;
  outMin = Min;
  outMax = Max;
}


void PID_SAM::reset()
{
  ITerm = 0.00;
  lastInput = 0.00;
  output = 0.00;
  error = 0.00;
  SampleTimeInSec = 0.00;
  dInput = 0.00;
  lastTime = millis();
}

