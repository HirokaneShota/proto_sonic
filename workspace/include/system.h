#pragma once
#include <cstdint>
#include <string.h>
#include <memory>
#include <string>
#include "ev3api.h"
#define CORRECTIONDATA_ON
#define SYS_OK 0    //����I��
#define SYS_NG 1    //�ُ�I��
#define SYS_PARAM 2 //�����G���[
#define TIMEATTACK_NUM 21//21
#define SLALOMEEBUI_NUM 21//21
#define SLALOMEIFIE_NUM 16//16
#define SLALOMBLACKY_NUM 16//16
#define GARAGE_NUM 26

#define CAR_WIDTH 134.22f      //�ԑ̂̕�(mm)
#define CAR_WHEEL_WIDTH 90.33f //�ԗւ̒��a(mm)

// integer 8bit
using int8 = int8_t;

// integer 16bit
using int16 = int16_t;

// integer 32bit
using int32 = int32_t;

// integer 64bit
using int64 = int64_t;

// unsigned integer 8bit
using uint8 = uint8_t;

// unsigned integer 16bit
using uint16 = uint16_t;

// unsigned integer 32bit
using uint32 = uint32_t;

// unsigned integer 64bit
using uint64 = uint64_t;

// int pointer
using intptr = intptr_t;

// uint pointer
using uintptr = uintptr_t;

/* �񋓌^�̒�` */
// �؂�ւ�������
enum JudgeType
{
	JUDGE_NONE,
	JUDGE_RGB,
	JUDGE_POS,
	JUDGE_DIS,
	JUDGE_DIR,
	JUDGE_V,
	JUDGE_S,
	JUDGE_SEND,//�␳����g�p
};

//���[�^�[�|�[�g�ԍ�
enum MotorPort
{
	MOTOR_ARM,   //�A�[�����[�^�[
	MOTOR_RIGHT, //�E�փ��[�^�[
	MOTOR_LEFT,  //���փ��[�^�[
	MOTOR_TAIL,  //�K�����[�^�[
};

enum SensorPort
{
	SENSOR_TOUCH, //�^�b�`�Z���T�[
	SENSOR_COLOR, //�J���[�Z���T�[
	SENSOR_SONAR, //�����g�Z���T�[
	SENSOR_GYRO,  //�W���C���Z���T�[
};

// ����p����
enum Range
{
	HIGH,
	LOW,
	NONE,
};

// ������
enum ActionType
{
	LINE_TRACE,
	STRAIGHT,
	CURVE,
	LINE_CURVE,
	TURN,
	ARM_ACTION,
	ARMDOWN_ACTION,
};

// �J�[�u�̐i�s����
enum CurveType
{
	CURVE_LEFT,
	CURVE_RIGHT,
};

/* �\���̒�` */
// RGB�̍\����
typedef struct RGB_TAG {
	uint16 r;
	uint16 g;
	uint16 b;
	Range condition;
}RGBData;

// �������̍\����
typedef struct Direction_TAG {
	float direction;
	Range condition;
}DirectionData;

//�J�[�u���̍\����
typedef struct CurveData_TAG {
	float radius;
	CurveType dirction;
}CurveData;

//v�l���̍\����
typedef struct V_TAG {
	uint16 v;
	Range condition;
}VData;

//s�l���̍\����
typedef struct S_TAG {
	uint16 s;
	Range condition;
}SData;


// ���W�̍\����
typedef struct Position_TAG {
	float x;
	float y;
}CORDINATE;

// ���W���̍\����
typedef struct PositionTAG {
	CORDINATE potision;
	Range xCondition;
	Range yCondition;
}PosInfoData;

// ���[�^�p���[
typedef struct MotorPower_TAG {
	int32 right;
	int32 left;
}MOTOR_POWER;

// ���[�^�p�x
typedef struct MotorAngle_TAG {
	int32 right;
	int32 left;
}MOTOR_ANGLE;

// ���E�̎ԗւ̈ړ��ʂ��i�[
typedef struct WheelDist_s
{
	float left;  //���ֈړ���
	float right; //�E�ֈړ���
} WheelDist;


// �؂�ւ��p���
typedef struct ChangeInfo_Tag {
	RGBData rgb_data;		            // �؂�ւ��p��RGB�l
	PosInfoData pos_info_data;		    // �؂�ւ��p�̍��W
	DirectionData direction_data;	// �؂�ւ��p�̋@�̂̌���
	uint8 distance;		            // �؂�ւ��p�̒����g����
	VData vData;					//�؂�ւ��p��v�l
	SData sData;					//�؂�ւ��p��s�l
	JudgeType judge;		                // �؂�ւ��l�̔���		��F�|�W�V�����̐؂�ւ����s�������Ȃ�AJUDGE_POS������			
	ActionType section_act;	        	// �V�[���̓��������		��F���C���g���[�X�̃V�[���Ȃ�ALINE_TRACE������			
	int32 speed;		            // ���̃V�[�����̖ڕW���x					
}ChangeInfo;

typedef struct PositionCorrection_TAG {
	PosInfoData correctionValue;
	DirectionData correctionValueDirection;
	PosInfoData correctionPosition;
	RGBData correctionRGB;
	VData correctionV;
	SData correctionS;
	DirectionData correctionDirection;
	uint8 distance;
	JudgeType correctionCondition;
}PositionCorrectionData;

typedef struct PIDData_Tag
{
	float pGain; //���Q�C��	
	float iGain; //�ϕ��Q�C��	
	float dGain; //�����Q�C��	
	float targetVal; //�ڕW�l	
}PIDData;