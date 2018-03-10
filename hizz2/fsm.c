
#include "elev.h"
#include <stdio.h>
#include "channels.h"
#include "queue.h"
#include "timer.h"

typedef enum{
    INIT,
    IDLE,
    IDLE_INBETWEEN,
    MOVING,
    MOVING_INBETWEEN,
    OPEN_DOOR,
    EMERGENCY,
} state_c;

int direction;
int current_floor; 
int prev_floor;
int prev_direction;
int current_floor_inbetween;

state_c state_current = INIT;

void fsm() {
current_floor = q_current_floor();
printf("CURRENT FLOOR %d\n",current_floor);
q_watch_buttons();
q_update_lights();
switch(state_current){

    case INIT:
        printf("INIT\n");
        direction = DIRN_UP;
        current_floor = q_current_floor();
        prev_floor = q_prev_floor(current_floor,direction);

        while(elev_get_floor_sensor_signal() == -1) {
              elev_set_motor_direction(direction);
        }

        
        elev_set_motor_direction(DIRN_STOP);
        state_current = IDLE; // setter state -> IDLE etter initialisering

case IDLE:

    current_floor_inbetween = q_current_floor_inbetween(current_floor);

    if (elev_get_stop_signal()) {
      state_current = EMERGENCY;
      break;
    }
    


    printf("IDLE\n");
    elev_set_floor_indicator(current_floor);
        printf("Current floor inbetween IDLE %d\n",current_floor_inbetween);
    printf("Current floor i IDLE %d\n",current_floor);
    printf("Prev_floor i IDLE %d\n", prev_floor);
    q_printOrders();
    

      //direction = q_motor_direction(current_floor, direction);
      if(q_check_orders(current_floor)>= 0){
        state_current = MOVING;
        printf("Setter state til MOVING\n");
      }
      else if(q_check_orders(current_floor) == -2){
        state_current = OPEN_DOOR;
      }
      else if(q_check_orders(current_floor) == -1){
        state_current = IDLE;
      }
      printf("%d\n",q_check_orders(current_floor));
  
      break;
case MOVING:
    if(current_floor != -1){
        prev_floor = q_prev_floor(current_floor,direction);
    }

    elev_set_floor_indicator(current_floor_inbetween);
    q_printOrders();
    if (elev_get_stop_signal() == 1) {
        state_current = EMERGENCY;
        break;
    }

    printf("MOVING\n");
    printf("Next order: %d\n", q_check_orders(current_floor));
    q_printOrders();
    
    if(q_check_orders(current_floor) < current_floor && current_floor != -1) {
      elev_set_motor_direction(DIRN_DOWN);
      printf("SETTER RETNING NED\n");
      direction = -1;
    }
    if (q_check_orders(current_floor) > current_floor && current_floor !=-1) {
      elev_set_motor_direction(DIRN_UP);
      printf("SETTER REGNING OPP\n");
      direction = 1;
    }

    // setter retning i forhold til neste bestilling

    printf("Retning i MOVING: %d\n", direction);
    printf("Current floor inbetween MOVING %d\n",current_floor_inbetween);
    printf("Current floor i MOVING: %d\n", current_floor);
    printf("Previous floor i moving: %d\n", prev_floor);
    printf("retning før check if stop %d \n", direction);
    if (q_check_if_stop(prev_floor, direction) == 1) {
          state_current = OPEN_DOOR;
          }
    else{
          state_current = MOVING;
          }

   /*if (q_change_dir(current_floor, direction) == DIRN_UP) {
      direction = DIRN_UP;
      elev_set_motor_direction(DIRN_UP);
    }
    if (q_change_dir(current_floor, direction) == DIRN_DOWN){
      direction = DIRN_DOWN;
      elev_set_motor_direction(DIRN_DOWN);
    }*/



    break;

    case MOVING_INBETWEEN:

    q_printOrders();
    
    if(q_check_orders(current_floor_inbetween) < current_floor_inbetween && current_floor_inbetween != -1) {
      elev_set_motor_direction(DIRN_DOWN);
      printf("SETTER RETNING NED\n");
      direction = -1;
    }
    if (q_check_orders(current_floor_inbetween) > current_floor_inbetween && current_floor_inbetween !=-1) {
      elev_set_motor_direction(DIRN_UP);
      printf("SETTER REGNING OPP\n");
      direction = 1;
    }


    if (q_check_if_stop(prev_floor, direction) == 1) {
          state_current = OPEN_DOOR;
          }
    else{
          state_current = MOVING;
          }

    break;

case OPEN_DOOR:
    
    if (elev_get_stop_signal() == 1) {

      state_current = EMERGENCY;
      break;
    }

    printf("OPEN_DOOR\n");
    printf("Vår retning er %d\n", direction);
    printf("Current floor: %d\n", current_floor);

    //current_floor = q_current_floor();
    //prev_floor = q_previous_floor(current_floor, direction);
    q_clear_current_floor(current_floor);
    elev_set_motor_direction(DIRN_STOP);
//timer
    q_printOrders();

    while(timer() != 1){
      elev_set_door_open_lamp(100);
      q_watch_buttons();
    }
    state_current = IDLE;
    

    break;


case EMERGENCY:
    elev_set_motor_direction(DIRN_STOP);
    q_clear_all_orders();
    q_printOrders();
    if(current_floor == -1){
    state_current = IDLE_INBETWEEN;
}
else{
  state_current = OPEN_DOOR;
}
//    printf("EMERGENCY\n");
    break;

case IDLE_INBETWEEN:
printf("IDLE INBETWEEN\n");
printf("current_floor_inbetween %d", current_floor_inbetween);
q_watch_buttons();
      if(q_check_orders(current_floor_inbetween)>= 0 || q_check_orders(current_floor_inbetween) == current_floor_inbetween){
              current_floor = current_floor_inbetween;
              state_current = MOVING_INBETWEEN;
              printf("Setter state til MOVING\n");
            } 
            break;

/*if((q_handle_order_inbetween(prev_floor, direction) == 1) || (q_handle_order_inbetween(prev_floor, direction) == -1))
  {
    direction = (q_handle_order_inbetween(prev_floor, direction));
    state_current = MOVING;
    break;
  }*/



     }//switch

}//fsm

















/*
if(direction != 0){
  elev_set_motor_direction(direction);
  state_current = MOVING;
}

void fsm_orderBtnPressed(int floor, int button){
    q_printOrders();
    current_floor = elev_get_floor_sensor_signal();
    switch(state_current){

        case MOVING:
            //q_set_order(floor, button);
        case OPEN_DOOR:
            //q_set_order(floor, button);
        case IDLE:
                  printf("IDLE\n");
                  if(floor == current_floor)
                {
                  elev_set_door_open_lamp(1);
                  //timer(3);
                  state_current = OPEN_DOOR;
                }
                else{
                  q_set_order(floor, button);
                  printf("nåværende retning er %d\n", direction);
                  prev_direction = direction;
                  direction = q_motor_direction(elev_get_floor_sensor_signal());
                  printf("neste retning er %d\n", direction);
                  elev_set_motor_direction(direction);
                  state_current = MOVING;
                  q_printOrders();
                }
          }
    }



void fsm_arrivedAtFloor(int floor, int direction){
    current_floor = elev_get_floor_sensor_signal();

    q_clear_current_floor(current_floor, direction);
    switch(state_current){
        case INIT:
            printf("INIT\n" );
            state_current = IDLE;
            break;

        case IDLE:

        printf("IDLE\n");


        case MOVING:

          printf("nå beveger jeg meg til denne etasjen: %d\n",current_floor );
          if(q_check_if_stop(current_floor, direction)){
          state_current = OPEN_DOOR;
          }

          case OPEN_DOOR:

          elev_set_motor_direction(DIRN_STOP);
          q_printOrders();
          break;
            }

    }


void fsm_stopBtnPressedAtFloor(){
    elev_set_motor_direction(DIRN_STOP);
    elev_set_stop_lamp(1);

    switch(state_current){
        case IDLE:
            elev_set_door_open_lamp(1);
            break;*/
