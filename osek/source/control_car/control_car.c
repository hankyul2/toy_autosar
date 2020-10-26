/* control_car */
#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(straightTask);
DeclareTask(curveTask);
DeclareTask(slowBreakTask);
DeclareTask(breakTask);
DeclareTask(setRecordModeTask);
DeclareTask(playRecordModeTask);
DeclareTask(mainTask);
DeclareTask(idelTask);
DeclareTask(slowStartTask);

DeclareEvent(straightClickEvent);
DeclareEvent(curvePressEvent);
DeclareEvent(curveReleaseEvent);
DeclareEvent(breakPressEvent);
DeclareEvent(breakReleaseEvent);
DeclareEvent(BBtnClickEvent);
DeclareResource(recordResource);

// BT에서 값 받기 위한 buffer
static U8 bt_receive_buf[32];

// 전진인지 후진인지 구분하기 위한 state value
int straight_state = 0;

// 회전 후, 다시 돌아오는 상태를 알기위한 state value
int curve_state = 0;

// 추가기능B의 기록된 차량움직임을 되돌리기로 진행하기 위한 state value
int start_play_back = 0;

// 차량의 속도
int speed = 55;

// 급브레이크와 천천히브레이크 상태를 구분하기 위한 state value
int breakMode = 0;
int is_slow_break_on = 0;

// 추가기능B의 차량의 움직임을 기록하기 위한 배열
int record[100][3] = {
    0,
};

// 추가기능B의 상태를 알기위한 state value
int record_mode = 0;

// 추가기능B의 배열 index
int record_index = 0x01;

// B버튼의 이전 상태를 기록하기 위한 state value, 추가기능 B를 구현하기 위해 첫 번째 클릭인지 두 번째 클릭인지 구분해야 한다.
int before_stateB = 0;

// 좌,우회전을 위한 회전각값
int steering_speed = 0;

// 천천히 속도 증가를 위한 state value
int startstatus = 0;

// 천천히 속도 증가를 위한 speed value
int maxspeed = 0;
/* below macro enables run-time Bluetooth connection */
#define RUNTIME_CONNECTION

/* LEJOS OSEK hooks */
void ecrobot_device_initialize() {
#ifndef RUNTIME_CONNECTION
  ecrobot_init_bt_slave("Rhc");
  nxt_motor_set_count(NXT_PORT_A, 0);
#endif
}

void ecrobot_device_terminate() {
  ecrobot_term_bt_connection();
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
  StatusType ercd;

  ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
  if (ercd != E_OK) {
    ShutdownOS(ercd);
  }
}

//천천히 출발하기 위한 Task, alarm으로 250ms마다 천천히 속도를 증가.
TASK(slowStartTask) {
  if (startstatus == 1 && speed < maxspeed) {
    speed += 5;
  }
  TerminateTask();
}

//전후진하는 Task
TASK(straightTask) {
  while (WaitEvent(straightClickEvent) == E_OK) {
    ClearEvent(straightClickEvent);
    if (bt_receive_buf[3] == 2 && straight_state) {
      startstatus = 0;
      if (speed < 0) speed = -speed;
      ecrobot_set_motor_speed(NXT_PORT_B, speed);
      ecrobot_set_motor_speed(NXT_PORT_C, speed);
      if (record_mode) {  // For record_mode
        record[record_index][1] = nxt_motor_get_count(NXT_PORT_B);
        record[record_index][2] = 0;
        record[record_index++][0] = speed;
      }
    } else if (bt_receive_buf[3] == 1 && straight_state) {
      startstatus = 1;
      if (speed > 0) speed = -speed;
      ecrobot_set_motor_speed(NXT_PORT_B, speed);
      ecrobot_set_motor_speed(NXT_PORT_C, speed);
      if (record_mode) {  // For record_mode
        record[record_index][1] = nxt_motor_get_count(NXT_PORT_B);
        record[record_index][2] = 0;
        record[record_index++][0] = speed;
      }
    }
    bt_receive_buf[3] = 0x00;
  }
  TerminateTask();
}

// 좌,우 조향하는 Task
TASK(curveTask) {  // Turn corner
  while (TRUE) {
    // 좌, 우 버튼이 눌렸을 때
    WaitEvent(curvePressEvent);
    ClearEvent(curvePressEvent);
    if (record_mode) {
      record[record_index][1] = nxt_motor_get_count(NXT_PORT_B);
      record[record_index][2] = 0;
      record[record_index++][0] = speed;
    }
    steering_speed = bt_receive_buf[4] == 3 ? -45 : 45;
    nxt_motor_set_speed(NXT_PORT_A, steering_speed, 1);

    // 좌, 우 버튼이 띄어질 때
    WaitEvent(curveReleaseEvent);
    ClearEvent(curveReleaseEvent);
    if (nxt_motor_get_count(NXT_PORT_A) > 0) {
      steering_speed = -45;
      if (record_mode) {
        record[record_index][1] = nxt_motor_get_count(NXT_PORT_B);
        record[record_index][2] = -steering_speed;
        record[record_index++][0] = speed;
      }
    } else {
      steering_speed = 45;
      if (record_mode) {
        record[record_index][1] = nxt_motor_get_count(NXT_PORT_B);
        record[record_index][2] = -steering_speed;
        record[record_index++][0] = speed;
      }
    }

    nxt_motor_set_speed(NXT_PORT_A, steering_speed, 1);
    bt_receive_buf[4] == 0x01;
  }
  TerminateTask();
}

// 천천히 브레이크를 위한 Task, Alarm으로 500ms마다 실행하여 천천히 속도를 줄임.
TASK(slowBreakTask) {
  if (is_slow_break_on) {
    if (speed >= 10)
      speed = speed - 10;
    else if (speed <= -10)
      speed = speed + 10;
    else
      speed = 0;
    ecrobot_set_motor_speed(NXT_PORT_B, speed);
    ecrobot_set_motor_speed(NXT_PORT_C, speed);
  }
  TerminateTask();
}

// 즉시 브레이크를 위한 Task
TASK(breakTask) {
  int org_speed;
  // break버튼이 눌렸을 때
  while (1) {
    WaitEvent(breakPressEvent);
    ClearEvent(breakPressEvent);
    org_speed = speed;
    if (breakMode == 1) {
      speed = 0;
      ecrobot_set_motor_speed(NXT_PORT_B, speed);
      ecrobot_set_motor_speed(NXT_PORT_C, speed);
    } else if (breakMode == 2) {
      is_slow_break_on = 1;
    }

    // break버튼이 띄어졌을 때
    WaitEvent(breakReleaseEvent);
    ClearEvent(breakReleaseEvent);
    is_slow_break_on = 0;
    speed = org_speed;
    ecrobot_set_motor_speed(NXT_PORT_B, speed);
    ecrobot_set_motor_speed(NXT_PORT_C, speed);
  }
  TerminateTask();
}

//추가기능, 차량의 이동방향,속도등을 저장하는 Task
TASK(setRecordModeTask) {
  while (1) {
    WaitEvent(BBtnClickEvent);
    ClearEvent(BBtnClickEvent);
    GetResource(recordResource);

    if (record_mode) {
      display_goto_xy(0, 7);
      display_string("returnMode");
      display_update();
      record[record_index][1] = nxt_motor_get_count(NXT_PORT_B);
      record[record_index][0] = speed;
      record[record_index][2] = steering_speed;
      if (start_play_back != 1) curve_state = 3;
      start_play_back = 1;
      record_mode = 0;

    } else {
      display_goto_xy(0, 7);
      display_string("recordMode");
      display_update();
      record_mode = 0x01;
      speed = 0;
      ecrobot_set_motor_speed(NXT_PORT_B, speed);
      ecrobot_set_motor_speed(NXT_PORT_C, speed);
      for (int q = 0; q < 100; q++) {
        for (int j = 0; j < 3; j++) {
          record[q][j] = 0;
        }
      }
      nxt_motor_set_count(NXT_PORT_B, 0);
    }

    ReleaseResource(recordResource);

    bt_receive_buf[7] == 0x03;
  }
  TerminateTask();
}

// setRecordTask에서 저장한 기록을 리플레이하는 Task
TASK(playRecordModeTask) {
  if (start_play_back) {
    if (!record_index) {
      start_play_back = 0;
      record_index = 1;
      display_clear(0);
    } else {
      //기록된 속도로 전,후진을 세팅하는 구간
      speed = -record[record_index][0];
      ecrobot_set_motor_speed(NXT_PORT_B, speed);
      ecrobot_set_motor_speed(NXT_PORT_C, speed);

      //기록된 만큼 조향하는 구간
      if (curve_state == 3) {
        nxt_motor_set_speed(NXT_PORT_A, record[record_index][2], 1);
        display_goto_xy(0, 6);
        display_int(1, 1);
        display_update();
      }
      if (curve_state == 3 && (nxt_motor_get_count(NXT_PORT_A) > 45 || nxt_motor_get_count(NXT_PORT_A) < -45)) {
        nxt_motor_set_speed(NXT_PORT_A, 0, 1);
        curve_state = 2;
        display_goto_xy(2, 6);
        display_int(2, 1);
        display_update();
      }
      if (curve_state == 1 && (nxt_motor_get_count(NXT_PORT_A) > -15 && nxt_motor_get_count(NXT_PORT_A) < 15)) {
        nxt_motor_set_speed(NXT_PORT_A, 0, 1);
        curve_state = 3;
        display_goto_xy(4, 6);
        display_int(3, 1);
        display_update();
      }

      //전,후진에 따라서 조향각을 바꾸는 구간
      display_goto_xy(8, 6);
      display_int(nxt_motor_get_count(NXT_PORT_A), 2);
      display_update();
      if (speed >= 0 && record[record_index - 1][1] <= nxt_motor_get_count(NXT_PORT_B)) {
        if (curve_state == 2) {
          display_goto_xy(6, 6);
          display_int(4, 1);
          display_update();
          nxt_motor_set_speed(NXT_PORT_A, -record[record_index][2], 1);
          curve_state = 1;
        }
        record_index = record_index--;
      } else if (speed < 0 && record[record_index - 1][1] >= nxt_motor_get_count(NXT_PORT_B)) {
        if (curve_state == 2) {
          display_goto_xy(6, 6);
          display_int(4, 1);
          display_update();
          nxt_motor_set_speed(NXT_PORT_A, -record[record_index][2], 1);
          curve_state = 1;
        }
        record_index = record_index--;
      }
    }
  }
  TerminateTask();
}

// 메인 Task
TASK(mainTask) {
  // 데이터 값을 확인하기 위해 NXT에 출력하는 구간
  display_goto_xy(0, 0);
  display_string("RIndex: ");
  display_goto_xy(7, 0);
  display_int(record_index, 3);
  display_goto_xy(0, 1);
  display_string("Speed: ");
  display_goto_xy(7, 1);
  display_int(speed, 3);
  display_goto_xy(0, 2);
  display_string("Curve: ");
  display_goto_xy(7, 2);
  display_int(nxt_motor_get_count(NXT_PORT_A), 3);
  display_goto_xy(0, 3);
  display_string("BMode: ");
  display_goto_xy(7, 3);
  display_int(breakMode, 3);
  display_goto_xy(0, 4);
  display_string("Cstate: ");
  display_goto_xy(7, 4);
  display_int(curve_state, 3);

  display_update();

  ecrobot_read_bt_packet(bt_receive_buf, 32);
  display_goto_xy(0, 5);
  display_string("packet: ");
  display_goto_xy(8, 5);
  display_int(bt_receive_buf[3], 2);
  display_goto_xy(10, 5);
  display_int(bt_receive_buf[4], 2);
  display_goto_xy(13, 5);
  display_int(bt_receive_buf[5], 1);
  display_goto_xy(14, 5);
  display_int(bt_receive_buf[6], 1);
  display_goto_xy(15, 5);
  display_int(bt_receive_buf[7], 1);
  display_update();

  // 전,후진 버튼을 입력받고 수행하는 구간
  if (bt_receive_buf[3] == 1 || bt_receive_buf[3] == 2) {
    straight_state ^= 1;
    SetEvent(straightTask, straightClickEvent);
  }

  // 좌,우 버튼이 눌렸을 때 수행하는 구간
  if (start_play_back == 0 && bt_receive_buf[4] == 3 || bt_receive_buf[4] == 4) {
    curve_state = 1;
    SetEvent(curveTask, curvePressEvent);
  }
  // 좌,우 버튼이 떼어졌을 때 수행하는 구간
  if (start_play_back == 0 && bt_receive_buf[4] == 0) {
    curve_state = 5;
    SetEvent(curveTask, curveReleaseEvent);
  }

  // 지정한 값 만큼만 좌우 조향을 하기 위한 구간
  if (start_play_back == 0 && curve_state == 1 && (nxt_motor_get_count(NXT_PORT_A) > 45 || nxt_motor_get_count(NXT_PORT_A) < -45)) {
    steering_speed = 0;
    nxt_motor_set_speed(NXT_PORT_A, 0, 1);
  }
  if (start_play_back == 0 && curve_state == 5 && (nxt_motor_get_count(NXT_PORT_A) > -15 && nxt_motor_get_count(NXT_PORT_A) < 15)) {
    steering_speed = 0;
    nxt_motor_set_speed(NXT_PORT_A, 0, 1);
    curve_state = 0;
  }

  // 조향축을 중앙으로 조절하기 위한 구간
  if (nxt_motor_get_count(NXT_PORT_A) != 0 && curve_state == 0) {
    if (nxt_motor_get_count(NXT_PORT_A) > 5) {
      nxt_motor_set_speed(NXT_PORT_A, -45, 1);
    } else if (nxt_motor_get_count(NXT_PORT_A) <= -1) {
      nxt_motor_set_speed(NXT_PORT_A, 45, 1);
    }
  }

  // 고속, 저속 모드를 입력받는 구간
  if (bt_receive_buf[5] == 1) {
    if (speed < 0) {
      speed = -55;
      maxspeed = speed;
    } else {
      speed = 55;
      maxspeed = speed;
    }
    bt_receive_buf[5] = 0x00;
  } else if (bt_receive_buf[5] == 2) {
    if (speed < 0) {
      speed = -30;
      maxspeed = speed;
    } else {
      speed = 30;
      maxspeed = speed;
    }
    bt_receive_buf[5] = 0x00;
  }

  // 브레이크 모드를 입력받는 구간
  if (bt_receive_buf[6] == 1) {
    breakMode = 1;
    bt_receive_buf[6] = 0x00;
  }
  if (bt_receive_buf[6] == 2) {
    breakMode = 2;
    bt_receive_buf[6] = 0x00;
  }

  // A,B 버튼을 입력받아 수행하는 구간
  if (bt_receive_buf[7] == 1) {
    SetEvent(breakTask, breakPressEvent);
  }
  if (bt_receive_buf[7] == 0) {
    SetEvent(breakTask, breakReleaseEvent);
    before_stateB = 0;
  }
  if (bt_receive_buf[7] == 2 && before_stateB == 0) {
    before_stateB = 2;
    SetEvent(setRecordModeTask, BBtnClickEvent);
  }
  TerminateTask();
}

/* IdleTask */
TASK(idleTask) {
  static SINT bt_status = BT_NO_INIT;

  while (1) {
#ifdef RUNTIME_CONNECTION
    ecrobot_init_bt_slave("Rhc");
#endif
    if (ecrobot_get_bt_status() == BT_STREAM && bt_status != BT_STREAM) {
    }
    bt_status = ecrobot_get_bt_status();
  }
}