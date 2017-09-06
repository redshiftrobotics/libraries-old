package org.firstinspires.ftc.teamcode;

import com.qualcomm.hardware.bosch.BNO055IMU;
import com.qualcomm.robotcore.hardware.DcMotor;

public class PIDController {
    private float error, lastError;
    private float target;

    private long time, lastTime, deltaTime;

    private float P, I, D;
    private float kP, kI, kD; //these are the tuning constants, tune PID turning with them

    private SensorHAL inputSensor;

    PIDController(SensorHAL sensor){
        inputSensor = sensor;
    }

    public void SetTuning(float p, float i, float d){
        kP = p;
        kI = i;
        kD = d;
    }

    public float GetPIDOutput(){
        lastError = inputSensor.GetLastSensorValue() - target;
        error = inputSensor.GetSensorValue() - target;
    
        lastTime = time;
        time = System.currentTimeMillis();
        deltaTime = time - lastTime;
        P = error;
        I += error * deltaTime;
        D = (error - lastError) / deltaTime;

        return P * kP + I * kI + D * kD;
    }
}