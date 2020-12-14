//
// Created by Michal on 21-Oct-20.
//
#ifdef __cplusplus
extern "C" {
#endif

#ifndef SOLARCONVERTERCONNECTIONLIB_INVERTERCOMM_H
#define SOLARCONVERTERCONNECTIONLIB_INVERTERCOMM_H
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define IO_ERROR 1
#define MEM_ERROR 2
#define BAD_ARG 3

struct usbSolarContext_t
{
    int childServerSocket;
    int parentClientSocket;
    int childClientSocket;

    int deviceFD;
    unsigned long childPID;

    char *socketAddr;
    char *deviceAddr;
    struct termios *deviceSettings;
};
typedef struct usbSolarContext_t inverterCommContext;

struct generalStringInfo_t
{
    char gridVoltage[6];
    char gridFrequency[5];
    char acOutput[6];
    char acOutFreq[5];

    char acOutputApparentPower[5];
    char acOutputActivePower[5];
    char outputLoadPercent[4];

    char busVoltage[4];
    char batteryVoltage[6];
    char batteryChargingCurrent[3];
    char batteryCapacity[4];
    char heatSinkTemp[5];

    char pvInputCurrentBattery[5];
    char pvInputVoltage1[6];
    char batteryVoltageSCC[6];
    char batteryDischargeCurrent[6];

    char deviceFlags[9];
};

typedef struct generalStringInfo_t stringInfo;

typedef struct
{
    uint8_t reserved : 1;
    uint8_t configStatus : 1;
    uint8_t SCCFirmwareVersion : 1;
    uint8_t LoadStatus : 1;
    uint8_t reserve : 1;
    uint8_t chargingStatus : 1;
    uint8_t chargingStatusSCC : 1;
    uint8_t chargingAC : 1;
} niceFlags;

typedef union
{
    char allFlags;
    niceFlags flags;
} deviceFlags;

struct generalInfo_t
{
    float gridVoltage;
    float gridFrequency;
    float acOutput;
    float acOutFreq;

    short acOutputApparentPower;
    short acOutputActivePower;
    short outputLoadPercent;

    short busVoltage;
    float batteryVoltage;
    char batteryChargingCurrent;
    short batteryCapacity;
    short heatSinkTemp;

    short pvInputCurrentBattery;
    short pvInputVoltage1;
    float batteryVoltageSCC;
    int batteryDischargeCurrent;

    char deviceFlags[8];
};

typedef struct generalInfo_t generalInfo;

static const char *CMD_GENERAL_STATUS = "QPIGS\xB7\xA9";
/* Device Mode inquiry */
static const char *CMD_MODE_INQUIRY = "QMOD\x49\xC1";
/* Device Warning Status inquiry */
static const char *CMD_WARNING_STATUS = "QPIWS\xB4\xDA";
/* The device serial number inquiry */
static const char *CMD_SERIAL_INQUIRY = "QID\xD6\xEA";
/* Main CPU Firmware version inquiry */
static const char *CMD_FIRMWARE_PRIM_VER_INQUIRY = "QVFW\x62\x99";
/* Another CPU Firmware version inquiry  */
static const char *CMD_FIRMWARE_SEC_VER_INQUIRY = "QVFW2\xC3\xF5";
/* Device Rating Information inquiry */
static const char *CMD_RATING_INQUIRY = "QPIRI\xF8\x54";
/* Device flag status inquiry */
static const char *CMD_FLAG_INQUIRY = "QFLAG\x98\x74";

typedef enum
{
    CMD_GENERAL_STATUS_LEN = 7,
    CMD_MODE_INQUIRY_LEN = 6,
    CMD_WARNING_STATUS_LEN = 7,
    CMD_SERIAL_INQUIRY_LEN = 5,
    CMD_FIRMWARE_PRIM_VER_INQUIRY_LEN = 6,
    CMD_FIRMWARE_SEC_VER_INQUIRY_LEN = 7,
    CMD_RATING_INQUIRY_LEN = 7,
    CMD_FLAG_INQUIRY_LEN = 7
} commandLengths;

inverterCommContext *createContext(const char *serialDevicePath);

int appendCRC(char *message, int messageLen);
char *createMessage(char *body, int bodyLen);
int basicQuery(inverterCommContext *context, const char *command, int length, uint8_t *buffer, size_t bufferSize, ssize_t *readBytes);
int destroyContext(inverterCommContext *context);
int getState(inverterCommContext *context, generalInfo *info);

#endif // SOLARCONVERTERCONNECTIONLIB_INVERTERCOMM_H

#ifdef __cplusplus
}
#endif
