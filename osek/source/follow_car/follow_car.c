/* btslave.c */
#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "math.h"

//포트 정의
#define A NXT_PORT_A
#define B NXT_PORT_B
#define C NXT_PORT_C

#define S1 NXT_PORT_S1
#define S2 NXT_PORT_S2
#define S3 NXT_PORT_S3
#define S4 NXT_PORT_S4

//초음파 센서 값 저장 배열 길이
#define ArrayLen 5

//조향 모터 속도
#define steerspeed 40

//최대 조향 motor count
#define maxmotorcount 35

//초기 안전 거리
#define SAFE_DISTANCE_BASE 20

//안전 거리 계산 변수
#define SAFE_DISTANCE_RANGE 60

//이전 진행 상태
#define STOP 0
#define LEFT 1
#define RIGHT 2

DeclareCounter(SysTimerCnt);
DeclareTask(DriveTask);
DeclareTask(Ultrasonic);
DeclareTask(ChangeSteer);
DeclareTask(ChangeSpeed);
DeclareTask(Init);
DeclareTask(Emergency);
DeclareTask(Break);
DeclareTask(curSpeed);

DeclareEvent(ChangeSteerEvent);
DeclareEvent(ChangeSpeedEvent);

//초음파 센서 값 변수
int us1 = 0;
int us2 = 0;
int us3 = 0;

//초음파 센서 값 저장 배열
int us1array[ArrayLen] = { 0 };
int us2array[ArrayLen] = { 0 };
int us3array[ArrayLen] = { 0 };

//초음파 센서 오름차순 정렬 이용 변수
int sorttemp;

//median을 구하기 위한 배열이 가득 찼는지 판단하는 변수
int us1status = 0;
int us2status = 0;
int us3status = 0;

//터치 센서 변수
int touchcheck = 0;

//계산된 모터 속도 변수
int spvalue;

//모터 카운트 변수
int motorcount;

//모터 속도 변수
int motorspeed;

//뒤 차량의 안전거리 상태
int safestatus;

//뒤 차량의 이전 진행 상태
int beforeStatus;

//뒤 차량의 실제 속도
int curSPValue;

//실제 속도를 구하기 위한 이전 motor count 변수
int before_count;

//초음파 센서 배열에 오름차순으로 정렬
void sort1()
{
	for (int i = 0; i < ArrayLen - 1; i++)
	{
		for (int j = i + 1; j < ArrayLen; j++)
		{
			if (us1array[i] > us1array[j])
			{
				sorttemp = us1array[j];
				us1array[j] = us1array[i];
				us1array[i] = sorttemp;
			}
		}
	}
}

void sort2()
{
	for (int i = 0; i < ArrayLen - 1; i++)
	{
		for (int j = i + 1; j < ArrayLen; j++)
		{
			if (us2array[i] > us2array[j])
			{
				sorttemp = us2array[j];
				us2array[j] = us2array[i];
				us2array[i] = sorttemp;
			}
		}
	}
}

void sort3()
{
	for (int i = 0; i < ArrayLen - 1; i++)
	{
		for (int j = i + 1; j < ArrayLen; j++)
		{
			if (us3array[i] > us3array[j])
			{
				sorttemp = us3array[j];
				us3array[j] = us3array[i];
				us3array[i] = sorttemp;
			}
		}
	}
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	StatusType ercd;

	ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
	if (ercd != E_OK)
	{
		ShutdownOS(ercd);
	}
}

int emergency = 0;

//차 기능 정지
void shutdownFunc(void)
{
	StatusType ex = (StatusType)1;
	ShutdownOS(ex);
}

TASK(Emergency)
{
	ecrobot_sound_tone(2000, 2000, 100);
	systick_wait_ms(1000);
	shutdownFunc();
	TerminateTask();
}

TASK(DriveTask)
{
	display_clear(0);
	display_goto_xy(0, 1);
	display_int(us1, 3);
	display_goto_xy(0, 2);
	display_int(us2, 3);
	display_goto_xy(0, 3);
	display_int(us3, 3);
	display_goto_xy(0, 4);
	display_int(touchcheck, 3);
	display_goto_xy(0, 5);
	display_int(motorspeed, 3);
	display_goto_xy(0, 6);
	display_int(motorcount, 3);
	display_update();
	TerminateTask();
}

//초음파 센서 값 정제
TASK(Ultrasonic)
{
	int temp1, temp2, temp3;
	temp1 = ecrobot_get_sonar_sensor(NXT_PORT_S1);
	temp2 = ecrobot_get_sonar_sensor(NXT_PORT_S2);
	temp3 = ecrobot_get_sonar_sensor(NXT_PORT_S3);
	touchcheck = ecrobot_get_touch_sensor(NXT_PORT_S4);

	if (touchcheck == 1) //후방 충돌 감지 기능
	{
		ActivateTask(Emergency);
	}

	us1array[us1status] = temp1;
	us2array[us2status] = temp2;
	us3array[us3status] = temp3;
	us1status++;
	us2status++;
	us3status++;

	if (us1status == ArrayLen - 1)
	{
		//초음파 센서 배열 정렬
		sort1();
		sort2();
		sort3();

		//median 값으로 센서값 정제
		us1 = us1array[1];
		us2 = us2array[1];
		us3 = us3array[1];

		us1status = 0;
		us2status = 0;
		us3status = 0;
	}

	//초음파 센서값 중 최솟값 변수
	int dist = us1 < us2 ? us1 : us2;
	dist = dist > us3 ? us3 : dist;

	//안전거리
	if (us2 >= 15 && us2 <= 20)
	{
		safestatus = 1; //안전거리 내
	}
	else if (us2 < 10)
	{
		safestatus = 2; //안전거리보다 가까움
	}
	else if (us2 > 20 && us2 <= 100)
	{
		safestatus = 3; //안전거리보다 멈
	}
	else if (us2 > 100)
	{
		safestatus = 4; //앞 물체 사라짐
	}
	else if (dist < 15 && dist >= 10)
	{
		safestatus = 5; //긴급정지
	}

	if (dist > 150)
	{
		safestatus = 6; //모든 초음파 센서 측정값이 인식 불가일 때
	}

	//중립을 찾아야 할 때
	if ((us1 - us3) <= 1 && (us1 - us3) >= -1) //양 쪽 차이가 -1 ~ 1 일때
	{
		motorcount = 0;
	}
	//우회전 해야 할 때
	else if ((us1 - us3) > 1)
	{
		beforeStatus = RIGHT;
		if (us1 > 100) //us1 수치 잃음 -> 우회전
		{
			if (safestatus == 4) //us1, us2 수치 잃음 -> 오른쪽 급커브
			{
				motorcount = maxmotorcount;
			}
			else //us1 수치 잃음 -> 오른쪽 커브
			{
				motorcount = maxmotorcount - 5;
			}
		}
		else //모든 수치 있는 우회전 -> 미세 조향
		{
			if ((us1 - us3) * 3 >= 24)
			{
				motorcount = maxmotorcount - 6;
			}
			else
			{
				motorcount = (us1 - us3) * 3;
			}
		}
	}

	//좌회전 해야 할 때
	else if ((us1 - us3) < -1)
	{
		beforeStatus = LEFT;
		if (us3 > 100) //us3 수치 잃음 -> 좌회전
		{
			if (safestatus == 4) //us2, us3 수치 잃음 -> 왼쪽 급커브
			{
				motorcount = -maxmotorcount;
			}
			else
			{ //us3 수치 잃음 -> 오른쪽 커브
				motorcount = -maxmotorcount + 5;
			}
		}
		else //모든 수치 있는 좌회전 -> 미세 조향
		{
			if ((us1 - us3) * 3 <= -24)
			{
				motorcount = -maxmotorcount + 6;
			}
			else
			{
				motorcount = (us1 - us3) * 3;
			}
		}
	}

	SetEvent(ChangeSteer, ChangeSteerEvent);
	SetEvent(ChangeSpeed, ChangeSpeedEvent);

	TerminateTask();
}

int backstatus = 0;

TASK(ChangeSpeed)
{
	while (1)
	{
		WaitEvent(ChangeSpeedEvent);
		ClearEvent(ChangeSpeedEvent);

		//초음파 센서값 중 최솟값 변수
		int dist = us1 < us2 ? us1 : us2;
		dist = dist > us3 ? us3 : dist;

		//속도에 따른 안전거리 계산 알고리즘
		int safe_distance =
			(curSPValue < 20) ? SAFE_DISTANCE_BASE : (SAFE_DISTANCE_BASE + SAFE_DISTANCE_RANGE * fabs((curSPValue - 20) / 60.0));

		if (dist < safe_distance)
		{
			spvalue = 0;
			if (dist < 10)
			{
				spvalue = -30;
				backstatus = 1;
			}
		}
		else if (dist < safe_distance + 10)
		{
			spvalue = 35;
			backstatus = 2;
		}
		else
		{
			spvalue = 65;
			backstatus = 2;
		}

		ecrobot_set_motor_speed(NXT_PORT_B, -spvalue);
		ecrobot_set_motor_speed(NXT_PORT_C, -spvalue);
	}
	TerminateTask();
}

TASK(Init) //센서 초기화
{
	ecrobot_init_sonar_sensor(NXT_PORT_S1);
	ecrobot_init_sonar_sensor(NXT_PORT_S2);
	ecrobot_init_sonar_sensor(NXT_PORT_S3);
	nxt_motor_set_count(A, 0);
	TerminateTask();
}

//차량 조향
TASK(ChangeSteer)
{
	while (1)
	{
		WaitEvent(ChangeSteerEvent);
		ClearEvent(ChangeSteerEvent);

		double motorR = 1.0;

		//세 센서값을 모두 잃었을 때 find 구현
		if (safestatus == 6)
		{
			if (beforeStatus == LEFT)
			{
				motorcount = -maxmotorcount;
			}
			else
			{
				motorcount = maxmotorcount;
			}
		}

		//속도에 따른 조향 각 조절
		if (spvalue > 60)
		{
			motorR = 0.6;
		}

		motorcount *= motorR;

		if (backstatus == 2) //전진 조향
		{
			if (motorcount > 0) //우회전
			{
				if (nxt_motor_get_count(A) < motorcount)
				{
					ecrobot_set_motor_speed(A, steerspeed);
				}
				else
				{
					ecrobot_set_motor_speed(A, 0);
				}
			}
			else if (motorcount < 0) //좌회전
			{
				if (nxt_motor_get_count(A) > motorcount)
				{
					ecrobot_set_motor_speed(A, -steerspeed);
				}
				else
				{
					ecrobot_set_motor_speed(A, 0);
				}
			}
			else if (motorcount == 0) //중립 -> 중앙(momtorcount = 0)을 찾아감
			{
				if (nxt_motor_get_count(A) > motorcount)
				{
					ecrobot_set_motor_speed(A, -steerspeed);
				}
				else if (nxt_motor_get_count(A) < motorcount)
				{
					ecrobot_set_motor_speed(A, steerspeed);
				}
				else
				{
					ecrobot_set_motor_speed(A, 0);
				}
			}
		}
		else if (backstatus == 1) //후진 조향 -> 전진 조향과 반대
		{
			if (motorcount > 0) //좌회전
			{
				if (nxt_motor_get_count(A) > -motorcount)
				{
					ecrobot_set_motor_speed(A, -steerspeed);
				}
				else
				{
					ecrobot_set_motor_speed(A, 0);
				}
			}
			else if (motorcount < 0) //우회전
			{
				if (nxt_motor_get_count(A) < -motorcount)
				{
					ecrobot_set_motor_speed(A, steerspeed);
				}
				else
				{
					ecrobot_set_motor_speed(A, 0);
				}
			}
			else if (motorcount == 0) //중립 -> 중앙(momtorcount = 0)을 찾아감
			{
				if (nxt_motor_get_count(A) > motorcount)
				{
					ecrobot_set_motor_speed(A, -steerspeed);
				}
				else if (nxt_motor_get_count(A) < motorcount)
				{
					ecrobot_set_motor_speed(A, steerspeed);
				}
				else
				{
					ecrobot_set_motor_speed(A, 0);
				}
			}
		}
	}
	TerminateTask();
}

//긴급 브레이크
TASK(Break)
{
	if (safestatus == 5)
	{
		motorspeed = 0;
		ecrobot_set_motor_speed(B, motorspeed);
		ecrobot_set_motor_speed(C, motorspeed);
	}
	TerminateTask();
}

//실제 진행 속도 계산 알고리즘
TASK(curSpeed)
{
	curSPValue = (before_count - nxt_motor_get_count(B)) * 2;
	before_count = nxt_motor_get_count(B);
	TerminateTask();
}
