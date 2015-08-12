#define	MY_ID			0	 //my id for addr

#define	SERV_TCP_PORT	(9000 + MY_ID) // tcp port num
#define	SERV_HOST_ADDR	"112.108.39.255" // host IP

#define	MSG_REQUEST		1 //request msg
#define	MSG_REPLY		2 //reply msg


typedef struct  { // struct for msg
	int		type;
	char	data[128];
}
	MsgType;
