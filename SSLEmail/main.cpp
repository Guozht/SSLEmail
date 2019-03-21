// main.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "SSLEmail.h"
#include <iostream>
#include <fstream>

#include <Windows.h>

//function copied from https://blog.csdn.net/charlessimonyi/article/details/8722859
std::string UTF8_To_GBK(const std::string &source)
{
	enum { GB2312 = 936 };

	unsigned long len = ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL);
	if (len == 0)
		return std::string();
	wchar_t *wide_char_buffer = new wchar_t[len];
	::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, wide_char_buffer, len);

	len = ::WideCharToMultiByte(GB2312, NULL, wide_char_buffer, -1, NULL, NULL, NULL, NULL);
	if (len == 0)
	{
		delete[] wide_char_buffer;
		return std::string();
	}
	char *multi_byte_buffer = new char[len];
	::WideCharToMultiByte(GB2312, NULL, wide_char_buffer, -1, multi_byte_buffer, len, NULL, NULL);

	std::string dest(multi_byte_buffer);
	delete[] wide_char_buffer;
	delete[] multi_byte_buffer;
	return dest;
}

int main()
{
	std::string buffer;

	SSLEmailService service;
	SSLEmailService::EmailInfo info;
	info.charset = "gbk";
	info.sender = "LXHPassnote";
	info.password = "password";
	info.senderEmail = "test@example.com";
	info.recipient = "receiver";
	info.recipientEmail = "recipient@example.com";
	info.MIMEContentType = "text/html";
	info.subject = "��������";
	info.message = "������Ϣ";

	info.smtpServer = "smtp.example.com";
	info.serverPort = "465";

	if (service.SendEmail(info, true))
	{
		std::cout << service.lastErrorMsg;
	}
	else
	{
		std::cout << "�������";
	}
	std::cin.get();

	return 0;
}

