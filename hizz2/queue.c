//queue
#include "channels.h"
#include "elev.h"
#include "io.h"
#include <stdio.h>
#include "queue.h"


static int orders[4][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};//opp ned command

void q_set_order(int floor, int button_type){
  if(floor != elev_get_floor_sensor_signal()){
    orders[floor][button_type] = 1;
  }
}

void q_set_order_lamp (int floor, int button_type){
    if(orders[floor][button_type] == 1){
        elev_set_button_lamp(button_type, floor, 1);
    }

}

int q_get_order(int floor, int button_type){
    return orders[floor][button_type];
}


void q_printOrders(){
    for (int i=0; i < 4; i++) {
            printf("\n");
        for (int y=0; y < 3; y++) {
            printf("%d", orders[i][y]);
        }
    }
}


void q_clear_all_orders() {
    for (int floor = 1; floor<4; floor++) {
      elev_set_button_lamp(1,floor,0);
      orders[floor][1] = 0;
    }
    for (int floor = 0; floor<3; floor++) {
                elev_set_button_lamp(0, floor, 0);
                orders[floor][0] = 0;
    }
    for (int floor = 0; floor<4; floor++) {
                elev_set_button_lamp(2, floor, 0);
                orders[floor][2] = 0;
    }
}

int q_is_queue_empty(){

    for(int floor = 0; floor<4; floor++){
        for(int button_type = 0; button_type<3; button_type++){
            if(orders[floor][button_type] == 1){
                return 0;
                    }
                }
            }
    return 1;
        }

int q_check_if_already_in_q(int floor, int button){
    if(orders[floor][button] == 1){
        return 1;
    }
    else{
        return 0;
    }
}

int q_check_if_stop(int current_floor, int direction) {

  if(direction == DIRN_UP){

    if(orders[3][1] == 1 || orders[3][2] == 1){
      printf("vi skal stoppe i 4.etasje\n");
      if(q_check_if_order_above(current_floor) != 1){
        
        if(elev_get_floor_sensor_signal() == 3){
          printf("vi har stoppet i 4. etasje!!!!\n");
        return 1;
      }
    }
  }
    if(orders[1][0] == 1){
      printf("vi skal stoppe i neste etasje %d\n",current_floor+1);
        if(elev_get_floor_sensor_signal() == 1){
      return 1;
    }
  }
  if(orders[1][2] == 1){
      printf("vi skal stoppe i neste etasje %d\n",current_floor+1);
        if(elev_get_floor_sensor_signal() == 1){
      return 1;
    }
  }
  if(orders[2][0] == 1){
      printf("vi skal stoppe i neste etasje %d\n",current_floor+1);
        if(elev_get_floor_sensor_signal() == 2){
      return 1;
    }
  }
  if(orders[2][2] == 1){
      printf("vi skal stoppe i neste etasje %d\n",current_floor+1);
        if(elev_get_floor_sensor_signal() == 2){
      return 1;
    }
  }

  if(orders[1][1] == 1){
      printf("vi skal stoppe i neste etasje %d\n",current_floor+1);
        if(elev_get_floor_sensor_signal() == 1){
      return 1;
    }
  }
  if(orders[2][1] == 1){
      printf("vi skal stoppe i neste etasje %d\n",current_floor+1);
        if(elev_get_floor_sensor_signal() == 2){
      return 1;
    }
  }


} 


  if(direction == DIRN_DOWN){

    if(orders[0][0] == 1 || orders[0][2] == 1){
      printf("vi skal stoppe i 1.etasje\n",current_floor-1);
        if(q_check_if_order_below(current_floor) != 1){
          if(elev_get_floor_sensor_signal() == 0){
            printf("vi har stoppet i 1. etasje!!\n");
                 return 1;
          }
        }
      } 

    if(orders[2][1] == 1){
      printf("vi skal stoppe i neste etasje %d\n",current_floor-1);
        if(elev_get_floor_sensor_signal() == 2){
      return 1;
    }
  }
  if (orders[2][2] == 1) {
      printf("vi skal stoppe i neste etasje %d\n",current_floor-1);
      if(elev_get_floor_sensor_signal() == 2){
      return 1;
    }
  }

    if(orders[1][1] == 1){
      printf("vi skal stoppe i neste etasje %d\n",current_floor-1);
        if(elev_get_floor_sensor_signal() == 1){
      return 1;
    }
  }
  
  if (orders[1][2] == 1) {
      printf("vi skal stoppe i neste etasje %d\n",current_floor-1);
      if(elev_get_floor_sensor_signal() == 1){
      return 1;
    }
  }
  if (orders[2][0] == 1) {
      printf("vi skal stoppe i neste etasje %d\n",current_floor-1);
      if(elev_get_floor_sensor_signal() == 2){
      return 1;
    }
  }
  if (orders[1][0] == 1) {
      printf("vi skal stoppe i neste etasje %d\n",current_floor-1);
      if(elev_get_floor_sensor_signal() == 1){
      return 1;
    }
  }
  
  

}
  return 0;

}

void q_clear_current_floor(int floor, int direction){

    orders[floor][0] = 0;
    orders[floor][1] = 0;
    orders[floor][2] = 0;

}


int q_current_floor_in_moving(int current_floor, int direction){
  if(current_floor != -1){
    return current_floor;
  }
}


int q_current_floor_inbetween(int current_floor){
  if(current_floor == -1){

  }
  else{
    printf("setter current floor inbetween mellom \n");
    return current_floor;
  }
}
int q_prev_floor(int floor, int direction){
  if(floor != -1){
    if(direction == 1){
      if(floor == 0){
        return 0;
      }
      else{
        return floor-1;
      }
    }

    if(direction == -1){
      if(floor == 3){
        return 3;
      }
      else{
        return floor+1;
      }
    }
  }
return -1;
}

int q_orders_above(int current_floor){
    for(int x = current_floor+1; x<4; x++){
        if(orders[x][0] == 1){
            return 1;
        }
        if(orders[x][2] == 1){
            return 1;
        }
        if(orders[x][1] == 1){
            return 1;
        }
    }
    return 0;
}

int q_orders_below(int current_floor){
    for(int x = 0; x<current_floor; x++){
        if(orders[x][1] == 1){
            return -1;
        }
        if(orders[x][2] == 1){
            return -1;
        }
        if(orders[x][0] == 1){
            return -1;
        }
    }
    return 0;
}

int q_check_up_orders(int current_floor){

      for(int floor = 0; floor<3; floor++){
        if(orders[floor][0] == 1 || orders[floor][2] == 1){
          return floor;
        }
      }
    return -1;

}

int q_check_down_orders(int current_floor) {



      for(int floor = 0; floor>0; floor--){
        if(orders[floor][1] == 1 ||  orders[floor][2] == 1){
          return floor;
        }
      }


      return -1;
}

int q_check_orders(int current_floor) {

  if(current_floor != floor){
      for(int floor = 3; floor>=0; floor--){
        if(orders[floor][1] == 1 ||  orders[floor][2] == 1){
          return floor;
        }
      }

      for(int floor = 0; floor<4; floor++){

        if(orders[floor][0] == 1 || orders[floor][2] == 1){
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
      return -1;
}

int q_change_dir(int current_floor, int direction) {

  if (direction == DIRN_UP && current_floor != 3) {

    if (q_check_if_order_above(current_floor)) {
      return DIRN_UP;
    }
    
    if(q_check_if_order_below(current_floor)) {

        return DIRN_DOWN;
      }
  }
  if (direction == DIRN_DOWN && current_floor != 0) {

    if (q_check_if_order_below(current_floor)) {
      return DIRN_DOWN;
    }
    
    if(q_check_if_order_above(current_floor)) {

        return DIRN_UP;
      }

}

  return DIRN_STOP;
}




int q_current_floor(){
  return elev_get_floor_sensor_signal();
}

int q_motor_direction(int current_floor, int prev_floor){
    if(prev_floor < current_floor){
        if(q_orders_above(current_floor) == 1){
            return 1;
        }
        if(q_orders_below(current_floor) == 1){
            return -1;
        }
    }
    if(prev_floor > current_floor){
        if(q_orders_below(current_floor) == 1){
            return -1;
        }
        if(q_orders_above(current_floor) == 1){
            return 1;
        }
    }
    return 0;
}

void q_watch_buttons() {


          for(int floor = 0; floor<3; floor++) {
            if(elev_get_button_signal(0,floor)){
              orders[floor][0]=1;
            }
          }
          for(int floor = 1; floor<4; floor++) {
            if(elev_get_button_signal(1,floor)){
              orders[floor][1]=1;

            }
          }
          for(int floor = 0; floor<4; floor++) {
            if(elev_get_button_signal(2,floor)){
              orders[floor][2]=1;

            }
          }

}



int q_check_if_order_above(int floor){
    for(int x = floor; x<4; x++){
        if(orders[x][0] == 1){
          printf("det er ordre over\n");
            return 1;
        }
        if(orders[x][2] == 1 && x != 3){
          printf("det er ordre over\n");
            return 1;
        }
    }
        return 0;

}

int q_check_if_order_below(int floor){

    for(int x = floor; x>=0; x--){
        if(orders[x][1] == 1){
            return 1;
            printf("det er ordre under\n");
        }
        if(orders[x][2] == 1 && x != 0){
          printf("det er ordre under\n");
            return 1;
    }


  }
        return 0;
}
