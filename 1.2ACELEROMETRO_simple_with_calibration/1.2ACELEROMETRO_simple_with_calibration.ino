#include "MPU9250.h"
#define WAIT_TIME 1
#define ARR_LINES 8500

MPU9250 mpu;

void print_accelX_accelY_accelZ(void);
void print_calibration(void);
float medidasAcc[ARR_LINES*3];
uint32_t tiempo;


void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    while(!mpu.setup(0x68)) {  // change to your own address
        
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        
    }

    // calibrate anytime you want to
    Serial.println("Accel Gyro calibration will start in 5sec.");
    Serial.println("Please leave the device still on the flat plane.");
    mpu.verbose(true);
    delay(5000);
    mpu.calibrateAccelGyro();



    //print calibration
    print_calibration();
    mpu.verbose(false);
}


void loop() {
    if (mpu.update()) {
      for (static int i = 0 ; i<(ARR_LINES*3 - 1) ; i++){
        if(i == 0) {
          Serial.println("Empiezan las medidas.");
          tiempo = millis();
          }

        medidasAcc[i]=mpu.getAccZ();
        i++;
        medidasAcc[i]=mpu.getAccY();
        i++;
        medidasAcc[i]=mpu.getAccX();
        delay(1);
        
        if(i == (ARR_LINES*3 - 1) ) {
          Serial.println("Han terminado las medidas.");
          Serial.print("El tiempo de medidas ha sido: ");
          Serial.println(millis() - tiempo);
        }


        }
      for(static int j = 0; j<(ARR_LINES*3 - 1); j++){
        Serial.print(medidasAcc[j]);
        Serial.print(" ");
        j++;
        Serial.print(medidasAcc[j]);
        Serial.print(" ");
        j++;
        Serial.print(medidasAcc[j]);
        Serial.println(";");
        }       
      }
    }







/*    Funcion que obtiene los valores del giroscopio a traves de los metodos del objeto.
              INPUT: void.
              OUTPUT: serial.
void print_roll_pitch_yaw() {
    Serial.print("Yaw, Pitch, Roll: ");
    Serial.print(mpu.getYaw(), 2);
    Serial.print(", ");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(", ");
    Serial.println(mpu.getRoll(), 2);
}
*/

// Funcion que obtiene los valores de los acelerometros a traves de metodos del objeto centra las medidas alrededor de 0 a traves de la calibracion.
void print_accelX_accelY_accelZ(void){
  Serial.print(mpu.getAccZ(),2);
  Serial.print(", ");
  Serial.print(mpu.getAccY(),2);
  Serial.print(", ");
  Serial.println(mpu.getAccX(),2);
}


void print_calibration() {

    //    Imprime los SESGOS del acelerometro.
    Serial.println("< calibration parameters >");
    Serial.println("accel bias [g]: ");
    Serial.print(mpu.getAccBiasX() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getAccBiasY() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getAccBiasZ() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.println();
    
    
    /*    Imprime los SESGOS del giroscopio
    Serial.println("gyro bias [deg/s]: ");
    Serial.print(mpu.getGyroBiasX() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getGyroBiasY() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getGyroBiasZ() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.println();
    */


    /*    Imprime los SESGOS del magnetometro
    Serial.println("mag bias [mG]: ");
    Serial.print(mpu.getMagBiasX());
    Serial.print(", ");
    Serial.print(mpu.getMagBiasY());
    Serial.print(", ");
    Serial.print(mpu.getMagBiasZ());
    Serial.println();
    Serial.println("mag scale []: ");
    Serial.print(mpu.getMagScaleX());
    Serial.print(", ");
    Serial.print(mpu.getMagScaleY());
    Serial.print(", ");
    Serial.print(mpu.getMagScaleZ());
    Serial.println();
    */
}
