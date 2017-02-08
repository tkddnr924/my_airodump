#ifndef AP_INFO_H
#define AP_INFO_H
#include <string>
#include <tins/tins.h>

using namespace Tins;

class AP_info
{
public:
    AP_info();

    void SetBssid(std::string bssid);       // bssid
    void SetChannel(uint8_t channel);       // channel
    void SetPwr(int pwr);                   // pwr
    void SetEncrypt(Dot11Beacon beacon);    // enc, cipher
    void SetAuth(Dot11Beacon beacon);       // auth
    void SetEssid(std::string essid);       // essid
    void SetMB(Dot11Beacon beacon);

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
