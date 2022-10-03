/*--------------------------------------------------*/
/*-----------------RangeFinder ---------------------*/
/*--------------------------------------------------*/
void TaskRangeFind(void *pvParameters)  // This is a task.
{
(void) pvParameters;
for (;;)
  {
  myservo.write(posLeft);
  vTaskDelay(pdMS_TO_TICKS(550));
  intRangeLeft = sonar.ping_cm(); 
  intRangeLeft += sonar.ping_cm();
  intRangeLeft += sonar.ping_cm();
  intRangeLeft = intRangeLeft/3;

  vTaskDelay(pdMS_TO_TICKS(20));
  //Serial.print(F("Left range is : "));
  //Serial.println(intRangeLeft);
  
  myservo.write(posCenter);
  vTaskDelay(pdMS_TO_TICKS(550));
  intRangeCenter = sonar.ping_cm();
  intRangeCenter += sonar.ping_cm();
  intRangeCenter += sonar.ping_cm();
  intRangeCenter += sonar.ping_cm();
  intRangeCenter = intRangeCenter/3;

  vTaskDelay(pdMS_TO_TICKS(20));
  //Serial.print(F("Center range is : "));
  //Serial.println(intRangeCenter);
  
  myservo.write(posRight);
  vTaskDelay(pdMS_TO_TICKS(550));
  intRangeRight = sonar.ping_cm();
  intRangeRight += sonar.ping_cm();
  intRangeRight += sonar.ping_cm();
  intRangeRight = intRangeRight/3;

  vTaskDelay(pdMS_TO_TICKS(20));
  //Serial.print(F("Right range is : "));
  //Serial.println(intRangeRight);
  
  myservo.write(posCenter);
  vTaskDelay(pdMS_TO_TICKS(550));
  intRangeCenter = sonar.ping_cm();
  intRangeCenter += sonar.ping_cm();
  intRangeCenter += sonar.ping_cm();
  intRangeCenter += sonar.ping_cm();
  intRangeCenter = intRangeCenter/3;
 
  vTaskDelay(pdMS_TO_TICKS(10));
  //Serial.print(F("Center range is : "));
  //Serial.println(intRangeCenter);
  }
}
  /*
  if(intRangeLeft == 0)
    {
      intRangeLeft = 100;
    }
    */
