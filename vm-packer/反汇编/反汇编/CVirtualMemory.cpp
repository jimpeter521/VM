// VMPackLib

#include "stdafx.h"
#include "CVirtualMemory.h"

CVirtualMemory::CVirtualMemory()
{
		m_BaseAddr = NULL;
		m_addrlen  = 0;
		m_VirtualBaseAddress = 0;
		CurrentAddress = NULL;
}

CVirtualMemory::CVirtualMemory(DWORD VirtualAddress,
							   int len)
{
		m_BaseAddr = NULL;
		m_addrlen  = 0;
		m_VirtualBaseAddress = 0;
		CurrentAddress = NULL;
		CreateVirtualMemory(VirtualAddress,len);
}

CVirtualMemory::~CVirtualMemory()
{
	if( m_BaseAddr ) delete[] m_BaseAddr;m_BaseAddr = NULL;
}

// 创建一片对应虚拟地址的内存空间
void CVirtualMemory::CreateVirtualMemory(DWORD VirtualAddress,
										 int len)
{
		if( m_BaseAddr ) delete[] m_BaseAddr;m_BaseAddr = NULL;
		m_BaseAddr = new char[len];
		memset(m_BaseAddr,0,len);
		m_addrlen  = len;
		m_VirtualBaseAddress = VirtualAddress;
		CurrentAddress = m_BaseAddr;
}

// 根据内存地址换算出虚拟线性地址
DWORD CVirtualMemory::GetVirtualAddress(char* addr)
{
		if( addr < m_BaseAddr )
			return -1;
		return m_VirtualBaseAddress + (DWORD)(addr - m_BaseAddr);
}

// 根据虚拟地址计算出内存空间地址
char* CVirtualMemory::GetAddrOfVirtualAddr(DWORD VirtualAddress)
{
	return m_BaseAddr + VirtualAddress - m_VirtualBaseAddress;
}

// 复制数据到虚拟内存,返回数据的起始虚拟地址.
DWORD CVirtualMemory::WriteData(char* src,
								   int len)
{
	if( !src || !len )
	{
		MessageBox(0,"内部错误","err",MB_OK);
		return 0;
	}
	if( m_addrlen - (CurrentAddress - m_BaseAddr) < len )//空间不够
	{
		MessageBox(0,"[memory to small]内部错误","err",MB_OK);
		return 0;
	}
	DWORD StartVirtualAddress = 0;
	memcpy(CurrentAddress,src,len);
	StartVirtualAddress = m_VirtualBaseAddress + (DWORD)(CurrentAddress - m_BaseAddr);
	CurrentAddress += len;
	return StartVirtualAddress;
}
//复制数据到指令虚拟内存地址
DWORD CVirtualMemory::WriteData(DWORD VirtualCode,char* src,int len)
{
	if( !src || !len )
		return 0;
	if( m_BaseAddr + m_addrlen - CurrentAddress < len )//空间不够
		return 0;
	DWORD StartVirtualAddress = 0;
	memcpy(GetAddrOfVirtualAddr(VirtualCode),src,len);
	return VirtualCode;
}
// 清空内存
void CVirtualMemory::ClearMemory()
{
	memset(m_BaseAddr,0,m_addrlen);
	CurrentAddress = m_BaseAddr;
}
// 获得还未使用的空间
char* CVirtualMemory::GetCurrentAddr(void)
{
	return CurrentAddress;
}
// 获得当前可用的虚拟地质
DWORD CVirtualMemory::GetCurrentVirtualAddress(void)
{
	return GetVirtualAddress(CurrentAddress);
} 