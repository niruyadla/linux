/*
 * hifi misc driver.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __HIFI_LPP_H__
#define __HIFI_LPP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/list.h>
//lwp:no need include global_ddr_map.h, just define hifi's address config here
//#include "global_ddr_map.h"

//Added to avoid the crash
//#define CONFIG_HISI_FAMA

#ifdef  CONFIG_HISI_FAMA
#define HISI_RESERVED_HIFI_PHYMEM_BASE_FAMA              0x5A8900000
#endif
#define HISI_RESERVED_HIFI_PHYMEM_BASE                   0x88900000
#define HISI_RESERVED_HIFI_PHYMEM_SIZE                   (0x980000)

#ifdef  CONFIG_HISI_FAMA
#define HISI_RESERVED_HIFI_DATA_PHYMEM_BASE_FAMA         0x5AAA00000
#endif
#define HISI_RESERVED_HIFI_DATA_PHYMEM_BASE              0x8AA00000
#define HISI_RESERVED_HIFI_DATA_PHYMEM_SIZE              (0x380000)

/* mailbox mail_len max */
#define MAIL_LEN_MAX	(512)

#ifndef OK
#define OK			 0
#endif

#define ERROR		(-1)
#define BUSY		(-2)
#define NOMEM		(-3)
#define INVAILD 	(-4)
#define COPYFAIL	(-0xFFF)

/* IOCTL��κͳ��ε�SIZE���� */
#define SIZE_LIMIT_PARAM		(256)

/* AP��NV���С���� */
#define NVPARAM_COUNT        400         //HIFI NV size is 400
#define NVPARAM_NUMBER       258         //256+2, nv_data(256) + nv_id(2)
#define NVPARAM_START        2           //head protect_number 0x5a5a5a5a
#define NVPARAM_TAIL         2           //tail protect_number 0x5a5a5a5a
#define NVPARAM_TOTAL_SIZE   ((NVPARAM_NUMBER * NVPARAM_COUNT + NVPARAM_START + NVPARAM_TAIL) * sizeof(unsigned short))

/* HIFIר���� */
#ifdef CONFIG_HISI_FAMA
#define HIFI_BASE_ADDR                      (HISI_RESERVED_HIFI_DATA_PHYMEM_BASE_FAMA)
#else
#define HIFI_BASE_ADDR                      (HISI_RESERVED_HIFI_DATA_PHYMEM_BASE)
#endif

#ifdef CONFIG_HISI_FAMA
#define HIFI_SECDDR_BASE_ADDR                  (HISI_RESERVED_HIFI_PHYMEM_BASE_FAMA)
#else
#define HIFI_SECDDR_BASE_ADDR                  (HISI_RESERVED_HIFI_PHYMEM_BASE)
#endif

/** for chicago only **/
/** unsecured region 3.5M **/
/* |~0x8AA00000~|~0x8AB32000~|~0x8AC32000~|~0x8ACB1000~|~0x8ACB2000~|~0x8ACC5000~|~0x8ACC6000~|~0x8ACC7000~|~0x8ACF9800~|~0x8AD09800~|~0x8AD0C800~~| */
/* |~Music data~|~~~PCM data~|~~hifi uart~|~panic stack|~icc debug~~|~flag data ~|DDR sec head|~~~AP NV ~~~|~AP&HIFI MB~|~hikey share|unsec reserve| */
/* |~~~~~1.2M~~~|~~~~~1M~~~~~|~~~508k~~~~~|~~~~~~4k~~~~|~~~~76k~~~~~|~~~~~4k~~~~~|~~~~~4k~~~~~|~~~~202k~~~~|~~~~~64k~~~~|~~~~~12k~~~~|~~~~462k~~~~~| */
/* |~0x8AB31fff~|~0x8AC31fff~|~0x8ACB0fff~|~0x8ACB1fff~|~0x8ACC4fff~|~0x8ACC5fff~|~0x8ACC6fff~|~0x8ACF97ff~|~0x8AD097ff~|~0x8AD0C7ff~|~~0x8AD7ffff~| */

/** secure region 9.5M **/
/* |~~~0x88900000~~~|~~~0x88f00000~~~|~~~0x88f30000~~|~~~0x88f64000~~~| */
/* |~~HIFI RUNNING~~|~OCRAM img bak~~|~~TCM img bak~~|~~~~IMG bak~~~~~| */
/* |~~~~~~~6M~~~~~~~|~~~~~~192K~~~~~~|~~~~~208k~~~~~~|~~~~~~3.1M ~~~~~| */
/* |~~~0x88efffff~~~|~~~0x88f2ffff~~~|~~~0x88f63fff~~|~~~0x89280000~~~| */

/** for chicago only  **/
/*  ASP HIFI DTCM: 0xe8058000 - 0xe807ffff (160k) */
/*  ASP HIFI ITCM: 0xe8080000 - 0xe808bffff (48k) */

#define HIFI_UNSEC_REGION_SIZE              (0x380000)
#define HIFI_MUSIC_DATA_SIZE                (0x132000)
#define PCM_PLAY_BUFF_SIZE                  (0x100000)
#define DRV_DSP_UART_TO_MEM_SIZE            (0x7f000)
#define DRV_DSP_UART_TO_MEM_RESERVE_SIZE    (0x100)
#define DRV_DSP_STACK_TO_MEM_SIZE           (0x1000)
#define HIFI_ICC_DEBUG_SIZE                 (0x13000)

#define HIFI_FLAG_DATA_SIZE                 (0x1000)
#define HIFI_SEC_HEAD_SIZE                  (0x1000)
#define HIFI_AP_NV_DATA_SIZE                (0x32800)
#define HIFI_AP_MAILBOX_TOTAL_SIZE          (0x10000)
#define HIFI_HIKEY_SHARE_SIZE               (0x1800 * 2)
#define HIFI_UNSEC_RESERVE_SIZE             (0xe800)
#define HIFI_FLAG_DATA_ADDR             (HIFI_ICC_DEBUG_LOCATION + HIFI_ICC_DEBUG_SIZE)
#define HIFI_UNSEC_BASE_ADDR            (HIFI_BASE_ADDR)
#define HIFI_MUSIC_DATA_LOCATION        (HIFI_UNSEC_BASE_ADDR)
#define PCM_PLAY_BUFF_LOCATION          (HIFI_MUSIC_DATA_LOCATION + HIFI_MUSIC_DATA_SIZE)
#define DRV_DSP_UART_TO_MEM             (PCM_PLAY_BUFF_LOCATION + PCM_PLAY_BUFF_SIZE)
#define DRV_DSP_STACK_TO_MEM            (DRV_DSP_UART_TO_MEM + DRV_DSP_UART_TO_MEM_SIZE)
#define HIFI_ICC_DEBUG_LOCATION         (DRV_DSP_STACK_TO_MEM + DRV_DSP_STACK_TO_MEM_SIZE)

#define HIFI_SEC_HEAD_BACKUP            (HIFI_FLAG_DATA_ADDR + HIFI_FLAG_DATA_SIZE)
#define HIFI_AP_NV_DATA_ADDR            (HIFI_SEC_HEAD_BACKUP + HIFI_SEC_HEAD_SIZE)
#define HIFI_AP_MAILBOX_BASE_ADDR       (HIFI_AP_NV_DATA_ADDR + HIFI_AP_NV_DATA_SIZE)
#define HIFI_HIKEY_SHARE_MEM_ADDR       (HIFI_AP_MAILBOX_BASE_ADDR + HIFI_AP_MAILBOX_TOTAL_SIZE)
#define HIFI_UNSEC_RESERVE_ADDR         (HIFI_HIKEY_SHARE_MEM_ADDR + HIFI_HIKEY_SHARE_SIZE)

#define HIFI_DUMP_TCM_ADDR              (DRV_DSP_UART_TO_MEM - HIFI_IMAGE_TCMBAK_SIZE)
#define HIFI_DUMP_BIN_SIZE              (HIFI_UNSEC_RESERVE_ADDR - DRV_DSP_UART_TO_MEM + HIFI_IMAGE_TCMBAK_SIZE)
#define HIFI_DUMP_BIN_ADDR              (HIFI_DUMP_TCM_ADDR)

#define DRV_DSP_PANIC_MARK              (HIFI_FLAG_DATA_ADDR)
#define DRV_DSP_UART_LOG_LEVEL          (DRV_DSP_PANIC_MARK + 4)
#define DRV_DSP_UART_TO_MEM_CUR_ADDR    (DRV_DSP_UART_LOG_LEVEL + 4)
#define DRV_DSP_EXCEPTION_NO            (DRV_DSP_UART_TO_MEM_CUR_ADDR + 4)
#define DRV_DSP_IDLE_COUNT_ADDR         (DRV_DSP_EXCEPTION_NO + 4)
#define DRV_DSP_LOADED_INDICATE         (DRV_DSP_IDLE_COUNT_ADDR + 4)
#define DRV_DSP_KILLME_ADDR             (DRV_DSP_LOADED_INDICATE + 4)
#define DRV_DSP_WRITE_MEM_PRINT_ADDR    (DRV_DSP_KILLME_ADDR + 4)
#define DRV_DSP_POWER_STATUS_ADDR       (DRV_DSP_WRITE_MEM_PRINT_ADDR + 4)
#define DRV_DSP_NMI_FLAG_ADDR           (DRV_DSP_POWER_STATUS_ADDR + 4)

#define DRV_DSP_POWER_ON                (0x55AA55AA)
#define DRV_DSP_POWER_OFF               (0x55FF55FF)
#define DRV_DSP_KILLME_VALUE            (0xA5A55A5A)
#define DRV_DSP_NMI_COMPLETE            (0xB5B5B5B5)
#define DRV_DSP_NMI_INIT                (0xA5A5A5A5)

#define HIFI_SEC_REGION_SIZE            (0x980000)
#define HIFI_IMAGE_OCRAMBAK_SIZE        (0x30000)
#ifdef HIFI_TCM_208K
#define HIFI_RUN_SIZE                   (0x600000)
#define HIFI_IMAGE_TCMBAK_SIZE          (0x34000)
#define HIFI_IMAGE_SIZE                 (0x31C000)
#define HIFI_RUN_ITCM_BASE              (0xe8080000)
#define HIFI_RUN_ITCM_SIZE              (0x9000)
#define HIFI_RUN_DTCM_BASE              (0xe8058000)
#define HIFI_RUN_DTCM_SIZE              (0x28000)
#else
#define HIFI_RUN_SIZE                   (0x500000)
#define HIFI_IMAGE_TCMBAK_SIZE          (0x1E000)
#define HIFI_IMAGE_SIZE                 (0x400000)
#define HIFI_SEC_RESERVE_SIZE           (0x32000)
#define HIFI_RUN_ITCM_BASE              (0xe8070000)
#define HIFI_RUN_ITCM_SIZE              (0x6000)
#define HIFI_RUN_DTCM_BASE              (0xe8058000)
#define HIFI_RUN_DTCM_SIZE              (0x18000)
#endif

#ifdef HIFI_TCM_208K
#define HIFI_SEC_REGION_ADDR            (HIFI_SECDDR_BASE_ADDR) /* chciago */
#define HIFI_RUN_LOCATION               (HIFI_SEC_REGION_ADDR)
#define HIFI_IMAGE_OCRAMBAK_LOCATION    (HIFI_RUN_LOCATION + HIFI_RUN_SIZE)
#define HIFI_IMAGE_TCMBAK_LOCATION      (HIFI_IMAGE_OCRAMBAK_LOCATION + HIFI_IMAGE_OCRAMBAK_SIZE)
#define HIFI_IMAGE_LOCATION             (HIFI_IMAGE_TCMBAK_LOCATION + HIFI_IMAGE_TCMBAK_SIZE)
#else
#define HIFI_SEC_REGION_ADDR            (HIFI_BASE_ADDR + HIFI_UNSEC_REGION_SIZE) /* austin dallas */
#define HIFI_IMAGE_OCRAMBAK_LOCATION    (HIFI_SEC_REGION_ADDR)
#define HIFI_IMAGE_TCMBAK_LOCATION      (HIFI_IMAGE_OCRAMBAK_LOCATION + HIFI_IMAGE_OCRAMBAK_SIZE)
#define HIFI_IMAGE_LOCATION             (HIFI_IMAGE_TCMBAK_LOCATION + HIFI_IMAGE_TCMBAK_SIZE)
#define HIFI_SEC_RESERVE_ADDR           (HIFI_IMAGE_LOCATION + HIFI_IMAGE_SIZE)
#define HIFI_RUN_LOCATION               (HIFI_SEC_RESERVE_ADDR + HIFI_SEC_RESERVE_SIZE)
#endif

#define HIFI_OCRAM_BASE_ADDR                    (0xE8000000)
#define HIFI_TCM_BASE_ADDR                      (0xE8058000)
#define HIFI_RUN_DDR_REMAP_BASE         (0xC0000000)

#define HIFI_TCM_PHY_BEGIN_ADDR         (HIFI_TCM_BASE_ADDR)
#define HIFI_TCM_PHY_END_ADDR           (HIFI_TCM_PHY_BEGIN_ADDR + HIFI_TCM_SIZE - 1)
#define HIFI_TCM_SIZE                   (HIFI_RUN_ITCM_SIZE + HIFI_RUN_DTCM_SIZE)

#define HIFI_OCRAM_PHY_BEGIN_ADDR       (HIFI_OCRAM_BASE_ADDR)
#define HIFI_OCRAM_PHY_END_ADDR         (HIFI_OCRAM_PHY_BEGIN_ADDR + HIFI_OCRAM_SIZE - 1)
#define HIFI_OCRAM_SIZE                 (HIFI_IMAGE_OCRAMBAK_SIZE)

#define SIZE_PARAM_PRIV                         (206408) /*refer from function dsp_nv_init in dsp_soc_para_ctl.c  */
#define HIFI_SYS_MEM_ADDR                       (HIFI_RUN_LOCATION)
#define SYS_TIME_STAMP_REG                      (0xFFF0A534)

/* ����HIFI��Ϣ��ǰ��cmd_idռ�õ��ֽ��� */
#define SIZE_CMD_ID 	   (8)

/* notice�����ϱ�һ�λ��� */
#define REV_MSG_NOTICE_ID_MAX		2

#define ACPU_TO_HIFI_ASYNC_CMD	  0xFFFFFFFF

#define BUFFER_NUM	8
#define MAX_NODE_COUNT 10

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

typedef enum HIFI_MSG_ID_ {

	/*DTS command id from ap*/
	ID_AP_AUDIO_SET_DTS_ENABLE_CMD		= 0xDD36,
	ID_AP_AUDIO_SET_DTS_DEV_CMD			= 0xDD38,
	ID_AP_AUDIO_SET_DTS_GEQ_CMD			= 0xDD39,
	ID_AP_AUDIO_SET_DTS_GEQ_ENABLE_CMD	= 0xDD3B,

	/* Voice Record */
	ID_AP_HIFI_VOICE_RECORD_START_CMD	= 0xDD40,
	ID_AP_HIFI_VOICE_RECORD_STOP_CMD	= 0xDD41,

	/* voicePP MSG_ID */
	ID_AP_VOICEPP_START_REQ				= 0xDD42,						/* ����VOICEPPͨ�� */
	ID_VOICEPP_MSG_START				= ID_AP_VOICEPP_START_REQ,
	ID_VOICEPP_AP_START_CNF				= 0xDD43,
	ID_AP_VOICEPP_STOP_REQ				= 0xDD44,						/* ��ֹVOICEPPͨ�� */
	ID_VOICEPP_AP_STOP_CNF				= 0xDD45,
	ID_AP_VOICEPP_SET_DEVICE_REQ		= 0xDD46,						/* ������������豸 */
	ID_VOICEPP_AP_SET_DEVICE_CNF		= 0xDD47,
	ID_AP_VOICEPP_SET_WB_REQ			= 0xDD48,						/* ���ÿ�խ�� */
	ID_VOICEPP_AP_SET_WB_CNF			= 0xDD49,
	ID_VOICEPP_MSG_END					= 0xDD4A,

	ID_AP_AUDIO_PLAY_START_REQ			= 0xDD51,/* AP����Hifi audio player request���� */
	ID_AUDIO_AP_PLAY_START_CNF			= 0xDD52,/* Hifi����audio player��ظ�AP confirm���� */
	ID_AP_AUDIO_PLAY_PAUSE_REQ			= 0xDD53,/* APֹͣHifi audio player request���� */
	ID_AUDIO_AP_PLAY_PAUSE_CNF			= 0xDD54,/* Hifiֹͣaudio player��ظ�AP confirm���� */
	ID_AUDIO_AP_PLAY_DONE_IND			= 0xDD56,/* Hifi֪ͨAP audio playerһ�����ݲ�����ϻ��߲����ж�indication */
	ID_AP_AUDIO_PLAY_UPDATE_BUF_CMD 	= 0xDD57,/* AP֪ͨHifi�����ݿ����command */
	ID_AP_AUDIO_PLAY_QUERY_TIME_REQ 	= 0xDD59,/* AP��ѯHifi audio player���Ž���request���� */
	ID_AP_AUDIO_PLAY_WAKEUPTHREAD_REQ	= 0xDD5A,
	ID_AUDIO_AP_PLAY_QUERY_TIME_CNF 	= 0xDD60,/* Hifi�ظ�AP audio player���Ž���confirm���� */
	ID_AP_AUDIO_PLAY_QUERY_STATUS_REQ	= 0xDD61,/* AP��ѯHifi audio player����״̬request���� */
	ID_AUDIO_AP_PLAY_QUERY_STATUS_CNF	= 0xDD62,/* Hifi�ظ�AP audio player����״̬confirm���� */
	ID_AP_AUDIO_PLAY_SEEK_REQ			= 0xDD63,/* AP seek Hifi audio player��ĳһλ��request���� */
	ID_AUDIO_AP_PLAY_SEEK_CNF			= 0xDD64,/* Hifi�ظ�AP seek���confirm���� */
	ID_AP_AUDIO_PLAY_SET_VOL_CMD		= 0xDD70,/* AP������������ */
	ID_AP_AUDIO_RECORD_PCM_HOOK_CMD		= 0xDD7A,/* AP ֪ͨHIFI��ʼץȡPCM���� */
	/* enhance msgid between ap and hifi */
	ID_AP_HIFI_ENHANCE_START_REQ		= 0xDD81,
	ID_HIFI_AP_ENHANCE_START_CNF		= 0xDD82,
	ID_AP_HIFI_ENHANCE_STOP_REQ 		= 0xDD83,
	ID_HIFI_AP_ENHANCE_STOP_CNF 		= 0xDD84,
	ID_AP_HIFI_ENHANCE_SET_DEVICE_REQ	= 0xDD85,
	ID_HIFI_AP_ENHANCE_SET_DEVICE_CNF	= 0xDD86,

	/* audio enhance msgid between ap and hifi */
	ID_AP_AUDIO_ENHANCE_SET_DEVICE_IND	= 0xDD91,
	ID_AP_AUDIO_MLIB_SET_PARA_IND		= 0xDD92,
	ID_AP_AUDIO_CMD_SET_SOURCE_CMD		= 0xDD95,
	ID_AP_AUDIO_CMD_SET_DEVICE_CMD		= 0xDD96,
	ID_AP_AUDIO_CMD_SET_MODE_CMD		= 0xDD97,
	ID_AP_AUDIO_CMD_SET_ANGLE_CMD		= 0xDD99,

	/* for 3mic */
	ID_AP_AUDIO_ROUTING_COMPLETE_REQ    = 0xDDC0,/*AP ֪ͨHIFI 3Mic/4Mic ͨ·�ѽ���*/
	ID_AUDIO_AP_DP_CLK_EN_IND           = 0xDDC1,/* HIFI ֪ͨA�˴򿪻�ر�Codec DPʱ�� */
	ID_AP_AUDIO_DP_CLK_STATE_IND        = 0xDDC2,/* A��֪ͨHIFI ��Codec DPʱ��״̬( �򿪻�ر�) */
	ID_AUDIO_AP_OM_DUMP_CMD             = 0xDDC3,/* HIFI ֪ͨA��dump��־ */
	ID_AUDIO_AP_FADE_OUT_REQ            = 0xDDC4,/* HIFI֪ͨAP���������� */
	ID_AP_AUDIO_FADE_OUT_IND            = 0xDDC5,/* AP֪ͨHIFI������� */
	ID_AUDIO_AP_OM_CMD                  = 0xDDC9,
	ID_AP_AUDIO_STR_CMD                 = 0xDDCB,/* AP��HIFI����һ���ַ��������庬��hifi�н��� */
	ID_AUDIO_AP_VOICE_BSD_PARAM_CMD     = 0xDDCC,/* VOICE BSD �����ϱ� */
} HIFI_MSG_ID;

typedef enum HI6402_DP_CLK_STATE_ {
	HI6402_DP_CLK_OFF = 0x0,
	HI6402_DP_CLK_ON = 0x1,
} HI6402_DP_CLK_STATE;

/*����hifi�ظ���Ϣ����¼cmd_id������*/
typedef struct {
	unsigned char *mail_buff;		/* �������ݽ��յ�buff */
	unsigned int mail_buff_len;
	unsigned int cmd_id;			/* �����������ǰ4���ֽ���cmd_id */
	unsigned char *out_buff_ptr;	/* ָ��mail_buff cmd_id���λ�� */
	unsigned int out_buff_len;
} rev_msg_buff;

struct recv_request {
	struct list_head recv_node;
	rev_msg_buff rev_msg;
};

struct misc_recmsg_param {
	unsigned short	msgID;
	unsigned short	playStatus;
};

struct common_hifi_cmd{
	unsigned short msg_id;
	unsigned short reserve;
	unsigned int   value;
};

struct dp_clk_request {
	struct list_head dp_clk_node;
	struct common_hifi_cmd dp_clk_msg;
};

typedef struct {
	unsigned short	down_cpu_utilization;    /* DDR�µ�cpu ռ����ˮ�� */
	unsigned short	up_cpu_utilization;      /* DDR�ϵ�cpu ռ����ˮ�� */
	unsigned short	ddr_freq;               /* ����ddrƵ��*/
	unsigned short	is_vote_ddr;             /* �Ƿ��ǵ�ǰͶƱ��DDRƵ�� */
} audio_vote_ddr_freq_stru;

typedef struct {
	unsigned short	enable_vote_ddr;         /* �Ƿ�ʹ�ܶ�̬DDRͶƱ,����Ϊ0��ʾֻ��ӡcpuռ����,����ͶƱ */
	unsigned short	ddr_freq_count;          /* ddr��Ƶ�б��� */
	unsigned short	check_interval;         /* DDRͶƱcpuռ���ʼ����,��λ���� */
	unsigned short	report_interval;        /* cpuռ�����ϱ����,��λ�� */
	audio_vote_ddr_freq_stru *pst_vote_ddr_freq;  /* DDR��Ƶ�����б�,�ɱ䳤��,���ȼ�uhwDdrFreqCount */
} audio_cpu_load_cfg_stru;

int hifi_send_msg(unsigned int mailcode, void *data, unsigned int length);
void hifi_get_log_signal(void);
void hifi_release_log_signal(void);
void sochifi_watchdog_send_event(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of hifi_lpp.h */

