#include "ap_info.h"

AP_info::AP_info()
{
    this->cnt = 0;
}

// Set Method
void AP_info::SetBssid(const Dot11ManagementFrame& mgf)
{
    const Dot11Beacon& beacon = mgf.rfind_pdu<Dot11Beacon>();
    this->bssid = beacon.addr2().to_string();
}

void AP_info::SetChannel(const Dot11ManagementFrame& mgf)
{
    const Dot11Beacon& beacon = mgf.rfind_pdu<Dot11Beacon>();
    uint channel = beacon.ds_parameter_set();
    this->channel = channel;
}

void AP_info::SetPwr(int pwr)
{
    this->pwr = pwr;
}

void AP_info::SetEncrypt(const Dot11ManagementFrame& mgf)
{
    try
    {
        const Dot11Beacon& beacon = mgf.rfind_pdu<Dot11Beacon>();
        RSNInformation rsn = beacon.rsn_information();

        switch (rsn.pairwise_cyphers()[0]) {
        case RSNInformation::CCMP:
            this->enc = "WPA2";
            this->cipher = "CCMP";
            break;
        case RSNInformation::TKIP:
            this->enc = "WPA";
            this->cipher = "TKIP";
            break;
        case RSNInformation::WEP_40:
            this->enc = "WPA2";
            this->cipher = "WEP";
            break;
        case RSNInformation::WEP_104:
            this->enc = "WPA2";
            this->cipher = "WEP_104";
            break;
        default:
            this->cipher = "";
            break;
        }
    }
    catch(option_not_found)
    {
    }
}

void AP_info::SetAuth(const Dot11ManagementFrame& mgf)
{
    try
    {
        const Dot11Beacon& beacon = mgf.rfind_pdu<Dot11Beacon>();
        RSNInformation rsn = beacon.rsn_information();

        auto akm = rsn.akm_cyphers();

        switch (akm[0]) {
        case RSNInformation::PSK:
            this->auth = "PSK";
            break;
        case RSNInformation::PMKSA:
            this->auth = "PMKSA";
            break;
        default:
            this->auth = "";
            break;
        }

    }
    catch(option_not_found)
    {
    }
}

void AP_info::SetEssid(const Dot11ManagementFrame& mgf)
{
    const Dot11Beacon& beacon = mgf.rfind_pdu<Dot11Beacon>();
    std::string essid = beacon.ssid();
    this->essid = essid;
}

void AP_info::SetMB(const Dot11ManagementFrame& mgf)
{
    try{
        const Dot11Beacon& beacon = mgf.rfind_pdu<Dot11Beacon>();
        float sr = beacon.supported_rates().back();
        float esr = beacon.extended_supported_rates().back();
        this->mb = (sr > esr) ? std::to_string((int)sr) : std::to_string((int)esr);

        if(!beacon.capabilities().qos())
        {
            this->mb += "e";
        }
    }
    catch(option_not_found)
    {}
}

// Get Method
std::string AP_info::GetBssid()
{
    return this->bssid;
}

uint8_t AP_info::GetChannel()
{
    return this->channel;
}

int AP_info::GetPwr()
{
    return this->pwr;
}

std::string AP_info::GetEnc()
{
    return this->enc;
}

std::string AP_info::GetCipher()
{
    return this->cipher;
}

std::string AP_info::GetAuth()
{
    return this->auth;
}

std::string AP_info::GetEssid()
{
    return this->essid;
}

std::string AP_info::GetMB()
{
    return this->mb;
}

int AP_info::GetCnt()
{
    return this->cnt;
}

// Increase Count
void AP_info::IncreCnt()
{
    this->cnt++;
}
