#ifndef __RFMON_CMN_H__
#define __RFMON_CMN_H__

#define MON_SOCK               "/tmp/rfmon.sock"
#define SLEEP_TIMER_INTERVAL      1000 // 1 second

#define AIM_GENERATE_TEST_EVT   "rf_gen_test_event"

enum mon_states
{
    MON_STATE_RUNNING = 1,
    MON_STATE_STOP
};


#define MON_MAX_PAYLOAD  1024

typedef struct monitor_packet
{
	unsigned int    event;
	unsigned int    timestamp;
	unsigned int    sender_pid;
	unsigned short  data_len;// data length in data[] payload
	unsigned short  cc; //completion code

	unsigned char  op; //0 req, 1 resp
	unsigned char  needack;
	unsigned char  reserved[2];
    unsigned char  data[MON_MAX_PAYLOAD];

}mon_packet;


#endif
