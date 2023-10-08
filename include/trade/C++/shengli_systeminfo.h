
#ifndef _SHENGLI_SYSTEMINFO_H_
#define _SHENGLI_SYSTEMINFO_H_

#ifdef SHENGLI_WINDOWS
#define EXPORT_DEFINE           _declspec(dllexport)
#else
#define EXPORT_DEFINE
#endif

typedef		unsigned char		T_ENCRPYT_FLAG;
#define		ENCRYPT_FLAG_TEST		1	/// 测试密钥
#define		ENCRYPT_FLAG_CFMMC		2	/// 期货市场监控密钥


/// 获取采集加密后的数据
/**
	param T_ENCRYPT_FLAG	加密密钥的类型
	param char* p_conn_ip	连接服务端要用到的IP地址，如果填写空串，系统 自动采集第一个IP 
	param char* p_out_buf	输出加密后串空间的起始地址
	param int  n_out_len    输出加密串空间的长度
	return   int			-1：密码类型错误  0:采集失败  >0:返回加密串的真实长度
*/
extern "C" EXPORT_DEFINE int shengli_get_encrypt_local_symbolinfo(T_ENCRPYT_FLAG n_en_flag, const char* p_conn_ip, char* p_out_buf, int n_out_len);

/// 获取采集加密后的数据
/**
	param int  n_out_len    输出加密串空间的长度
	return   int			-1:加密失败    >0:返回加密串的真实长度
*/
extern "C" EXPORT_DEFINE int shengli_get_system_terminal_info(char *buffer, int len);

#endif

