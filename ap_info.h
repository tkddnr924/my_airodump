#ifndef AP_INFO_H
#define AP_INFO_H
#include <string>
#include <tins/tins.h>

using namespace Tins;

class AP_info
{
public:
    AP_info();

    void SetBssid(const Dot11ManagementFrame& mgf);       // bssid
    void SetChannel(const Dot11ManagementFrame& mgf);       // channel
    void SetPwr(int pwr);                   // pwr
    void SetEncrypt(const Dot11ManagementFrame& mgf);    // enc, cipher
    void SetAuth(const Dot11ManagementFrame& mgf);       // auth
    void SetEssid(const Dot11ManagementFrame& mgf);       // essid
    void SetMB(const Dot11ManagementFrame& mgf);

    std::string GetBssid();
    uint8_t GetChannel();
    int GetPwr();
    std::string GetEnc();
    std::string GetCipher();
    std::string GetAuth();
    std::string GetEssid();
    std::string GetMB();
    int GetCnt();

    void IncreCnt();
private:
    std::string bssid;
    int pwr;
    uint8_t channel;
    std::string mb;
    std::string enc = "OPN";
    std::string cipher = "";
    std::string auth;
    std::string essid;
    int cnt;
};

#endif // AP_INFO_H
