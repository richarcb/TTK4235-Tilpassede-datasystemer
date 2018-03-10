


void q_set_order (int floor, int button_type);
int q_get_order(int floor, int button_type);
void q_printOrders();
void q_clear_all_orders();
void q_clear_all_orders();
int q_is_queue_empty();
int q_check_if_order_above(int floor);
int q_check_if_order_below(int floor);
int q_check_if_already_in_q(int floor, int button);
int q_current_floor_inbetween(int current_floor);
int q_check_if_stop(int current_floor, int direction);
int q_prev_floor(int current_floor, int direction);
int q_current_floor();
int q_motor_direction(int current_floor, int prev_floor);
void q_clear_current_floor(int floor, int direction);
//int q_previous_floor(int floor, int direction);
void q_watch_buttons();
int q_check_orders(int current_floor);
int q_check_down_orders(int current_floor);
int q_check_up_orders(int current_floor);
int q_change_dir(int current_floor, int direction);
int q_current_floor_in_moving(int current_floor, int direction);


