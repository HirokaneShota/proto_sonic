/**
 ******************************************************************************
 ** ファイル名 : app.c
 **
 ** 概要 : 二輪差動型ライントレースロボットのTOPPERS/HRP3用Cサンプルプログラム
 **
 ** 注記 : sample_c4 (sample_c3にBluetooth通信リモートスタート機能を追加)
 ******************************************************************************
 **/
#include "ev3api.h"
#include "app.h"
#include "etroboc_ext.h"
#include "workspace/include/system.h"
// 超音波センサー
#include "workspace/include/UltraSonic.h"
//#include "workspace/include/Calculation/BrightCalc.h"
#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif
bool flag = false;
/**
 * EV3システム生成
 * モーター設定
 */
static void user_system_create()
{

}
static void user_system_destroy()
{

}
/*  スタート処理タスク */
void start_task(intptr_t unused)
{
    char command[] = {"logon -section -trace \n"};
    
    uint16 index = 0;
    ev3_sensor_config(EV3_PORT_1, TOUCH_SENSOR);
    /* 動的に生成するインスタンスの初期化 */
    user_system_create();
    //フライング
    while (1)
    {
        if (ev3_touch_sensor_is_pressed(EV3_PORT_1) == 1)
        {
            break;
        }
        tslp_tsk(10 * 1000U);
    }

    act_tsk(MAIN_TASK);
    ext_tsk();
}

/* メインタスク */
void main_task(intptr_t unused)
{
	uint16_t distance;
    UltraSonic ultrasonic = UltraSonic::getInstance();
    UltraSonicSensor ultrasonicsensor = UltraSonicSensor::getInstance();
    //センサー初期化
    ultrasonicsensor.init();

    //while(1){
    distance = ultrasonic.getDistance();
    printf("%d\n",distance);
    ultrasonic.update();
    //}
    ext_tsk();
}
