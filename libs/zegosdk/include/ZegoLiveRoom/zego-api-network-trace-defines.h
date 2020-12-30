#ifndef zego_api_network_trace_defines_h
#define zego_api_network_trace_defines_h

#include "zego-api-defines.h"

namespace ZEGO
{
	namespace NETWORKTRACE
	{
		struct NetworkTraceConfig
		{
			/**
			  是否进行traceroute 0 不进行 1进行 默认0

			  @attention 开启traceroute 将会显著增长探测时间
			*/
			int traceroute = 0; 
		};

		struct HttpTraceResult
		{
			/**
			http 探测是否成功。0成功 非0失败
			*/
			unsigned int uCode = 0;   

			/**
			http 探测消耗时间 单位ms
			*/
			int requestMs = 0;
		};

		struct TcpTraceResult
		{
			/**
			tcp 探测是否成功。0成功 非0失败
			*/
			unsigned int uCode = 0;

			/**
			tcp 探测链接消耗时间 单位ms
			*/
			int connectMs = 0;

			/**
			tcp 探测rtt
			*/
			int rtt = 0;
		};
		
		struct UdpTraceResult
		{
			/**
			udp 探测是否成功。0成功 非0失败
			*/
			unsigned int uCode = 0;

			/**
			udp 探测rtt
			*/
			int rtt = 0;
		};

		struct TracerouteResult
		{
			/**
			traceroute 探测是否成功。0成功 非0失败, 路由跟踪，最多jump 30次 (traceroute结果供参考，不代表最终连通性结果。优先已http,tcp,udp为准)
			*/
			unsigned int uCode = 0;

			/**
			traceroute 消耗时间 单位ms
			*/
			int  time= 0;
		};
		

		struct NetworkTraceResult
		{
		   HttpTraceResult* httpResult = nullptr; 
		   TcpTraceResult* tcpResult = nullptr;
		   UdpTraceResult*  udpResult = nullptr;
		   TracerouteResult* tracerouteResult = nullptr;
		};
    }
}

#endif
