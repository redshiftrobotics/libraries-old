import com.qualcomm.hardware.bosch.BNO055IMU;

public interface SensorHAL {
    public abstract float GetSensorValue();
    public abstract float GetLastSensorValue();
}


public class IMULayer implements SensorHAL {

    private int IMURotations;
    private float lastSensorValue;

    IMULayer(BNO055IMU imu) {
        this.imu = imu;
    }

    @Override
    public float GetLastSensorValue(){
        return lastSensorValue;
    }

    @Override
    public float GetSensorValue(){
        if(lastSensorValue>270&&imu.getAngularOrientation().firstAngle<90){ //make sure if our current heading and our target are more than 180 appart we are fine
            IMURotations++;
        }else if(lastSensorValue<90&&imu.getAngularOrientation().firstAngle>270){
            IMURotations--;
        }
        lastSensorValue = imu.getAngularOrientation().firstAngle;
        return imu.getAngularOrientation().firstAngle + 360 * IMURotations;
    }

    private BNO055IMU imu;
}