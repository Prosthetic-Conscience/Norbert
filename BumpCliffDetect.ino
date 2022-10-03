/*--------------------------------------------------*/
/*------------------BumpDeteector-------------------*/
/*--------------------------------------------------*/
void TaskBumpCLiffDetect(void *pvParameters)  // This is a task.
{
(void) pvParameters;
bool cliffTriggered = false;
int loopIterations = 0;
for (;;)
  {
  _Bump_L = digitalRead(BUMP_L);
  _Bump_R = digitalRead(BUMP_R);
  _Cliff= digitalRead(CLIFF);
  //Serial.print(F("Left: "));
  //Serial.print(_Bump_L);
  //Serial.print(F("    Right: "));
  //Serial.println(_Bump_R);
  if(_Bump_L  && _Bump_R )
    {
    digitalWrite(LED_BUILTIN,LOW);
    }
  if(!_Bump_L || !_Bump_R)
    {
    digitalWrite(LED_BUILTIN,HIGH);
    } 

 if(_Cliff) //Detect cliff triggered, if so suspend navigation and rangefinder
    {
    // Suspend a task from the outside
    //vTaskSuspend(task_handle);
    vTaskSuspend(TaskHandle_Rangefind);
    vTaskSuspend(TaskHandle_Navigate);
    cliffTriggered = true;
    }
 if(!_Cliff && cliffTriggered) //If cliff had been detected and tasks stopped, count to 10 instances of no cliff and resume
    {
    loopIterations++;
    if(loopIterations > 10)
      {
      loopIterations = 0;
      cliffTriggered = false; 
      // Resume a task (only possible from the outside)     
      //vTaskResume(task_handle);
      vTaskResume(TaskHandle_Rangefind);
      vTaskResume(TaskHandle_Navigate);
      }
    }
      
  vTaskDelay(pdMS_TO_TICKS(100));
  }
}
// Suspend a task from the outside
//vTaskSuspend(task_handle);
// Resume a task (only possible from the outside)
//vTaskResume(task_handle);
