#include "capture.h"
Capture::Capture(std::string interface)
{
    this->interface = interface;
}

void Capture::Start()
{
    SnifferConfiguration sconf;
    sconf.set_rfmon(true);
    Sniffer sniffer(this->interface, sconf);

    std::cout << "Start-----------------------------------------" << std::endl;
    sniffer.sniff_loop(make_sniffer_handler(this, &Capture::Loop));
    std::cout << "END-----------------------------------------" << std::endl;
}

bool Capture::Loop(PDU& pdu)
{
    AP_info* ap_info = new AP_info();
    try
    {
        const RadioTap& radiotap = pdu.rfind_pdu<RadioTap>();
        const Dot11Beacon& beacon = pdu.rfind_pdu<Dot11Beacon>();

        if (!beacon.from_ds() && !beacon.to_ds())
        {
            if(radiotap.present() & RadioTap::DBM_SIGNAL)
            {
                ap_info->SetPwr((int)radiotap.dbm_signal());
            }

            ap_info->SetBssid(beacon.addr2().to_string());      // setting bssid
            ap_info->SetChannel(beacon.ds_parameter_set());     // setting channel
            ap_info->SetEncrypt(beacon);                        // setting Encrypt, Cipher
            ap_info->SetAuth(beacon);                           // setting Auth
            ap_info->SetEssid(beacon.ssid());                   // setting essid
            ap_info->SetMB(beacon);                             // setting MB
        }

    }
    catch(pdu_not_found)
    {
    }

    if(!ExistAP(ap_info))
    {
        this->ap_vec.push_back(ap_info);
    }
    PrintAP();
    return true;
}

bool Capture::ExistAP(AP_info* ap)
{
    bool status = false;
    for(AP_info* a_vec : this->ap_vec)
    {
        if(a_vec->GetBssid() == ap->GetBssid())
        {
            a_vec->IncreCnt();
            a_vec->SetPwr(ap->GetPwr());
            status = true;
            break;
        }
    }
    return status;
}

void Capture::PrintAP()
{
    std::system("clear");
    std:: cout << "BSSID\t\t\t PWR\t BEACONS\t CHANNEL\t MB\t ENC\t CIPHER\t AUTH\t ESSID" << std::endl;
    for(AP_info* ap : this->ap_vec)
    {
        if(ap->GetEssid() == "")
            continue;
        std::cout << ap->GetBssid() << "\t";
        std::cout << ap->GetPwr() << "\t ";
        std::cout << ap->GetCnt() << "\t\t ";
        std::cout << (int)ap->GetChannel() << "\t\t ";
        std::cout << ap->GetMB() << "\t ";
        std::cout << ap->GetEnc() << "\t ";
        std::cout << ap->GetCipher() << "\t ";
        std::cout << ap->GetAuth() << "\t ";
        std::cout << ap->GetEssid() << std::endl;
    }
}
