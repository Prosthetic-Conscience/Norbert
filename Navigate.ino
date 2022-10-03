
/*
intRangeCenter = 100;
intRangeRight = 100;
intRangeLeft = 100;
*/

void TaskNavigate(void *pvParameters) 
{
(void) pvParameters;
for (;;)
  {
  //Bump Left segment
  if(!BUMP_L && BUMP_R)
    {
    //Motor A is left, B is right
    //Both reverse
    digitalWrite( MOTOR_A_DIR, HIGH ); // direction = reverse
    analogWrite( MOTOR_A_PWM, PWM_SLOW ); // PWM speed = slow 
    digitalWrite( MOTOR_B_DIR, HIGH ); // direction = reverse
    analogWrite( MOTOR_B_PWM, PWM_SLOW); // PWM speed = slow
    vTaskDelay(pdMS_TO_TICKS(1000));
    //Stop Left
    digitalWrite( MOTOR_A_DIR, LOW );
    digitalWrite( MOTOR_A_PWM, LOW );
    //Stop a random time later so it'll be heading some diff direction
    int randomDelayTime = random(200, 1000);
    vTaskDelay(pdMS_TO_TICKS(randomDelayTime));
    digitalWrite( MOTOR_B_DIR, LOW );
    digitalWrite( MOTOR_B_PWM, LOW );     
    }
  //Bump Right segment
  if(!BUMP_R && BUMP_L)
    {
    //Motor A is left, B is right
    //Both reverse
    digitalWrite( MOTOR_A_DIR, HIGH ); // direction = reverse
    analogWrite( MOTOR_A_PWM, PWM_SLOW ); // PWM speed = slow 
    digitalWrite( MOTOR_B_DIR, HIGH ); // direction = reverse
    analogWrite( MOTOR_B_PWM, PWM_SLOW); // PWM speed = slow
    vTaskDelay(pdMS_TO_TICKS(1000));
    //Stop Right
    digitalWrite( MOTOR_B_DIR, LOW );
    digitalWrite( MOTOR_B_PWM, LOW );
    //Stop a random time later so it'll be heading some diff direction
    int randomDelayTime = random(200, 1000);
    vTaskDelay(pdMS_TO_TICKS(randomDelayTime));
    digitalWrite( MOTOR_A_DIR, LOW );
    digitalWrite( MOTOR_A_PWM, LOW );
    }
  //Both bumpers hit
  if(!BUMP_R && !BUMP_L)
    {
    //Motor A is left, B is right
    //Both reverse
    digitalWrite( MOTOR_A_DIR, HIGH ); // direction = reverse
    analogWrite( MOTOR_A_PWM, PWM_SLOW ); // PWM speed = slow 
    digitalWrite( MOTOR_B_DIR, HIGH ); // direction = reverse
    analogWrite( MOTOR_B_PWM, PWM_SLOW); // PWM speed = slow
    vTaskDelay(pdMS_TO_TICKS(1000));
    int randomLeftRight = random(0, 1);
    int randomDelayTime = random(200, 1000);
    //Random back left or right
    //back right
    if(randomLeftRight == 0)
      {
      digitalWrite( MOTOR_A_DIR, LOW );
      digitalWrite( MOTOR_A_PWM, LOW );
      vTaskDelay(pdMS_TO_TICKS(randomDelayTime));
      digitalWrite( MOTOR_B_DIR, LOW );
      digitalWrite( MOTOR_B_PWM, LOW );
      }
    //back left
    if(randomLeftRight == 1)
      {
      digitalWrite( MOTOR_B_DIR, LOW );
      digitalWrite( MOTOR_B_PWM, LOW );
      vTaskDelay(pdMS_TO_TICKS(randomDelayTime));
      digitalWrite( MOTOR_A_DIR, LOW );
      digitalWrite( MOTOR_A_PWM, LOW );
      }     
    }
   // Back Up segment rangefinder
   //Runs when bump not detected and all readings less than 5cm   
   //Motor A is left, B is righ
   if(intRangeLeft < 20 && intRangeCenter  < 20 && intRangeRight < 20 &&  BUMP_L && BUMP_R)
   { 
    while(BUMP_L && BUMP_R)
      {
      //Reverse both motors
      digitalWrite( MOTOR_B_DIR, HIGH ); // direction = reverse
      analogWrite( MOTOR_B_PWM, PWM_SLOW); // PWM speed = slow
      digitalWrite( MOTOR_A_DIR, HIGH ); // direction = reverse
      analogWrite( MOTOR_A_PWM, PWM_SLOW ); // PWM speed = slow 
      vTaskDelay(pdMS_TO_TICKS(1000));
      int randomLeftRight = random(0, 1);
      int randomDelayTime = random(200, 1000);
      //Random back left or right
      //back right
      if(randomLeftRight == 0)
        {
        digitalWrite( MOTOR_A_DIR, LOW );
        digitalWrite( MOTOR_A_PWM, LOW );
        vTaskDelay(pdMS_TO_TICKS(randomDelayTime));
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );
        }
      //back left
      if(randomLeftRight == 1)
        {
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );
        vTaskDelay(pdMS_TO_TICKS(randomDelayTime));
        digitalWrite( MOTOR_A_DIR, LOW );
        digitalWrite( MOTOR_A_PWM, LOW );
        }     
      break;
     }
   }
    //Runs when bump not detected and all left less than 5cm 
    //Motor A is left, B is righ  
    if(intRangeLeft < 20 && intRangeCenter  > 20 && intRangeRight > 20 &&  BUMP_L && BUMP_R)
    { 
    while(BUMP_L && BUMP_R)
      {
      //Stop right motor
      digitalWrite( MOTOR_B_DIR, LOW );
      digitalWrite( MOTOR_B_PWM, LOW );
      //left motor ahead
      digitalWrite( MOTOR_A_DIR, LOW ); // direction = forward
      analogWrite( MOTOR_A_PWM, PWM_SLOW ); // PWM speed = slow 
      vTaskDelay(pdMS_TO_TICKS(1000));
      break;
      }
    }

    //Runs when bump not detected and  right less than 5cm   
    //Motor A is left, B is righ
    if(intRangeLeft > 20 && intRangeCenter  > 20 && intRangeRight < 20 &&  BUMP_L && BUMP_R)
    { 
    while(BUMP_L && BUMP_R)
      {
      //Stop left motor
      digitalWrite( MOTOR_A_DIR, LOW );
      digitalWrite( MOTOR_A_PWM, LOW );
      //right motor ahead
      digitalWrite( MOTOR_B_DIR, LOW ); // direction = forward
      analogWrite( MOTOR_B_PWM, PWM_SLOW ); // PWM speed = slow 
      vTaskDelay(pdMS_TO_TICKS(1000));
      break;
      break;
      }
    }

    //Runs when bump not detected and center less than 5cm   
    //Motor A is left, B is righ
    if(intRangeLeft > 20 && intRangeCenter  < 20 && intRangeRight > 20 &&  BUMP_L && BUMP_R)
    { 
    while(BUMP_L && BUMP_R)
      {
      //Stop left motor
      digitalWrite( MOTOR_A_DIR, LOW );
      digitalWrite( MOTOR_A_PWM, LOW );
      //Stop right motor
      digitalWrite( MOTOR_A_DIR, LOW );
      digitalWrite( MOTOR_A_PWM, LOW );
      vTaskDelay(pdMS_TO_TICKS(250));
      //Left motor backwards
      digitalWrite( MOTOR_A_DIR, LOW ); //direction reverse
      digitalWrite( MOTOR_A_PWM, PWM_SLOW );
      vTaskDelay(pdMS_TO_TICKS(750));
      break;
      }
    }

    //Runs when bump not detected and all greater than 5cm   
    if(intRangeLeft > 20 && intRangeCenter  > 20 && intRangeRight > 20 &&  BUMP_L && BUMP_R)
    { 
    while(BUMP_L && BUMP_R)
      {
      digitalWrite( MOTOR_A_DIR, LOW); // direction = forward
      analogWrite( MOTOR_A_PWM, PWM_SLOW ); // PWM speed = slow 
      digitalWrite( MOTOR_B_DIR, LOW); // direction = forward
      analogWrite( MOTOR_B_PWM, PWM_SLOW); // PWM speed = slow
      break;
      }
    }    
  vTaskDelay(pdMS_TO_TICKS(500));
  }
}

//DO I put the display here? or in cliff detection?
/*
const uint8_t rook_bitmap[] PROGMEM = {
  0x00,         // 00000000 
  0x55,         // 01010101
  0x7f,          // 01111111
  0x3e,         // 00111110
  0x3e,         // 00111110 
  0x3e,         // 00111110
  0x3e,         // 00111110 
  0x7f           // 01111111
};
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.drawBitmapP( 62, 32, 1, 8, rook_bitmap);
  u8g.drawBitmapP( 50, 26, 4, 10, smile_bitmap);
}

 // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  */
