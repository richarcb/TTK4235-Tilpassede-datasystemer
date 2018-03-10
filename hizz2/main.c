#include "elev.h"
#include <stdio.h>
#include "channels.h"
#include "queue.h"
#include "fsm.h"

int main() {





    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;

    }
     printf("Press STOP button to stop elevator and exit program.\n");
    while(1){


      
elev_set_floor_indicator(2);

       fsm();


       /*
      if (elev_get_stop_signal()) {
           elev_set_motor_direction(DIRN_STOP);
           printf("stoppet\n");
           break;
       }
*/
      
















        /*

        int init = 0;
        while (!init){
          if(elev_get_floor_sensor_signal() != -1){
              elev_set_motor_direction(DIRN_STOP);
              printf("initialized\n" );
              init = 1;
          }

        }


        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }
        */



        // Stop elevator and exit program if the stop button is pressed

        //printf("1ygyugiyggyygu");


        /*for(int floor = 0; floor<N_FLOORS; floor++){
            for(int buttons = 0; buttons<3; buttons++){
                if(elev_get_button_signal(buttons, floor)){
                //fsm_orderBtnPressed(floor, buttons);//kjører fsm funksjon fsm_orderBtnPressed
                  printf("en knapp er trykket\n");
                }
            }
        }*/



         /*if(elev_get_floor_sensor_signal() != -1 && current_floor != elev_get_floor_sensor_signal()){
              fsm();
            //  printf("nå er vi i %d etasje\n", elev_get_floor_sensor_signal());
        }*/





        //sjekker når heisen ankommer en etasje, og kjører fsm_arrivedAtFloor() for følt etasje.

        //printf("\n");


    }
}

/*if (prev_floor < current_floor){
  printf("Prev floor er mindre enn current floor");
  for(int floor=current_floor; floor <4; floor++) {
    if (orders[floor][0]==1 || orders[floor][2]==1) {
      printf("Nå skal vi oppover til %d\n", floor);

      return floor;
    }
  }
}


else if (orders[current_floor][0] || orders[current_floor][1] || orders[current_floor][2]) {
  printf("Trykket samme etasje");
  return -2;

}
else {
  printf("Skal kjøre nedover");
  for(int floor=current_floor; floor >= 0; floor--) {
    if (orders[floor][1]==1 || orders[floor][2]==1) {
      printf("Nå skal vi nedover til %d\n", floor);

      return floor;
    }

  }

}

  }
  for(int floor = 0; floor<4; floor++){
    if(current_floor != floor){
        for(int buttons = 0; buttons<3; buttons++){
          if(orders[floor][buttons] == 1){

            printf("Nå skal vi til %d\n", floor);
            return floor;
          }
        }
      }
      else{
        for(int buttons = 0; buttons <3; buttons++) {
        if(orders[current_floor][buttons] == 1){
          printf("Trykket i samme etasje");
          return -2;

        }
        }
      }
    }
  return -1;
}

*/





/*  for(int floor = 0; floor<4; floor++){
    if(current_floor != floor){
        for(int buttons = 0; buttons<3; buttons++){
          if(orders[floor][buttons] == 1){

            printf("Nå skal vi til %d\n", floor);
            return floor;
          }
        }
      }
      else{
        for(int buttons = 0; buttons <3; buttons++) {
        if(orders[current_floor][buttons] == 1){
          printf("Trykket i samme etasje");
          return -2;

        }
        }
      }
    }
  return -1;*/

/*int q_motor_direction(int previous_direction, int floor){
    if(previous_direction == DIRN_UP){
        if(q_check_if_order_above(floor) == 1){
            return DIRN_UP;
        }
    }
    if(previous_direction == DIRN_DOWN){
        if(q_check_if_order_below(floor) == 1){
            return DIRN_DOWN;
        }
    }
    if(q_check_if_order_above(floor) == 1){
        return DIRN_UP;
    }
    if(q_check_if_order_below(floor) == 1){
        return DIRN_DOWN;
    }
    return previous_direction;
}*/

/*

int q_set_direction(int current_floor, int direction) {

//sjekker bestillinger på vei opp
if (direction == DIRN_UP) {

if (q_check_if_order_above(current_floor) == 1) {
    return DIRN_UP;
}

}

if (direction == DIRN_DOWN) {

if (q_check_if_order_below(current_floor) == 1) {
    return DIRN_DOWN;
}

}

else {

if (q_check_if_order_above(current_floor) == 1) {
        return DIRN_UP;
    }
if (q_check_if_order_belowclang: error: linker command failed with exit code 1 (use -v to see invocation)
Makefile:24: recipe for target 'heis' failed
make: *** [heis] Error 1
(current_floor) == 1) {
        return DIRN_DOWN;
    }


}

}



int q_check_reach_top_floor() {

    if (elev_get_floor_sensor_signal() == N_FLOORS -1) {
        if (q_check_if_order_below(0) == 1) {
            elev_set_motor_direction(DIRN_DOWN);
        }
        else {
            elev_set_motor_direction(DIRN_STOP);
        }
    }
    else
        return 0;
}

int q_check_reach_bottom_floor() {

    if (elev_get_floor_sensor_signal() == 0) {
        if (q_check_if_order_above(0) == 1) {

            elev_set_motor_direction(DIRN_UP);
        }
        else {
            elev_set_motor_direction(DIRN_STOP);
        }

    }
    return 0;
}




int q_set_direction(int current_floor, int current_direction){
    if(current_direction == DIRN_UP){
        if(q_check_if_order_above(current_floor) == 1){
            return DIRN_UP;
        }
      else if(q_check_if_order_below(current_floor) == 1){
            return DIRN_DOWN;
        }
    }
    if(current_direction == DIRN_DOWN){
        if(q_check_if_order_below(current_floor) == 1){
            return DIRN_DOWN;
        }
        else if(q_check_if_order_above(current_floor) == 1){
            return DIRN_UP;
        }
    }
    return 0;
}
*/


/*
//sjekker om det noen bestillinger over som skal opp eller i command
int q_check_if_order_above(int floor){
  for(int floor_above = 0; floor_above<N_FLOORS-floor; floor_above++){
    if(orders[floor_above][0] == 1){
      printf("det er ordre over\n");
      return 1;
    }
    if(orders[floor_above][2] == 1){
      printf("det er ordre over\n");
      return 1;
    }
    return 0;
  }

*/

/*    for(int floor_above = floor+1; floor_above<N_FLOORS; floor_above++){
        if(orders[floor_above][0] == 1){
            printf("det er ordre over\n");
            return 1;
        }
        if(orders[floor_above][2] == 1){
          printf("det er ordre over\n");
            return 1;
        }
    }
}
*/

/*
//sjekker om det er noen bestillinger under som skal ned eller i command
int q_check_if_order_below(int floor){
  for(int floor_below = 0; floor_below<floor; floor_below++){
    if(orders[floor_below][1] == 1){
      printf("det er ordre under\n");
      return 1;
    }
    if(orders[floor_below][2] == 1){
      printf("det er ordre under\n");
      return 1;
    }
    return 0;
  }

  for(int floor_below = 0; floor_below<floor; floor_below++){
    if(orders[floor_below][1]){
      printf("det er ordre under\n");
      return 1;
    }
    if(orders[floor_below][2]){
      printf("det er ordre under\n");
      return 1;
    }
  }

}
*/
/*
int q_motor_direction(int current_floor){
  if(q_check_if_order_above(current_floor)){
    printf("opp\n");
    return DIRN_UP;
  }

  if(q_check_if_order_below(current_floor)){
    printf("opp\n");
    return DIRN_DOWN;
  }
  return DIRN_STOP;
}
*/